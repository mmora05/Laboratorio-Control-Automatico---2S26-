%% Limpieza del entorno
clear; clc; close all;

%% 0. Parámetros de diseño
factor_obstruccion = 0.15;   % Factor de obstrucción del flujo [-]
N_placas = 2;                % Número de placas PTC [-]
P_placa = 80;                % Potencia nominal de una placa PTC [W]

%% 1. Parámetros del Aire y Ventilación
caudal_nominal = 42.66 / 3600;                          % Caudal nominal del ventilador [m^3/s]
caudal_volumetrico = caudal_nominal * factor_obstruccion; % [m^3/s]
densidad_aire = 1.2;         % Densidad estándar del aire [kg/m^3]
flujo_masico = caudal_volumetrico * densidad_aire;      % Flujo másico [kg/s]
Cp_aire = 1005;              % Capacidad calorífica a presión constante del aire [J/(kg*°C)]
nu_aire = 1.5e-5;            % Viscosidad cinemática del aire [m^2/s]
Pr_aire = 0.71;              % Número de Prandtl del aire [-]
k_aire = 0.026;              % Conductividad térmica del aire [W/(m*K)]

%% 2. Geometría del Ducto y Pérdidas Térmicas
longitud_ducto = 0.4;        % Longitud de la cámara/ducto [m]
diametro_ducto = 0.15;       % Diámetro del ducto [m]
Area_lateral_ducto = pi * diametro_ducto * longitud_ducto; % Área lateral [m^2]
Area_transversal = pi * diametro_ducto^2 / 4;              % Área transversal [m^2]
U = 10;                      % Coeficiente global de transferencia de calor [W/(m^2*°C)]

% Conductancia equivalente con el ambiente (G_eq = m_dot * Cp + UA)
G_eq = (flujo_masico * Cp_aire) + (U * Area_lateral_ducto); % [W/°C]

%% 3. Capacidad Térmica Equivalente de la Cavidad (C_eq)
% --- Aporte de la Carga de Café ---
masa_cafe = 0.25;             % Masa de granos de café [kg]
humedad_cafe = 0.35;         % Fracción de humedad [-]
Cp_agua = 4184;              % [J/(kg*°C)]
Cp_seco = 1200;              % [J/(kg*°C)]
Cp_cafe = (Cp_agua * humedad_cafe) + (Cp_seco * (1 - humedad_cafe)); % [J/(kg*°C)]
C_cafe = Cp_cafe * masa_cafe; % [J/°C]

% --- Aporte de Partes Metálicas (Estructura) ---
masa_aluminio = 0.15;        % Masa equivalente de aluminio [kg]
Cp_aluminio = 900;           % [J/(kg*°C)]
C_metal = Cp_aluminio * masa_aluminio; % [J/°C]

% --- Aporte del Aire Interno ---
volumen_aire = Area_transversal * longitud_ducto; % [m^3]
masa_aire = densidad_aire * volumen_aire;         % [kg]
C_aire = masa_aire * Cp_aire;                     % [J/°C]

% --- Capacidad Térmica Total Equivalente de la Cavidad ---
C_eq = C_cafe + C_metal + C_aire; % [J/°C]

%% 4. Capacidad Térmica del Actuador (Placa PTC - C_p)
grosor_actuador = 3e-3;      % [m]
largo_placa = 80e-3;         % Dimensión en la dirección del flujo [m]
ancho_placa = 30e-3;         % [m]
area_actuador = largo_placa * ancho_placa; % Área de una placa [m^2]

% Componente de aluminio del actuador
densidad_al = 2700;          % [kg/m^3]
masa_actuador_Al = densidad_al * grosor_actuador * area_actuador;
C_p_Al = Cp_aluminio * masa_actuador_Al;

% Componente cerámico del actuador (Titanato de bario)
densidad_ceramica = 5700;    % [kg/m^3]
Cp_ceramica = 350;           % [J/(kg*°C)]
masa_actuador_cer = densidad_ceramica * grosor_actuador * area_actuador;
C_p_cer = Cp_ceramica * masa_actuador_cer;

% Capacidad térmica equivalente de la placa (promedio ponderado, no escala con N_placas)
Cp = (C_p_cer / 2) + (C_p_Al / 2); % [J/°C]

%% 5. Conductancia Térmica de Convección Forzada (G_1)
% Correlación de placa plana en flujo laminar paralelo
velocidad_aire = caudal_volumetrico / Area_transversal; % [m/s]
Re_L = velocidad_aire * largo_placa / nu_aire;          % [-]
if Re_L >= 5e5
    warning('Re_L >= 5e5: la correlación laminar de placa plana no aplica.');
end
Nu_L = 0.664 * Re_L^0.5 * Pr_aire^(1/3);                % [-]
h1 = Nu_L * k_aire / largo_placa;                       % [W/(m^2*°C)]
A1 = 2 * area_actuador * N_placas;                      % Ambas caras, todas las placas [m^2]
G1 = h1 * A1;               % Conductancia placa-aire [W/°C]

%% 6. Modelo Matemático de la Planta (Funciones de Transferencia)
P_nom = N_placas * P_placa; % Potencia nominal combinada de las placas PTC [W]

% Coeficientes del denominador común para un sistema de 2do orden
den_s2 = C_eq * Cp;
den_s1 = (C_eq * G1) + (Cp * G1) + (Cp * G_eq);
den_s0 = G1 * G_eq;

% Numeradores para las entradas D(s) y T_amb(s)
num_GD = P_nom * G1;
num_Gamb = G_eq * [Cp, G1]; % G_eq * (Cp*s + G1)

% Definición de las funciones de transferencia en Laplace (s)
s = tf('s');
G_D = tf(num_GD, [den_s2, den_s1, den_s0])
G_amb = tf(num_Gamb, [den_s2, den_s1, den_s0])
dcgain(G_D)

%% 7. Análisis Interno Aire-Café (Subsistema de Dos Nodos / Reducción)
C_F = C_cafe;
C_A = C_metal + C_aire;

% --- Coeficiente de convección en el lecho (Brooker et al., 1992) ---
% h2 = A*Ca*Ga*(2*r0*Ga/(C + D*T))^B   [W/(m^2*K)] según la fuente
% Ca en kJ/(kg*K), Ga en kg/(h*m^2), T en K
diametro_grano = 7e-3;       % Diámetro equivalente del grano [m]
r0 = diametro_grano / 2;     % Radio equivalente [m]
T_aire_K = 40 + 273.15;      % Temperatura del aire [K]
Brooker_A = 0.2755; Brooker_B = -0.34; Brooker_C = 0.06175; Brooker_D = 0.000165;
Ca = Cp_aire / 1000;                        % [kJ/(kg*K)]
Ga = flujo_masico * 3600 / Area_transversal; % Flujo másico de aire [kg/(h*m^2)]
h2 = Brooker_A * Ca * Ga * ((2 * r0 * Ga) / (Brooker_C + Brooker_D * T_aire_K))^Brooker_B; % [W/(m^2*°C)]

% --- Área de transferencia del lecho ---
masa_grano = 0.15e-3;                       % Masa por grano [kg]
N_granos = masa_cafe / masa_grano;          % Número de granos [-]
A_grano = pi * diametro_grano^2;            % Área superficial por grano [m^2]
A_bed = N_granos * A_grano;                 % Área total del lecho [m^2]

G2 = h2 * A_bed; % Conductancia de convección forzada en el lecho empacado [W/°C]

% Ecuación característica del subsistema interno: lambda^2 + a*lambda + b = 0
a = (G2 / C_F) + ((G2 + G_eq) / C_A);
b = (G2 * G_eq) / (C_F * C_A);

% Raíces características (polos), ordenadas por magnitud
polos_interno = roots([1, a, b]);
taus = sort(-1 ./ real(polos_interno), 'descend');
tau_lento = taus(1);
tau_rapido = taus(2);

%fprintf('--- RESULTADOS DEL MODELADO ---\n');
%fprintf('Capacidad equivalente de la cavidad (C_eq): %.2f J/°C\n', C_eq);
%fprintf('Capacidad térmica de la placa PTC (Cp): %.2f J/°C\n', Cp);
%fprintf('Conductancia equivalente al ambiente (G_eq): %.2f W/°C\n', G_eq);
%fprintf('Constante de tiempo lenta (aprox): %.2f s\n', tau_lento);
%fprintf('Constante de tiempo rápida (aprox): %.2f s\n', tau_rapido);