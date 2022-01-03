/*
 * This sketch is for a optical detection module based on Hamamatsu's G13913-128FB linear image sensor and STM32 Smart V2.0
 * MCU development board. It has been made freely available for download under the Creative Commons 4.0 Copyright terms, 
 * in conformity with the open science policy, in the following repository: https://github.com/ISEL-DEETC/PhotoAKI.
 * 
 * Author: Paulo Soares
 * Date: December 2021
 * 
 * To enable support for the STM32 MCU board in the Arduino IDE, a package from STM32duino project has been used.
 * I hereby acknowledge and express my gratitude to these developers for their contributions to open source. More 
 * information on this project can be found in https://github.com/stm32duino.
 * 
 * Bellow are instructions on how to install the required software and upload this sketch to the STM32 Smart V2.0 board.
 * 
 * ------------------------------------------------------------------------------------------------------------------
 * 
 * I've successfuly used Arduino package 'STM32 Cores by STMicroelectronics version 1.9.0' and Maple DFU and serial 
 * drivers to program the STM32 MCU with the Arduino WITH and upload sketches and communicate through the COM port.
 *
 * Since then this package has deprecated so I strongly recommend to visit https://github.com/stm32duino/Arduino_Core_STM32 
 * for instructions on how to get the system up and running with updated tools.
 * 
 * -------------------------------------------------------------------------------------------------------------------
 * 
 * If you still want to follow the same steps I have, I leave the following instructions:
 * 
 * 1º Install STM32 Cores in Arduino IDE 
 * - In 'File -> Preferences -> Additional Boards Manager URLS' add:
 *   https://raw.githubusercontent.com/stm32duino/BoardManagerFiles/master/STM32/package_stm_index.json
 * - In 'Tools -> Boards Manager' search and install the the package 'STM32 Cores by STMicroelectronics version 1.9.0'
 * 
 * 2º Burn the bootloader to the MCU using ST-Link or other tool
 *   (Booatloader file from: https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/bootloader_only_binaries/smart-v2.bin )
 * 
 * 3º Install Maple DFU and serial Drivers for windows
 *   (Found in: https://github.com/jeffm852/Arduino_STM32/tree/master/drivers/win )
 * 
 * 4º Upload sketches to board using the following settings in Arduino IDE:
 *   Board: Generic STM32F1 Series
 *   Board Part Number: Generic F103C8
 *   U(S)ART Support: Enabled (generic serial)
 *   USB Support: CDC (generic 'Serial' supersede U(S)ART)
 *   USB Speed: Low/Full Speed
 *   Upload Method: Maple DFU Bootloader 2.0
 * 
 * 
 * I roughfly followed the instructions in the article on the following page:
 * https://emilio-moretti.medium.com/stm32-smart-v2-on-arduino-ide-3398be518a76
 * 
 */

 
#include "DeviceSCPI.h"


void setup() {

  Serial.begin(115200);
  Device_InitialSetup();
  SCPI_Setup();

}

const uint32_t serialReadFreq = 20;
static uint32_t serialTime;
static char cmd_buffer[256];

void loop()
{
  if(millis()-serialTime > (int)(1000.0/serialReadFreq) )
  {
    serialTime = millis();
    if(Serial.available() > 0 )
    {
      uint32_t i = 0;
      int ch;
      while((ch = Serial.read()) >=0 && ch != '\n')
      {
         cmd_buffer[i++] = (char)ch;
      }
      cmd_buffer[i]='\0';
      if(SCPI_IsEchoOn())
      {
        Serial.println(cmd_buffer);
      }
      SCPI_RunCommand(cmd_buffer);
    }
  }
  Device_ContAcquisition();

  delay(1);
}
