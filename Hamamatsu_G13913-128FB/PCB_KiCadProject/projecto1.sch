EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Shield de STM32 Smart V2.0 para sensor de imagem G13913"
Date "2021-08-27"
Rev "v1.5"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 1000 750  0    98   ~ 0
STM32 Smart V2.0 Pins
Text Notes 1500 3700 0    98   ~ 0
G13913 Pins
Text GLabel 1400 5050 0    50   Input ~ 0
AD_trig
Text GLabel 1400 4950 0    50   Input ~ 0
GND
Text GLabel 1400 4850 0    50   Input ~ 0
AD_sp
Text GLabel 1400 4750 0    50   Input ~ 0
Vhold
Text GLabel 1400 4650 0    50   Input ~ 0
CLK
Text GLabel 1400 4550 0    50   Input ~ 0
Reset
Text GLabel 1400 4450 0    50   Input ~ 0
Fvref
Text GLabel 1400 4350 0    50   Input ~ 0
Video
Text GLabel 1400 4250 0    50   Input ~ 0
PDN
Text GLabel 1400 4150 0    50   Input ~ 0
INP
Text GLabel 1400 4050 0    50   Input ~ 0
3V3
Text GLabel 1400 3950 0    50   Input ~ 0
Cf_select
Text Notes 8500 3700 0    100  ~ 0
ADC 1.8V Supply
Text GLabel 4350 2200 0    50   Input ~ 0
DAC_D0
Text GLabel 4350 2100 0    50   Input ~ 0
DAC_D1
Text GLabel 4350 2000 0    50   Input ~ 0
DAC_D2
Text GLabel 4350 1900 0    50   Input ~ 0
DAC_D3
Text GLabel 4350 1700 0    50   Input ~ 0
DAC_D5
Text GLabel 4350 1600 0    50   Input ~ 0
DAC_D6
Text GLabel 4350 1500 0    50   Input ~ 0
DAC_D7
Text GLabel 4350 2300 0    50   Input ~ 0
CS_DAC
Text GLabel 4350 2400 0    50   Input ~ 0
CS_DAC
Text GLabel 5850 1800 2    50   Input ~ 0
GND
Text GLabel 5850 2400 2    50   Input ~ 0
GND
Text GLabel 5850 1500 2    50   Input ~ 0
GND
Text GLabel 5850 2200 2    50   Input ~ 0
GND
Text GLabel 5850 2300 2    50   Input ~ 0
3V3
Text Notes 2450 5900 2    100  ~ 0
LDO 2.5V Ref
Text GLabel 5750 3500 2    50   Input ~ 0
SCK
Text GLabel 10300 2250 2    50   Input ~ 0
SCK
Text GLabel 10300 2150 2    50   Input ~ 0
MOSI
Text GLabel 10300 2350 2    50   Input ~ 0
MISO
Text GLabel 10300 2450 2    50   Input ~ 0
CS_ADC
Text GLabel 5750 3600 2    50   Input ~ 0
MOSI
Text GLabel 4650 3700 0    50   Input ~ 0
GND
Text GLabel 4650 3400 0    50   Input ~ 0
PGA_Output
Text GLabel 4650 3500 0    50   Input ~ 0
Video
Text GLabel 4650 3600 0    50   Input ~ 0
PGA_Vref
Text Notes 4650 5900 0    100  ~ 0
3.3V  Supply
$Comp
L power:GND #PWR020
U 1 1 605C0BC8
P 10800 2400
F 0 "#PWR020" H 10800 2150 50  0001 C CNN
F 1 "GND" H 10805 2227 50  0000 C CNN
F 2 "" H 10800 2400 50  0001 C CNN
F 3 "" H 10800 2400 50  0001 C CNN
	1    10800 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 2400 10800 2350
Wire Wire Line
	10800 2050 10300 2050
$Comp
L power:GND #PWR018
U 1 1 605C4B24
P 9100 2450
F 0 "#PWR018" H 9100 2200 50  0001 C CNN
F 1 "GND" H 9105 2277 50  0000 C CNN
F 2 "" H 9100 2450 50  0001 C CNN
F 3 "" H 9100 2450 50  0001 C CNN
	1    9100 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 2150 9100 2150
$Comp
L power:GND #PWR013
U 1 1 605CF4F3
P 8100 2550
F 0 "#PWR013" H 8100 2300 50  0001 C CNN
F 1 "GND" H 8105 2377 50  0000 C CNN
F 2 "" H 8100 2550 50  0001 C CNN
F 3 "" H 8100 2550 50  0001 C CNN
	1    8100 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2250 8100 2250
Connection ~ 8100 2250
Text GLabel 7800 2250 0    50   Input ~ 0
PGA_Output
Connection ~ 1600 6600
Wire Wire Line
	1600 6300 1600 6250
Text GLabel 1600 6100 0    50   Input ~ 0
3V3
Wire Wire Line
	2050 6600 2050 6400
Wire Wire Line
	2050 6100 2250 6100
Wire Wire Line
	2050 6600 1600 6600
Wire Wire Line
	2050 6200 2250 6200
Connection ~ 2050 6200
Wire Wire Line
	2050 6200 2050 6100
Wire Wire Line
	2050 6300 2250 6300
Connection ~ 2050 6300
Wire Wire Line
	2050 6300 2050 6200
Wire Wire Line
	2050 6400 2250 6400
Connection ~ 2050 6400
Wire Wire Line
	2050 6400 2050 6300
Text GLabel 2250 6100 2    50   Input ~ 0
INP
Text GLabel 2250 6200 2    50   Input ~ 0
PDN
Text GLabel 2250 6300 2    50   Input ~ 0
Fvref
Text GLabel 2250 6400 2    50   Input ~ 0
Vhold
Connection ~ 6200 3400
Wire Wire Line
	6200 3400 5750 3400
$Comp
L power:GND #PWR010
U 1 1 605BD45D
P 6200 3750
F 0 "#PWR010" H 6200 3500 50  0001 C CNN
F 1 "GND" H 6205 3577 50  0000 C CNN
F 2 "" H 6200 3750 50  0001 C CNN
F 3 "" H 6200 3750 50  0001 C CNN
	1    6200 3750
	1    0    0    -1  
$EndComp
Text GLabel 5750 3700 2    50   Input ~ 0
CS_PGA
$Comp
L power:GND #PWR015
U 1 1 605E540C
P 8450 4600
F 0 "#PWR015" H 8450 4350 50  0001 C CNN
F 1 "GND" H 8455 4427 50  0000 C CNN
F 2 "" H 8450 4600 50  0001 C CNN
F 3 "" H 8450 4600 50  0001 C CNN
	1    8450 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4300 8450 4300
Text Notes 6300 900  2    100  ~ 0
DAC p/ Saída de video
Text Notes 9350 1000 2    100  ~ 0
ADC
Text Notes 5350 2850 2    100  ~ 0
PGA
Wire Wire Line
	5800 6400 5800 6500
Wire Wire Line
	5800 6400 5650 6400
Connection ~ 5800 6400
$Comp
L power:GND #PWR08
U 1 1 60565937
P 5800 6800
F 0 "#PWR08" H 5800 6550 50  0001 C CNN
F 1 "GND" H 5805 6627 50  0000 C CNN
F 2 "" H 5800 6800 50  0001 C CNN
F 3 "" H 5800 6800 50  0001 C CNN
	1    5800 6800
	-1   0    0    -1  
$EndComp
Text GLabel 6350 6200 2    50   Input ~ 0
5V
$Comp
L power:GND #PWR04
U 1 1 605655B5
P 4400 6150
F 0 "#PWR04" H 4400 5900 50  0001 C CNN
F 1 "GND" H 4405 5977 50  0000 C CNN
F 2 "" H 4400 6150 50  0001 C CNN
F 3 "" H 4400 6150 50  0001 C CNN
	1    4400 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 6600 4550 6500
$Comp
L power:GND #PWR05
U 1 1 60565CDA
P 4550 6950
F 0 "#PWR05" H 4550 6700 50  0001 C CNN
F 1 "GND" H 4555 6777 50  0000 C CNN
F 2 "" H 4550 6950 50  0001 C CNN
F 3 "" H 4550 6950 50  0001 C CNN
	1    4550 6950
	1    0    0    -1  
$EndComp
Connection ~ 4550 6500
Wire Wire Line
	5800 6400 6350 6400
Wire Wire Line
	4550 6100 4400 6100
Wire Wire Line
	4400 6100 4400 6150
Text GLabel 1050 2550 0    50   Input ~ 0
PGA_Output
Text GLabel 1050 2750 0    50   Input ~ 0
AD_sp
Text GLabel 1050 2850 0    50   Input ~ 0
AD_trig
$Comp
L power:GND #PWR016
U 1 1 6056A293
P 8800 3000
F 0 "#PWR016" H 8800 2750 50  0001 C CNN
F 1 "GND" H 8805 2827 50  0000 C CNN
F 2 "" H 8800 3000 50  0001 C CNN
F 3 "" H 8800 3000 50  0001 C CNN
	1    8800 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 6056A4F4
P 8400 3000
F 0 "#PWR014" H 8400 2750 50  0001 C CNN
F 1 "GND" H 8405 2827 50  0000 C CNN
F 2 "" H 8400 3000 50  0001 C CNN
F 3 "" H 8400 3000 50  0001 C CNN
	1    8400 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 3000 8400 2700
Wire Wire Line
	8800 2700 8700 2700
Wire Wire Line
	9100 2350 8800 2350
Wire Wire Line
	8800 2350 8800 2700
Connection ~ 8800 2700
Text Notes 8200 1500 0    50   ~ 0
Configuração segundo Figura 6-7 do datasheet. Valores dos \ncondensadores de desacoplamento em nota no Cap 5.1.1.\nCondensadores colocados no circuito de 1.8V Supply
Text Notes 4200 1050 0    50   ~ 0
DAC AD7801, montagem como figura 27 do datasheet.
$Comp
L power:GND #PWR012
U 1 1 60580CCA
P 6600 2300
F 0 "#PWR012" H 6600 2050 50  0001 C CNN
F 1 "GND" H 6605 2127 50  0000 C CNN
F 2 "" H 6600 2300 50  0001 C CNN
F 3 "" H 6600 2300 50  0001 C CNN
	1    6600 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 60580FB9
P 6200 2300
F 0 "#PWR09" H 6200 2050 50  0001 C CNN
F 1 "GND" H 6205 2127 50  0000 C CNN
F 2 "" H 6200 2300 50  0001 C CNN
F 3 "" H 6200 2300 50  0001 C CNN
	1    6200 2300
	1    0    0    -1  
$EndComp
Text Notes 3000 850  0    50   ~ 0
Pinos para shunt de \nBOOT0 a GND ou 3V3.\n?Ou fazer shunt directo no shield?\n
Connection ~ 6200 2000
Wire Wire Line
	2650 950  3200 950 
Wire Wire Line
	3200 950  3200 1050
Wire Wire Line
	3200 1050 2650 1050
Wire Wire Line
	6100 1600 5850 1600
$Comp
L power:GND #PWR011
U 1 1 60675E0F
P 6300 1800
F 0 "#PWR011" H 6300 1550 50  0001 C CNN
F 1 "GND" H 6305 1627 50  0000 C CNN
F 2 "" H 6300 1800 50  0001 C CNN
F 3 "" H 6300 1800 50  0001 C CNN
	1    6300 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 60685243
P 5300 5050
F 0 "#PWR07" H 5300 4800 50  0001 C CNN
F 1 "GND" H 5305 4877 50  0000 C CNN
F 2 "" H 5300 5050 50  0001 C CNN
F 3 "" H 5300 5050 50  0001 C CNN
	1    5300 5050
	1    0    0    -1  
$EndComp
Text GLabel 5300 4350 2    50   Input ~ 0
3V3
Text GLabel 4300 4600 0    50   Input ~ 0
SCL
Text GLabel 4300 4700 0    50   Input ~ 0
SDA
$Comp
L power:GND #PWR06
U 1 1 6068651B
P 4800 4800
F 0 "#PWR06" H 4800 4550 50  0001 C CNN
F 1 "GND" H 4805 4627 50  0000 C CNN
F 2 "" H 4800 4800 50  0001 C CNN
F 3 "" H 4800 4800 50  0001 C CNN
	1    4800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4800 4800 4800
Text GLabel 5700 4700 2    50   Input ~ 0
PGA_Vref
Text Notes 4050 4150 0    100  ~ 0
DAC p/ Deslocamento de nivel
$Comp
L power:GND #PWR03
U 1 1 6068C24E
P 3950 4600
F 0 "#PWR03" H 3950 4350 50  0001 C CNN
F 1 "GND" H 3955 4427 50  0000 C CNN
F 2 "" H 3950 4600 50  0001 C CNN
F 3 "" H 3950 4600 50  0001 C CNN
	1    3950 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6068C6D8
P 3650 4600
F 0 "#PWR02" H 3650 4350 50  0001 C CNN
F 1 "GND" H 3655 4427 50  0000 C CNN
F 2 "" H 3650 4600 50  0001 C CNN
F 3 "" H 3650 4600 50  0001 C CNN
	1    3650 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4300 3950 4300
Connection ~ 3950 4300
Wire Wire Line
	6100 1400 6100 1600
Wire Wire Line
	6100 1400 6200 1400
Connection ~ 6100 1600
Text Label 8900 2250 0    50   ~ 0
ADC+
Text Label 8900 2350 0    50   ~ 0
ADC-
$Comp
L power:GND #PWR019
U 1 1 606EF1F9
P 10100 4500
F 0 "#PWR019" H 10100 4250 50  0001 C CNN
F 1 "GND" H 10105 4327 50  0000 C CNN
F 2 "" H 10100 4500 50  0001 C CNN
F 3 "" H 10100 4500 50  0001 C CNN
	1    10100 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 4200 9650 4200
Wire Wire Line
	9100 2050 9050 2050
Text Notes 8700 5350 0    100  ~ 0
PWM Pins
Text GLabel 8800 5600 0    50   Input ~ 0
PWM
$Comp
L power:GND #PWR01
U 1 1 605DC4ED
P 1400 7000
F 0 "#PWR01" H 1400 6750 50  0001 C CNN
F 1 "GND" H 1405 6827 50  0000 C CNN
F 2 "" H 1400 7000 50  0001 C CNN
F 3 "" H 1400 7000 50  0001 C CNN
	1    1400 7000
	1    0    0    -1  
$EndComp
Text Notes 650  7750 0    50   ~ 0
De acordo com o datasheet do G13913, os pinos INP, PDN, \nFvref e Vhold consumirão no máximo 1 mA cada um, \ntotalizando 4 mA. O LM4040 mantem uma tensão constante \ncom uma corrente inversa entre 60uA e 15 mA. Com R = 180ohm\nserá fornecida uma corrente de 4,4 mA.
Wire Wire Line
	1600 6600 1600 6750
Wire Wire Line
	1600 6950 1400 6950
Wire Wire Line
	1400 6950 1400 7000
Text Label 2050 6600 0    50   ~ 0
2V5
NoConn ~ 1050 1150
NoConn ~ 1050 1250
NoConn ~ 1050 1350
NoConn ~ 1050 1450
NoConn ~ 1050 1550
NoConn ~ 1050 1650
NoConn ~ 2650 1150
NoConn ~ 2650 1550
NoConn ~ 2650 2050
NoConn ~ 2650 2150
NoConn ~ 2650 2350
NoConn ~ 2650 2450
NoConn ~ 1050 2650
NoConn ~ 1600 7150
Text Label 6200 1400 0    50   ~ 0
ANALOG_OUT
Wire Wire Line
	5300 5000 5300 5050
Wire Wire Line
	4550 6900 4550 6950
Wire Wire Line
	6200 3700 6200 3750
Wire Wire Line
	6200 2000 6600 2000
Wire Wire Line
	5850 2000 6200 2000
Text GLabel 5850 1900 2    50   Input ~ 0
3V3
Text GLabel 5850 2100 2    50   Input ~ 0
3V3
Text GLabel 6600 2000 1    50   Input ~ 0
3V3
Wire Wire Line
	6250 3400 6200 3400
Text GLabel 4350 1800 0    50   Input ~ 0
DAC_D4
Text GLabel 2650 1450 2    50   Input ~ 0
PWM
Text GLabel 2650 1350 2    50   Input ~ 0
SCL
Text GLabel 2650 1250 2    50   Input ~ 0
SDA
Text GLabel 2650 1050 2    50   Input ~ 0
GND
Text GLabel 2650 950  2    50   Input ~ 0
GND
Text GLabel 1050 1050 0    50   Input ~ 0
GND
Text GLabel 1050 1750 0    50   Input ~ 0
CS_ADC
Text GLabel 1050 1850 0    50   Input ~ 0
CS_PGA
Text GLabel 1050 1950 0    50   Input ~ 0
Reset
Text GLabel 1050 2050 0    50   Input ~ 0
Cf_select
Text GLabel 1050 2150 0    50   Input ~ 0
SCK
Text GLabel 1050 2250 0    50   Input ~ 0
MISO
Text GLabel 1050 2350 0    50   Input ~ 0
MOSI
Text GLabel 1050 2450 0    50   Input ~ 0
CLK
Text GLabel 2650 2550 2    50   Input ~ 0
DAC_D3
Text GLabel 2650 2650 2    50   Input ~ 0
DAC_D2
Text GLabel 2650 2750 2    50   Input ~ 0
DAC_D1
Text GLabel 2650 2250 2    50   Input ~ 0
CS_DAC
Text GLabel 2650 2850 2    50   Input ~ 0
DAC_D0
Text GLabel 2650 1650 2    50   Input ~ 0
DAC_D4
Text GLabel 2650 1750 2    50   Input ~ 0
DAC_D5
Text GLabel 2650 1850 2    50   Input ~ 0
DAC_D6
Text GLabel 2650 1950 2    50   Input ~ 0
DAC_D7
Text GLabel 9050 2150 0    50   Input ~ 0
1V8
Text GLabel 8550 4200 0    50   Input ~ 0
GND
Text GLabel 8450 4300 0    50   Input ~ 0
1V8
Text GLabel 9650 4200 2    50   Input ~ 0
3V3
$Comp
L SamacSys_Parts:MCP6S91-E_SN IC3
U 1 1 6057A7E7
P 4650 3400
F 0 "IC3" H 5200 3665 50  0000 C CNN
F 1 "MCP6S91-E_SN" H 5200 3574 50  0000 C CNN
F 2 "SOIC127P600X175-8N" H 5600 3500 50  0001 L CNN
F 3 "http://docs-emea.rs-online.com/webdocs/0806/0900766b808065ce.pdf" H 5600 3400 50  0001 L CNN
F 4 "Rail-to-Rail Programmable Gain Amplifier" H 5600 3300 50  0001 L CNN "Description"
F 5 "1.75" H 5600 3200 50  0001 L CNN "Height"
F 6 "Microchip" H 5600 3100 50  0001 L CNN "Manufacturer_Name"
F 7 "MCP6S91-E/SN" H 5600 3000 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "579-MCP6S91-E/SN" H 5600 2900 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Microchip-Technology/MCP6S91-E-SN?qs=Y8sGFBEOzV8guHFCFN0vog%3D%3D" H 5600 2800 50  0001 L CNN "Mouser Price/Stock"
F 10 "MCP6S91-E/SN" H 5600 2700 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/mcp6s91-esn/microchip-technology" H 5600 2600 50  0001 L CNN "Arrow Price/Stock"
	1    4650 3400
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:MCP1700T-1802E_TT IC4
U 1 1 6057D4AD
P 8550 4200
F 0 "IC4" H 9100 4465 50  0000 C CNN
F 1 "MCP1700T-1802E_TT" H 9100 4374 50  0000 C CNN
F 2 "SOT95P237X112-3N" H 9500 4300 50  0001 L CNN
F 3 "" H 9500 4200 50  0001 L CNN
F 4 "Microchip MCP1700T-1802E/TT, LDO Voltage Regulator, 200mA, 1.8 V +/-2%, 2.3  6 Vin, 3-Pin SOT-23" H 9500 4100 50  0001 L CNN "Description"
F 5 "" H 9500 4000 50  0001 L CNN "Height"
F 6 "Microchip" H 9500 3900 50  0001 L CNN "Manufacturer_Name"
F 7 "MCP1700T-1802E/TT" H 9500 3800 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "579-MCP1700T1802E/TT" H 9500 3700 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Microchip-Technology/MCP1700T-1802E-TT/?qs=YUl711QUJY0TiDgzmNmFrg%3D%3D" H 9500 3600 50  0001 L CNN "Mouser Price/Stock"
F 10 "MCP1700T-1802E/TT" H 9500 3500 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/mcp1700t-1802ett/microchip-technology" H 9500 3400 50  0001 L CNN "Arrow Price/Stock"
	1    8550 4200
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:AD7801BRZ IC1
U 1 1 6058661C
P 4350 1500
F 0 "IC1" H 5100 1765 50  0000 C CNN
F 1 "AD7801BRZ" H 5100 1674 50  0000 C CNN
F 2 "SOIC127P1032X265-20N" H 5700 1600 50  0001 L CNN
F 3 "http://docs-emea.rs-online.com/webdocs/077f/0900766b8077fe26.pdf" H 5700 1500 50  0001 L CNN
F 4 "AD7801BRZ, 8-Bit 8 Bit DAC 833ksps, Parallel, 20-Pin SOIC W" H 5700 1400 50  0001 L CNN "Description"
F 5 "2.65" H 5700 1300 50  0001 L CNN "Height"
F 6 "Analog Devices" H 5700 1200 50  0001 L CNN "Manufacturer_Name"
F 7 "AD7801BRZ" H 5700 1100 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "584-AD7801BRZ" H 5700 1000 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Analog-Devices/AD7801BRZ/?qs=%2FtpEQrCGXCyxB86MH6WA8A%3D%3D" H 5700 900 50  0001 L CNN "Mouser Price/Stock"
F 10 "AD7801BRZ" H 5700 800 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/ad7801brz/analog-devices" H 5700 700 50  0001 L CNN "Arrow Price/Stock"
	1    4350 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 605BBA77
P 7950 2250
F 0 "R2" V 7743 2250 50  0000 C CNN
F 1 "22" V 7834 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 7880 2250 50  0001 C CNN
F 3 "~" H 7950 2250 50  0001 C CNN
	1    7950 2250
	0    1    1    0   
$EndComp
$Comp
L Device:C C11
U 1 1 605BF371
P 10100 4350
F 0 "C11" H 10215 4396 50  0000 L CNN
F 1 "10uF" H 10215 4305 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 10138 4200 50  0001 C CNN
F 3 "~" H 10100 4350 50  0001 C CNN
	1    10100 4350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 605BFE12
P 10800 2200
F 0 "C12" H 10915 2246 50  0000 L CNN
F 1 ".1uF" H 10915 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 10838 2050 50  0001 C CNN
F 3 "~" H 10800 2200 50  0001 C CNN
	1    10800 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 605CEFF5
P 8100 2400
F 0 "C8" H 8215 2446 50  0000 L CNN
F 1 "1.7nF" H 8215 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8138 2250 50  0001 C CNN
F 3 "~" H 8100 2400 50  0001 C CNN
	1    8100 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 605DE251
P 1600 6450
F 0 "R1" H 1530 6404 50  0000 R CNN
F 1 "180" H 1530 6495 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 1530 6450 50  0001 C CNN
F 3 "~" H 1600 6450 50  0001 C CNN
	1    1600 6450
	-1   0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 605BC9D6
P 6200 3550
F 0 "C6" H 6315 3596 50  0000 L CNN
F 1 ".1uF" H 6315 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6238 3400 50  0001 C CNN
F 3 "~" H 6200 3550 50  0001 C CNN
	1    6200 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 605E4A8C
P 8450 4450
F 0 "C9" H 8565 4496 50  0000 L CNN
F 1 "1uF" H 8565 4405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8488 4300 50  0001 C CNN
F 3 "~" H 8450 4450 50  0001 C CNN
	1    8450 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 60565F1E
P 5800 6650
F 0 "C4" H 5915 6696 50  0000 L CNN
F 1 "1uF" H 5915 6605 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 5838 6500 50  0001 C CNN
F 3 "~" H 5800 6650 50  0001 C CNN
	1    5800 6650
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 605612AD
P 6150 6200
F 0 "J5" H 6230 6192 50  0000 L CNN
F 1 "Conn_01x02" H 6230 6101 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 6150 6200 50  0001 C CNN
F 3 "~" H 6150 6200 50  0001 C CNN
	1    6150 6200
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 605662F9
P 4550 6750
F 0 "C3" H 4665 6796 50  0000 L CNN
F 1 "1uF" H 4665 6705 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 4588 6600 50  0001 C CNN
F 3 "~" H 4550 6750 50  0001 C CNN
	1    4550 6750
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:MCP1700T-3302E_TT IC2
U 1 1 6056EA3B
P 4550 6400
F 0 "IC2" H 5100 6665 50  0000 C CNN
F 1 "MCP1700T-3302E_TT" H 5100 6574 50  0000 C CNN
F 2 "SOT95P237X112-3N" H 5500 6500 50  0001 L CNN
F 3 "" H 5500 6400 50  0001 L CNN
F 4 "LDO voltage regulator 250mA Isupply 1uA" H 5500 6300 50  0001 L CNN "Description"
F 5 "1.12" H 5500 6200 50  0001 L CNN "Height"
F 6 "579-MCP1700T3302E/TT" H 5500 6100 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Microchip-Technology/MCP1700T-3302E-TT?qs=fM4xO01eazPmCNDrdHEdaw%3D%3D" H 5500 6000 50  0001 L CNN "Mouser Price/Stock"
F 8 "Microchip" H 5500 5900 50  0001 L CNN "Manufacturer_Name"
F 9 "MCP1700T-3302E/TT" H 5500 5800 50  0001 L CNN "Manufacturer_Part_Number"
	1    4550 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6056912B
P 8550 2700
F 0 "R3" V 8343 2700 50  0000 C CNN
F 1 "22" V 8434 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 8480 2700 50  0001 C CNN
F 3 "~" H 8550 2700 50  0001 C CNN
	1    8550 2700
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C10
U 1 1 60569FE1
P 8800 2850
F 0 "C10" H 8915 2896 50  0000 L CNN
F 1 "1.7nF" H 8915 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8838 2700 50  0001 C CNN
F 3 "~" H 8800 2850 50  0001 C CNN
	1    8800 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 605808A9
P 6600 2150
F 0 "C7" H 6715 2196 50  0000 L CNN
F 1 ".1uF" H 6715 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6638 2000 50  0001 C CNN
F 3 "~" H 6600 2150 50  0001 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 6057F8C4
P 6200 2150
F 0 "C5" H 6315 2196 50  0000 L CNN
F 1 "10uF" H 6315 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6238 2000 50  0001 C CNN
F 3 "~" H 6200 2150 50  0001 C CNN
	1    6200 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial J6
U 1 1 606745BA
P 6300 1600
F 0 "J6" H 6400 1575 50  0000 L CNN
F 1 "Conn_Coaxial" H 6400 1484 50  0000 L CNN
F 2 "SamacSys_Parts:PCBSMAFRAHT" H 6300 1600 50  0001 C CNN
F 3 " ~" H 6300 1600 50  0001 C CNN
	1    6300 1600
	1    0    0    -1  
$EndComp
$Comp
L Analog_DAC:MCP4725xxx-xCH U2
U 1 1 60684447
P 5300 4700
F 0 "U2" H 5744 4746 50  0000 L CNN
F 1 "MCP4725xxx-xCH" H 5744 4655 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 5300 4450 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/22039d.pdf" H 5300 4700 50  0001 C CNN
	1    5300 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 6068B4A6
P 3950 4450
F 0 "C2" H 4065 4496 50  0000 L CNN
F 1 "10uF" H 4065 4405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3988 4300 50  0001 C CNN
F 3 "~" H 3950 4450 50  0001 C CNN
	1    3950 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6068BEDE
P 3650 4450
F 0 "C1" H 3765 4496 50  0000 L CNN
F 1 ".1uF" H 3765 4405 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 3688 4300 50  0001 C CNN
F 3 "~" H 3650 4450 50  0001 C CNN
	1    3650 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J1
U 1 1 60797219
P 1250 1850
F 0 "J1" H 1330 1842 50  0000 L CNN
F 1 "Conn_01x20" H 1330 1751 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 1250 1850 50  0001 C CNN
F 3 "~" H 1250 1850 50  0001 C CNN
	1    1250 1850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J3
U 1 1 6079B295
P 2450 1850
F 0 "J3" H 2368 2967 50  0000 C CNN
F 1 "Conn_01x20" H 2368 2876 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 2450 1850 50  0001 C CNN
F 3 "~" H 2450 1850 50  0001 C CNN
	1    2450 1850
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 J2
U 1 1 607B6C8F
P 1600 4450
F 0 "J2" H 1680 4442 50  0000 L CNN
F 1 "Conn_01x12" H 1680 4351 50  0000 L CNN
F 2 "Connector_FFC-FPC:Hirose_FH12-12S-0.5SH_1x12-1MP_P0.50mm_Horizontal" H 1600 4450 50  0001 C CNN
F 3 "~" H 1600 4450 50  0001 C CNN
	1    1600 4450
	1    0    0    -1  
$EndComp
$Comp
L SamacSys_Parts:MCP33131D-10-E_MS IC5
U 1 1 606AA079
P 9100 2050
F 0 "IC5" H 9700 2315 50  0000 C CNN
F 1 "MCP33131D-10-E_MS" H 9700 2224 50  0000 C CNN
F 2 "SOP50P490X110-10N" H 10150 2150 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/MCP33131-MCP33121-MCP33111-Family-Data-Sheet-DS20006122A.pdf" H 10150 2050 50  0001 L CNN
F 4 "Analog to Digital Converters - ADC 16-bit,1 Msps, single channel, differential SAR ADC" H 10150 1950 50  0001 L CNN "Description"
F 5 "1.1" H 10150 1850 50  0001 L CNN "Height"
F 6 "579-MCP33131D10EMS" H 10150 1750 50  0001 L CNN "Mouser Part Number"
F 7 "https://www.mouser.co.uk/ProductDetail/Microchip-Technology/MCP33131D-10-E-MS/?qs=byeeYqUIh0NhU4NZQbhNiA%3D%3D" H 10150 1650 50  0001 L CNN "Mouser Price/Stock"
F 8 "Microchip" H 10150 1550 50  0001 L CNN "Manufacturer_Name"
F 9 "MCP33131D-10-E/MS" H 10150 1450 50  0001 L CNN "Manufacturer_Part_Number"
	1    9100 2050
	1    0    0    -1  
$EndComp
$Comp
L Outros:LM4040CIX3-2_5T U1
U 1 1 6079EF05
P 2300 6950
F 0 "U1" H 2832 6996 50  0000 L CNN
F 1 "LM4040CIX3-2_5T" H 2832 6905 50  0000 L CNN
F 2 "SOT65P210X110-3N" H 2300 6950 50  0001 L BNN
F 3 "" H 2300 6950 50  0001 L BNN
	1    2300 6950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial J7
U 1 1 6073AEA2
P 9150 5600
F 0 "J7" H 9250 5575 50  0000 L CNN
F 1 "Conn_Coaxial" H 9250 5484 50  0000 L CNN
F 2 "SamacSys_Parts:PCBSMAFRAHT" H 9150 5600 50  0001 C CNN
F 3 " ~" H 9150 5600 50  0001 C CNN
	1    9150 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 6073AEA8
P 9150 5800
F 0 "#PWR0101" H 9150 5550 50  0001 C CNN
F 1 "GND" H 9155 5627 50  0000 C CNN
F 2 "" H 9150 5800 50  0001 C CNN
F 3 "" H 9150 5800 50  0001 C CNN
	1    9150 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 5600 8800 5600
Text GLabel 9050 2050 0    50   Input ~ 0
3V3
Text GLabel 6250 3400 2    50   Input ~ 0
3V3
Text GLabel 10300 2050 2    50   Input ~ 0
3V3
$Comp
L power:+3.3V #PWR0102
U 1 1 607733EB
P 4200 6500
F 0 "#PWR0102" H 4200 6350 50  0001 C CNN
F 1 "+3.3V" H 4215 6673 50  0000 C CNN
F 2 "" H 4200 6500 50  0001 C CNN
F 3 "" H 4200 6500 50  0001 C CNN
	1    4200 6500
	1    0    0    -1  
$EndComp
Text GLabel 4100 6500 0    50   Input ~ 0
3V3
Wire Wire Line
	4550 6100 4550 6400
Wire Wire Line
	4200 6500 4550 6500
Wire Wire Line
	4100 6500 4200 6500
Connection ~ 4200 6500
Wire Wire Line
	6350 6200 6350 6400
Text GLabel 2450 4200 0    50   Input ~ 0
Video
Text GLabel 2450 4400 0    50   Input ~ 0
AD_trig
$Comp
L Connector_Generic:Conn_01x01 J9
U 1 1 60925258
P 2650 4600
F 0 "J9" H 2730 4642 50  0000 L CNN
F 1 "Conn_01x01" H 2730 4551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 2650 4600 50  0001 C CNN
F 3 "~" H 2650 4600 50  0001 C CNN
	1    2650 4600
	1    0    0    -1  
$EndComp
Text GLabel 2450 4600 0    50   Input ~ 0
GND
Text Notes 2400 3950 0    50   ~ 0
Debug
$Comp
L Connector_Generic:Conn_01x04 J8
U 1 1 60952354
P 2650 4200
F 0 "J8" H 2730 4242 50  0000 L CNN
F 1 "Conn_01x04" H 2730 4151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 2650 4200 50  0001 C CNN
F 3 "~" H 2650 4200 50  0001 C CNN
	1    2650 4200
	1    0    0    -1  
$EndComp
Text GLabel 2450 4300 0    50   Input ~ 0
AD_sp
$Comp
L Device:R R5
U 1 1 6128E363
P 4600 4450
F 0 "R5" H 4530 4404 50  0000 R CNN
F 1 "4.7k" H 4530 4495 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4530 4450 50  0001 C CNN
F 3 "~" H 4600 4450 50  0001 C CNN
	1    4600 4450
	-1   0    0    1   
$EndComp
Wire Wire Line
	5300 4300 5300 4400
Wire Wire Line
	3950 4300 4350 4300
$Comp
L Device:R R4
U 1 1 612952D8
P 4350 4550
F 0 "R4" H 4280 4504 50  0000 R CNN
F 1 "4.7k" H 4280 4595 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 4280 4550 50  0001 C CNN
F 3 "~" H 4350 4550 50  0001 C CNN
	1    4350 4550
	-1   0    0    1   
$EndComp
Connection ~ 4600 4600
Wire Wire Line
	4600 4600 4900 4600
Connection ~ 4600 4300
Wire Wire Line
	4600 4300 5300 4300
Wire Wire Line
	4300 4600 4600 4600
Wire Wire Line
	4300 4700 4350 4700
Connection ~ 4350 4700
Wire Wire Line
	4350 4700 4900 4700
Wire Wire Line
	4350 4400 4350 4300
Connection ~ 4350 4300
Wire Wire Line
	4350 4300 4600 4300
Text GLabel 2450 4100 0    50   Input ~ 0
CLK
Text GLabel 1050 950  0    50   Input ~ 0
MCU3V3
Text GLabel 4100 6900 0    50   Input ~ 0
MCU3V3
$Comp
L Device:R R6
U 1 1 6128E83F
P 4200 6700
F 0 "R6" H 4270 6746 50  0000 L CNN
F 1 "0" H 4270 6655 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 4130 6700 50  0001 C CNN
F 3 "~" H 4200 6700 50  0001 C CNN
	1    4200 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 6550 4200 6500
Wire Wire Line
	4200 6850 4200 6900
Wire Wire Line
	4200 6900 4100 6900
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 612CC1CC
P 1300 6250
F 0 "J4" H 1380 6242 50  0000 L CNN
F 1 "Conn_01x01" H 1380 6151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 1300 6250 50  0001 C CNN
F 3 "~" H 1300 6250 50  0001 C CNN
	1    1300 6250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 6250 1600 6250
Connection ~ 1600 6250
Wire Wire Line
	1600 6250 1600 6100
$EndSCHEMATC
