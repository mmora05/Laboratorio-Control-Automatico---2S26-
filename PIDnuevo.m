% Script de simulación térmica - Planta de 80W y Controlador PID
clear; clc; close all;

% 1. Parámetros físicos del modelo
P_nom = 80;      
G_1 = 0.035;     
C_eq = 1265.7;   
C_p = 15.93;     
G_eq = 7.60;     

% 2. Coeficientes de la función de transferencia
A_coef = P_nom * G_1;
B_coef = C_eq * C_p;
C_coef = (C_eq * G_1) + (C_p * G_1) + (C_p * G_eq); 
D_coef = G_1 * G_eq;

% 3. Definición de la planta
s = tf('s');
G_planta = A_coef / (B_coef * s^2 + C_coef * s + D_coef);

% 4. Controlador PID diseñado para 80W (Meta: Settling Time ~ 10 min)
Kp = 0.85;
Ki = 0.0016;
Kd = 72.7;
Tf = 1; % Constante de tiempo del filtro derivativo (s)

% Definición del PID continuo con filtro derivativo
C_pid = Kp + Ki/s + (Kd*s)/(Tf*s + 1);

% 5. Sistema a lazo cerrado
H_lazo_cerrado = feedback(C_pid * G_planta, 1);

% 6. Configuración de la simulación
t = 0:1:3600; % Simulación de 60 minutos
[y_abierto, ~] = step(G_planta, t);
[y_cerrado, ~] = step(H_lazo_cerrado, t);

% 7. Figura 1: Comparativa Lazo Abierto vs Lazo Cerrado (PID)
figure('Name', 'Comparativa de Respuestas (PID)', 'Color', 'w');
plot(t, y_abierto, 'LineWidth', 1.5, 'LineStyle', '--', 'Color', [0 0.4470 0.7410]); 
hold on;
plot(t, y_cerrado, 'LineWidth', 2, 'Color', [0.8500 0.3250 0.0980]);
yline(1, 'k:', 'Referencia', 'LineWidth', 1.5, 'LabelHorizontalAlignment', 'right');
grid on;
title('Respuesta al Escalón: Lazo Abierto vs Lazo Cerrado (PID)', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Tiempo (s)', 'FontSize', 11);
ylabel('Temperatura / Magnitud Normalizada', 'FontSize', 11);
legend('Lazo Abierto (Planta Pura)', 'Lazo Cerrado (Planta + PID)', 'Location', 'best');
xlim([0 t(end)]);
hold off;

% 8. Figura 2: Solo Lazo Cerrado (PID)
figure('Name', 'Respuesta a Lazo Cerrado PID', 'Color', 'w');
plot(t, y_cerrado, 'LineWidth', 2, 'Color', [0.8500 0.3250 0.0980]);
hold on;
yline(1, 'k:', 'Referencia', 'LineWidth', 1.5, 'LabelHorizontalAlignment', 'right');
grid on;
title('Respuesta al Escalón a Lazo Cerrado (PID + Planta 80 W)', 'FontSize', 12, 'FontWeight', 'bold');
xlabel('Tiempo (s)', 'FontSize', 11);
ylabel('Temperatura Normalizada', 'FontSize', 11);
legend('Respuesta del Sistema', 'Referencia Deseada', 'Location', 'best');
xlim([0 t(end)]);
ylim([0 1.2]);
hold off;

% 9. Métricas de desempeño del lazo cerrado
info_cerrado = stepinfo(y_cerrado, t, 1);

fprintf('\nMétricas del lazo cerrado con controlador PID:\n');
fprintf('Rise Time      : %.2f s (%.2f min)\n', info_cerrado.RiseTime, info_cerrado.RiseTime/60);
fprintf('Settling Time  : %.2f s (%.2f min)\n', info_cerrado.SettlingTime, info_cerrado.SettlingTime/60);
fprintf('Overshoot      : %.2f %%\n', info_cerrado.Overshoot);