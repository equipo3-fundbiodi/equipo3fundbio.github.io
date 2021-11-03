//Seteo de los pines del sensor capacitivo TTP223
int TTP223B=34; // pin 34 en adelante es solo de lectura
int LED=33; // para comprobar que se puede controlar componentes dentro del loop
int ESTADO = LOW;
int contador_toques=0; //contador de tiempo que el usuario presiona para des/activar el sistema

//Seteo de los pines de los 3 diales

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

const int pinesDIAL1[3] = {pinPMWD1,pinD1IN2,pinD1IN1}; //lista de los pines de cada dial
const int pinesDIAL2[3] = {pinPMWD2,pinD2IN2,pinD2IN1};
const int pinesDIAL3[3] = {pinPMWD3,pinD3IN2,pinD3IN1};

enum moveDirection { //estados
   adelante,
   atras
};
/*enum turnDirection { // para futuras pruebas
   horario,
   antihorario
};
enum selectorDial {
  DIAL1,
  DIAL2,
  DIAL3,
  }
*/

//---------------------Deficion de la cabecera de los amplificadores de señal---------------------------
#include "HX711.h"

  //Definicion de los pines de los HumpPads
    
  const int HUMPAD1_DOUT_PIN = 5;
  const int HUMPAD1_SCK_PIN = 8;
  const int HUMPAD2_DOUT_PIN = 41;
  const int HUMPAD2_SCK_PIN = 40;
  const int HUMPAD3_DOUT_PIN = 42;
  const int HUMPAD3_SCK_PIN = 27;
  
// Definición de los objetos de la distribición de las 4 galgas
// en puente Wheatstone por cada Humpad

HX711 hx711_galga_1;
HX711 hx711_galga_2;
HX711 hx711_galga_3;

//Cada distribución debe tener entradas analógicas por eso no se definen en el setup

//-------------------------------------------------
const float fuerza_ideal_HP_1;
const float fuerza_ideal_HP_2;
const float fuerza_ideal_HP_3;

float fuerza_sensada_HP_1=0;
float fuerza_sensada_HP_2=0;
float fuerza_sensada_HP_3=0;


void setup(){
  
   pinMode(TTP223B, INPUT);
   pinMode(LED,OUTPUT);
   Serial.begin(9600);
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
   digitalWrite(SDTBY_D1,LOW);
   digitalWrite(SDTBY_D2,LOW);
   digitalWrite(SDTBY_D3,LOW);
   fuerza_ideal_HP_1= /*valores seteables para hacer las comparaciones futuras*/;
   fuerza_ideal_HP_2= /*valores seteables para hacer las comparaciones futuras*/ ;
   fuerza_ideal_HP_3= /*valores seteables para hacer las comparaciones futuras*/;
   hx711_galga_1.begin(HUMPAD1_DOUT_PIN,HUMPAD1_SCK_PIN);
   hx711_galga_2.begin(HUMPAD2_DOUT_PIN,HUMPAD2_SCK_PIN);
   hx711_galga_3.begin(HUMPAD3_DOUT_PIN,HUMPAD3_SCK_PIN);
}

void loop(){
  int contador_toques=0;
  
  while (digitalRead(TTP223B)==HIGH){ //encendido del sistema inicialmente apagado
    Serial.println("\nLeyendo cantidad de toques del usuario...");
    contador_toques=contador_toques+1; //contando el tiempo cada dos segundos
    delay(2000); //presionar durante 2 segundos para activar el sistema
    Serial.print(contador_toques);
  }
  if (contador_toques==1){ 
  
    while(contador_toques==1){ //activacion de un "loop" del sistema encendido
      int contador_toques_2=0;
      Serial.println("\nEl sistema ha sido encendido...");
      digitalWrite(LED,HIGH);
      delay(1000);
//Tomado de lecturas de las galgas
      if(hx711_galga_1.is_ready()){
    long reading_galga_1 = hx711_galga_1.read();
    Serial.print("HX711 2 reading: ");
    Serial.println(reading_galga_1);
  }
  else{
    
  }
  if(hx711_galga_2.is_ready()){
    long reading_galga_2 = hx711_galga_2.read();
    Serial.print("HX711 2 reading: ");
    Serial.println(reading_galga_2);
  }
  else{
    
  }
  if(hx711_galga_3.is_ready()){
    long reading_galga_3 = hx711_galga_3.read();
    Serial.print("HX711 3 reading: ");
    Serial.println(reading_galga_3);
  }
  else{
    
  }
  /*
  
  fuerza_sensada_HP_1 = !FACTOR DE CONVERSIÓN*! * reading_galga_1;
  fuerza_sensada_HP_2 = !FACTOR DE CONVERSIÓN*! * reading_galga_2;
  fuerza_sensada_HP_3 = !FACTOR DE CONVERSIÓN*! * reading_galga_3;
  
  NOTA!!! : !FACTOR DE CONVERSIÓN*! --> Este valor puede ser obtenido por medio de otra librería
  que nos permite calibrar justamente para obtener el factor de conversión para obtener el peso
  y en todo caso, probar de manera experimental si nos da la fuerza aplicada en el sistema para
  poder dejarlo ahí, o hacer un factor de conversión de gravedad para lograr medir fuerzas en Newtons

  - Lo que se vio es que requieren rangos de 100 N, y sensado a masa sería de 10kG de sensado
  
  */

//Termina el sensado en cad loop y si hay uno que no no este en los rangos se procederá a ajustar el que esté más cerca en el código

      //----------Espacio para el ajuste automático-----------------------------------------------------------------------------

//Ajuste del dial 1
      if (fuerza_sensada_HP_1<= (95/100)*fuerza_ideal_HP_1 || fuerza_sensada_HP_1>= (105/100)*fuerza_ideal_HP_1 ){
        while(fuerza_sensada_HP_1<= (95/100)*fuerza_ideal_HP_1 || fuerza_sensada_HP_1>= (105/100)*fuerza_ideal_HP_1){
          if (fuerza_sensada_HP_1<= (95/100)*fuerza_ideal_HP_1){
            activar_dial_1();
            ajuste_automático(pinesDIAL1,adelante,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL1);
            fuerza_sensada_HP_1=sensado_de_fuerzas_D1(galga1);
            delay(500);
          }
          if (fuerza_sensada_HP_1>= (105/100)*fuerza_ideal_HP_1)){
            activar_dial_1();
            ajuste_automático(pinesDIAL1,atras,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL1);
            fuerza_sensada_HP_1=sensado_de_fuerzas_D1(galga1);
            delay(500);
          }
        }
        
       desactivar_dial_1();
      }
//Ajuste del dial 2
      if (fuerza_sensada_HP_2<= (95/100)*fuerza_ideal_HP_2 || fuerza_sensada_HP_2>= (105/100)*fuerza_ideal_HP_2 ){
        while(fuerza_sensada_HP_2<= (95/100)*fuerza_ideal_HP_2 || fuerza_sensada_HP_2>= (105/100)*fuerza_ideal_HP_2){
          if (fuerza_sensada_HP_2<= (95/100)*fuerza_ideal_HP_2){
            activar_dial_2();
            ajuste_automático(pinesDIAL2,adelante,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL2);
            fuerza_sensada_HP_2=sensado_de_fuerzas_D2(galga2);
            delay(500);
          }
          if (fuerza_sensada_HP_2>= (105/100)*fuerza_ideal_HP_2)){
            activar_dial_2();
            ajuste_automático(pinesDIAL2,atras,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL2);
            fuerza_sensada_HP_2=sensado_de_fuerzas_D2(galga2);
            delay(500);
          }
        }
        
       desactivar_dial_2();
      }
//Ajuste del dial 3
      if (fuerza_sensada_HP_3<= (95/100)*fuerza_ideal_HP_3 || fuerza_sensada_HP_3>= (105/100)*fuerza_ideal_HP_3 ){
        while(fuerza_sensada_HP_3<= (95/100)*fuerza_ideal_HP_3 || fuerza_sensada_HP_3>= (105/100)*fuerza_ideal_HP_3){
          if (fuerza_sensada_HP_3<= (95/100)*fuerza_ideal_HP_3){
            activar_dial_3();
            ajuste_automático(pinesDIAL3,adelante,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL3);
            fuerza_sensada_HP_3=sensado_de_fuerzas_D3(galga3);
            delay(500);
          }
          if (fuerza_sensada_HP_3>= (105/100)*fuerza_ideal_HP_3)){
            activar_dial_3();
            ajuste_automático(pinesDIAL3,atras,500);
            delay(waitTime);
            parar_giro_del_dial (pinesDIAL3);
            fuerza_sensada_HP_3=sensado_de_fuerzas_D3(galga3);
            delay(500);
          }
        }
        
       desactivar_dial_3();
      }

//Fin de la parte del ajuste
      //----------------------------------------------------------------------------------------------------------------------------
     //En esta sección se verá si se está presionando para que se desactive el sistema 
        while (digitalRead(TTP223B)==HIGH){ //iniciar un contador para salir del sistema y apagarlo
      Serial.println("\nLeyendo cantidad de toques del usuario...");
      contador_toques_2=contador_toques_2+1;
      delay(2000);
      Serial.print(contador_toques_2);
    }
      if (contador_toques_2==2){
      
        break; //si presiona 4 segundos se rompe el bucle y sale para apagar
        }
    }
      
      ESTADO=digitalRead(LED);
      digitalWrite(LED,!ESTADO);
      
      
      while(digitalRead(TTP223B)==LOW){ //se mantiene en el low hasta que se encienda de nuevo
        Serial.println("\nEl sistema ha sido apagado");
        delay(1000);
      } 
  
}
}

//-------------Espacio de definición de funciones-------------------

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
