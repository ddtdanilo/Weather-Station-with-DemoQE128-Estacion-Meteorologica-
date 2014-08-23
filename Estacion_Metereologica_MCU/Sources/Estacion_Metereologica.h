/*
 * Estacion_Metereologica.h
 *
 *  Created on: May 12, 2014
 *      Author: Danilo
 */

#ifndef ESTACION_METEREOLOGICA_H_
#define ESTACION_METEREOLOGICA_H_


#include "Cpu.h"
#include "Events.h"
#include "S1.h"
#include "Senal_25u.h"
#include "Tiempo.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"



//Variables
typedef union{
	byte Val_Byte[2];
	word Val_Word;
}Word_Byte;

extern Word_Byte Tiempo_1;
extern Word_Byte Tiempo_2;

extern bool Dato_0x01;
extern bool Dato_0x03;
extern bool Dato_0x06;
extern bool Dato_0x07;

extern S1_TComData Pot[5];
extern S1_TComData Temp_Amb[5];
extern S1_TComData Temp_Suelo[5];
extern S1_TComData Humedad_Amb[5];
extern S1_TComData Humedad_Suelo[5];
extern S1_TComData Luz[5];
extern S1_TComData Tiempo_Anemometro_1[5];
extern S1_TComData Tiempo_Anemometro_2[5];

extern bool tiempo_OK;
extern bool Med_1_OK;
extern bool Med_2_OK;

//FUNCIONES


//Procede a enviar la señal
//bool Enviar_Senal();

//Convierte al formato del protocolo de comunicaciones.
//word Dato: Dato a convertir.
//byte *data_salida Apuntador a un arreglo de bytes de tamaño TAMANO
void Convertir_Dato_Serial(word Dato,byte data_salida[]);

//Devuelve el byte de informacion, *Dato es la variable que va a contener la informacion y data_entrada es el arreglo
//recibido por serial.
byte Convertir_Serial_Dato(word *Dato, byte data_entrada[]);

//Manda a medir en el MCU esclavo la temperatura
void get_temp();

//PROTOCOLO DE COMUNICACIONES









#endif /* ESTACION_METEREOLOGICA_H_ */
