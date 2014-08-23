/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-05-12, 12:53, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "Estacion_Metereologica.h"

//bool tiempo_OK = FALSE;

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  (void)Entrada_Anemometro_1_Disable();
  (void)Entrada_Anemometro_2_Disable();
  (void)Senal_25u_SetRatio16(32767);
  (void)Senal_25u_Disable();
  //Tiempo_2_Disable();
  Senal_25u_2_Disable();
  (void)S1_ClearRxBuf();
  (void)S1_ClearTxBuf();
  
  
  for(;;)
  {
	  S1_LED_PutVal(0);
	  S2_LED_PutVal(0);
	  //tiempo_OK = FALSE;
	  if(tiempo_OK == TRUE) (void)AD1_Measure(TRUE);
  }
  
  
  
  
  
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
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
