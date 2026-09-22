/*
  Lectura de sensor LM35DZ con Referencia Interna de 1.1V
  Aumenta la resolución a ~0.1 °C por escalón del ADC.
*/

const int PIN_LM35 = A0;             // Pin analógico de entrada
const unsigned long INTERVALO = 1000; // Intervalo de muestreo: 1000 ms (1 Hz)
const int NUM_MUESTRAS = 10;         // Muestras para promediar

unsigned long ultimoTiempo = 0;

void setup() {
  Serial.begin(9600);
  
  // Configura el ADC del Arduino Uno para usar la referencia interna de 1.1V
  analogReference(INTERNAL);
  
  pinMode(PIN_LM35, INPUT);
  
  // Lectura descartada inicial para permitir que el multiplexor del ADC se estabilice
  analogRead(PIN_LM35);
  delay(10);
}

void loop() {
  unsigned long tiempoActual = millis();

  if (tiempoActual - ultimoTiempo >= INTERVALO) {
    ultimoTiempo = tiempoActual;

    // Promediado de lecturas para reducir ruido
    long sumaADC = 0;
    for (int i = 0; i < NUM_MUESTRAS; i++) {
      sumaADC += analogRead(PIN_LM35);
      delay(2); // Breve pausa entre lecturas
    }
    
    float promedioADC = (float)sumaADC / NUM_MUESTRAS;

    // Cálculo con la referencia de 1.1V:
    // Temp (°C) = (ADC * 1.1 V / 1024) / 0.01 V/°C = ADC * (110.0 / 1024.0)
    float temperaturaC = (promedioADC * 110.0) / 1024.0;

    // Imprimir resultados con 1 decimal de resolución real
    Serial.print("Temperatura: ");
    Serial.print(temperaturaC, 4);
    Serial.println(" °C");
  }
}