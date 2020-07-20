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
L MCU_Module:WeMos_D1_mini U2
U 1 1 5F140222
P 4450 4950
F 0 "U2" H 4450 4061 50  0000 C CNN
F 1 "WeMos_D1_mini" H 4450 3970 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 4450 3800 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 2600 3800 50  0001 C CNN
	1    4450 4950
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5F140C56
P 3000 2300
F 0 "A1" H 3000 1211 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 3000 1120 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 3000 2300 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3000 2300 50  0001 C CNN
	1    3000 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F14AAE6
P 1150 1600
F 0 "#PWR02" H 1150 1350 50  0001 C CNN
F 1 "GND" H 1155 1427 50  0000 C CNN
F 2 "" H 1150 1600 50  0001 C CNN
F 3 "" H 1150 1600 50  0001 C CNN
	1    1150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1450 1150 1450
Wire Wire Line
	1150 1450 1150 1600
$Comp
L power:VCC #PWR01
U 1 1 5F14B262
P 1150 1200
F 0 "#PWR01" H 1150 1050 50  0001 C CNN
F 1 "VCC" H 1167 1373 50  0000 C CNN
F 2 "" H 1150 1200 50  0001 C CNN
F 3 "" H 1150 1200 50  0001 C CNN
	1    1150 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1350 1150 1350
Wire Wire Line
	1150 1350 1150 1200
$Comp
L power:VCC #PWR06
U 1 1 5F14C486
P 3200 900
F 0 "#PWR06" H 3200 750 50  0001 C CNN
F 1 "VCC" H 3217 1073 50  0000 C CNN
F 2 "" H 3200 900 50  0001 C CNN
F 3 "" H 3200 900 50  0001 C CNN
	1    3200 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5F14D709
P 3100 3550
F 0 "#PWR05" H 3100 3300 50  0001 C CNN
F 1 "GND" H 3105 3377 50  0000 C CNN
F 2 "" H 3100 3550 50  0001 C CNN
F 3 "" H 3100 3550 50  0001 C CNN
	1    3100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3300 3100 3400
Wire Wire Line
	2500 1700 1900 1700
Wire Wire Line
	2500 1800 2000 1800
$Comp
L power:VCC #PWR03
U 1 1 5F164846
P 3000 4200
F 0 "#PWR03" H 3000 4050 50  0001 C CNN
F 1 "VCC" H 3017 4373 50  0000 C CNN
F 2 "" H 3000 4200 50  0001 C CNN
F 3 "" H 3000 4200 50  0001 C CNN
	1    3000 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F165019
P 3200 5500
F 0 "#PWR04" H 3200 5250 50  0001 C CNN
F 1 "GND" H 3205 5327 50  0000 C CNN
F 2 "" H 3200 5500 50  0001 C CNN
F 3 "" H 3200 5500 50  0001 C CNN
	1    3200 5500
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR07
U 1 1 5F165D0F
P 4350 3400
F 0 "#PWR07" H 4350 3250 50  0001 C CNN
F 1 "VCC" H 4367 3573 50  0000 C CNN
F 2 "" H 4350 3400 50  0001 C CNN
F 3 "" H 4350 3400 50  0001 C CNN
	1    4350 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3400 4350 3550
$Comp
L power:GND #PWR08
U 1 1 5F166619
P 4450 5950
F 0 "#PWR08" H 4450 5700 50  0001 C CNN
F 1 "GND" H 4455 5777 50  0000 C CNN
F 2 "" H 4450 5950 50  0001 C CNN
F 3 "" H 4450 5950 50  0001 C CNN
	1    4450 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4150 4550 3850
$Comp
L Device:R R1
U 1 1 5F167434
P 6050 4850
F 0 "R1" H 6120 4896 50  0000 L CNN
F 1 "470" H 6120 4805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 5980 4850 50  0001 C CNN
F 3 "~" H 6050 4850 50  0001 C CNN
	1    6050 4850
	1    0    0    -1  
$EndComp
$Comp
L Isolator:LTV-817 U3
U 1 1 5F168069
P 6350 5250
F 0 "U3" H 6350 5575 50  0000 C CNN
F 1 "LTV-817" H 6350 5484 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm_LongPads" H 6150 5050 50  0001 L CIN
F 3 "http://www.us.liteon.com/downloads/LTV-817-827-847.PDF" H 6350 5150 50  0001 L CNN
	1    6350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5000 6050 5150
$Comp
L power:GND #PWR09
U 1 1 5F169121
P 6050 5500
F 0 "#PWR09" H 6050 5250 50  0001 C CNN
F 1 "GND" H 6055 5327 50  0000 C CNN
F 2 "" H 6050 5500 50  0001 C CNN
F 3 "" H 6050 5500 50  0001 C CNN
	1    6050 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 5350 6050 5500
Wire Wire Line
	4850 4650 6050 4650
Wire Wire Line
	6050 4650 6050 4700
Wire Wire Line
	6750 5150 6650 5150
Wire Wire Line
	6750 5350 6650 5350
Text GLabel 6750 5350 2    50   UnSpc ~ 0
BTN-
Text GLabel 6750 5150 2    50   UnSpc ~ 0
BTN+
Text GLabel 3800 2800 2    50   Input ~ 0
SCL
Text GLabel 3800 2700 2    50   Input ~ 0
SDA
Text GLabel 1050 1450 0    50   Input ~ 0
GND
Text GLabel 1050 1350 0    50   Input ~ 0
VCC
Text GLabel 1300 5450 2    50   Input ~ 0
VCC
Text GLabel 1300 5550 2    50   Input ~ 0
GND
Text GLabel 1300 5650 2    50   Input ~ 0
SDA
Text GLabel 1300 5750 2    50   Input ~ 0
SCL
Text GLabel 1300 5850 2    50   UnSpc ~ 0
BTN+
Text GLabel 1300 5950 2    50   UnSpc ~ 0
BTN-
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5F17ED0F
P 3000 1000
F 0 "J2" H 3108 1089 50  0000 C CNN
F 1 "Conn_01x02_Male" H 3108 1090 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3000 1000 50  0001 C CNN
F 3 "~" H 3000 1000 50  0001 C CNN
	1    3000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1100 3200 1300
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5F184318
P 4150 3550
F 0 "J3" H 4258 3639 50  0000 C CNN
F 1 "Conn_01x02_Male" H 4258 3640 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4150 3550 50  0001 C CNN
F 3 "~" H 4150 3550 50  0001 C CNN
	1    4150 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 5F18D879
P 900 5650
F 0 "J1" H 1008 5939 50  0000 C CNN
F 1 "Conn_01x06_Male" H 1008 5940 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 900 5650 50  0001 C CNN
F 3 "~" H 900 5650 50  0001 C CNN
	1    900  5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5450 1100 5450
Wire Wire Line
	1300 5550 1100 5550
Wire Wire Line
	1300 5650 1100 5650
Wire Wire Line
	1300 5750 1100 5750
Wire Wire Line
	1300 5850 1100 5850
Wire Wire Line
	1300 5950 1100 5950
NoConn ~ 2500 1900
NoConn ~ 2500 2000
NoConn ~ 2500 2300
NoConn ~ 2500 2400
NoConn ~ 2500 2500
NoConn ~ 2500 2600
NoConn ~ 2500 2700
NoConn ~ 2500 2800
NoConn ~ 2500 2900
NoConn ~ 2500 3000
NoConn ~ 3500 1700
NoConn ~ 3500 1800
NoConn ~ 3500 2100
NoConn ~ 3500 2300
NoConn ~ 3500 2400
NoConn ~ 3500 2500
NoConn ~ 3500 2600
NoConn ~ 3500 2900
NoConn ~ 3500 3000
NoConn ~ 4050 4550
NoConn ~ 4850 4450
NoConn ~ 4850 4550
NoConn ~ 4850 4750
NoConn ~ 4850 4850
NoConn ~ 4850 4950
NoConn ~ 4850 5050
NoConn ~ 4850 5150
NoConn ~ 4850 5250
NoConn ~ 4850 5350
NoConn ~ 2900 1300
NoConn ~ 3100 1300
Wire Wire Line
	1900 4950 2750 4950
Wire Wire Line
	1900 1700 1900 4950
Wire Wire Line
	2000 4850 2750 4850
Wire Wire Line
	2000 1800 2000 4850
Wire Wire Line
	3200 5500 3200 5400
Wire Wire Line
	3000 4200 3000 4300
Wire Wire Line
	4550 3850 3200 3850
Wire Wire Line
	3200 3850 3200 4300
Wire Wire Line
	3450 4850 4050 4850
Wire Wire Line
	3450 4950 4050 4950
NoConn ~ 2750 4650
NoConn ~ 2750 4750
NoConn ~ 3450 4650
NoConn ~ 3450 4750
Wire Wire Line
	3000 5350 3000 5400
Wire Wire Line
	3000 5400 3200 5400
Connection ~ 3200 5400
Wire Wire Line
	3200 5400 3200 5350
Wire Wire Line
	3200 1000 3200 900 
Wire Wire Line
	3000 3300 3000 3400
Wire Wire Line
	3000 3400 3100 3400
Connection ~ 3100 3400
Wire Wire Line
	3100 3400 3100 3550
Wire Wire Line
	4350 3650 4350 4150
Wire Wire Line
	4450 5750 4450 5950
NoConn ~ 2500 2100
NoConn ~ 2500 2200
Wire Wire Line
	3800 2700 3500 2700
Wire Wire Line
	3800 2800 3500 2800
$Comp
L 4Bit_China_Level_Shifter:4Bit_China_Level_Shifter U1
U 1 1 5F17922D
P 3100 5250
F 0 "U1" H 3100 6381 50  0000 C CNN
F 1 "4Bit_China_Level_Shifter" H 3100 6290 50  0000 C CNN
F 2 "Projectspecific:4Bit_China_Level_Shifter" H 3100 5000 50  0001 C CNN
F 3 "https://www.amazon.de/gp/product/B07RY15XMJ" H 3100 5000 50  0001 C CNN
	1    3100 5250
	1    0    0    -1  
$EndComp
$EndSCHEMATC