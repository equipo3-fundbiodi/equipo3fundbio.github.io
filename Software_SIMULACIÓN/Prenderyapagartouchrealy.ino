

volatile int interruptCounter;
volatile bool flag_monitor3;
int totalInterruptCounter;



//definir variables
const int M_rele = 0;      //salida rele on/off
const int M_rele1 = 2;      //salida rele on/off
const int Touch = 1;       //entrada pulsador

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
  // Configura as portas como salidas
  pinMode(M_rele, OUTPUT);
  pinMode(M_rele1, OUTPUT);
  // Configura as portas como entrada
  pinMode(Touch, INPUT);
  
  
}
//***********************************************************************************************
//***********************************************************************************************
//*********************** Programa principal    *************************************************
void loop() 
{
  Control_onoff();
  
}
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
