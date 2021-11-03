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

const int pinesDIAL1[3] = {pinPMWD1,pinD1IN2,pinD1IN1};
const int pinesDIAL2[3] = {pinPMWD2,pinD2IN2,pinD2IN1};
const int pinesDIAL3[3] = {pinPMWD3,pinD3IN2,pinD3IN1};

enum moveDirection {
   adelante,
   atras
};
enum turnDirection {
   horario,
   antihorario
};
enum selectorDial {
  DIAL1,
  DIAL2,
  DIAL3,
  }

void setup() {
  
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

}

void loop() {
  
  activar_dial_1();
  ajuste_automático(pinesDIAL1,adelante,500);
  delay(waitTime);

}

void activar_dial_1(){
  digitalWrite(SDTBY_D1,HIGH);
  }
void activar_dial_2(){
  digitalWrite(SDTBY_D2,HIGH);
  }
void activar_dial_3(){
  digitalWrite(SDTBY_D3,HIGH);
  }

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
void mover_motor_atras (const int DIAL[3], int velocidad){
  digitalWrite(DIAL[1],LOW);
  digitalWrite(DIAL[2],HIGH);
  analogWrite(DIAL[0],500);
  }
void parar_giro_del_dial (const int DIAL[3]){
  digitalWrite(DIAL[1],LOW);
  digitalWrite(DIAL[2],LOW);
  analogWrite(DIAL[0],0);
  }
