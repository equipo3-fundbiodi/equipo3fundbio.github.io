#include "HX711.h"

  const int HUMPAD1_DOUT_PIN = 5;
  const int HUMPAD1_SCK_PIN = 8;
  const int HUMPAD2_DOUT_PIN = 41;
  const int HUMPAD2_SCK_PIN = 40;
  const int HUMPAD3_DOUT_PIN = 42;
  const int HUMPAD3_SCK_PIN = 27;

HX711 hx711_galga_1;
HX711 hx711_galga_2;
HX711 hx711_galga_3;

void setup() {
  
  Serial.begin(9600);
  hx711_galga_1.begin(HUMPAD1_DOUT_PIN,HUMPAD1_SCK_PIN);
  hx711_galga_2.begin(HUMPAD2_DOUT_PIN,HUMPAD2_SCK_PIN);
  hx711_galga_3.begin(HUMPAD3_DOUT_PIN,HUMPAD3_SCK_PIN);
  
}

void loop() {
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
}
