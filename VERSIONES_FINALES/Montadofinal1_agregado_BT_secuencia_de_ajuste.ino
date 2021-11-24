#include "HX711.h"
#include "math.h"
#include "BluetoothSerial.h"
#include <analogWrite.h>

//*************************************************************************************
//Variable para la interrupcion TMR0
volatile int interruptCounter;
volatile bool flag_monitor3;
int totalInterruptCounter;
hw_timer_t * timer0 = NULL;
portMUX_TYPE timer0Mux = portMUX_INITIALIZER_UNLOCKED;
//*************************************************************************************

HX711 hx711_galga_1;

BluetoothSerial SerialBT;

int dato_entrante;
float dato_salida;
char datos_serial;
float fuerza_ideal=9.81;
float FuerzaMin= 5;   //(95/100)*fuerza_ideal;
float FuerzaMax= 7;   //(105/100)*fuerza_ideal;
int   velocidad = 90;    //fija la velocidad del motor, max 255
float FuerzaSensada;
int HP = 1;

//definir variables
//const int pulsador1 = 36;
const int led = 2; //led de prueba
const int led2 = 15; //led de prueba
const int M_rele = 4;      //salida rele on/off
const int Touch = 17;       //entrada pulsador
const int HUMPAD1_DOUT_PIN = 22;
const int HUMPAD1_SCK_PIN = 14;
const int pinPMWD1= 26;  //1;  //Control PWM para el control de la velocidad de giro 
const int pinD1IN2= 27;  //3; //Pin digital para inicio del giro para controlar adelante/atrás o horario/antihorario
const int pinD1IN1= 18;
const int SDTBY_D1= 12;//Definición de pines para controlar el modo ahorro de energía



const int waitTime = 1000; //Tiempo de muestreo
const int maximo_velocidad= 1500;  //Velocidad de giro para el motor

const int pinesDIAL1[3] = {pinPMWD1,pinD1IN2,pinD1IN1};

enum moveDirection {
   adelante,
   atras
};



boolean f0 = false;
boolean f1 = false;
boolean f2 = false;
boolean f3 = false;
boolean f4 = false;
boolean f5 = false;
boolean f6 = false;
boolean f7 = false;
boolean flag_monitor0 = false;
boolean flag_monitor1 = false;
boolean flag_monitor2 = false;
boolean flag_monitor4 = false;
boolean flag_monitor5 = false;
boolean flag_monitor6 = false;
boolean flag_monitor7 = false;
byte  pulsadores =0;
byte  buffer_pulsador;
int   conta_pulsador =0;
byte  reg_pulsador = 0;     //hasta 8 pulsadores
//boolean flag_monitor3 = false;
boolean flag_reloj0 = false;
boolean flag_reloj1 = false;
boolean flag_reloj2 = false;
boolean flag_reloj3 = false;
boolean flag_reloj4 = false;
boolean flag_reloj5 = false;
boolean flag_reloj6 = false;
int tempr=0;
int tiempo0 = 0;
int tiempo00 = 0;
int tiempo1 = 0;
int tiempo11 = 0;
int tiempo2 = 0;
int tiempo22 = 0;
int tiempo3 = 0;
int temp=400;
byte funcion = 0;


//***********************************************************************************************
//********** Definir llamadas a subrutinas  *****************************************************
void  relojes();
void  temporizador0();
void  temporizador1();
void  temporizador2();
void  temporizador3();
void  fija_velocidad_motor();
void  antirrebotes();
void  eligir_funcion();
void  lectura_pulsadores();
void  salida_efecto_motor();
void  lectura_modulo_galga();
void  control_motor();
void  Control_onoff();
void activar_dial_1();
void desactivar_dial_1();
void ajuste_automatico(const int DIAL[3], int direccion, int velocidad);
void mover_motor_adelante (const int DIAL[3], int velocidad);
void mover_motor_atras (const int DIAL[3], int velocidad);
void parar_giro_del_dial (const int DIAL[3]);
void  manejo_bluetooth();
//***********************************************************************************************
//*********************** Llamada a interrupcion TIMER0 *****************************************
//enlaces https://descubrearduino.com/esp32-arduino-interrupciones-timer/
//https://www.prometec.net/esp32/
//https://www.electrogeekshop.com/como-controlar-un-motor-paso-a-paso-con-el-a4988-y-arduino/
void IRAM_ATTR onTimer0() 
{
  portENTER_CRITICAL_ISR(&timer0Mux);
  interruptCounter++;
  flag_monitor3 = HIGH;
  portEXIT_CRITICAL_ISR(&timer0Mux);
  relojes();
  f3 = LOW;
}
//***********************************************************************************************
//***********************************************************************************************
//*********************** Zona de configuracion *************************************************
void setup() 
{ 
  Serial.begin(115200);
  //Habilitando interrupcion TIMER0
  timer0 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer0, &onTimer0, true);
  timerAlarmWrite(timer0, 1000, true);
  timerAlarmEnable(timer0); 
  // Configura as portas como salidas
  pinMode(M_rele, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  // Configura as portas como entrada
  pinMode(Touch, INPUT);

   pinMode(pinPMWD1, OUTPUT);
   pinMode(pinD1IN2, OUTPUT);
   pinMode(pinD1IN1, OUTPUT);
   pinMode(SDTBY_D1, OUTPUT);
   digitalWrite(led, LOW);
   digitalWrite(M_rele, LOW);  
   reg_pulsador = 0; 
  hx711_galga_1.begin(HUMPAD1_DOUT_PIN,HUMPAD1_SCK_PIN);
  Serial.println("1233");
  SerialBT.begin("ORTESIS");
  delay(100);
  f4 = HIGH;  //para el rele arranque apagado
  //velocidad = 200;    //fija la velocidad del motor
}
//***********************************************************************************************
//***********************************************************************************************
//*********************** Programa principal    *************************************************
void loop() 
{
  if(f3 == LOW)
  {
    f3 = HIGH;
    Control_onoff();
    lectura_modulo_galga();
    control_motor();
    //manejo_bluetooth();
  }
}
   
/**********************************************************************************************/
/************************Fin de la rutina principal *******************************************/
/**********************************************************************************************/
    
/**********************************************************************************************/
/************************   Habilita motor          *******************************************/              
void activar_dial_1(){
  digitalWrite(SDTBY_D1,HIGH);
  }
/**********************************************************************************************/
/************************   Desactiva Motor         *******************************************/
void desactivar_dial_1(){
  digitalWrite(SDTBY_D1,LOW);
  }   
/**********************************************************************************************/
/************************   Avance o retrocede      *******************************************/
void ajuste_automatico(const int DIAL[3], int direccion, int velocidad){

    if(direccion==adelante){     
        mover_motor_adelante(DIAL,velocidad);    
      }
    else{    
        mover_motor_atras(DIAL,velocidad);      
      } 
  }
/**********************************************************************************************/
/************************   Avance                  *******************************************/
void mover_motor_adelante (const int DIAL[3], int velocidad){
  digitalWrite(DIAL[1],HIGH);
  digitalWrite(DIAL[2],LOW);
  analogWrite(DIAL[0],velocidad);
  }
/**********************************************************************************************/
/************************   Atras                   *******************************************/
void mover_motor_atras (const int DIAL[3], int velocidad){
  digitalWrite(DIAL[1],LOW);
  digitalWrite(DIAL[2],HIGH);
  analogWrite(DIAL[0],velocidad);
  }
/**********************************************************************************************/
/************************   Stop                    *******************************************/
void parar_giro_del_dial (const int DIAL[3]){
  digitalWrite(DIAL[1],LOW);
  digitalWrite(DIAL[2],LOW);
  analogWrite(DIAL[0],0);
  }
/**********************************************************************************************/
/**********************************************************************************************/
/************************   Lectura Galga            *******************************************/
void  lectura_modulo_galga()
{
  if(f2 == HIGH)    //Esta habilitado rele principal
  {    
    if(hx711_galga_1.is_ready())
    {
      //digitalWrite(led2,HIGH );      
      long reading_galga_1 = -1*(hx711_galga_1.read()/6423.84)-207;   
      Serial.print("Lectura en gramos: ");
      Serial.print(reading_galga_1);
      Serial.print("   Lectura en newtons: ");
      Serial.print(reading_galga_1*pow(10,-3)*(9.807));
      Serial.print("\n"); 
      dato_salida = (reading_galga_1*pow(10,-3)*(9.807));
      FuerzaSensada = (reading_galga_1*pow(10,-3)*(9.807));
      char HUMP=HP;
      String datos_de_salida;
      datos_de_salida= String ("1,");
      datos_de_salida += FuerzaSensada;
      datos_de_salida += ",";
      datos_de_salida += HP;

      Serial.println(datos_de_salida);
      Serial.println("Enviando un dato 1...");
      SerialBT.print(datos_de_salida);
    } 
    //digitalWrite(led2,LOW );
  }
}
/**********************************************************************************************/
/**********************************************************************************************/
/***************************    Control Motor         *****************************************/
void  control_motor()
{
  if(f2 == HIGH)    //Esta habilitado rele principal
  {   
    if ((FuerzaSensada <= FuerzaMin) || (FuerzaSensada >= FuerzaMax))
    {
      if(FuerzaSensada <= FuerzaMin)
      {
        //digitalWrite(led2,!digitalRead(led2));
        digitalWrite(led2,HIGH );
        digitalWrite(SDTBY_D1,HIGH);  //activar_dial_1();pinesDIAL1[3] = {pinPMWD1,pinD1IN2,pinD1IN1};
        digitalWrite(pinD1IN2,HIGH);   //ajuste_automatico( pinesDIAL1, adelante, 200 );
        digitalWrite(pinD1IN1,LOW);
        analogWrite(pinPMWD1,velocidad);
      }
      if (FuerzaSensada >= FuerzaMax)
      {
        //digitalWrite(led2,!digitalRead(led2));
        digitalWrite(SDTBY_D1,HIGH);  //activar_dial_1();
        digitalWrite(pinD1IN2,LOW);   //ajuste_automatico( pinesDIAL1, atras, 200 );
        digitalWrite(pinD1IN1,HIGH);
        analogWrite(pinPMWD1,velocidad);
      }
    }
    else
    {
      digitalWrite(pinD1IN2,LOW);  //Parar giro del motor
      digitalWrite(pinD1IN1,LOW);
      analogWrite(pinPMWD1,0);
      digitalWrite(SDTBY_D1,LOW); //desaactiva modulo 
    }
  }
}

/**********************************************************************************************/
/**********************************************************************************************/
/***************************    Bluetooth             *****************************************/       
void  manejo_bluetooth()
{     
      
      if(SerialBT.available()){
      Serial.println("Se conecto el dispositivo BITCH");
      dato_entrante=SerialBT.read();
      
      int estado=dato_entrante;

      switch (estado){
        
        case 1: 
        Serial.println("Comando para ENCENDER un led activado");
       
        digitalWrite(led, HIGH);
        break;
        case 2: 
         Serial.println("Comando para APAGAR un led activado");
        
        digitalWrite(led, LOW);
        break;          
        }
  }
}    
/**********************************************************************************************/
/**********************************************************************************************/
/***************************    Control on/off        *****************************************/
void  Control_onoff()
{
  if(bitRead(reg_pulsador,7) == HIGH) //entrada Touch
  {
    if(f0 == LOW)
    {
      f0 = HIGH;
      f1 = LOW;
    }
  }
  else
  {
    if(f1 == LOW)
    {
      f1 = HIGH;
      f0 = LOW;
      if(f4 == LOW)  { digitalWrite(M_rele, !digitalRead(M_rele));  } else f4=LOW;    
      digitalWrite(led, digitalRead(M_rele));
      if(digitalRead(M_rele) == HIGH) 
      { 
        f2 = HIGH; 
      } 
      else 
      {  
        f2 = LOW; //f2 = HIGH, rele habilitado
        parar_giro_del_dial (pinesDIAL1);
      }
    }
  }
}
/**********************************************************************************************/
//***********************************************************************************************
//*********************  lee el estado de los pulsadores    *************************************
void  lectura_pulsadores()
{
  if(digitalRead(Touch)==HIGH)  { bitSet(pulsadores,7); }  else { bitClear(pulsadores,7); }
} 
//***********************************************************************************************
//*********************    Eliminar rebotes en pulsadores ***************************************
void  antirrebotes()
{
   buffer_pulsador=pulsadores;
   if(buffer_pulsador != reg_pulsador)
   {    
      if(conta_pulsador==300)     //300ms de antirrebote
      {
         conta_pulsador=0;
         reg_pulsador=buffer_pulsador;        
      }
      else  {  conta_pulsador++;  }
   }  else conta_pulsador=0;
}
//***********************************************************************************************
//*********************** Subrutina relojes     *************************************************
void relojes()
{
    lectura_pulsadores();
    antirrebotes();
    portENTER_CRITICAL(&timer0Mux);
    flag_monitor3 = LOW;
    portEXIT_CRITICAL(&timer0Mux);    
  if(flag_reloj0 == HIGH)  {  temporizador0();  }  
  if(flag_reloj1 == HIGH)  {  temporizador1();  }  
  if(flag_reloj2 == HIGH)  {  temporizador2();  }    
  if(flag_reloj3 == HIGH)  {  temporizador3();  }    
  //digitalWrite(led,!digitalRead(led));   
}
/***********************************************/
/********** fija la velocidad del motor pap ****/
void temporizador0()
{
  tempr=tiempo0+1;
  if(tempr == 100)  {
    tiempo0=0;
    flag_reloj0=LOW;    
  }else{tiempo0++;}
}
/***********************************************/
void temporizador1()
{
  tempr=tiempo1+1;
  if(tempr == 100){
    tiempo1=0;
    tempr=tiempo11 + 1;
    if(tempr == 20){
      tiempo11=0;
      flag_reloj1=LOW;
    }else{tiempo11++;}
  }else{tiempo1++;}
}
/***********************************************/
void temporizador2()
{
  tempr=tiempo2+1;
  if(tempr == 100){
    tiempo2=0;
    tempr=tiempo22 + 1;
    if(tempr == 20){
      tiempo22=0;
      flag_reloj2=LOW;
    }else{tiempo22++;}
  }else{tiempo2++;}
}
/***********************************************/
void temporizador3()
{
  tempr=tiempo3+1;
  if(tempr == 2000) {
  tiempo3=0; 
  flag_reloj3=LOW;  }
  else tiempo3++;
}
