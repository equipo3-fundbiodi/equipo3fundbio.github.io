#include <analogWrite.h> //definición de la librería para poder usar el analoWrite que no viene por defecto en el esp32

#include "math.h"

/*El código anti rebotes se usará para evitar que el paciente accidentalmente toque el boton de inicio y se desactive todo el sistema,
para esto se usará el algoritmo ya creado en combinación con este que permitirá gestionar el encendido de un módulo relé, haciendo más simple
el loop, que constará de una función de encendido del de led que mientras esté encendido el sisema funcionará*/

#include "BluetoothSerial.h" //definición de la librería bluetooth por defecto del esp32

BluetoothSerial SerialBT; //DEFINICIÓN DEL OBJETO BLUETOOTH

//DEFINICION DE LOS DATOS QUE SERÁN ENVIADOS POR BLUETOOTH
int dato_entrante_LED;
int dato_salida_HP1;
int dato_salida_HP2;
int dato_salida_HP3;
//ETIQUETA DE SALIDA DE LOS DATOS PARA IDENTFICAR EN QUE IMAGEN Y SECCIÓN PONERLO EN LA APLICACIÓN
int HP1=1;
int HP1=2;
int HP1=3;

//Defincion de variables a usar para el código antirrebotes (incluye el módulo TTP223)
volatile int interruptCounter;
volatile bool flag_monitor3;
int totalInterruptCounter;



//definir variables
const int M_rele = 0;      //salida rele on/off
const int M_rele1 = 2;      //salida rele on/off
const int TTP223B = 1;       //entrada pulsador

boolean f0 = false;
boolean f1 = false;

byte  pulsadores =0;
byte  buffer_pulsador;
int   conta_pulsador =0;
byte  reg_pulsador = 0;     //hasta 8 pulsadores


boolean flag_reloj0 = false;
boolean flag_reloj1 = false;
boolean flag_reloj2 = false;
boolean flag_reloj3 = false;
boolean flag_reloj4 = false;
boolean flag_reloj5 = false;
boolean flag_reloj6 = false;
int tempr;
int tiempo0 = 0;
int tiempo00 = 0;
int tiempo1 = 0;
int tiempo11 = 0;
int tiempo2 = 0;
int tiempo22 = 0;


//********** Definir llamadas a subrutinas  *****************************************************
void  relojes();
void  temporizador0();
void  temporizador1();
void  temporizador2();
void  antirrebotes();
void  lectura_pulsadores();
void Control_onoff();
//***********************************************************************************************
//*********************** Llamada a interrupcion TIMER1 *****************************************
//https://circuits4you.com/2018/01/02/esp8266-timer-ticker-example/
void ICACHE_RAM_ATTR onTimerISR()
{
  timer1_write(5000);//1ms
  relojes();
  digitalWrite(M_rele1, !digitalRead(M_rele1));
}

//--------------------Seteo de los pines de los 3 diales--------------------------------

//Definición de los pines que usarán para el control de los micromotores N20 de 1000rpm

const int pinPMWD1= 20;  //Control PWM para el control de la velocidad de giro 
const int pinD1IN2= 18; //Pin digital para inicio del giro para controlar adelante/atrás o horario/antihorario
const int pinD1IN1= 16;

const int pinPMWD2=15;
const int pinD2IN2=14;
const int pinD2IN1=13;

const int pinPMWD3= 12;
const int pinD3IN2= 11;
const int pinD3IN1= 10;

//Definición de pines para controlar el modo ahorro de energía

const int SDTBY_D1=21;
const int SDTBY_D2=24;
const int SDTBY_D3=25;

const int waitTime = 1000; //Tiempo de muestreo
const int maximo_velocidad= 1000;  //Velocidad de giro para el motor

//Encapsulado de los pines del los diales para su modificación futura

const int pinesDIAL1[3] = {pinPMWD1,pinD1IN2,pinD1IN1}; //lista de los pines de cada dial
const int pinesDIAL2[3] = {pinPMWD2,pinD2IN2,pinD2IN1}; //Orden 0=velocidad, 1= primera salida, 2=segunda salida
const int pinesDIAL3[3] = {pinPMWD3,pinD3IN2,pinD3IN1};

//establecemos los estados de movimiento
enum moveDirection { //estados
   adelante,
   atras
};

//---------------------Deficion de la cabecera de los amplificadores de señal---------------------------
/*-------------------------*/#include "HX711.h"/*---------------------------*/
//Definicion de los pines de las galgas que estarán conectadas al HX711

  const int HUMPAD1_DOUT_PIN = 5; //cada módulo HX711 necesita de: alimentación vcc y gnd
  const int HUMPAD1_SCK_PIN = 8; // además de 2 pines DOUT y SCK para transmitir los datos
  const int HUMPAD2_DOUT_PIN = 41;
  const int HUMPAD2_SCK_PIN = 40;
  const int HUMPAD3_DOUT_PIN = 42;
  const int HUMPAD3_SCK_PIN = 27;

// Definición de los objetos de la distribición de las 4 galgas
// en puente Wheatstone por cada Humpad
//Como cada arreglo estará en una almohadilla, se define 3 objteos HX711, uno por cada 4 galgas

HX711 hx711_galga_1;
HX711 hx711_galga_2;
HX711 hx711_galga_3;

//Cada distribución debe tener entradas que sean sensibles al cambio de voltaje, por eso no se definen en el setup
// debido a que cada pin se considerará como un INPUT

//------------------------------------------------------------
//Definición de variables necesarias para la comparación sensado y almacenamiento de las variables sensadas

const float fuerza_ideal_HP_1; //sección de fuerzas que se quieren alcanzar
const float fuerza_ideal_HP_2;
const float fuerza_ideal_HP_3;

//Definimos las varibles de limites del rango de modo que :   limite_inferior_HPX < fuerza_sensada_HP_X < limite_superior_HPX
const float limite_superior_HP1=0;
const float limite_inferior_HP1=0;
const float limite_superior_HP2=0;
const float limite_inferior_HP2=0;
const float limite_superior_HP3=0;
const float limite_inferior_HP3=0;

float fuerza_sensada_HP_1=0; // esta variable será la que se convertirá del valor obtenido de la galga y el factor de conversión por calibración
float fuerza_sensada_HP_2=0; //se define una por cada sección en la que estará la almohadilla
float fuerza_sensada_HP_3=0;


//-------------------------------------------------------------

//***********************************************************************************************
//***********************************************************************************************
//*********************** Zona de configuracion *************************************************
void setup() 
{ 

  
  Serial.begin(115200);
  //Habilitando interrupcion TIMER1
  noInterrupts();
  timer1_attachInterrupt (onTimerISR); 
    timer1_enable (TIM_DIV16, TIM_EDGE, TIM_SINGLE); 
    timer1_write (5000); // 120000 us 
  interrupts();
  
  //CONFIGURACIÓN DE LOS RELES COMO SALIDAS
  
  pinMode(M_rele, OUTPUT);
  pinMode(M_rele1, OUTPUT);
  
  //SETEO DEL TTP223B COMO ENTRADA
  
  pinMode(TTP223B, INPUT); // definición del módulo TTP223B

  //SETEO DE LOS PINES DE CONTROL DE LOS MOTORES, TODOS COMO SALIDAS
  
   pinMode(pinPMWD1, OUTPUT);
   pinMode(pinD1IN2, OUTPUT);
   pinMode(pinD1IN1, OUTPUT);
   pinMode(SDTBY_D1,OUTPUT);
   pinMode(pinPMWD2, OUTPUT);
   pinMode(pinD2IN2, OUTPUT);
   pinMode(pinD2IN1, OUTPUT);
   pinMode(SDTBY_D2,OUTPUT);
   pinMode(pinPMWD3, OUTPUT);
   pinMode(pinD3IN2, OUTPUT);
   pinMode(pinD3IN1, OUTPUT);
   pinMode(SDTBY_D3,OUTPUT);
  
    //SUB-SETEO
      //Se establece todos los pines inicialmente en modo ahorro de energía
      //para que sean activados via algoritmo en el loop solo cuando se requiera
        digitalWrite(SDTBY_D1,LOW);
        digitalWrite(SDTBY_D2,LOW);
        digitalWrite(SDTBY_D3,LOW);

  //SETEO DE VALORES DE FUERZA IDEAL
   fuerza_ideal_HP_1= /*valores seteables para hacer las comparaciones futuras*/;
   fuerza_ideal_HP_2= /*valores seteables para hacer las comparaciones futuras*/ ;
   fuerza_ideal_HP_3= /*valores seteables para hacer las comparaciones futuras*/;

  //SETEO DE LOS VALORES DE FUERZA LÍMITES DE CADA SECCION
  //Trabajaremos primero con un rango de +/- 5% de las fuerzas ideales
      limite_superior_HP1=(105/100)*fuerza_ideal_HP_1;
      limite_inferior_HP1=(95/100)*fuerza_ideal_HP_1;
      limite_superior_HP2=(105/100)*fuerza_ideal_HP_1;
      limite_inferior_HP2=(95/100)*fuerza_ideal_HP_1;
      limite_superior_HP3=(105/100)*fuerza_ideal_HP_1;
      limite_inferior_HP3=(95/100)*fuerza_ideal_HP_1;
  
  //INICIALIZACIÓN DE LOS OBJETOS HX711 
   
   hx711_galga_1.begin(HUMPAD1_DOUT_PIN,HUMPAD1_SCK_PIN); //SE ESTABLECEN SUS PINES A USAR
   hx711_galga_2.begin(HUMPAD2_DOUT_PIN,HUMPAD2_SCK_PIN);
   hx711_galga_3.begin(HUMPAD3_DOUT_PIN,HUMPAD3_SCK_PIN);

  //INICIALIZACIÓN DEL OBJETO BLUETOOTH

  SerialBT.begin("ORTESIS"); //establecemos el nombre que va a estar vinculado en el celular del usuario
  
   
}

//***********************************************************************************************
//***********************************************************************************************
//*********************** Programa principal    *************************************************
void loop() {
  
  Control_onoff(); //controla el encendido y el apagado del sistema

  //En cada pasado del loop se tomarán las medidas solo si el rele (equivalente del sistema, está encendido)
  
  if (digitalRead(M_rele==HIGH)){

    //Lo primeró que se hará será tomar las medidas de cada loop en ese momento
    
    if(hx711_galga_1.is_ready()){ // solo se tomará si la galga está conectada
    long reading_galga_1 = -2*(hx711_galga_1.read()/139.37-59935); // dividimos nuestro valor sensado entre el factor de conversión y le restamos una "tara";
    Serial.print("HX711 1 reading: ");
    
    fuerza_sensada_HP_1= reading_galga_1*pow(10,-3)*(9.807) //Se establece la conversión a fuerza por medio del factor de conversión y la reducción obtenida
    // experimentalmente
    Serial.println(fuerza_sensada_HP_1);

       //definimos que para humpad si está establecida una conexión BT entonces se enviarán los datps

      double dato_salida_HP1 = (reading_galga_1*pow(10,-3)*(9.807));
      
      char HUMP=HP1;
      String datos_de_salida_HP_1;
      datos_de_salida_HP_1 = String("1,");

      datos_de_salida_HP_1 += dato_salida_HP1;//fuerza de humpad  //iniciamos el proceso de concatenar los datos en un string que será interpretado en la app
      datos_de_salida_HP_1 += ",";
      datos_de_salida_HP_1 += HP1;
      
      //char enviar_dato_BT= dato_BT + "," +HUMP;
      Serial.println(datos_de_salida_HP_1);
      delay(1000);
      Serial.println("Enviando un dato 1...");
      SerialBT.print(datos_de_salida_HP_1); //enviamos el string a la aplicacion constante mente
      
    }
    else{
    Serial.print("HX711 1 no está conectado ERROR: ");
    }
    if(hx711_galga_2.is_ready()){
    long reading_galga_2 = hx711_galga_2.read()/(-142.17)-479;
    Serial.print("HX711 2 reading: ");
    fuerza_sensada_HP_2= reading_galga_2*pow(10,-3)*(9.807);
    Serial.println(fuerza_sensada_HP_2);

    
    //definimos que para humpad si está establecida una conexión BT entonces se enviarán los datps

      double dato_salida_HP2 = (reading_galga_2*pow(10,-3)*(9.807));
      
      char HUMP=HP2;
      String datos_de_salida_HP_2;
      datos_de_salida_HP_2 = String("1,");

      datos_de_salida_HP_2 += dato_salida_HP2;//fuerza de humpad  //iniciamos el proceso de concatenar los datos en un string que será interpretado en la app
      datos_de_salida_HP_2 += ",";
      datos_de_salida_HP_2 += HP2;
      
      //char enviar_dato_BT= dato_BT + "," +HUMP;
      Serial.println(datos_de_salida_HP_2);
      delay(1000);
      Serial.println("Enviando un dato 1...");
      SerialBT.print(datos_de_salida_HP_2); //enviamos el string a la aplicacion constante mente
      
    }
    else{
    Serial.print("HX711 2 no está conectado ERROR: ");
    }
    if(hx711_galga_3.is_ready()){
    long reading_galga_3 = hx711_galga_3.read()/(-142.17)-479;
    Serial.print("HX711 3 reading: ");
    fuerza_sensada_HP_3= reading_galga_3*pow(10,-3)*(9.807);
    Serial.println(fuerza_sensada_HP_3);
    //definimos que para humpad si está establecida una conexión BT entonces se enviarán los datps

      double dato_salida_HP3 = (reading_galga_3*pow(10,-3)*(9.807));
      
      char HUMP=HP3;
      String datos_de_salida_HP_3;
      datos_de_salida_HP_3 = String("1,");

      datos_de_salida_HP_3 += dato_salida_HP3;//fuerza de humpad  //iniciamos el proceso de concatenar los datos en un string que será interpretado en la app
      datos_de_salida_HP_3 += ",";
      datos_de_salida_HP_3 += HP1;
      
      //char enviar_dato_BT= dato_BT + "," +HUMP;
      Serial.println(datos_de_salida_HP_3);
      delay(1000);
      Serial.println("Enviando un dato 1...");
      SerialBT.print(datos_de_salida_HP_3); //enviamos el string a la aplicacion constante mente
      
    }
    else{
    Serial.print("HX711 3 no está conectado ERROR: ");
    }
  }

  //Termina el sensado en cada loop y si hay uno que no no este en los rangos se procederá a ajustar el que esté más cerca en el código

  //----------Espacio para el ajuste automático-----------------------------------------------------------------------------

  /********************************AJUSTE DEL DIAL 1*********************************************************
****************************************************************************************************************
***************************************************************************************************************
****************************************************************************************************************/
  
  if (fuerza_sensada_HP_1<=limite_inferior_HP1  || fuerza_sensada_HP_1>= limite_superior_HP1 ){
        while(fuerza_sensada_HP_1<= limite_inferior_HP1 || fuerza_sensada_HP_1>= limite_superior_HP1){
          if (fuerza_sensada_HP_1<= limite_inferior_HP1){ //Mientras que la fuerza sea menor, haremos que el dial vaya adelante
            activar_dial_1(); //función que hace que el modo de ahorro de energía se desactive
            ajuste_automático(pinesDIAL1,adelante,500); // definimos el dial a usar, la dirección del enum y el tiempo de giro
            delay(waitTime); //esperaremos un delay a que la acción se complete completamente
            parar_giro_del_dial (pinesDIAL1); // funcion que no apagará sino parará la rotación para hacer un nuevo sensado
            fuerza_sensada_HP_1=hx711_galga_1.read()/(-142.17)-479)*pow(10,-3)*(9.807);
            delay(500);
          }
          if (fuerza_sensada_HP_1>= limite_superior_HP1){ //Mientras que la fuerza sea mayor, haremos que el dial vaya atras
            activar_dial_1();
            ajuste_automático(pinesDIAL1,atras,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL1);
            fuerza_sensada_HP_1=(hx711_galga_1.read()/(-142.17)-479)*pow(10,-3)*(9.807); //volvemos a sensar para romper el bucle while
            delay(500);
          }
        }
        
       desactivar_dial_1(); // cuando salgamos del bucle while, se entrará nuevamente al estado de ahorro de energía
      }

  /********************************AJUSTE DEL DIAL 2*********************************************************
****************************************************************************************************************
***************************************************************************************************************
****************************************************************************************************************/
   if (fuerza_sensada_HP_2<=limite_inferior_HP2  || fuerza_sensada_HP_2>= limite_superior_HP2 ){
        while(fuerza_sensada_HP_2<= limite_inferior_HP2 || fuerza_sensada_HP_2>= limite_superior_HP2){
          if (fuerza_sensada_HP_2<= limite_inferior_HP2){ //Mientras que la fuerza sea menor, haremos que el dial vaya adelante
            activar_dial_2(); //función que hace que el modo de ahorro de energía se desactive
            ajuste_automático(pinesDIAL2,adelante,500); // definimos el dial a usar, la dirección del enum y el tiempo de giro
            delay(waitTime); //esperaremos un delay a que la acción se complete completamente
            parar_giro_del_dial (pinesDIAL2); // funcion que no apagará sino parará la rotación para hacer un nuevo sensado
            fuerza_sensada_HP_2=(hx711_galga_2.read()/(-142.17)-479)*pow(10,-3)*(9.807);
            delay(500);
          }
          if (fuerza_sensada_HP_2>= limite_superior_HP2){ //Mientras que la fuerza sea mayor, haremos que el dial vaya atras
            activar_dial_2();
            ajuste_automático(pinesDIAL2,atras,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL2);
            fuerza_sensada_HP_2=(hx711_galga_2.read()/(-142.17)-479)*pow(10,-3)*(9.807); //volvemos a sensar para romper el bucle while
            delay(500);
          }
        }
        
       desactivar_dial_2(); // cuando salgamos del bucle while, se entrará nuevamente al estado de ahorro de energía
      }

  /********************************AJUSTE DEL DIAL 3*********************************************************
****************************************************************************************************************
***************************************************************************************************************
****************************************************************************************************************/
   if (fuerza_sensada_HP_3<=limite_inferior_HP3|| fuerza_sensada_HP_3>= limite_superior_HP3 ){
        while(fuerza_sensada_HP_3<= limite_inferior_HP3 || fuerza_sensada_HP31>= limite_superior_HP3){
          if (fuerza_sensada_HP_3<= limite_inferior_HP3){ //Mientras que la fuerza sea menor, haremos que el dial vaya adelante
            activar_dial_3(); //función que hace que el modo de ahorro de energía se desactive
            ajuste_automático(pinesDIAL3,adelante,500); // definimos el dial a usar, la dirección del enum y el tiempo de giro
            delay(waitTime); //esperaremos un delay a que la acción se complete completamente
            parar_giro_del_dial (pinesDIAL3); // funcion que no apagará sino parará la rotación para hacer un nuevo sensado
            fuerza_sensada_HP_3=(hx711_galga_3.read()/(-142.17)-479)*pow(10,-3)*(9.807);
            delay(500);
          }
          if (fuerza_sensada_HP_3>= limite_superior_HP3){ //Mientras que la fuerza sea mayor, haremos que el dial vaya atras
            activar_dial_3();
            ajuste_automático(pinesDIAL3,atras,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL3);
            fuerza_sensada_HP_3=(hx711_galga_3.read()/(-142.17)-479)*pow(10,-3)*(9.807); //volvemos a sensar para romper el bucle while
            delay(500);
          }
        }
        
       desactivar_dial_3(); // cuando salgamos del bucle while, se entrará nuevamente al estado de ahorro de energía
      }
 //Fin de la parte del ajuste
}

//----------------------------------------DEFINICION DE LAS FUNCIONES----------------------------------------------

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
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
      digitalWrite(M_rele, !digitalRead(M_rele));
    }
  }
}
/**********************************************************************************************/
//***********************************************************************************************
//*********************  lee el estado de los pulsadores    *************************************
void  lectura_pulsadores()
{
  if(digitalRead(Touch)==HIGH) { bitSet(pulsadores,7); }  else { bitClear(pulsadores,7); }
} 
//***********************************************************************************************
//*********************    Eliminar rebotes en pulsadores ***************************************
void  antirrebotes()
{
   buffer_pulsador=pulsadores;
   if(buffer_pulsador != reg_pulsador)
   {    
      if(conta_pulsador==300)      //300ms de antirrebote
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
    flag_monitor3 = LOW;   
  if(flag_reloj0 == HIGH)  {  temporizador0();  }  
  if(flag_reloj1 == HIGH)  {  temporizador1();  }  
  if(flag_reloj2 == HIGH)  {  temporizador2();  }    
  //digitalWrite(led,!digitalRead(led));   
}
/***********************************************/
/********** fija la velocidad del motor pap ****/
void temporizador0()
{
  tempr=tiempo0+1;
  if(tempr >= 100)  {
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
    if(tempr == 2){
      tiempo22=0;
      flag_reloj2=LOW;
    }else{tiempo22++;}
  }else{tiempo2++;}
}
//***********************************************************************************************
//totalInterruptCounter++;
//      Serial.print("An interrupt as occurred. Total number: ");
//      Serial.println(totalInterruptCounter);
//      Serial.println(velocidad); }

//Para que el driver salga del modo de consumo bajo de energía y permita activar los motores

void activar_dial_1(){
  digitalWrite(SDTBY_D1,HIGH);
  }
void activar_dial_2(){
  digitalWrite(SDTBY_D2,HIGH);
  }
void activar_dial_3(){
  digitalWrite(SDTBY_D3,HIGH);
  }
//Para que el driver entre al modo de consumo bajo de energía y permita desactivar los motores
void desactivar_dial_1(){
  digitalWrite(SDTBY_D1,LOW);
  }
void desactivar_dial_2(){
  digitalWrite(SDTBY_D2,LOW);
  }
void desactivar_dial_3(){
  digitalWrite(SDTBY_D3,LOW);
  }

//Funcion para ejecutar el ajuste automático dependiendo del tipo de dial que queramos girar

void ajuste_automático(const int DIAL[3], int direccion, int velocidad){

    if(direccion==adelante){
      
        mover_motor_adelante(DIAL,velocidad);
      
      }
    else{
      
        mover_motor_atras(DIAL,velocidad);
      
      }
  
  }

//Funcion para controlar el tipo de giro hacia adelante
void mover_motor_adelante (const int DIAL[3], int velocidad){
  digitalWrite(DIAL[1],HIGH);
  digitalWrite(DIAL[2],LOW);
  analogWrite(DIAL[0],500);
  }
//Funcion para controlar el tipo de giro hacia atras
void mover_motor_atras (const int DIAL[3], int velocidad){
  digitalWrite(DIAL[1],LOW);
  digitalWrite(DIAL[2],HIGH);
  analogWrite(DIAL[0],500);
  }
//Funcion para detener el giro del motor
void parar_giro_del_dial (const int DIAL[3]){
  digitalWrite(DIAL[1],LOW);
  digitalWrite(DIAL[2],LOW);
  analogWrite(DIAL[0],0);
  }
