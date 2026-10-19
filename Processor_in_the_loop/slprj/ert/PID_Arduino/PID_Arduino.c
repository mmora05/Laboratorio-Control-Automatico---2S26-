/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PID_Arduino.c
 *
 * Code generated for Simulink model 'PID_Arduino'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Fri Oct 16 07:20:38 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PID_Arduino.h"
#include "rtwtypes.h"
#include "PID_Arduino_private.h"

P_PID_Arduino_T PID_Arduino_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S31>/Derivative Gain'
   */
  48.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S37>/Integral Gain'
   */
  0.000633,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S45>/Proportional Gain'
   */
  0.395,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S33>/Filter Differentiator TF'
   */
  0.0F,

  /* Mask Parameter: PIDController_InitialConditio_j
   * Referenced by: '<S40>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController_LowerIntegratorSa
   * Referenced by: '<S40>/Integrator'
   */
  0.0F,

  /* Mask Parameter: PIDController_LowerSaturationLi
   * Referenced by:
   *   '<S47>/Saturation'
   *   '<S30>/DeadZone'
   */
  0.0F,

  /* Mask Parameter: PIDController_UpperIntegratorSa
   * Referenced by: '<S40>/Integrator'
   */
  1.0F,

  /* Mask Parameter: PIDController_UpperSaturationLi
   * Referenced by:
   *   '<S47>/Saturation'
   *   '<S30>/DeadZone'
   */
  1.0F,

  /* Expression: N
   * Referenced by: '<S42>/N Copy'
   */
  100.0,

  /* Expression: 45
   * Referenced by: '<Root>/Constant2'
   */
  45.0,

  /* Computed Parameter: Constant1_Value
   * Referenced by: '<S28>/Constant1'
   */
  0.0F,

  /* Computed Parameter: FilterDenConstant_Value
   * Referenced by: '<S33>/Filter Den Constant'
   */
  1.0F,

  /* Computed Parameter: FilterDifferentiatorTF_NumCoef
   * Referenced by: '<S33>/Filter Differentiator TF'
   */
  { 1.0F, -1.0F },

  /* Expression: N
   * Referenced by: '<S43>/Filter Coefficient'
   */
  100.0F,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S40>/Integrator'
   */
  1.0F,

  /* Computed Parameter: Clamping_zero_Value
   * Referenced by: '<S28>/Clamping_zero'
   */
  0.0F,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S28>/Constant'
   */
  1,

  /* Computed Parameter: Constant2_Value_c
   * Referenced by: '<S28>/Constant2'
   */
  -1,

  /* Computed Parameter: Constant3_Value
   * Referenced by: '<S28>/Constant3'
   */
  1,

  /* Computed Parameter: Constant4_Value
   * Referenced by: '<S28>/Constant4'
   */
  -1
};

/* System initialize for referenced model: 'PID_Arduino' */
void PID_Arduino_Init(DW_PID_Arduino_f_T *localDW)
{
  /* InitializeConditions for DiscreteTransferFcn: '<S33>/Filter Differentiator TF' */
  localDW->FilterDifferentiatorTF_states =
    PID_Arduino_P.PIDController_InitialConditionF;

  /* InitializeConditions for DiscreteIntegrator: '<S40>/Integrator' */
  localDW->Integrator_DSTATE = PID_Arduino_P.PIDController_InitialConditio_j;
}

/* Output and update for referenced model: 'PID_Arduino' */
void PID_ArduinoTID0(void)
{
}

/* Output and update for referenced model: 'PID_Arduino' */
void PID_ArduinoTID1(const real32_T *rtu_In1, real32_T *rty_Out1,
                     DW_PID_Arduino_f_T *localDW)
{
  real_T rtb_Sum4;
  real32_T rtb_IntegralGain;
  real32_T rtb_Sum;
  int8_T tmp;
  int8_T tmp_0;

  /* Math: '<S33>/Reciprocal' incorporates:
   *  Constant: '<S33>/Filter Den Constant'
   *  Constant: '<S42>/N Copy'
   *  DataTypeConversion: '<S33>/Passthrough for tuning'
   *  Sum: '<S33>/SumDen'
   *
   * About '<S33>/Reciprocal':
   *  Operator: reciprocal
   */
  rtb_Sum = 1.0F / (PID_Arduino_P.FilterDenConstant_Value + (real32_T)
                    PID_Arduino_P.NCopy_Value);

  /* Sum: '<Root>/Sum4' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  rtb_Sum4 = PID_Arduino_P.Constant2_Value - *rtu_In1;

  /* DiscreteTransferFcn: '<S33>/Filter Differentiator TF' incorporates:
   *  Gain: '<S31>/Derivative Gain'
   *  UnaryMinus: '<S33>/Unary Minus'
   */
  localDW->FilterDifferentiatorTF_tmp = (real32_T)(PID_Arduino_P.PIDController_D
    * rtb_Sum4) - -rtb_Sum * localDW->FilterDifferentiatorTF_states;

  /* Sum: '<S49>/Sum' incorporates:
   *  DiscreteIntegrator: '<S40>/Integrator'
   *  DiscreteTransferFcn: '<S33>/Filter Differentiator TF'
   *  Gain: '<S43>/Filter Coefficient'
   *  Gain: '<S45>/Proportional Gain'
   *  Product: '<S33>/DenCoefOut'
   */
  rtb_Sum = (PID_Arduino_P.FilterDifferentiatorTF_NumCoef[0] *
             localDW->FilterDifferentiatorTF_tmp +
             PID_Arduino_P.FilterDifferentiatorTF_NumCoef[1L] *
             localDW->FilterDifferentiatorTF_states) * rtb_Sum *
    PID_Arduino_P.FilterCoefficient_Gain + ((real32_T)
    (PID_Arduino_P.PIDController_P * rtb_Sum4) + localDW->Integrator_DSTATE);

  /* DeadZone: '<S30>/DeadZone' incorporates:
   *  Saturate: '<S47>/Saturation'
   */
  if (rtb_Sum > PID_Arduino_P.PIDController_UpperSaturationLi) {
    rtb_IntegralGain = rtb_Sum - PID_Arduino_P.PIDController_UpperSaturationLi;
    *rty_Out1 = PID_Arduino_P.PIDController_UpperSaturationLi;
  } else {
    if (rtb_Sum >= PID_Arduino_P.PIDController_LowerSaturationLi) {
      rtb_IntegralGain = 0.0F;
    } else {
      rtb_IntegralGain = rtb_Sum - PID_Arduino_P.PIDController_LowerSaturationLi;
    }

    if (rtb_Sum < PID_Arduino_P.PIDController_LowerSaturationLi) {
      *rty_Out1 = PID_Arduino_P.PIDController_LowerSaturationLi;
    } else {
      *rty_Out1 = rtb_Sum;
    }
  }

  /* End of DeadZone: '<S30>/DeadZone' */

  /* Gain: '<S37>/Integral Gain' */
  rtb_Sum = (real32_T)(PID_Arduino_P.PIDController_I * rtb_Sum4);

  /* Update for DiscreteTransferFcn: '<S33>/Filter Differentiator TF' */
  localDW->FilterDifferentiatorTF_states = localDW->FilterDifferentiatorTF_tmp;

  /* Switch: '<S28>/Switch1' incorporates:
   *  Constant: '<S28>/Clamping_zero'
   *  Constant: '<S28>/Constant'
   *  Constant: '<S28>/Constant2'
   *  RelationalOperator: '<S28>/fix for DT propagation issue'
   */
  if (rtb_IntegralGain > PID_Arduino_P.Clamping_zero_Value) {
    tmp = PID_Arduino_P.Constant_Value;
  } else {
    tmp = PID_Arduino_P.Constant2_Value_c;
  }

  /* Switch: '<S28>/Switch2' incorporates:
   *  Constant: '<S28>/Clamping_zero'
   *  Constant: '<S28>/Constant3'
   *  Constant: '<S28>/Constant4'
   *  RelationalOperator: '<S28>/fix for DT propagation issue1'
   */
  if (rtb_Sum > PID_Arduino_P.Clamping_zero_Value) {
    tmp_0 = PID_Arduino_P.Constant3_Value;
  } else {
    tmp_0 = PID_Arduino_P.Constant4_Value;
  }

  /* Switch: '<S28>/Switch' incorporates:
   *  Constant: '<S28>/Clamping_zero'
   *  Constant: '<S28>/Constant1'
   *  Logic: '<S28>/AND3'
   *  RelationalOperator: '<S28>/Equal1'
   *  RelationalOperator: '<S28>/Relational Operator'
   *  Switch: '<S28>/Switch1'
   *  Switch: '<S28>/Switch2'
   */
  if ((PID_Arduino_P.Clamping_zero_Value != rtb_IntegralGain) && (tmp == tmp_0))
  {
    rtb_Sum = PID_Arduino_P.Constant1_Value;
  }

  /* Update for DiscreteIntegrator: '<S40>/Integrator' incorporates:
   *  Switch: '<S28>/Switch'
   */
  localDW->Integrator_DSTATE += PID_Arduino_P.Integrator_gainval * rtb_Sum;
  if (localDW->Integrator_DSTATE > PID_Arduino_P.PIDController_UpperIntegratorSa)
  {
    localDW->Integrator_DSTATE = PID_Arduino_P.PIDController_UpperIntegratorSa;
  } else if (localDW->Integrator_DSTATE <
             PID_Arduino_P.PIDController_LowerIntegratorSa) {
    localDW->Integrator_DSTATE = PID_Arduino_P.PIDController_LowerIntegratorSa;
  }

  /* End of Update for DiscreteIntegrator: '<S40>/Integrator' */
}

/* Model initialize function */
void PID_Arduino_initialize(const char_T **rt_errorStatus,
  RT_MODEL_PID_Arduino_T *const PID_Arduino_M)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatusPointer(PID_Arduino_M, rt_errorStatus);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
