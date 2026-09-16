% =========================================================================
% Simulación en MATLAB: Lazo Abierto vs. Lazo Cerrado con Controlador PI
% =========================================================================

clear; clc; close all;

% 1. Definición de la Planta Gp(s) = 0.1316 / (166.5s + 1)
K = 0.1316;
tau = 166.5;
Gp = tf(K, [tau 1]);

% 2. Parámetros del Controlador PI (Diseñado para ts = 600 s)
ts_deseado = 600;           % Tiempo de asentamiento deseado (criterio 2%)
tau_cl = ts_deseado / 4;    % Constante de tiempo en lazo cerrado (150 s)

Kp = tau / (K * tau_cl);    % Ganancia Proporcional (~8.4347)
Ki = 1 / (K * tau_cl);      % Ganancia Integral (~0.0507)

% Controlador PI: C(s) = Kp + Ki/s = (Kp*s + Ki) / s
C = tf([Kp Ki], [1 0]);

% 3. Transferencia en Lazo Cerrado T(s) = C(s)Gp(s) / (1 + C(s)Gp(s))
T_cl = feedback(C * Gp, 1);

% 4. Tiempo de simulación
t = 0:1:1200; % 1200 segundos para observar ambos comportamientos

% 5. Gráfica de respuestas al escalón unitario
figure('Name', 'Comparativa Lazo Abierto vs Lazo Cerrado', 'Color', 'w');
plot_open  = step(Gp, t);
plot_closed = step(T_cl, t);

plot(t, plot_open, 'r--', 'LineWidth', 1.5); hold on;
plot(t, plot_closed, 'b-', 'LineWidth', 2);

% Líneas de referencia
yline(1, 'k:', 'Consigna (Setpoint = 1)', 'LineWidth', 1.2);
yline(K, 'r:', sprintf('Valor final Lazo Abierto (%.4f)', K));
xline(ts_deseado, 'g--', sprintf('ts = %d s', ts_deseado), 'LineWidth', 1.2);

grid on;
title('Respuesta al Escalón Unitario');
xlabel('Tiempo [s]');
ylabel('Amplitud');
legend('Lazo Abierto (Planta pura)', 'Lazo Cerrado (Con Controlador PI)', ...
    'Location', 'southeast');

% 6. Mostrar información detallada de la respuesta en lazo cerrado
info_cl = stepinfo(T_cl, 'SettlingTimeThreshold', 0.02);
fprintf('--- Métricas en Lazo Cerrado ---\n');
fprintf('Tiempo de asentamiento (2%%): %.2f s\n', info_cl.SettlingTime);
fprintf('Sobrepico (Overshoot): %.2f %%\n', info_cl.Overshoot);
fprintf('Error en estado estable: %.4f\n', 1 - info_cl.Peak);

pidTuner(Gp, 'PI')