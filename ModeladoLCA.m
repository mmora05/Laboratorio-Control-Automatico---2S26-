%% Limpieza del entorno
clear; clc; close all;

%% 1. Parámetros del Aire y Ventilación
% Caudal volumétrico del ventilador axial (convertido de m^3/h a m^3/s)
factor_obstruccion=0.4;
caudal_volumetrico = 42.66/ 3600*factor_obstruccion;                                          %%modificable                              
densidad_aire = 1.2; % Densidad estándar del aire [kg/m^3]
flujo_masico = caudal_volumetrico * densidad_aire; % Flujo másico [kg/s]
Cp_aire = 1005; % Capacidad calorífica a presión constante del aire [J/(kg*°C)]

%% 2. Geometría del Ducto y Pérdidas Térmicas
longitud_ducto = 0.4; % Longitud de la cámara/ducto [m]                     %%modificable
diametro_ducto = 0.15; % Diámetro del ducto [m]                             %%modificable
% Área superficial lateral del ducto cilíndrico (A = pi * d * L) [m^2]
Area_ducto = pi * diametro_ducto * longitud_ducto; 
U = 10; % Coeficiente global de transferencia de calor [W/(m^2*°C)]         %%revisar/justificar

%% 3. Capacidad Térmica Equivalente (Inercia del Sistema)
% --- Aporte de la Carga de Café ---
masa_cafe = 0.5; % Masa de granos de café [kg]                              %%modificable
% Estimación del Cp ponderado (Fracción húmeda * Cp_agua + Fracción seca * Cp_seca)
Cp_cafe = (4184 * 0.35) + (1200 * 0.65);                                    %%revisar/justificar
Cm_cafe = Cp_cafe * masa_cafe;

% --- Aporte de Partes Metálicas (Resistencia PTC y Estructura) ---
masa_aluminio = 0.15; % Masa equivalente de aluminio [kg]                   %%revisar/justificar
Cp_aluminio = 900; % Capacidad calorífica del aluminio [J/(kg*°C)]
Cm_metal = Cp_aluminio * masa_aluminio;

% --- Aporte del Aire Interno ---
volumen_aire = pi * (diametro_ducto / 2)^2 * longitud_ducto; % [m^3]
masa_aire = densidad_aire * volumen_aire; % [kg]
Cm_aire = Cp_aire * masa_aire;

% --- Capacidad Térmica Total Equivalente (Cm_equivalente = m * Cp) ---
Cm_equivalente = Cm_aire + Cm_metal + Cm_cafe;

%% 4. Cálculo de Parámetros de la Planta (Tau y K)
% Conductancia equivalente total (Evacuación por aire forzado + Pérdidas al ambiente) [W/°C]
G_equiv = (flujo_masico * Cp_aire) + (U * Area_ducto);

% Constante de tiempo térmica del sistema (tau = C_eq / G_equiv) [segundos]
tau = Cm_equivalente / G_equiv;

% Ganancia estática del sistema (K = 1 / G_equiv) [°C/W]
% (Nota: Se corrige la relación dimensional para que K represente el incremento de T por vatio)
K = 1 / G_equiv; 

%% 5. Resultados en Consola
fprintf('--- Resultados del Modelo Térmico ---\n');
fprintf('Constante de tiempo (tau): %.2f segundos (%.2f minutos)\n', tau, tau/60);
fprintf('Ganancia estática (K): %.4f °C/W\n', K);

