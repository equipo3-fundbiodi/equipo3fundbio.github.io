#include <RTClib.h>
#include <Wire.h>
#include <math.h>
RTC_DS3231 rtc;
int hora_i, minutos_i, segundo_i,contador=1;
int hora_f, minutos_f, segundo_f;
int tiempo_inicial_segundos, tiempo_final_segundos,resta_de_tiempo,horas_de_uso;
double minutos_de_uso, horas_de_uso_double,diferencia_decimal_de_horas,conversion_minutos;
void setup() {
  Serial.begin(9600);

  if(! rtc.begin()) {
    Serial.println("Modulo RTC no encontrado !");
    while(1);
  }
  rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  DateTime fecha= rtc.now();
  
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(" ");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.print(fecha.second());
  
   hora_i=fecha.hour();
   minutos_i=fecha.minute();
   segundo_i=fecha.second();

   while(contador<=16){
   
    hora_f++;
    minutos_f++;
    segundo_f++;
    contador++;
   }

   tiempo_inicial_segundos= segundo_i+ (60*minutos_i)+(3600*hora_i);
   tiempo_final_segundos=segundo_f+ (60*minutos_f)+(3600*hora_f);
   resta_de_tiempo=tiempo_final_segundos-tiempo_inicial_segundos;
   
   horas_de_uso=resta_de_tiempo/3600;
   horas_de_uso_double=resta_de_tiempo/3600.0;
   diferencia_decimal_de_horas=horas_de_uso_double-horas_de_uso;
   conversion_minutos= (60*diferencia_decimal_de_horas);
   Serial.print("\nLas horas de uso son:");
   Serial.print(horas_de_uso);
   Serial.print("\nLos minutos de uso double son:");
   Serial.print((int)conversion_minutos);

  delay(1000);
}
