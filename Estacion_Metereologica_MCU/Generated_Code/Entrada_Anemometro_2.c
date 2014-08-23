/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Entrada_Anemometro_2.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Component   : ExtInt
**     Version     : Component 02.105, Driver 01.24, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-06-13, 16:14, # CodeGen: 115
**     Abstract    :
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**         Interrupt name              : Vkeyboard
**         User handling procedure     : Int_Anemometro_2
**
**         Used pin                    :
**             ----------------------------------------------------
**                Number (on package)  |    Name
**             ----------------------------------------------------
**                       40            |  PTB2_KBI1P6_SPSCK1_ADP6
**             ----------------------------------------------------
**
**         Port name                   : PTB
**
**         Bit number (in port)        : 2
**         Bit mask of the port        : $0004
**
**         Signal edge/level           : falling
**         Priority                    : 
**         Pull option                 : off
**         Initial state               : Enabled
**
**
**         Port data register          : PTBD      [$0002]
**         Port control register       : PTBDD     [$0003]
**     Contents    :
**         Enable  - void Entrada_Anemometro_2_Enable(void);
**         Disable - void Entrada_Anemometro_2_Disable(void);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file Entrada_Anemometro_2.c
** @version 01.24
** @brief
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup Entrada_Anemometro_2_module Entrada_Anemometro_2 module documentation
**  @{
*/         

#include "Entrada_Anemometro_2.h"

/*Including shared modules, which are used for all project*/

#include "Events.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Entrada_Anemometro_2_Enable (component ExtInt)
**     Description :
**         Enable the component - the external events are accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Entrada_Anemometro_2_Enable(void)

**      This method is implemented as macro. See Entrada_Anemometro_2.h file.      **
*/

/*
** ===================================================================
**     Method      :  Entrada_Anemometro_2_Disable (component ExtInt)
**     Description :
**         Disable the component - the external events are not accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Entrada_Anemometro_2_Disable(void)

**      This method is implemented as macro. See Entrada_Anemometro_2.h file.      **
*/

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
