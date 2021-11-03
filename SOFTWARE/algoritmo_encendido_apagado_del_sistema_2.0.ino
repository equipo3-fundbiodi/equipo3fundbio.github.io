int TTP223B=5;
int LED=4;
int ESTADO = LOW;
int contador_toques=0;

void setup(){
  
  pinMode(TTP223B, INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
 
}

void loop(){
  int contador_toques=0;
  while (digitalRead(TTP223B)==HIGH){
    Serial.println("\nLeyendo cantidad de toques del usuario...");
    contador_toques=contador_toques+1;
    delay(2000);
    Serial.print(contador_toques);
  }
  if (contador_toques==1){
  
    while(contador_toques==1){
      int contador_toques_2=0;
      Serial.println("\nEl sistema ha sido encendido...");
      digitalWrite(LED,HIGH);
      delay(1000);
      
        while (digitalRead(TTP223B)==HIGH){
      Serial.println("\nLeyendo cantidad de toques del usuario...");
      contador_toques_2=contador_toques_2+1;
      delay(2000);
      Serial.print(contador_toques_2);
    }
      if (contador_toques_2==2){
      
        break;
        }
    }
      
      ESTADO=digitalRead(LED);
      digitalWrite(LED,!ESTADO);
      
      
      while(digitalRead(TTP223B)==LOW){
        Serial.println("\nEl sistema ha sido apagado");
        delay(1000);
      } 
  
}
}
