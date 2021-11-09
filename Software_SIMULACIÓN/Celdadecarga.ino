

#include "HX711.h"
#include "math.h"
  const int HUMPAD1_DOUT_PIN = 5;
  const int HUMPAD1_SCK_PIN = 14;
 

HX711 hx711_galga_1;


void setup() {
  
  Serial.begin(9600);
  hx711_galga_1.begin(HUMPAD1_DOUT_PIN,HUMPAD1_SCK_PIN);
 
}

void loop() {
  if(hx711_galga_1.is_ready()){
    long reading_galga_1 = hx711_galga_1.read()/(-142.17)-479;
    
    Serial.print("Lectura en gramos: ");
    Serial.print(reading_galga_1);
    delay (1000);
    Serial.print("   Lectura en newtons: ");
    Serial.print(reading_galga_1*pow(10,-3)*(9.807));
    Serial.print("\n");
    delay (1000);
  }
  else{
    
  }
 
 
}
