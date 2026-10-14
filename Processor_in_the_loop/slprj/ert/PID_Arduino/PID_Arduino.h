/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_Arduino.h
 *
 * Code generated for Simulink model 'PID_Arduino'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Wed Oct 14 16:01:24 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef PID_Arduino_h_
#define PID_Arduino_h_
#ifndef PID_Arduino_COMMON_INCLUDES_
#define PID_Arduino_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* PID_Arduino_COMMON_INCLUDES_ */

#include "PID_Arduino_types.h"

/* Block states (default storage) for model 'PID_Arduino' */
typedef struct {
  real32_T FilterDifferentiatorTF_states;/* '<S33>/Filter Differentiator TF' */
  real32_T Integrator_DSTATE;          /* '<S40>/Integrator' */
  real32_T FilterDifferentiatorTF_tmp; /* '<S33>/Filter Differentiator TF' */
} DW_PID_Arduino_f_T;

/* Parameters (default storage) */
struct P_PID_Arduino_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S31>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S37>/Integral Gain'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S45>/Proportional Gain'
                                        */
  real32_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S33>/Filter Differentiator TF'
                               */
  real32_T PIDController_InitialConditio_j;
                              /* Mask Parameter: PIDController_InitialConditio_j
                               * Referenced by: '<S40>/Integrator'
                               */
  real32_T PIDController_LowerIntegratorSa;
                              /* Mask Parameter: PIDController_LowerIntegratorSa
                               * Referenced by: '<S40>/Integrator'
                               */
  real32_T PIDController_LowerSaturationLi;
                              /* Mask Parameter: PIDController_LowerSaturationLi
                               * Referenced by:
                               *   '<S47>/Saturation'
                               *   '<S30>/DeadZone'
                               */
  real32_T PIDController_UpperIntegratorSa;
                              /* Mask Parameter: PIDController_UpperIntegratorSa
                               * Referenced by: '<S40>/Integrator'
                               */
  real32_T PIDController_UpperSaturationLi;
                              /* Mask Parameter: PIDController_UpperSaturationLi
                               * Referenced by:
                               *   '<S47>/Saturation'
                               *   '<S30>/DeadZone'
                               */
  real_T NCopy_Value;                  /* Expression: N
                                        * Referenced by: '<S42>/N Copy'
                                        */
  real_T Constant2_Value;              /* Expression: 45
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S28>/Constant1'
                                        */
  real32_T FilterDenConstant_Value;
                                  /* Computed Parameter: FilterDenConstant_Value
                                   * Referenced by: '<S33>/Filter Den Constant'
                                   */
  real32_T FilterDifferentiatorTF_NumCoef[2];
                           /* Computed Parameter: FilterDifferentiatorTF_NumCoef
                            * Referenced by: '<S33>/Filter Differentiator TF'
                            */
  real32_T FilterCoefficient_Gain;     /* Expression: N
                                        * Referenced by: '<S43>/Filter Coefficient'
                                        */
  real32_T Integrator_gainval;         /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S40>/Integrator'
                                        */
  real32_T Clamping_zero_Value;       /* Computed Parameter: Clamping_zero_Value
                                       * Referenced by: '<S28>/Clamping_zero'
                                       */
  int8_T Constant_Value;               /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S28>/Constant'
                                        */
  int8_T Constant2_Value_c;            /* Computed Parameter: Constant2_Value_c
                                        * Referenced by: '<S28>/Constant2'
                                        */
  int8_T Constant3_Value;              /* Computed Parameter: Constant3_Value
                                        * Referenced by: '<S28>/Constant3'
                                        */
  int8_T Constant4_Value;              /* Computed Parameter: Constant4_Value
                                        * Referenced by: '<S28>/Constant4'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PID_Arduino_T {
  const char_T **errorStatus;
};

typedef struct {
  DW_PID_Arduino_f_T rtdw;
  RT_MODEL_PID_Arduino_T rtm;
} MdlrefDW_PID_Arduino_T;

/* Model reference registration function */
extern void PID_Arduino_initialize(const char_T **rt_errorStatus,
  RT_MODEL_PID_Arduino_T *const PID_Arduino_M);
extern void PID_Arduino_Init(DW_PID_Arduino_f_T *localDW);
extern void PID_ArduinoTID0(void);
extern void PID_ArduinoTID1(const real32_T *rtu_In1, real32_T *rty_Out1,
  DW_PID_Arduino_f_T *localDW);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PID_Arduino'
 * '<S1>'   : 'PID_Arduino/PID Controller'
 * '<S2>'   : 'PID_Arduino/PID Controller/Anti-windup'
 * '<S3>'   : 'PID_Arduino/PID Controller/D Gain'
 * '<S4>'   : 'PID_Arduino/PID Controller/External Derivative'
 * '<S5>'   : 'PID_Arduino/PID Controller/Filter'
 * '<S6>'   : 'PID_Arduino/PID Controller/Filter ICs'
 * '<S7>'   : 'PID_Arduino/PID Controller/I Gain'
 * '<S8>'   : 'PID_Arduino/PID Controller/Ideal P Gain'
 * '<S9>'   : 'PID_Arduino/PID Controller/Ideal P Gain Fdbk'
 * '<S10>'  : 'PID_Arduino/PID Controller/Integrator'
 * '<S11>'  : 'PID_Arduino/PID Controller/Integrator ICs'
 * '<S12>'  : 'PID_Arduino/PID Controller/N Copy'
 * '<S13>'  : 'PID_Arduino/PID Controller/N Gain'
 * '<S14>'  : 'PID_Arduino/PID Controller/P Copy'
 * '<S15>'  : 'PID_Arduino/PID Controller/Parallel P Gain'
 * '<S16>'  : 'PID_Arduino/PID Controller/Reset Signal'
 * '<S17>'  : 'PID_Arduino/PID Controller/Saturation'
 * '<S18>'  : 'PID_Arduino/PID Controller/Saturation Fdbk'
 * '<S19>'  : 'PID_Arduino/PID Controller/Sum'
 * '<S20>'  : 'PID_Arduino/PID Controller/Sum Fdbk'
 * '<S21>'  : 'PID_Arduino/PID Controller/Tracking Mode'
 * '<S22>'  : 'PID_Arduino/PID Controller/Tracking Mode Sum'
 * '<S23>'  : 'PID_Arduino/PID Controller/Tsamp - Integral'
 * '<S24>'  : 'PID_Arduino/PID Controller/Tsamp - Ngain'
 * '<S25>'  : 'PID_Arduino/PID Controller/postSat Signal'
 * '<S26>'  : 'PID_Arduino/PID Controller/preInt Signal'
 * '<S27>'  : 'PID_Arduino/PID Controller/preSat Signal'
 * '<S28>'  : 'PID_Arduino/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S29>'  : 'PID_Arduino/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S30>'  : 'PID_Arduino/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S31>'  : 'PID_Arduino/PID Controller/D Gain/Internal Parameters'
 * '<S32>'  : 'PID_Arduino/PID Controller/External Derivative/Error'
 * '<S33>'  : 'PID_Arduino/PID Controller/Filter/Disc. Backward Euler Filter'
 * '<S34>'  : 'PID_Arduino/PID Controller/Filter/Disc. Backward Euler Filter/Tsamp'
 * '<S35>'  : 'PID_Arduino/PID Controller/Filter/Disc. Backward Euler Filter/Tsamp/Internal Ts'
 * '<S36>'  : 'PID_Arduino/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S37>'  : 'PID_Arduino/PID Controller/I Gain/Internal Parameters'
 * '<S38>'  : 'PID_Arduino/PID Controller/Ideal P Gain/Passthrough'
 * '<S39>'  : 'PID_Arduino/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S40>'  : 'PID_Arduino/PID Controller/Integrator/Discrete'
 * '<S41>'  : 'PID_Arduino/PID Controller/Integrator ICs/Internal IC'
 * '<S42>'  : 'PID_Arduino/PID Controller/N Copy/Internal Parameters'
 * '<S43>'  : 'PID_Arduino/PID Controller/N Gain/Internal Parameters'
 * '<S44>'  : 'PID_Arduino/PID Controller/P Copy/Disabled'
 * '<S45>'  : 'PID_Arduino/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S46>'  : 'PID_Arduino/PID Controller/Reset Signal/Disabled'
 * '<S47>'  : 'PID_Arduino/PID Controller/Saturation/Enabled'
 * '<S48>'  : 'PID_Arduino/PID Controller/Saturation Fdbk/Disabled'
 * '<S49>'  : 'PID_Arduino/PID Controller/Sum/Sum_PID'
 * '<S50>'  : 'PID_Arduino/PID Controller/Sum Fdbk/Disabled'
 * '<S51>'  : 'PID_Arduino/PID Controller/Tracking Mode/Disabled'
 * '<S52>'  : 'PID_Arduino/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S53>'  : 'PID_Arduino/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S54>'  : 'PID_Arduino/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S55>'  : 'PID_Arduino/PID Controller/postSat Signal/Forward_Path'
 * '<S56>'  : 'PID_Arduino/PID Controller/preInt Signal/Internal PreInt'
 * '<S57>'  : 'PID_Arduino/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* PID_Arduino_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
