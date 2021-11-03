EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP32-WROOM-32 U1
U 1 1 618066D0
P 3700 3550
F 0 "U1" H 3700 5131 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 3700 5040 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3700 2050 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 3400 3600 50  0001 C CNN
	1    3700 3550
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:TB6612FNG U2
U 1 1 61807C99
P 5550 5850
F 0 "U2" H 5550 4761 50  0000 C CNN
F 1 "TB6612FNG" H 5550 4670 50  0000 C CNN
F 2 "Package_SO:SSOP-24_5.3x8.2mm_P0.65mm" H 6850 4950 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/us/product/linear/motordriver/detail.TB6612FNG.html" H 6000 6450 50  0001 C CNN
	1    5550 5850
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC M1
U 1 1 618090F1
P 7000 5500
F 0 "M1" H 7158 5496 50  0000 L CNN
F 1 "Motor_DC" H 7158 5405 50  0000 L CNN
F 2 "" H 7000 5410 50  0001 C CNN
F 3 "~" H 7000 5410 50  0001 C CNN
	1    7000 5500
	1    0    0    -1  
$EndComp
$Comp
L hx711:HX711 U?
U 1 1 6182662F
P 5850 2950
F 0 "U?" H 5850 3200 50  0001 C CNN
F 1 "HX711" H 5850 3233 50  0000 C CNN
F 2 "Sensor:SHT1x" H 5850 3200 50  0001 C CNN
F 3 "Transmisor de celda" H 5850 3200 50  0001 C CNN
	1    5850 2950
	-1   0    0    -1  
$EndComp
$Comp
L ttp223:TTP223 U?
U 1 1 618289E9
P 2100 2500
F 0 "U?" H 2100 2700 50  0001 C CNN
F 1 "TTP223" H 2042 2177 50  0000 C CNN
F 2 "Sensor_Pressure:Freescale_98ARH99089A" H 2100 2700 50  0001 C CNN
F 3 "Sensor Touch" H 2100 2700 50  0001 C CNN
	1    2100 2500
	-1   0    0    1   
$EndComp
$Comp
L galgaextensiometrica:GalgaExtensiometrica U?
U 1 1 6182C710
P 7200 2700
F 0 "U?" H 7150 3050 50  0001 C CNN
F 1 "GalgaExtensiometrica" H 7528 2705 50  0000 L CNN
F 2 "Sensor_Pressure:Freescale_98ARH99089A" H 7150 3050 50  0001 C CNN
F 3 "Sensor de presion" H 7150 3050 50  0001 C CNN
	1    7200 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61830EDD
P 2450 2650
F 0 "#PWR?" H 2450 2400 50  0001 C CNN
F 1 "GND" H 2455 2477 50  0000 C CNN
F 2 "" H 2450 2650 50  0001 C CNN
F 3 "" H 2450 2650 50  0001 C CNN
	1    2450 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 5450 6800 5300
Wire Wire Line
	6800 5300 7000 5300
Wire Wire Line
	6150 5450 6800 5450
Wire Wire Line
	7000 5800 6800 5800
Wire Wire Line
	6800 5800 6800 5650
Wire Wire Line
	6150 5650 6800 5650
Wire Wire Line
	6800 2600 6550 2600
Wire Wire Line
	6550 2600 6550 2800
Wire Wire Line
	6550 2800 6200 2800
Wire Wire Line
	6200 2900 6800 2900
Wire Wire Line
	6800 2750 6650 2750
Wire Wire Line
	6650 2750 6650 3000
Wire Wire Line
	6650 3000 6200 3000
Wire Wire Line
	6200 3100 6450 3100
Wire Wire Line
	6450 3100 6450 2500
Wire Wire Line
	6450 2500 6800 2500
$Comp
L power:GND #PWR?
U 1 1 6183C3AC
P 5350 3150
F 0 "#PWR?" H 5350 2900 50  0001 C CNN
F 1 "GND" H 5355 2977 50  0000 C CNN
F 2 "" H 5350 3150 50  0001 C CNN
F 3 "" H 5350 3150 50  0001 C CNN
	1    5350 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6185C57A
P 3700 4950
F 0 "#PWR?" H 3700 4700 50  0001 C CNN
F 1 "GND" H 3705 4777 50  0000 C CNN
F 2 "" H 3700 4950 50  0001 C CNN
F 3 "" H 3700 4950 50  0001 C CNN
	1    3700 4950
	1    0    0    -1  
$EndComp
Text Label 7450 7500 0    50   ~ 0
Esquema_electrónico_del_proyecto_de_Biodiseño
Text Label 8200 7650 0    50   ~ 0
1-11-21
$Comp
L Relay:DIPxx-1Cxx-51x K
U 1 1 61873CAC
P 2000 5950
F 0 "K" H 2430 5996 50  0000 L CNN
F 1 "DIPxx-1Cxx-51x" H 2430 5905 50  0000 L CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 2450 5900 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 2000 5950 50  0001 C CNN
	1    2000 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6250 1200 6250
$Comp
L power:+5V #PWR?
U 1 1 61881273
P 1200 6250
F 0 "#PWR?" H 1200 6100 50  0001 C CNN
F 1 "+5V" H 1215 6423 50  0000 C CNN
F 2 "" H 1200 6250 50  0001 C CNN
F 3 "" H 1200 6250 50  0001 C CNN
	1    1200 6250
	1    0    0    -1  
$EndComp
$Comp
L convertidordc-dc:ConvertidorDC-DC U?
U 1 1 6188848C
P 3750 5950
F 0 "U?" H 3750 6200 50  0001 C CNN
F 1 "ConvertidorDC-DC" H 3775 6173 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_RECOM_R-78B-2.0_THT" H 3750 6200 50  0001 C CNN
F 3 "dcdc" H 3750 6200 50  0001 C CNN
	1    3750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6250 2650 6250
Wire Wire Line
	2650 6250 2650 5900
$Comp
L lectormicrosd:LectorMicroSD U?
U 1 1 6189CBBD
P 5650 4100
F 0 "U?" H 5650 4500 50  0001 C CNN
F 1 "LectorMicroSD" H 6078 4105 50  0000 L CNN
F 2 "Transformer_SMD:Pulse_PA2005NL" H 5650 4500 50  0001 C CNN
F 3 "Modulo Lector Micro SD" H 5650 4500 50  0001 C CNN
	1    5650 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4250 4650 4250
$Comp
L power:+3.3V #PWR?
U 1 1 618AD3A0
P 4650 3500
F 0 "#PWR?" H 4650 3350 50  0001 C CNN
F 1 "+3.3V" H 4665 3673 50  0000 C CNN
F 2 "" H 4650 3500 50  0001 C CNN
F 3 "" H 4650 3500 50  0001 C CNN
	1    4650 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 618ADC85
P 5000 4450
F 0 "#PWR?" H 5000 4200 50  0001 C CNN
F 1 "GND" H 5005 4277 50  0000 C CNN
F 2 "" H 5000 4450 50  0001 C CNN
F 3 "" H 5000 4450 50  0001 C CNN
	1    5000 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4350 5000 4350
Wire Wire Line
	5000 4350 5000 4450
Wire Wire Line
	1800 4050 1800 5650
Wire Wire Line
	1800 4050 3100 4050
$Comp
L power:GND #PWR?
U 1 1 618B90E0
P 5250 6850
F 0 "#PWR?" H 5250 6600 50  0001 C CNN
F 1 "GND" H 5255 6677 50  0000 C CNN
F 2 "" H 5250 6850 50  0001 C CNN
F 3 "" H 5250 6850 50  0001 C CNN
	1    5250 6850
	0    1    1    0   
$EndComp
Wire Wire Line
	5650 4850 5650 4750
Wire Wire Line
	5650 4750 4500 4750
Wire Wire Line
	4500 4750 4500 5550
Wire Wire Line
	4200 6000 4300 6000
Wire Wire Line
	4300 6000 4300 6150
$Comp
L power:GND #PWR?
U 1 1 618BDE17
P 4300 6150
F 0 "#PWR?" H 4300 5900 50  0001 C CNN
F 1 "GND" H 4305 5977 50  0000 C CNN
F 2 "" H 4300 6150 50  0001 C CNN
F 3 "" H 4300 6150 50  0001 C CNN
	1    4300 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4350 4800 4350
Wire Wire Line
	4800 4350 4800 5650
Wire Wire Line
	4800 5650 4950 5650
Wire Wire Line
	4300 4450 4750 4450
Wire Wire Line
	4750 4450 4750 5950
Wire Wire Line
	4750 5950 4950 5950
Wire Wire Line
	4950 6050 4700 6050
Wire Wire Line
	4700 6050 4700 4550
Wire Wire Line
	4700 4550 4300 4550
Wire Wire Line
	5500 3000 5050 3000
Wire Wire Line
	5050 3000 5050 1850
Wire Wire Line
	5050 1850 2900 1850
Wire Wire Line
	2900 1850 2900 3950
Wire Wire Line
	2900 3950 3100 3950
Wire Wire Line
	5350 3100 5350 3150
Wire Wire Line
	2400 2450 2550 2450
$Comp
L power:+3.3V #PWR?
U 1 1 618D13A7
P 2550 1750
F 0 "#PWR?" H 2550 1600 50  0001 C CNN
F 1 "+3.3V" H 2565 1923 50  0000 C CNN
F 2 "" H 2550 1750 50  0001 C CNN
F 3 "" H 2550 1750 50  0001 C CNN
	1    2550 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2550 2450 2550
Wire Wire Line
	2450 2550 2450 2650
Wire Wire Line
	4500 5550 2300 5550
Wire Wire Line
	2300 5550 2300 5650
$Comp
L Device:Battery 7.4V
U 1 1 618E1826
P 2900 6400
F 0 "7.4V" H 3008 6446 50  0000 L CNN
F 1 "Battery" H 3008 6355 50  0000 L CNN
F 2 "" V 2900 6460 50  0001 C CNN
F 3 "~" V 2900 6460 50  0001 C CNN
	1    2900 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 5900 2900 5900
Wire Wire Line
	3350 6600 2900 6600
Wire Wire Line
	3350 6000 3350 6600
Wire Wire Line
	2900 6200 2900 5900
Connection ~ 2900 5900
Wire Wire Line
	2900 5900 3350 5900
$Comp
L power:GND #PWR?
U 1 1 618EBD5A
P 2900 6600
F 0 "#PWR?" H 2900 6350 50  0001 C CNN
F 1 "GND" H 2905 6427 50  0000 C CNN
F 2 "" H 2900 6600 50  0001 C CNN
F 3 "" H 2900 6600 50  0001 C CNN
	1    2900 6600
	1    0    0    -1  
$EndComp
Connection ~ 2900 6600
Wire Wire Line
	3700 1650 3700 2150
$Comp
L power:+5V #PWR?
U 1 1 618EE90A
P 3700 1650
F 0 "#PWR?" H 3700 1500 50  0001 C CNN
F 1 "+5V" H 3715 1823 50  0000 C CNN
F 2 "" H 3700 1650 50  0001 C CNN
F 3 "" H 3700 1650 50  0001 C CNN
	1    3700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4050 4450 4050
Wire Wire Line
	4450 4050 4450 3950
Wire Wire Line
	4450 3950 4300 3950
Wire Wire Line
	5150 4150 4500 4150
Wire Wire Line
	4500 4150 4500 3650
Wire Wire Line
	4500 3650 4300 3650
Wire Wire Line
	5150 3950 4550 3950
Wire Wire Line
	4550 3950 4550 3550
Wire Wire Line
	4550 3550 4300 3550
Wire Wire Line
	4300 2550 4750 2550
Wire Wire Line
	4750 2550 4750 3850
Wire Wire Line
	5150 3850 4750 3850
Wire Wire Line
	5500 2900 4950 2900
Wire Wire Line
	4950 1900 3050 1900
Wire Wire Line
	3050 1900 3050 3550
Wire Wire Line
	3050 3550 3100 3550
Wire Wire Line
	4300 2350 4400 2350
Wire Wire Line
	4400 2350 4400 2150
Wire Wire Line
	2700 2150 2700 2350
Wire Wire Line
	2700 2350 2400 2350
Wire Wire Line
	2700 2150 3700 2150
$Comp
L Device:CP 100uF
U 1 1 61920888
P 6250 4900
F 0 "100uF" H 6368 4946 50  0000 L CNN
F 1 "C2" H 6368 4855 50  0000 L CNN
F 2 "" H 6288 4750 50  0001 C CNN
F 3 "~" H 6250 4900 50  0001 C CNN
	1    6250 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 4750 5650 4750
Connection ~ 5650 4750
$Comp
L power:GND #PWR?
U 1 1 6192A840
P 6250 5050
F 0 "#PWR?" H 6250 4800 50  0001 C CNN
F 1 "GND" H 6255 4877 50  0000 C CNN
F 2 "" H 6250 5050 50  0001 C CNN
F 3 "" H 6250 5050 50  0001 C CNN
	1    6250 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1650 4100 1650
Connection ~ 3700 1650
$Comp
L Device:C 0.1uF
U 1 1 6192D6C2
P 4250 1650
F 0 "0.1uF" V 3998 1650 50  0000 C CNN
F 1 "C1 " V 4089 1650 50  0000 C CNN
F 2 "" H 4288 1500 50  0001 C CNN
F 3 "~" H 4250 1650 50  0001 C CNN
	1    4250 1650
	0    1    1    0   
$EndComp
Text Label 4300 1550 0    50   ~ 0
Ceramico
Text Label 6350 5050 0    50   ~ 0
Electrolítico
$Comp
L Device:C 0.1uF
U 1 1 6193E975
P 2300 1900
F 0 "0.1uF" V 2048 1900 50  0000 C CNN
F 1 "C3" V 2139 1900 50  0000 C CNN
F 2 "" H 2338 1750 50  0001 C CNN
F 3 "~" H 2300 1900 50  0001 C CNN
	1    2300 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 1750 2550 1900
Wire Wire Line
	2450 1900 2550 1900
Connection ~ 2550 1900
Wire Wire Line
	2550 1900 2550 2450
$Comp
L power:GND #PWR?
U 1 1 6194C51E
P 1850 1900
F 0 "#PWR?" H 1850 1650 50  0001 C CNN
F 1 "GND" H 1855 1727 50  0000 C CNN
F 2 "" H 1850 1900 50  0001 C CNN
F 3 "" H 1850 1900 50  0001 C CNN
	1    1850 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 1900 1850 1900
$Comp
L Device:C 0.1uF
U 1 1 6194F9CC
P 5150 3550
F 0 "0.1uF" V 4898 3550 50  0000 C CNN
F 1 "C4" V 4989 3550 50  0000 C CNN
F 2 "" H 5188 3400 50  0001 C CNN
F 3 "~" H 5150 3550 50  0001 C CNN
	1    5150 3550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61950252
P 5550 3550
F 0 "#PWR?" H 5550 3300 50  0001 C CNN
F 1 "GND" H 5555 3377 50  0000 C CNN
F 2 "" H 5550 3550 50  0001 C CNN
F 3 "" H 5550 3550 50  0001 C CNN
	1    5550 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3550 5300 3550
Wire Wire Line
	5000 3550 4650 3550
Wire Wire Line
	4650 3500 4650 3550
Connection ~ 4650 3550
$Comp
L Device:C 0.1uF
U 1 1 61964B65
P 5800 2300
F 0 "0.1uF" V 5548 2300 50  0000 C CNN
F 1 "C5" V 5639 2300 50  0000 C CNN
F 2 "" H 5838 2150 50  0001 C CNN
F 3 "~" H 5800 2300 50  0001 C CNN
	1    5800 2300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61965062
P 6100 2300
F 0 "#PWR?" H 6100 2050 50  0001 C CNN
F 1 "GND" H 6105 2127 50  0000 C CNN
F 2 "" H 6100 2300 50  0001 C CNN
F 3 "" H 6100 2300 50  0001 C CNN
	1    6100 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2300 6100 2300
Wire Wire Line
	5650 2300 5500 2300
Wire Wire Line
	5500 2300 5500 2800
$Comp
L power:+3.3V #PWR?
U 1 1 6197A812
P 5500 2300
F 0 "#PWR?" H 5500 2150 50  0001 C CNN
F 1 "+3.3V" H 5515 2473 50  0000 C CNN
F 2 "" H 5500 2300 50  0001 C CNN
F 3 "" H 5500 2300 50  0001 C CNN
	1    5500 2300
	1    0    0    -1  
$EndComp
Connection ~ 5500 2300
Wire Wire Line
	4350 5900 4350 5850
Wire Wire Line
	4200 5900 4350 5900
$Comp
L power:+5V #PWR?
U 1 1 6198359B
P 4350 5850
F 0 "#PWR?" H 4350 5700 50  0001 C CNN
F 1 "+5V" H 4365 6023 50  0000 C CNN
F 2 "" H 4350 5850 50  0001 C CNN
F 3 "" H 4350 5850 50  0001 C CNN
	1    4350 5850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 619842CA
P 5250 4650
F 0 "#PWR?" H 5250 4500 50  0001 C CNN
F 1 "+3.3V" H 5265 4823 50  0000 C CNN
F 2 "" H 5250 4650 50  0001 C CNN
F 3 "" H 5250 4650 50  0001 C CNN
	1    5250 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C 0.1uF
U 1 1 61987F8F
P 5500 4650
F 0 "0.1uF" V 5248 4650 50  0000 C CNN
F 1 "C6" V 5339 4650 50  0000 C CNN
F 2 "" H 5538 4500 50  0001 C CNN
F 3 "~" H 5500 4650 50  0001 C CNN
	1    5500 4650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6198B93F
P 5650 4650
F 0 "#PWR?" H 5650 4400 50  0001 C CNN
F 1 "GND" V 5655 4522 50  0000 R CNN
F 2 "" H 5650 4650 50  0001 C CNN
F 3 "" H 5650 4650 50  0001 C CNN
	1    5650 4650
	0    -1   1    0   
$EndComp
Wire Wire Line
	5350 4650 5250 4650
Wire Wire Line
	5250 4650 5250 4850
Connection ~ 5250 4650
Connection ~ 3700 2150
Wire Wire Line
	3700 2150 4400 2150
Text Label 1450 2800 0    50   ~ 0
Sensor_Touch_Capacitivo
Text Label 5250 7150 0    50   ~ 0
Driver_motor_DC
Text Label 1750 6450 0    50   ~ 0
Relay_ON|OFF
Text Label 5500 3300 0    50   ~ 0
Transmisor_serie_de_celda
Text Label 7650 2850 0    50   ~ 0
Tipo_Puente_Wheatstone
Text Label 7500 7250 0    50   ~ 0
Grupo_3
$Comp
L hx711:HX711 U?
U 1 1 6182DAE9
P 6700 1750
F 0 "U?" H 6700 2000 50  0001 C CNN
F 1 "HX711" H 6700 2033 50  0000 C CNN
F 2 "Sensor:SHT1x" H 6700 2000 50  0001 C CNN
F 3 "Transmisor de celda" H 6700 2000 50  0001 C CNN
	1    6700 1750
	-1   0    0    -1  
$EndComp
$Comp
L hx711:HX711 U?
U 1 1 6182EA1C
P 6700 1050
F 0 "U?" H 6700 1300 50  0001 C CNN
F 1 "HX711" H 6700 1333 50  0000 C CNN
F 2 "Sensor:SHT1x" H 6700 1300 50  0001 C CNN
F 3 "Transmisor de celda" H 6700 1300 50  0001 C CNN
	1    6700 1050
	-1   0    0    -1  
$EndComp
$Comp
L galgaextensiometrica:GalgaExtensiometrica U?
U 1 1 6182F2EB
P 7900 1000
F 0 "U?" H 7850 1350 50  0001 C CNN
F 1 "GalgaExtensiometrica" H 8228 1005 50  0000 L CNN
F 2 "Sensor_Pressure:Freescale_98ARH99089A" H 7850 1350 50  0001 C CNN
F 3 "Sensor de presion" H 7850 1350 50  0001 C CNN
	1    7900 1000
	1    0    0    -1  
$EndComp
$Comp
L galgaextensiometrica:GalgaExtensiometrica U?
U 1 1 6183018F
P 7900 1800
F 0 "U?" H 7850 2150 50  0001 C CNN
F 1 "GalgaExtensiometrica" H 8228 1805 50  0000 L CNN
F 2 "Sensor_Pressure:Freescale_98ARH99089A" H 7850 2150 50  0001 C CNN
F 3 "Sensor de presion" H 7850 2150 50  0001 C CNN
	1    7900 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 800  7300 800 
Wire Wire Line
	7300 800  7300 1200
Wire Wire Line
	7300 1200 7050 1200
Wire Wire Line
	7050 1100 7400 1100
Wire Wire Line
	7400 1100 7400 1050
Wire Wire Line
	7400 1050 7500 1050
Wire Wire Line
	7500 900  7050 900 
Wire Wire Line
	7450 1000 7450 1200
Wire Wire Line
	7450 1200 7500 1200
Wire Wire Line
	7050 1000 7450 1000
Wire Wire Line
	7500 1600 7200 1600
Wire Wire Line
	7200 1600 7200 1900
Wire Wire Line
	7200 1900 7050 1900
Wire Wire Line
	7050 1800 7400 1800
Wire Wire Line
	7400 1800 7400 1850
Wire Wire Line
	7400 1850 7500 1850
Wire Wire Line
	7500 2000 7300 2000
Wire Wire Line
	7300 2000 7300 1700
Wire Wire Line
	7300 1700 7050 1700
Wire Wire Line
	7050 1600 7100 1600
Wire Wire Line
	7100 1600 7100 1650
Wire Wire Line
	7100 1650 7500 1650
Wire Wire Line
	7500 1650 7500 1700
Wire Wire Line
	6350 1000 5150 1000
Wire Wire Line
	5150 1000 5150 2850
Wire Wire Line
	5150 2850 4300 2850
Wire Wire Line
	6350 1100 5250 1100
Wire Wire Line
	5250 1100 5250 2950
Wire Wire Line
	5250 2950 4300 2950
Wire Wire Line
	5300 3050 4300 3050
Wire Wire Line
	5350 3100 5500 3100
$Comp
L power:GND #PWR?
U 1 1 6188F55D
P 4400 1650
F 0 "#PWR?" H 4400 1400 50  0001 C CNN
F 1 "GND" V 4405 1522 50  0000 R CNN
F 2 "" H 4400 1650 50  0001 C CNN
F 3 "" H 4400 1650 50  0001 C CNN
	1    4400 1650
	0    -1   1    0   
$EndComp
Wire Wire Line
	6350 1700 4950 1700
Wire Wire Line
	4950 3250 4300 3250
Wire Wire Line
	4950 1700 4950 1900
Connection ~ 4950 1900
Wire Wire Line
	4950 1900 4950 2900
Connection ~ 4950 2900
Wire Wire Line
	4950 2900 4950 3250
Wire Wire Line
	5000 3350 5000 1800
Wire Wire Line
	5000 1800 6350 1800
$Comp
L Driver_Motor:TB6612FNG U?
U 1 1 618B7099
P 8050 4450
F 0 "U?" H 8050 3361 50  0000 C CNN
F 1 "TB6612FNG" H 8050 3270 50  0000 C CNN
F 2 "Package_SO:SSOP-24_5.3x8.2mm_P0.65mm" H 9350 3550 50  0001 C CNN
F 3 "https://toshiba.semicon-storage.com/us/product/linear/motordriver/detail.TB6612FNG.html" H 8500 5050 50  0001 C CNN
	1    8050 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3950 8800 3950
Wire Wire Line
	8800 3950 8800 4050
Wire Wire Line
	8800 4050 8650 4050
Wire Wire Line
	8650 4250 8800 4250
Wire Wire Line
	8800 4250 8800 4450
Wire Wire Line
	8800 4450 9150 4450
$Comp
L Motor:Motor_DC M2
U 1 1 618CC775
P 6700 6150
F 0 "M2" H 6858 6146 50  0000 L CNN
F 1 "Motor_DC" H 6858 6055 50  0000 L CNN
F 2 "" H 6700 6060 50  0001 C CNN
F 3 "~" H 6700 6060 50  0001 C CNN
	1    6700 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5950 6700 5950
Wire Wire Line
	6150 6150 6300 6150
Wire Wire Line
	6300 6150 6300 6450
Wire Wire Line
	6300 6450 6700 6450
Wire Wire Line
	4950 5450 4950 4300
Wire Wire Line
	4950 4300 4300 4300
Wire Wire Line
	4300 4300 4300 4250
Wire Wire Line
	4650 3550 4650 4250
Wire Wire Line
	4950 6150 4650 6150
Wire Wire Line
	4650 6150 4650 4400
Wire Wire Line
	4650 4400 4550 4400
Wire Wire Line
	4550 4400 4550 4250
Wire Wire Line
	4550 4250 4350 4250
Wire Wire Line
	4350 4250 4350 4150
Wire Wire Line
	4350 4150 4300 4150
Wire Wire Line
	4950 6250 4600 6250
Wire Wire Line
	4600 6250 4600 4200
Wire Wire Line
	4600 4200 4400 4200
Wire Wire Line
	4400 4200 4400 4050
Wire Wire Line
	4400 4050 4300 4050
Wire Wire Line
	7750 3450 7750 3300
Wire Wire Line
	8150 3450 8150 3300
$Comp
L power:+7.5V #PWR?
U 1 1 6190B934
P 8150 3200
F 0 "#PWR?" H 8150 3050 50  0001 C CNN
F 1 "+7.5V" H 8165 3373 50  0000 C CNN
F 2 "" H 8150 3200 50  0001 C CNN
F 3 "" H 8150 3200 50  0001 C CNN
	1    8150 3200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6190C31F
P 7750 3200
F 0 "#PWR?" H 7750 3050 50  0001 C CNN
F 1 "+3.3V" H 7765 3373 50  0000 C CNN
F 2 "" H 7750 3200 50  0001 C CNN
F 3 "" H 7750 3200 50  0001 C CNN
	1    7750 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP 100uF
U 1 1 6190D464
P 8550 3300
F 0 "100uF" H 8668 3346 50  0000 L CNN
F 1 "C8" H 8668 3255 50  0000 L CNN
F 2 "" H 8588 3150 50  0001 C CNN
F 3 "~" H 8550 3300 50  0001 C CNN
	1    8550 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3150 8250 3150
Wire Wire Line
	8250 3150 8250 3300
Wire Wire Line
	8250 3300 8150 3300
Connection ~ 8150 3300
Wire Wire Line
	8150 3300 8150 3200
$Comp
L power:GND #PWR?
U 1 1 619166AF
P 8550 3450
F 0 "#PWR?" H 8550 3200 50  0001 C CNN
F 1 "GND" H 8555 3277 50  0000 C CNN
F 2 "" H 8550 3450 50  0001 C CNN
F 3 "" H 8550 3450 50  0001 C CNN
	1    8550 3450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6191698C
P 7300 3600
F 0 "#PWR?" H 7300 3350 50  0001 C CNN
F 1 "GND" H 7305 3427 50  0000 C CNN
F 2 "" H 7300 3600 50  0001 C CNN
F 3 "" H 7300 3600 50  0001 C CNN
	1    7300 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C 0.1uF
U 1 1 61916E33
P 7300 3450
F 0 "0.1uF" H 7415 3496 50  0000 L CNN
F 1 "C9" H 7415 3405 50  0000 L CNN
F 2 "" H 7338 3300 50  0001 C CNN
F 3 "~" H 7300 3450 50  0001 C CNN
	1    7300 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3300 7750 3300
Connection ~ 7750 3300
Wire Wire Line
	7750 3300 7750 3200
$Comp
L Motor:Motor_DC M3
U 1 1 618B85EA
P 9150 4150
F 0 "M3" H 9308 4146 50  0000 L CNN
F 1 "Motor_DC" H 9308 4055 50  0000 L CNN
F 2 "" H 9150 4060 50  0001 C CNN
F 3 "~" H 9150 4060 50  0001 C CNN
	1    9150 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6192EAB0
P 7750 5450
F 0 "#PWR?" H 7750 5200 50  0001 C CNN
F 1 "GND" H 7755 5277 50  0000 C CNN
F 2 "" H 7750 5450 50  0001 C CNN
F 3 "" H 7750 5450 50  0001 C CNN
	1    7750 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:C 0.1uF
U 1 1 61973E30
P 5900 700
F 0 "0.1uF" V 5750 900 50  0000 C CNN
F 1 "C7" V 5739 700 50  0000 C CNN
F 2 "" H 5938 550 50  0001 C CNN
F 3 "~" H 5900 700 50  0001 C CNN
	1    5900 700 
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61973E36
P 6200 700
F 0 "#PWR?" H 6200 450 50  0001 C CNN
F 1 "GND" H 6300 700 50  0000 C CNN
F 2 "" H 6200 700 50  0001 C CNN
F 3 "" H 6200 700 50  0001 C CNN
	1    6200 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 700  6200 700 
Wire Wire Line
	5750 700  5600 700 
$Comp
L power:+3.3V #PWR?
U 1 1 61973E3F
P 5600 700
F 0 "#PWR?" H 5600 550 50  0001 C CNN
F 1 "+3.3V" H 5615 873 50  0000 C CNN
F 2 "" H 5600 700 50  0001 C CNN
F 3 "" H 5600 700 50  0001 C CNN
	1    5600 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 900  5600 900 
Wire Wire Line
	5600 900  5600 700 
Connection ~ 5600 700 
$Comp
L power:GND #PWR?
U 1 1 6198BB36
P 6350 1200
F 0 "#PWR?" H 6350 950 50  0001 C CNN
F 1 "GND" H 6355 1027 50  0000 C CNN
F 2 "" H 6350 1200 50  0001 C CNN
F 3 "" H 6350 1200 50  0001 C CNN
	1    6350 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6198C2DA
P 6350 1900
F 0 "#PWR?" H 6350 1650 50  0001 C CNN
F 1 "GND" H 6355 1727 50  0000 C CNN
F 2 "" H 6350 1900 50  0001 C CNN
F 3 "" H 6350 1900 50  0001 C CNN
	1    6350 1900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6198EF66
P 5650 1400
F 0 "#PWR?" H 5650 1250 50  0001 C CNN
F 1 "+3.3V" H 5665 1573 50  0000 C CNN
F 2 "" H 5650 1400 50  0001 C CNN
F 3 "" H 5650 1400 50  0001 C CNN
	1    5650 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C 0.1uF
U 1 1 6198F4C9
P 5900 1450
F 0 "0.1uF" V 5750 1650 50  0000 C CNN
F 1 "C10" V 5739 1450 50  0000 C CNN
F 2 "" H 5938 1300 50  0001 C CNN
F 3 "~" H 5900 1450 50  0001 C CNN
	1    5900 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 1600 5650 1600
Wire Wire Line
	5650 1600 5650 1450
Wire Wire Line
	5750 1450 5650 1450
Connection ~ 5650 1450
Wire Wire Line
	5650 1450 5650 1400
$Comp
L power:GND #PWR?
U 1 1 619A0B83
P 6050 1450
F 0 "#PWR?" H 6050 1200 50  0001 C CNN
F 1 "GND" V 6055 1322 50  0000 R CNN
F 2 "" H 6050 1450 50  0001 C CNN
F 3 "" H 6050 1450 50  0001 C CNN
	1    6050 1450
	0    -1   1    0   
$EndComp
Wire Wire Line
	7450 4050 6950 4050
Wire Wire Line
	6950 4050 6950 3450
Wire Wire Line
	6950 3450 4300 3450
Wire Wire Line
	7450 4250 6850 4250
Wire Wire Line
	6850 4250 6850 3400
Wire Wire Line
	6850 3400 4400 3400
Wire Wire Line
	4400 3400 4400 3150
Wire Wire Line
	4400 3150 4300 3150
Wire Wire Line
	4300 3350 5000 3350
Wire Wire Line
	7450 4550 6800 4550
Wire Wire Line
	6800 4550 6800 3750
Wire Wire Line
	6800 3750 4600 3750
Wire Wire Line
	4600 3750 4600 2750
Wire Wire Line
	4600 2750 4300 2750
Wire Wire Line
	7450 4650 6750 4650
Wire Wire Line
	6750 4650 6750 3700
Wire Wire Line
	6750 3700 4700 3700
Wire Wire Line
	4700 3700 4700 2650
Wire Wire Line
	4700 2650 4300 2650
Text Label 6150 2150 0    50   ~ 0
Transmisor_serie_de_celda
Text Label 6400 700  0    50   ~ 0
Transmisor_serie_de_celda
$EndSCHEMATC
