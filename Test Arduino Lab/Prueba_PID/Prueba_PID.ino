/*
  Control PID de Temperatura a 45 °C con LM35DZ
  Salida PWM en Pin 9 con escala u(t) de 0.0 (0%) a 1.0 (100%)
*/

const int PIN_LM35 = A0;             // Pin analógico del sensor LM35DZ[cite: 1]
const int PIN_PWM = 10;               // Pin digital con PWM por hardware
const int NUM_MUESTRAS = 10;         // Muestras para promediado del ADC[cite: 1]

// Configuración del Setpoint
const float SETPOINT = 45.0;         // Temperatura objetivo en °C

// Constantes PID (diseñadas para salida u(t) entre 0.0 y 1.0)[cite: 2]
const float Kp = 0.395;              // Ganancia Proporcional[cite: 2]
const float Ki = 0.000633;           // Ganancia Integral[cite: 2]
const float Kd = 24.0;               // Ganancia Derivativa[cite: 2]

// Variables del controlador PID
float integral = 0.0;
float errorPrevio = 0.0;
unsigned long tiempoPrevio = 0;

void setup() {
  Serial.begin(9600);
  
  // Referencia interna de 1.1V para aumentar precisión del LM35DZ[cite: 1]
  analogReference(INTERNAL);
  
  pinMode(PIN_LM35, INPUT);          //[cite: 1]
  pinMode(PIN_PWM, OUTPUT);          // Pin 9 configurado como salida PWM
  analogWrite(PIN_PWM, 0);
  
  // Lectura descartada inicial[cite: 1]
  analogRead(PIN_LM35);              //[cite: 1]
  delay(10);

  tiempoPrevio = millis();
}

void loop() {
  unsigned long tiempoActual = millis();
  float dt = (tiempoActual - tiempoPrevio) / 1000.0; // Tiempo en segundos

  // Ejecuta el PID cada 300 ms (0.3 s)
  if (dt >= 0.3) {
    tiempoPrevio = tiempoActual;

    // 1. Lectura de temperatura promediada[cite: 1]
    float temperaturaC = leerTemperaturaLM35();

    // 2. Cálculo del Error
    float error = SETPOINT - temperaturaC;

    // 3. Términos PID
    float P = Kp * error;

    integral += error * dt;
    float I = Ki * integral;

    float derivativa = (error - errorPrevio) / dt;
    float D = Kd * derivativa;

    // 4. Cálculo de u(t) en escala de 0.0 a 1.0
    float u = P + I + D;

    // Saturación entre 0.0 (0%) y 1.0 (100%) con Anti-Windup
    if (u > 1.0) {
      u = 1.0;
      integral -= error * dt; // Previene la saturación integral
    } else if (u < 0.0) {
      u = 0.0;
      integral -= error * dt;
    }

    errorPrevio = error;

    // 5. Conversión del ciclo de trabajo u(t) [0.0 - 1.0] a rango PWM de Arduino [0 - 255]
    int valorPWM = (int)(u * 255.0);

    // 6. Generación de la señal PWM
    analogWrite(PIN_PWM, valorPWM);

    // Monitoreo Serie
    Serial.print("Temp: ");
    Serial.print(temperaturaC, 2);
    Serial.print(" °C | Setpoint: ");
    Serial.print(SETPOINT, 1);
    Serial.print(" °C | Ciclo: ");
    Serial.print(u * 100.0, 1);
    Serial.print("% | PWM: ");
    Serial.println(valorPWM);
  }
}

// Lectura analógica del LM35DZ con referencia de 1.1V[cite: 1]
float leerTemperaturaLM35() {
  long sumaADC = 0;
  for (int i = 0; i < NUM_MUESTRAS; i++) {
    sumaADC += analogRead(PIN_LM35);  //[cite: 1]
    delay(2);                        //[cite: 1]
  }
  float promedioADC = (float)sumaADC / NUM_MUESTRAS;   //[cite: 1]
  return (promedioADC * 110.0) / 1024.0;               //[cite: 1]
}