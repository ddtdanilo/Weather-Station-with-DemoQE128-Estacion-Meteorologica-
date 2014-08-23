/* ###################################################################
**     Filename    : Events.h
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : Events
**     Version     : Driver 01.02
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-05-12, 12:53, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "S1.h"
#include "Senal_25u.h"
#include "Tiempo.h"
#include "Entrada_Anemometro_1.h"
#include "S2.h"
#include "S1_LED.h"
#include "S2_LED.h"
#include "AD1.h"
#include "Senal_25u_2.h"
#include "Entrada_Anemometro_2.h"
#include "Tiempo_2.h"


void S1_OnRxChar(void);
/*
** ===================================================================
**     Event       :  S1_OnRxChar (module Events)
**
**     Component   :  S1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Int_Anemometro_1(void);
/*
** ===================================================================
**     Event       :  Int_Anemometro_1 (module Events)
**
**     Component   :  Entrada_Anemometro_1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void S2_OnRxChar(void);
/*
** ===================================================================
**     Event       :  S2_OnRxChar (module Events)
**
**     Component   :  S2 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void S2_OnFullRxBuf(void);
/*
** ===================================================================
**     Event       :  S2_OnFullRxBuf (module Events)
**
**     Component   :  S2 [AsynchroSerial]
**     Description :
**         This event is called when the input buffer is full;
**         i.e. after reception of the last character 
**         that was successfully placed into input buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Medicion_Lista_ADC(void);
/*
** ===================================================================
**     Event       :  Medicion_Lista_ADC (module Events)
**
**     Component   :  AD1 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void Int_Anemometro_2(void);
/*
** ===================================================================
**     Event       :  Int_Anemometro_2 (module Events)
**
**     Component   :  Entrada_Anemometro_2 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/* END Events */
#endif /* __Events_H*/

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
