/* ###################################################################
**     Filename    : Events.c
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
** @file Events.c
** @version 01.02
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "AD1.h"
#include "Estacion_Metereologica.h"
Word_Byte Tiempo_1;
Word_Byte Tiempo_1_c; //Comparacion (cero)
Word_Byte Tiempo_2;
Word_Byte Tiempo_2_c; //Comparacion (cero)
Word_Byte Temperatura_Amb;
Word_Byte Temperatura_Suelo;
Word_Byte Humed_Suelo;
Word_Byte Luminosidad;
word Enviado;
word Recibido;


bool Med_1 = FALSE;
bool Med_2 = FALSE;


unsigned char cCodError;

S1_TComData Pot[5] = {0x00,0x00,0x00,0x00,0xFF};
S1_TComData Temp_Amb[5] = {0x01,0x00,0x00,0x00,0xFF};
S1_TComData Temp_Suelo[5] = {0x02,0x00,0x00,0x00,0xFF};
S1_TComData Humedad_Amb[5] = {0x03,0x00,0x00,0x00,0xFF};
S1_TComData Humedad_Suelo[5] = {0x04,0x00,0x00,0x00,0xFF};
S1_TComData Luz[5] = {0x05,0x00,0x00,0x00,0xFF};
S1_TComData Tiempo_Anemometro_1[5] = {0x06,0x00,0x00,0x00,0xFF};
S1_TComData Tiempo_Anemometro_2[5] = {0x07,0x00,0x00,0x00,0xFF};



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
void  S1_OnRxChar(void)
{

	byte in_S1;
	
	
	//tiempo_OK = FALSE;
	(void)S1_RecvChar(&in_S1);
	(void)S1_ClearRxBuf();
	(void)S1_ClearTxBuf();
	(void)S2_ClearRxBuf();
	//if(tiempo_OK == TRUE) 
	
	
	switch(in_S1)
	{
	
	case 0x01://Temperatura_Ambiente
		S1_LED_PutVal(1);
		(void)S2_SendChar(0x01);	
		break;
		
		//*************************************************************
		
	case 0x02:
		tiempo_OK = TRUE;
		//(void)AD1_Measure(TRUE);
		(void)S1_ClearRxBuf();
		//cCodError = AD1_Measure(TRUE);
		//(void)AD1_MeasureChan(TRUE,0x02);
		S1_LED_PutVal(0);
		//cCodError = AD1_GetValue16(&iADC.u16);
		//cCodError = AD1_GetChanValue16(0x02,&Temperatura_Suelo.Val_Word);
		Convertir_Dato_Serial(Temperatura_Suelo.Val_Word,Temp_Suelo);
		//if(S1_SendBlock(&Temp_Suelo,5,&Enviado) == ERR_OK);
		cCodError = S1_SendBlock(Temp_Suelo,5,&Enviado);
		//tiempo_OK = FALSE;
		
		break;
		
		//*************************************************************
		
	case 0x03:
		tiempo_OK = TRUE;
		S1_LED_PutVal(0);
		(void)S2_SendChar(0x03);
		//tiempo_OK = FALSE;
		break;
		
		//*************************************************************
		
	case 0x04:
		(void)S1_ClearRxBuf();
		//cCodError = AD1_Measure(TRUE);
		//(void)AD1_MeasureChan(TRUE,0x02);
		S1_LED_PutVal(0);
		//cCodError = AD1_GetValue16(&iADC.u16);
		//cCodError = AD1_GetChanValue16(0x02,&Temperatura_Suelo.Val_Word);
		Convertir_Dato_Serial(Humed_Suelo.Val_Word,Humedad_Suelo);
		//if(S1_SendBlock(&Temp_Suelo,5,&Enviado) == ERR_OK);
		cCodError = S1_SendBlock(Humedad_Suelo,5,&Enviado);
		break;
		
		//*************************************************************
		
	case 0x05:
		tiempo_OK = TRUE;
		(void)S1_ClearRxBuf();
				//cCodError = AD1_Measure(TRUE);
				//(void)AD1_MeasureChan(TRUE,0x02);
				S1_LED_PutVal(0);
				//cCodError = AD1_GetValue16(&iADC.u16);
				//cCodError = AD1_GetChanValue16(0x02,&Temperatura_Suelo.Val_Word);
				Convertir_Dato_Serial(Luminosidad.Val_Word,Luz);
				//if(S1_SendBlock(&Temp_Suelo,5,&Enviado) == ERR_OK);
				cCodError = S1_SendBlock(Luz,5,&Enviado);
				//tiempo_OK = FALSE;
		break;
		
		//*************************************************************
		
	case 0x06://Anemometro_1
		//Med_1 = TRUE;
		//if(Med_2 == FALSE){
	//(void)Senal_25u_Disable();
		tiempo_OK = FALSE;
		(void)S1_ClearRxBuf();
		(void)S1_ClearTxBuf();
		//(void)AD1_DisableEvent();
		(void)AD1_Disable();
		(void)S1_DisableEvent();
		(void)S2_DisableEvent();
		Entrada_Anemometro_2_Disable();
		S1_LED_PutVal(1);
		Entrada_Anemometro_1_Enable();
		(void)Senal_25u_2_Disable();
		Med_1 = TRUE;
		(void)Tiempo_Reset();
		
		
		(void)Senal_25u_Enable();
		//}
		
		break;
		
	case 0x07:
		//Med_2 = TRUE;
		//if(Med_1 == FALSE){
		tiempo_OK = FALSE;
		(void)S1_ClearRxBuf();
		(void)S1_ClearTxBuf();
		//(void)AD1_DisableEvent();
		(void)AD1_Disable();
		(void)S1_DisableEvent();
		(void)S2_DisableEvent();
		Entrada_Anemometro_1_Disable();
		S2_LED_PutVal(1);
		Entrada_Anemometro_2_Enable();
		(void)Senal_25u_Disable();
		Med_2 = TRUE;
		(void)Tiempo_Reset();
		
		(void)Senal_25u_2_Enable();
		//}
		
		break;
		
  

  
	}
  
}

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
void Int_Anemometro_1(void)
{
	if(Med_1 == TRUE && Med_2 == FALSE)
	{
  /* place your Entrada_Anemometro_1 interrupt procedure body here*/
	
	/*
	 * Envío y captura de Tiempo de Señal No.1
	 */
	Entrada_Anemometro_1_Disable();
	Entrada_Anemometro_2_Disable();
	if(Tiempo_GetCounterValue(&Tiempo_1.Val_Word) == ERR_OK);
	
	/*
	//Compara si el valor obtenido es correcto, si es así, se saca de la resta
	if(Tiempo_1.Val_Word > Tiempo_1_c.Val_Word) Tiempo_1.Val_Word = Tiempo_1.Val_Word - Tiempo_1_c.Val_Word;
	else Tiempo_1.Val_Word = 0xFFFF;
	*/
	Convertir_Dato_Serial(Tiempo_1.Val_Word,Tiempo_Anemometro_1);
	(void)Senal_25u_Disable();
	//(void)AD1_EnableEvent();
	(void)AD1_Enable();
	(void)S1_EnableEvent();
	(void)S2_EnableEvent();
	//(void)S1_ClearTxBuf();
	//if(Tiempo_Anemometro_1[0] == 0x07) Tiempo_Anemometro_1[0] = 0x00;
	
	(void)S1_ClearTxBuf();
	//Tiempo_Anemometro_1[0] = 0x06;
	//Tiempo_Anemometro_2[0] = 0x06;
	if(S1_SendBlock(Tiempo_Anemometro_1,5,&Enviado) == ERR_OK);
	tiempo_OK = TRUE;
	
	//Entrada_Anemometro_2_Enable();
	/*
	Med_1 = FALSE;
	Med_2 = TRUE;
	*/
	Med_1 = FALSE;
	}
	
}

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
void  S2_OnRxChar(void)
{
	
}

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
void  S2_OnFullRxBuf(void)
{
  /* Write your code here ... */
	//Comunicacion con el ATMEGA328P
		byte in;
		//Enciende el PTC0
		S2_LED_PutVal(0);
		//Obtengo los datos del buffer de tamaño 5
		(void)S2_RecvBlock(&Temp_Amb,5,&Recibido);
		(void)S2_ClearRxBuf();
		//Envio el dato temperatura
		if(S1_SendBlock(&Temp_Amb,5,&Enviado) == ERR_OK);
		//Termino la medicion y obtencion
		Dato_0x01 = TRUE;
}

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
void Medicion_Lista_ADC(void)
{
  /* Write your code here ... */
	
	//Luminosidad
	(void)AD1_GetChanValue16(0x00,&Luminosidad.Val_Word);
	Luminosidad.Val_Word = Luminosidad.Val_Word >> 4;
	
	
	//temperatura del suelo
	(void)AD1_GetChanValue16(0x01,&Temperatura_Suelo.Val_Word);
	Temperatura_Suelo.Val_Word = Temperatura_Suelo.Val_Word >> 4;
	
	
	//Humedad del Suelo
		(void)AD1_GetChanValue16(0x02,&Humed_Suelo.Val_Word);
		Humed_Suelo.Val_Word = Humed_Suelo.Val_Word >> 4;
		
		//tiempo_OK = FALSE;
}


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
** ==============================-=====================================
*/
void Int_Anemometro_2(void)
{
  /* place your Entrada_Anemometro_2 interrupt procedure body here*/
	/* place your Entrada_Anemometro_1 interrupt procedure body here*/
		
		/*
		 * Envío y captura de Tiempo de Señal No.2
		 */
		
	if(Med_1 == FALSE && Med_2 == TRUE)
	{
		Entrada_Anemometro_2_Disable();
		Entrada_Anemometro_1_Disable();
		if(Tiempo_GetCounterValue(&Tiempo_2.Val_Word) == ERR_OK);
		
		/*
		if(Tiempo_2.Val_Word > Tiempo_2_c.Val_Word) Tiempo_2.Val_Word = Tiempo_2.Val_Word - Tiempo_2_c.Val_Word;
		else Tiempo_2.Val_Word = 0xFFFF;
		*/
		
		Convertir_Dato_Serial(Tiempo_2.Val_Word,Tiempo_Anemometro_2);
		(void)Senal_25u_2_Disable();
		//(void)AD1_EnableEvent();
		(void)AD1_Enable();
		(void)S1_EnableEvent();
		(void)S2_EnableEvent();
		//(void)S1_ClearTxBuf();
		//Tiempo_Anemometro_2[0] = 0x07;
		(void)S1_ClearTxBuf();
		//Tiempo_Anemometro_2[0] = 0x07;
		if(S1_SendBlock(Tiempo_Anemometro_2,5,&Enviado) == ERR_OK);
		//(void)S1_ClearTxBuf();
		tiempo_OK = TRUE;
		
		/*
		Med_1 = TRUE;
		Med_2 = FALSE;
		*/
		//Entrada_Anemometro_1_Enable();
		Med_2 = FALSE;
	}

}

/* END Events */

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
