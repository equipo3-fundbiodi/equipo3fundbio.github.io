#include "HX711.h" //incluir la librería del HX711
#include "math.h" //math para potenciación
  const int HUMPAD1_DOUT_PIN = 5; 
  const int HUMPAD1_SCK_PIN = 14;
 

HX711 hx711_galga_1; // definición del objeto HX711


void setup() {
  
  Serial.begin(9600);
  hx711_galga_1.begin(HUMPAD1_DOUT_PIN,HUMPAD1_SCK_PIN); 
 
}

void loop() {
  if(hx711_galga_1.is_ready()){
    
    long reading_galga_1 = hx711_galga_1.read()/(-142.17)-479; // dividimos nuestro valor sensado entre el factor de conversión y le restamos una "tara"
    
    Serial.print("Lectura en gramos: ");
    Serial.print(reading_galga_1); //hacemos la lectura en gramos
    delay (1000);
    Serial.print("   Lectura en newtons: ");
    Serial.print(reading_galga_1*pow(10,-3)*(9.807)); // damos la lectura transformada en newtons, dado que la calibración
                                                      // arroja para valores de masa, lo convertiremos multiplicando por la gravedad
                                                      // se corrobora experimentalmente que se llega a valores proximos de 9.807 N para 1Kg
    Serial.print("\n");
    delay (1000);
  }
  else{
    
  }
 
 
}
