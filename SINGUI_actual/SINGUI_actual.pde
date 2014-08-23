 //Inicializaciones Twitter
import twitter4j.util.*;
import twitter4j.*;
import twitter4j.management.*;
import twitter4j.api.*;
import twitter4j.conf.*;
import twitter4j.json.*;
import twitter4j.auth.*;

//Import server
import processing.net.*;

//  Libreria G4P y serial 
import g4p_controls.*;
import processing.serial.*;

//Parámetros ThingSpeak
String APIKEY = "PAHG7X76ECJT8FQD";  
String FIELD;
String f1 = "field1";
String f2 = "field2";
String f3 = "field3";
String f4 = "field4";
String f5 = "field5";
String f6 = "field6";
String f7 = "field7";



//Inicializaciones - parámetro de twitter
static String OAuthConsumerKey = "VEdUfZHbomaTmAlra0sicHely";
static String OAuthConsumerSecret = "vJyKVdVDDmBfJjvWcorKkyc2DPlA76nhfLSrXIXwADdJTP9ZQM";
static String AccessToken = "2429758394-E8St09EVu8nVnzOOqL48tQ3YunbvtgGlMutVMHR";
static String AccessTokenSecret = "FSTysWUlk6quNGlVbXmVHXv8kWCBE4rgmasOCFo4lYyRK";

String myTimeline;
java.util.List statuses = null;
User[] friends;
Twitter twitter = new TwitterFactory().getInstance();
RequestToken requestToken;
String[] theSearchTweets = new String[11];



//Inicializaciones tiempo
int segundo;
int minuto;
int hora;
int dia;
int mes;
int year;


/*
        Interfaz Serial de Prueba
        
        El siguiente programa pretende funcion como una interfaz
        entre el MCU HCS08 de Freescale y la PC mediante puerto
        serial. El protocolo utilizado es el descrito a continuación:
        
        ** -> byte
        
        |**|**|**|**|0xFF|
          0  1  2  3   4
          
          Byte 0: Indica el tipo de dato enviado (Sensor).
          Byte 1: Indica DATA1, los bits más significativos de la medida.
          Byte 2: Indica DATA2, los bits menos significativos de la medida.
          Byte 3: Indica si en DATA1 o en DATA2 hubo 0xFF. Si fue en DATA1,
          envía 0x01, si fué en DATA2, envía 0x02, si fue en DATA1 y DATA2,
          envía 0x03. Caso contrario envía 0x00 (No hay 0xFF en la medida).
          Byte 4: Indica el fin de la trama enviada con 0xFF.
          
          
          Autores:
                  Danilo Díaz T.
                  Irene Michelle López C.
                  
                  
*/



/*

      Parámetros de Configuración
      
*/


String Puerto_DEMOQE;
int Baudios;
byte DISP = 0x00;
byte DATA1 = 0x01;
byte DATA2 = 0x02;
byte CONTROL_IN = 0x03;
byte CONTROL_OUT = 0x04;


/*

      Variables del Puerto Serial
      
*/

Serial DEMOQE;  // DEMOQE es un objeto de clase Serial

int SerialON = 0;
int Serialnum;
byte buff_size = 5;
byte[] inBuffer = new byte[5];
long[] inBuffer_long = new long[5];
byte[] DirV_serial = {(byte)0x07,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};
byte[] HumS_serial = {(byte)0x04,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};
byte[] HumA_serial = {(byte)0x03,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};
byte[] TempS_serial = {(byte)0x02,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};
byte[] TempA_serial = {(byte)0x01,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};
byte[] Luz_serial = {(byte)0x05,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};
byte[] VelV_serial = {(byte)0x06,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0xff};

byte[] Solicitud = {(byte)0x08,(byte)0x08,(byte)0x08,(byte)0x08,(byte)0x08};   //Solicitud de dato al grupo 2


//byte[] DirV_serial = new byte[]{0x07,0x00,0x00,0x00,0x00};
/*byte[] HumS_serial = new byte[]{(byte)0x04,(byte)0x00,(byte)0x00,(byte)0x00,(byte)0x00};
byte[] HumA_serial = new byte[]{0x03,0x00,0x00,0x00,0x00};
byte[] TempS_serial = new byte[]{0x02,0x00,0x00,0x00,0x00};
byte[] TempA_serial = new byte[]{0x01,0x00,0x00,0x00,0x00};
byte[] Luz_serial = new byte[]{0x05,0x00,0x00,0x00,0x00};
byte[] VelV_serial = new byte[]{0x06,0x00,0x00,0x00,0x00};
/*

Datos de Entrada y dispositivos

*/

long DATO_IN = 0x00000000;

long Pot_00 = 0x00;
long Temp_Amb_01 = 0x00;
float Temp_Suelo_02 = 0x00;
float Tem_Suelo_02 = 0x00;
long Humedad_Amb_03 = 0x00;
float Humedad_Suelo_04 = 0x00;
long Luz_05 = 0x00;
long Luzf_05 = 0x00;
float Vel_Viento_06 = 0x00;
float Dir_Viento_07 = 0x00;

float Viento_06 = 0x00;
float Viento_061 = 0x00;
float Viento_062 = 0x00;
float Viento_063 = 0x00;
float Viento_064 = 0x00;
float Viento_065 = 0x00;
float Viento_066 = 0x00;
float Viento_067 = 0x00;
float Viento_068 = 0x00;
float Viento_069 = 0x00;
float Viento_0610= 0x00;
int V06=0;

float Viento_07 = 0x00;
float Viento_071 = 0x00;
float Viento_072 = 0x00;
float Viento_073 = 0x00;
float Viento_074 = 0x00;
float Viento_075 = 0x00;
float Viento_076 = 0x00;
float Viento_077 = 0x00;
float Viento_078 = 0x00;
float Viento_079 = 0x00;
float Viento_0710= 0x00;
int V07=0;

String Humedad_suelo;

float Vel_Viento_ts = 0;
float Dir_Viento_ts = 0;

float Flecha_Dir = 0;


float temp=0x00;
long t2=0x01;


//CONSTANTES DE VIENTO. FLOTANTES

float distancia_06 = 32.5*0.01; //32 cm
float distancia_07 = 31*0.01; //32 cm
float medida_06_ant = 0;
float medida_07_ant = 0;




//Contadores
Timer timer;
Timer timerts;
/*Timer timer10s;
Timer timer30s;
Timer timer1m;
Timer timer5m;
Timer timer10m;
Timer timer30m;*/
//Cambio de 10 seg a 1 seg... y de 30 seg a 10
int op1=1;
int op2=10;
int op3=60;
int op4=300;
int op5=600;
int op6=1800;




//Servidor
Server s;
Client c;
String input;
int data[];
byte[] byteBuffer = new byte[5];
byte[] servBuffer = new byte[5];


//Banderas
boolean ton=false;
boolean refall=false;
boolean serialON=false;
//boolean primeramed=true;
boolean primeramed=false; //BORRAR ESTO!!!!! EL BUENO ES EL DE ARRIBA, ES UNA PRUEBA!!!!!!!!!
boolean tweet=false;
boolean first=true;
boolean waitserv=false;

boolean Vel=false;
boolean Dir=false;


public void setup(){
  println(Serial.list());
  connectTwitter();
  s = new Server(this, 12345);
   timerts = new Timer(16); 
  
  /*timer10s = new Timer(10);   //Tiempo en segundos
  timer30s = new Timer(30);   //Tiempo en segundos
  timer1m = new Timer(60); 
  timer5m = new Timer(300);
  timer10m = new Timer(600);
  timer30m = new Timer(1800);*/
  
  //Puerto_DEMOQE = Serial.list()[1];
  //Baudios = 19200;
  //DEMOQE = new Serial(this,Puerto_DEMOQE,Baudios);
  size(900, 620, JAVA2D);
  createGUI();
  customGUI();
  // Place your setup code here
 // PImage fondo;
  //size(900, 600);
 // fondo = loadImage("FondoNeg.jpg");
 
 
}



public void draw(){
  
  PImage img;
  img = loadImage("FondoNeg.jpg");
  background(img);
  //background(390);
   //hola="holi"; 
   //hola="meow";
   //println(hola);
   //println("ehm");
  //image(fondo, 0, 0); 
  
  /*c = s.available();
  if (c != null) {
    int byteCount = c.readBytes(byteBuffer); 
    if (byteCount > 0 ) {
      // Convert the byte array to a String
      String myString = new String(byteBuffer);
      // Show it text area
      println(myString); 
    } 
  
  }*/
  
  

  if (serialON && ton && timer.isFinished()) {  
    println("timer event occured " + System.currentTimeMillis()%10000000 );
    DEMOQE.write(0x04);
    refall=true;
    
    
    c = s.available();
  if (c != null) {
    
    int byteCount = c.readBytes(byteBuffer);
    if (byteCount > 0 ) {
      println(str(byteBuffer));
      
       if(byteBuffer[0]==0x01){   s.write(TempA_serial); } 
       else if(byteBuffer[0]==0x02){  s.write(TempS_serial);}
       else if(byteBuffer[0]==0x03){ s.write(HumA_serial);}
       else if(byteBuffer[0]==0x04){  s.write(HumS_serial);}
       else if(byteBuffer[0]==0x05){  s.write(Luz_serial);}
       else if(byteBuffer[0]==0x06){ s.write(VelV_serial);}
       else if(byteBuffer[0]==0x07){ s.write(DirV_serial);}
      
      else{ print("El dato recibido del grupo 2 fue:");println(str(byteBuffer)); waitserv=false;}
    }
  }
    
   //s.write("miau");
   /*s.write(TempA_serial);
   s.write(TempS_serial);
   s.write(HumA_serial);
   s.write(HumS_serial);
   s.write(Luz_serial);
   s.write(VelV_serial);
   s.write(DirV_serial);*/
   
   println(str(TempA_serial));
   println(str(TempS_serial));
   println(str(HumA_serial));
   println(str(HumS_serial));
   println(str(Luz_serial));
   println(str(VelV_serial));
   println(str(DirV_serial));
   

    timer.start();
  }
  
  
 if (serialON && ton && timerts.isFinished()) {
   /*FIELD=f1;
   sendNumber(Temp_Amb_01);
   FIELD=f2;
   sendNumber(Humedad_Amb_03);
   FIELD=f3;
   sendNumber(Luzf_05);
   FIELD=f4;
   sendNumber(Tem_Suelo_02);
  // FIELD=f5;
  // sendNumber(Tem_Suelo_02);
   FIELD=f6;
   sendNumber(Vel_Viento_06_f)*/
   
      if(!primeramed && tweet){  
      segundo=second();  
      minuto=minute();
      hora=hour();
      dia=day();
      mes=month();
      year=year();  
      sendTweet("Temperatura del Ambiente: "+ str(Temp_Amb_01) + "°C   |   " + "Humedad del Ambiente: "+ str(Humedad_Amb_03)+"%  |  " + "Luminosidad: " + str(Luzf_05)+ "%  " + "   [" + hora + ":"+ minuto + ":" + segundo + " , " + dia + "/" + mes + "/" + year+ "]   (1/3)");
      sendTweet("Velocidad del viento: "+ String.format("%.2f",Vel_Viento_06) + "m/s   |  " + "Dirección del viento: "+ String.format("%.2f",Dir_Viento_07) + "°    " + "  [" + hora + ":"+ minuto + ":" + segundo + " , " + dia + "/" + mes + "/" + year+ "]   (2/3)");
      sendTweet("Temperatura del Suelo: " + String.format("%.2f", Tem_Suelo_02)+ "°C   |   " + "Humedad del Suelo: "+ Humedad_suelo +"   " + "  [" + hora + ":"+ minuto + ":" + segundo + " , " + dia + "/" + mes + "/" + year+ "]   (3/3)");
    }
   
   
   s.write(Solicitud);
   waitserv=true;
   sendNumber(Temp_Amb_01, Humedad_Amb_03,Luzf_05,Tem_Suelo_02,Vel_Viento_ts,Dir_Viento_ts);
   print("ThingSpeak");
   timerts.start();
}


  strokeWeight(2);
  stroke(255,0,0);
  //drawArrow(50,50,(int)Vel_Viento_06 + 20,Flecha_Dir);
  drawArrow(50,320,(int)Vel_Viento_06 + 20,-Flecha_Dir);

}


void serialEvent(Serial p) {
  
    println("Evento");
    DEMOQE.readBytes(inBuffer);  
 //   inBuffer = DEMOQE.readBytes();
   

    // Revisión del dato de entrada
    for(byte k = 0 ; k<buff_size-1 ; k++)
    {
      //Se convierten los datos a positivos
      inBuffer_long[k] = inBuffer[k] & 0xFFFFFFFF;
      servBuffer[k]=inBuffer[k];
    }
     //inBuffer_long[DATA1] = 0xFF;
     //inBuffer_long[DATA2] = 0xFF;
      //Verifica si existieron 0xFF
      println("CONTROL: " + inBuffer[CONTROL_IN]);
      switch(inBuffer[CONTROL_IN])
       {
          case 0x00:          
            DATO_IN = unir_dato(inBuffer_long[DATA1],inBuffer_long[DATA2]);
            break;
            
          case 0x01:
            DATO_IN = unir_dato(0x000000FF,inBuffer_long[DATA2]);
            println("DATA: " + inBuffer_long[DATA2]);
            break;
            
          case 0x02:
            DATO_IN = unir_dato(inBuffer_long[DATA1],0x000000FF);
            break;

          case 0x03:
            DATO_IN = unir_dato(0x000000FF,0x000000FF);
            break;
            
          default:       
             println("Error! el dato se sale de los parámetros");
             break;                       
            
       }
                 
     
     
 //Switch que define de qué dispositivo viene el dato
      switch(inBuffer[DISP])
       {
          /*case 0x00://Potenciometro
            Pot_00 = DATO_IN;
          // textfield1.setText(str(Pot_00));
            break;*/
            
          case 0x01: // 
          
            for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //TempA_serial[k] = inBuffer[k];
               TempA_serial[k] = servBuffer[k];
            }
            
            Temp_Amb_01 = DATO_IN - 3;
            tempA.setText(Temp_Amb_01 + " °C");
            if(refall) DEMOQE.write(0x03);
            //hola="Dato 1";
            break;
            
          case 0x02:                                     //Número de prueba 04b0, da 1200 en decimal y equivale a 37.89°C
          
            for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //TempS_serial[k] = inBuffer[k];
               TempS_serial[k] = servBuffer[k];
            }
            Temp_Suelo_02 = DATO_IN;                    
            Tem_Suelo_02 = ((Temp_Suelo_02*3/4096)-0.5)/0.01;
            tempS.setText(String.format("%.2f", Tem_Suelo_02)+ " °C");
            if(refall) DEMOQE.write(0x01);
            break;

          case 0x03:
          
            for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //HumA_serial[k] = inBuffer[k];
               HumA_serial[k] = servBuffer[k];
            }
            
            Humedad_Amb_03 = DATO_IN;
            humedadA.setText(Humedad_Amb_03 + "%");
            if(refall) DEMOQE.write(0x05);
            break;
            
          case 0x04:
          
            for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //HumS_serial[k] = inBuffer[k];
               HumS_serial[k] = servBuffer[k];
            }    
            
            Humedad_Suelo_04 = DATO_IN;
          //  Humedad_suelo = "Demasiado humedo";
            //Humedad_suelo = "Humedo";
            
            if(Tem_Suelo_02 < 19 && Tem_Suelo_02 > -40){
            float vo=  Humedad_Suelo_04*3/4096; 
            float Rs= 992*(3-vo)/vo;
            Rs= -500*(19-Tem_Suelo_02) + Rs;
            vo= 992*3 / (Rs + 992);
            Humedad_Suelo_04 = vo*4096/3;        
            }            
            
            else if(Tem_Suelo_02 > 31 && Tem_Suelo_02 < 125){
            float vo=  Humedad_Suelo_04*3/4096; 
            float Rs= 992*(3-vo)/vo;
            Rs= -58*(31-Tem_Suelo_02) + Rs;
            vo= 992*3 / (Rs + 992);
            Humedad_Suelo_04 = vo*4096/3;     
            
            } 
            
            if(Humedad_Suelo_04 < 1150)  Humedad_suelo = "            Baja";
            else if (Humedad_Suelo_04 >= 1150  && Humedad_Suelo_04 <= 2304)  Humedad_suelo = "          Óptima";
            else if (Humedad_Suelo_04 > 2304)  Humedad_suelo = "        Excesiva";
           
            //Humedad_suelo = "Seco";
            //Humedad_suelo = "Demasiado seco";
            humedadS.setText(Humedad_suelo);
            if(refall) DEMOQE.write(0x02);            
            break;
            
          case 0x05:
          
            for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //Luz_serial[k] = inBuffer[k];
               Luz_serial[k] = servBuffer[k];
            } 
            
            Luz_05 = DATO_IN;
            Luzf_05 = Luz_05*100/4096;
            Luz.setText(Luzf_05 + "%");
            if(refall) DEMOQE.write(0x06);
            break;
            
            
          case 0x06:
          
              V06++;
          
            /*for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //VelV_serial[k] = inBuffer[k];
               VelV_serial[k] = servBuffer[k];
            }       */
            
            if(V06==1){
            Viento_061 = DATO_IN*0.635783;          
            DEMOQE.write(0x06);            
          }
            
            else if (V06==2){
            Viento_062 = DATO_IN*0.635783;
          //  if(abs(Viento_061-Viento_062) > 20) Viento_062=Viento_061;
            DEMOQE.write(0x06);
         }
            
            else if (V06==3){
            Viento_063 = DATO_IN*0.635783;
           // if(abs(Viento_062-Viento_063) > 20) Viento_063=Viento_062;
            DEMOQE.write(0x06);
          }
            
            else if (V06==4){
            Viento_064 = DATO_IN*0.635783;
         //   if(abs(Viento_063-Viento_064) > 20) Viento_064=Viento_063;
            DEMOQE.write(0x06);
          }
            
            else if (V06==5){  
            Viento_065 = DATO_IN*0.635783;
            //if(abs(Viento_064-Viento_065) > 20) Viento_065=Viento_064;
            DEMOQE.write(0x06);
          }
            
            else if (V06==6){
            Viento_066 = DATO_IN*0.635783;
            //if(abs(Viento_065-Viento_066) > 20) Viento_066=Viento_065;
            DEMOQE.write(0x06);
          }
                    
           else if (V06==7){
            Viento_067 = DATO_IN*0.635783;
            //if(abs(Viento_066-Viento_067) > 20) Viento_067=Viento_066;
            DEMOQE.write(0x06);
         }
            
            else if (V06==8){
            Viento_068 = DATO_IN*0.635783;
           // if(abs(Viento_067-Viento_068) > 20) Viento_068=Viento_067;
            DEMOQE.write(0x06);
          }
            
            else if (V06==9){
            Viento_069 = DATO_IN*0.635783;
            //if(abs(Viento_068-Viento_069) > 20) Viento_069=Viento_068;
            DEMOQE.write(0x06);
          }
            
            else if (V06==10){  
            Viento_0610 = DATO_IN*0.635783;
            //if(abs(Viento_069-Viento_0610) > 20) Viento_0610=Viento_069;
            DEMOQE.write(0x06);
          }
            
            
            else{  
             
              Viento_06=(Viento_061+Viento_062+Viento_063+Viento_064+Viento_065+Viento_066+Viento_067+Viento_068+Viento_069+Viento_0610)/10;
              V06=0;          
            }
           
            //velViento.setText(String.format("%.2f", Vel_Viento_06_f) + " ms");
            //if(refall) 
           /* if( medida_06_ant == 0 ) medida_06_ant = Viento_06;
       
            //31.6
            
            //ERROR de 26 us
              println("real"+ str(Viento_06));
              println("vieja"+str(medida_06_ant));
            if( abs(medida_06_ant - Viento_06) <= 27 && abs(medida_06_ant - Viento_06) >= 18)
            {
              
             Viento_06 = medida_06_ant;
            }
            else medida_06_ant = Viento_06;*/
            
            if(V06==0){
               
            float vel_s = velocidad_sonido(Temp_Amb_01);
            
            float d = vel_s*Viento_06*(0.000001)/1.16847;
            
            //float v1 = (distancia_06/(Vel_Viento_06_f*(0.000001)/1.16847)) - vel_s;
            Viento_06 = (distancia_06/(Viento_06*(0.000001))) - vel_s + 48;
            
            //if(v1 >= vel_s) v1 = v1 - vel_s;
            //else v1 = vel_s - v1;
            
           // velViento.setText(String.format("%.2f", Vel_Viento_06_f) + " ms");
            //velViento.setText(String.format("%.1f",v1) + " m/s");
         
            
            DEMOQE.write(0x07);}
            
            
            
            break;
            
            
            
            
            
          case 0x07:
          
           /* for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //DirV_serial[k] = inBuffer[k];
               DirV_serial[k] = servBuffer[k];
            }  */
            
             V07++;
          
            /*for(byte k = 0 ; k<buff_size-1 ; k++){ 
               //VelV_serial[k] = inBuffer[k];
               VelV_serial[k] = servBuffer[k];
            }       */
            
            if(V07==1){
            Viento_071 = DATO_IN*0.635783;          
            DEMOQE.write(0x07);            
          }
            
            else if (V07==2){
            Viento_072 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
         }
            
            else if (V07==3){
            Viento_073 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
            
            else if (V07==4){
            Viento_074 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
            
            else if (V07==5){  
            Viento_075 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
            
            else if (V07==6){
            Viento_076 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
                    
           else if (V07==7){
            Viento_077 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
         }
            
            else if (V07==8){
            Viento_078 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
            
            else if (V07==9){
            Viento_079 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
            
            else if (V07==10){  
            Viento_0710 = DATO_IN*0.635783;
            DEMOQE.write(0x07);
          }
            
            
            else{  
             
              Viento_07=(Viento_071+Viento_072+Viento_073+Viento_074+Viento_075+Viento_076+Viento_077+Viento_078+Viento_079+Viento_0710)/10;
              V07=0;          
            }
            
            
           if(V07==0){
               
            float vel_s = velocidad_sonido(Temp_Amb_01);
            
            float d = vel_s*Viento_07*(0.000001)/1.16847;
            
            //float v1 = (distancia_06/(Vel_Viento_06_f*(0.000001)/1.16847)) - vel_s;
            Viento_07 = (distancia_07/(Viento_07*(0.000001))) - vel_s + 45.5;
            
            //if(v1 >= vel_s) v1 = v1 - vel_s;
            //else v1 = vel_s - v1;
            
           // velViento.setText(String.format("%.2f", Vel_Viento_06_f) + " ms");
            //velViento.setText(String.format("%.1f",v1) + " m/s");
         
            Vel_Viento_06 = sqrt( sq(Viento_06) + sq(Viento_07) );
            
            if(Viento_06<0) Dir_Viento_07= 180 - degrees(atan(Viento_07/abs(Viento_06)));    // Vy=07 , Vx=06
            else Dir_Viento_07= degrees(atan(Viento_07/Viento_06));    // Vy=07 , Vx=06
            
          //  Dir_Viento_07= degrees(atan(Viento_07/Viento_06));    // Vy=07 , Vx=06
            
            if(Dir_Viento_07<0) Dir_Viento_07=360+Dir_Viento_07;
            
            Flecha_Dir = Dir_Viento_07;
            
            if(!Dir) velViento.setText(String.format("%.2f", Vel_Viento_06)+ " m/s"  );
            if(!Vel) dirViento.setText(String.format("%.2f",Dir_Viento_07) + "º");
            
           
  
            
            
            Vel_Viento_ts = Vel_Viento_06;
            Dir_Viento_ts = Dir_Viento_07;
            
            Dir=false;
            Vel=false;
        
            if(primeramed && refall) primeramed=false; 
            refall=false;
          
        }
                    
            
            break;
            

            
          default:       
             println("Error!");
             break;          
                     
       }
     
     
      // textfield1.setText(hola);
       // DEMOQE.write(0xFF);
        
}


//Funciones

//********************************************************************************************************************


long unir_dato(long a , long b)
{
  long union;
  
  
  union = (a << 8);
  if((union & 0x8000) == 0x00) //0x8000 es 100000000000000, y es para ver si el último bit es 0. Si la operacion AND es 0x00, quiere decir que es un número positivo y no hay problema
    union = union  & 0x7FFF; //0x7FFF es 0111111111111111, y se realiza el AND para eliminar el signo
  else union = (union  & 0x7FFF) + 32768; // 32768 = 2^16 (Error)
  if((b & 0x8000) == 0x00) //0x8000 es 100000000000000, y es para ver si el último bit es 0. Si la operacion AND es 0x00, quiere decir que es un número positivo y no hay problema
    union = union + b;
  else union = union + (b & 0x000000FF); //0x000000FF es 0000000000001111, y se realiza el AND para eliminar la parte superior que no nos interesa. No se porqué aparece
   
  return union;  
}



float velocidad_sonido(float temperatura)
{
  return 331.4+0.61*temperatura;
}


//void sendNumber(float num) {
  //c = new Client(this, "api.thingspeak.com", 80); // Connect to server on port 80
 // c.write("GET /update?key="+APIKEY+"&"+FIELD+"="+num+ "HTTP/1.1\n");
  
  
  void sendNumber(float num1, float num2, float num3, float num4, float num5, float num6) {
  c = new Client(this, "api.thingspeak.com", 80); // Connect to server on port 80
 c.write("GET /update?key="+APIKEY+"&"+f1+"="+num1+"&"+f2+"="+num2+"&"+f3+"="+num3+"&"+f4+"="+num4+"&"+f5+"="+num5+"&"+f6+"="+num6+ "HTTP/1.1\n");
  //c.write("GET /update?key=C1H84C7MPNSQAA6L&amp;field1=" + num + " HTTP/1.1\n");
  c.write("Host: my_domain_name.com\n\n"); // Be polite and say who we are
}


//********************************************************************************************************************


// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){

textarea1.setText(Serial.list());

}

public void boton_serial_click(GButton source, GEvent event) { //_CODE_:boton_serial:331067:
  println("button1 - GButton event occured " + System.currentTimeMillis()%10000000 );
  String Puerto = textfield3.getText();
  Puerto = Puerto.toUpperCase();              //VOLVER A PONER ESTO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  int Serial_len = Serial.list().length;
  int x=0;
  for(x = 0; x <Serial_len  && !(Serial.list()[x].equals(Puerto)) ; x++ );
  
 /* if(x==Serial_len) print("El número de puerto seleccionado no está disponible");
  else print("Se encuentra conectado a " + Serial.list()[x]);*/
  
  if(x==Serial_len){ 
      label10.setText("El número de puerto seleccionado no está disponible");
      label10.setLocalColorScheme(GCScheme.RED_SCHEME);
  }  
    else{
          label10.setText("Se encuentra conectado a " + Serial.list()[x]); 
          label10.setLocalColorScheme(GCScheme.GREEN_SCHEME);
           Puerto_DEMOQE = Serial.list()[x];
           Baudios = 19200;
           DEMOQE = new Serial(this,Puerto_DEMOQE,Baudios);
           DEMOQE.buffer(buff_size);
           serialON=true;
        }
    
} //_CODE_:boton_serial:331067:


//*************************************************************************************************


//Refresh medidas
public void refresh1_click(GImageButton source, GEvent event) { //_CODE_:refresh1:574566:
  if(serialON) DEMOQE.write(0x04);
  refall=false;
  println("imgButton1 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh1:574566:

public void refresh2_click(GImageButton source, GEvent event) { //_CODE_:refresh2:977138:
  if(serialON) DEMOQE.write(0x02);
  refall=false;
  println("imgButton2 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh2:977138:

public void refresh3_click(GImageButton source, GEvent event) { //_CODE_:refresh3:609440:
   if(serialON) DEMOQE.write(0x01);
   refall=false;
  println("imgButton5 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh3:609440:

public void refresh4_click(GImageButton source, GEvent event) { //_CODE_:refresh4:546982:
  if(serialON) DEMOQE.write(0x03);
  refall=false;
  println("imgButton4 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh4:546982:

public void refresh5_click(GImageButton source, GEvent event) { //_CODE_:refresh5:220192:
  if(serialON) DEMOQE.write(0x05);
  refall=false;
  println("imgButton6 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh5:220192:

public void refresh6_click(GImageButton source, GEvent event) { //_CODE_:refresh6:677549:
  if(serialON) DEMOQE.write(0x06);
  Vel=true;
  refall=false;
  println("imgButton3 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh6:677549:

public void refresh7_click(GImageButton source, GEvent event) { //_CODE_:refresh17:843328:
  if(serialON) DEMOQE.write(0x07);
  Dir=true;
  refall=false;
  println("imgButton7 - GImageButton event occured " + System.currentTimeMillis()%10000000 );
} //_CODE_:refresh17:843328:



//*************************************************************************************************



public void enviar_tweets_click(GButton source, GEvent event) { //_CODE_:enviar_tweets:472321:
  println("button2 - GButton event occured - tweet=true " + System.currentTimeMillis()%10000000 );
  tweet=true;
} //_CODE_:enviar_tweets:472321:

public void parar_tweets_click(GButton source, GEvent event) { //_CODE_:parar_tweets:940236:
  println("button3 - GButton event occured - tweet=false" + System.currentTimeMillis()%10000000 );
  tweet=false;
} //_CODE_:parar_tweets:940236:

public void option1_clicked1(GOption source, GEvent event) { //_CODE_:option1:200390:
  println("option1 - GOption event occured " + System.currentTimeMillis()%10000000 );
  timer = new Timer(op1); 
  ton=true;
} //_CODE_:option1:200390:

public void option2_clicked1(GOption source, GEvent event) { //_CODE_:option2:314961:
  println("option2 - GOption event occured " + System.currentTimeMillis()%10000000 );
  timer = new Timer(op2); 
  ton=true;
} //_CODE_:option2:314961:

public void option3_clicked1(GOption source, GEvent event) { //_CODE_:option3:319219:
  println("option3 - GOption event occured " + System.currentTimeMillis()%10000000 );
  timer = new Timer(op3); 
  ton=true;
} //_CODE_:option3:319219:

public void option4_clicked1(GOption source, GEvent event) { //_CODE_:option4:396671:
  println("option4 - GOption event occured " + System.currentTimeMillis()%10000000 );
  timer = new Timer(op4); 
  ton=true;
} //_CODE_:option4:396671:

public void option5_clicked1(GOption source, GEvent event) { //_CODE_:option5:514525:
  println("option5 - GOption event occured " + System.currentTimeMillis()%10000000 );
  timer = new Timer(op5); 
  ton=true;
} //_CODE_:option5:514525:

public void option6_clicked1(GOption source, GEvent event) { //_CODE_:option6:685773:
  println("option6 - GOption event occured " + System.currentTimeMillis()%10000000 );
  timer = new Timer(op6); 
  ton=true;
} //_CODE_:option6:685773:



