/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Senal_25u.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : PWM
**     Version     : Component 02.240, Driver 01.28, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-06-12, 19:35, # CodeGen: 110
**     Abstract    :
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
**     Settings    :
**         Used output pin             : 
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       61            |  PTA1_KBI1P1_TPM2CH0_ADP1_ACMP1MINUS
**             ----------------------------------------------------
**
**         Timer name                  : TPM2 [16-bit]
**         Counter                     : TPM2CNT   [$0051]
**         Mode register               : TPM2SC    [$0050]
**         Run register                : TPM2SC    [$0050]
**         Prescaler                   : TPM2SC    [$0050]
**         Compare register            : TPM2C0V   [$0056]
**         Flip-flop register          : TPM2C0SC  [$0055]
**
**         User handling procedure     : not specified
**
**         Port name                   : PTA
**         Bit number (in port)        : 1
**         Bit mask of the port        : $0002
**         Port data register          : PTAD      [$0000]
**         Port control register       : PTADD     [$0001]
**
**         Initialization:
**              Output level           : low
**              Timer                  : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 25165824 Hz
**           Initial value of            period     pulse width
**             Xtal ticks              : 1          0
**             microseconds            : 25         13
**             seconds (real)          : 0.000024994214 0.000012516975
**
**     Contents    :
**         Enable     - byte Senal_25u_Enable(void);
**         Disable    - byte Senal_25u_Disable(void);
**         SetRatio16 - byte Senal_25u_SetRatio16(word Ratio);
**         SetDutyUS  - byte Senal_25u_SetDutyUS(word Time);
**         SetDutyMS  - byte Senal_25u_SetDutyMS(word Time);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Senal_25u.c
** @version 01.28
** @brief
**         This component implements a pulse-width modulation generator
**         that generates signal with variable duty and fixed cycle. 
*/         
/*!
**  @addtogroup Senal_25u_module Senal_25u module documentation
**  @{
*/         


/* MODULE Senal_25u. */

#include "PE_Error.h"
#include "Senal_25u.h"

#pragma MESSAGE DISABLE C5703          /* WARNING C5703: Parameter _ declared in function _ but not referenced */
#pragma MESSAGE DISABLE C2705          /* WARNING C2705: Possible loss of data */
#pragma MESSAGE DISABLE C5919          /* WARNING C5919: Conversion of floating to unsigned integral */


typedef union {
  uint16_t Value;
  struct {
    uint8_t Hi;
    uint8_t Lo;
  } BB;
} TRatioValue;

static TRatioValue ActualRatio;        /* Ratio of L-level to H-level - 16-bit unsigned value */

/* Internal method prototypes */

/*
** ===================================================================
**     Method      :  SetRatio (component PWM)
**
**     Description :
**         The method stores duty value to compare register(s) and sets 
**         necessary bits or (in List mode) call SetReg method for duty 
**         value storing.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetRatio(void);

/* End of Internal methods declarations */

/*
** ===================================================================
**     Method      :  SetRatio (component PWM)
**
**     Description :
**         The method stores duty value to compare register(s) and sets 
**         necessary bits or (in List mode) call SetReg method for duty 
**         value storing.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetRatio(void)
{
  if (ActualRatio.Value == 0xFFFFU) {  /* Duty = 100%? */
    TPM2C0V = 0xFFFFU;                 /* Store new value to the compare reg. */
  } else {
    TRatioValue Tmp1, Tmp2;
    uint16_t Result;
    Result = (uint16_t)((uint16_t)ActualRatio.BB.Hi * 0x02U); /* HI * HI */
    Tmp1.Value = (uint16_t)((uint16_t)ActualRatio.BB.Hi * 0x75U); /* HI * LO */
    Result += Tmp1.BB.Hi;
    Tmp2.Value = (uint16_t)((uint16_t)ActualRatio.BB.Lo * 0x02U); /* LO * HI */
    Result += Tmp2.BB.Hi;
    if ((Tmp2.BB.Lo += Tmp1.BB.Lo) < Tmp1.BB.Lo) {
      ++Result;                        /* carry to result */
    }
    Tmp1.Value = (uint16_t)((uint16_t)ActualRatio.BB.Lo * 0x75U); /* LO * LO */
    if ((Tmp1.BB.Hi += Tmp2.BB.Lo) < Tmp2.BB.Lo) {
      ++Result;                        /* carry to result */
    }
    if (Tmp1.BB.Hi >= 0x80U) {
      ++Result;                        /* round */
    }
    TPM2C0V = Result;
  }
}

/*
** ===================================================================
**     Method      :  Senal_25u_Enable (component PWM)
**     Description :
**         This method enables the component - it starts the signal
**         generation. Events may be generated (<DisableEvent>
**         /<EnableEvent>).
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte Senal_25u_Enable(void)
{
  /* TPM2SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM2SC, 0x08U);              /* Run the counter (set CLKSB:CLKSA) */ 
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Senal_25u_Disable (component PWM)
**     Description :
**         This method disables the component - it stops the signal
**         generation and events calling. When the timer is disabled,
**         it is possible to call <ClrValue> and <SetValue> methods.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte Senal_25u_Disable(void)
{
  /* TPM2SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM2SC, 0x00U);              /* Stop counter (CLKSB:CLKSA = 00) */ 
  /* TPM2CNTH: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=0,BIT8=0 */
  setReg8(TPM2CNTH, 0x00U);            /* Reset HW Counter */ 
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Senal_25u_SetRatio16 (component PWM)
**     Description :
**         This method sets a new duty-cycle ratio. Ratio is expressed
**         as a 16-bit unsigned integer number. 0 - FFFF value is
**         proportional to ratio 0 - 100%. The method is available
**         only if it is not selected list of predefined values in
**         <Starting pulse width> property. 
**         Note: Calculated duty depends on the timer possibilities and
**         on the selected period.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Ratio           - Ratio to set. 0 - 65535 value is
**                           proportional to ratio 0 - 100%
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte Senal_25u_SetRatio16(word Ratio)
{
  ActualRatio.Value = Ratio;           /* Store new value of the ratio */
  SetRatio();                          /* Calculate and set up new appropriate values of the compare and modulo registers */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Senal_25u_SetDutyUS (component PWM)
**     Description :
**         This method sets the new duty value of the output signal.
**         The duty is expressed in microseconds as a 16-bit
**         unsigned integer number.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Duty to set [in microseconds]
**                      (0 to 25 us in high speed mode)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte Senal_25u_SetDutyUS(word Time)
{
  dlong rtval;                         /* Result of two 32-bit numbers multiplication */
  if (Time > 0x19U) {                  /* Is the given value out of range? */
    return ERR_RANGE;                  /* If yes then error */
  }
  PE_Timer_LngMul((dword)Time, 0x0A3E0BFCUL, &rtval); /* Multiply given value and High speed CPU mode coefficient */
  if (PE_Timer_LngHi2(rtval[0], rtval[1], &ActualRatio.Value)) { /* Is the result greater or equal than 65536 ? */
    ActualRatio.Value = 0xFFFFU;       /* If yes then use maximal possible value */
  }
  SetRatio();                          /* Calculate and set up new appropriate values of the compare and modulo registers */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  Senal_25u_SetDutyMS (component PWM)
**     Description :
**         This method sets the new duty value of the output signal.
**         The duty is expressed in milliseconds as a 16-bit
**         unsigned integer number.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Time            - Duty to set [in milliseconds]
**         Note: The period is too short. The method will return
**               just the error code in high speed mode.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_MATH - Overflow during evaluation
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte Senal_25u_SetDutyMS(word Time)
{
  /* Period is too short. The method SetDutyMS will return an error code only in High speed mode. */
  return ERR_MATH;                     /* Calculation error */
}

/*
** ===================================================================
**     Method      :  Senal_25u_Init (component PWM)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void Senal_25u_Init(void)
{
  /* TPM2SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=0,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM2SC, 0x00U);              /* Disable device */ 
  /* TPM2C0SC: CH0F=0,CH0IE=0,MS0B=1,MS0A=1,ELS0B=1,ELS0A=1,??=0,??=0 */
  setReg8(TPM2C0SC, 0x3CU);            /* Set up PWM mode with output signal level low */ 
  ActualRatio.Value = 0x8035U;         /* Store initial value of the ratio */
  /* TPM2MOD: BIT15=0,BIT14=0,BIT13=0,BIT12=0,BIT11=0,BIT10=0,BIT9=1,BIT8=0,BIT7=0,BIT6=1,BIT5=1,BIT4=1,BIT3=0,BIT2=1,BIT1=0,BIT0=0 */
  setReg16(TPM2MOD, 0x0274U);          /* Set modulo register */ 
  SetRatio();                          /* Calculate and set up new values of the compare according to the selected speed CPU mode */
  /* TPM2SC: TOF=0,TOIE=0,CPWMS=0,CLKSB=0,CLKSA=1,PS2=0,PS1=0,PS0=0 */
  setReg8(TPM2SC, 0x08U);              /* Run the counter (set CLKSB:CLKSA) */ 
}

/* END Senal_25u. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
