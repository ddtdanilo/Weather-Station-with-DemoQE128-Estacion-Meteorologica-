/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Tiempo_2.h
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : FreeCntr
**     Version     : Component 01.118, Driver 01.13, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-06-12, 20:38, # CodeGen: 114
**     Abstract    :
**         This device "FreeCntr" implements a free running counter for
**         time measurement.
**     Settings    :
**         Timer name                  : RTC (8-bit)
**         Compare name                : RTCmod
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 4096 Hz
**           Period
**             Xtal ticks              : 1368
**             microseconds            : 41748
**             milliseconds            : 42
**             seconds (real)          : 0.041748046875
**             Hz                      : 24
**           Frequency of counting (Bus clock / prescaler)
**             Hz                      : 4096
**
**         Initialization:
**              Timer                  : Enabled
**
**         Timer registers
**              Counter                : RTCCNT    [$1831]
**              Mode                   : RTCSC     [$1830]
**              Run                    : RTCSC     [$1830]
**              Prescaler              : RTCSC     [$1830]
**              Compare                : RTCMOD    [$1832]
**
**         User handling procedure     : not specified
**     Contents    :
**         Enable          - byte Tiempo_2_Enable(void);
**         GetCounterValue - byte Tiempo_2_GetCounterValue(Tiempo_2_TTimerValue *Value);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Tiempo_2.h
** @version 01.13
** @brief
**         This device "FreeCntr" implements a free running counter for
**         time measurement.
*/         
/*!
**  @addtogroup Tiempo_2_module Tiempo_2 module documentation
**  @{
*/         

#ifndef __Tiempo_2
#define __Tiempo_2

/* MODULE Tiempo_2. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
/* Include inherited components */
#include "Cpu.h"

/* PUBLISHED CONSTANTS */
#define Tiempo_2_COUNTER_INPUT_CLOCK_HZ 0x1000UL /* Initial counter input clock frequency [Hz] */
#define Tiempo_2_PERIOD_VALUE         0xABUL /* Initial period value in ticks of the timer */
#define Tiempo_2_PRESCALER_VALUE           0x08U /* Prescaler value of the timer in high speed mode */
#define Tiempo_2_TIMER_INPUT_CLOCK         0x8000UL /* Deprecated, Initial timer input clock value [Hz] */
#define Tiempo_2_UP_COUNTER                1 /* The timer counts upwards */
#define Tiempo_2_RESET_ON_COMPARE          1 /* Property "Reset on compare" selected */
/* High speed mode constants */
#define Tiempo_2_COUNTER_INPUT_CLOCK_HZ_HIGH 0x1000UL /* Counter input clock frequency in high speed mode [Hz] */
#define Tiempo_2_PERIOD_VALUE_HIGH    0xABUL /* Period value in ticks of the timer in high speed mode */
#define Tiempo_2_PRESCALER_VALUE_HIGH      0x08U /* Prescaler value of the timer in high speed mode */
#define Tiempo_2_TIMER_INPUT_CLOCK_HIGH    0x8000UL /* Deprecated, Initial timer input clock value [Hz] */

typedef byte Tiempo_2_TTimerValue;     /* Counter or compare value, width depends on timer width */

byte Tiempo_2_Enable(void);
/*
** ===================================================================
**     Method      :  Tiempo_2_Enable (component FreeCntr)
*/
/*!
**     @brief
**         This method enables the component, i.e. timer is enabled and
**         the internal clocks are counted. The method usually also
**         reset the counter (if it is supported by HW). 
**         The method is not available if the counter is shared.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/

#define Tiempo_2_GetCounterValue(Value) ( \
  *(Value) = RTCCNT,                   /* Set the flag "events disabled" */ \
  (byte)ERR_OK                         /* Return result */ \
)
/*
** ===================================================================
**     Method      :  Tiempo_2_GetCounterValue (component FreeCntr)
*/
/*!
**     @brief
**         This method returns a content of the counter.
**     @param
**         Value           - Pointer to returned value.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
*/
/* ===================================================================*/

void Tiempo_2_Init(void);
/*
** ===================================================================
**     Method      :  Tiempo_2_Init (component FreeCntr)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


/* END Tiempo_2. */

#endif /* ifndef __Tiempo_2 */
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
