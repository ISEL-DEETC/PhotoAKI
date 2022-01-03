#ifndef _MYDRIVERS_H_
#define _MYDRIVERS_H_

#define HAL_EXTI_MODULE_ENABLED

#include <Arduino.h>
#include "SPI.h"

#define PIN_MOSI       PA7
#define PIN_MISO       PA6
#define PIN_SCK        PA5
#define PIN_CSEL       PA4
#define PIN_CLOCK      PB0
#define PIN_ADC_IN     PB1
#define PIN_ADC_START  PB10
#define PIN_ADC_TRIG   PB11
#define PIN_RESET      PA3
#define PIN_PWM        PB7  
#define PIN_CS_DAC     PA10
#define PIN_CS_PGA     PA2
#define PIN_CS_ADC     PA1

#define PIN_DAC_0      PB12
#define PIN_DAC_1      PB13
#define PIN_DAC_2      PB14
#define PIN_DAC_3      PB15
#define PIN_DAC_4      PB5
#define PIN_DAC_5      PB4
#define PIN_DAC_6      PB3
#define PIN_DAC_7      PA15

#define ADC_MAX_VAL       4095
#define EXT_ADC_MAX_VAL  32767    // 15 bits are used in single-ended mode of operation
#define ADC_REF_MILIVOLT  3300

extern volatile uint16_t data[128];

/* Clock pin functions */

void Clock_Setup(float freq);
void Clock_Start();
void Clock_Stop();
void Clock_Freq(float freq);

/* Reset pin functions */
void Reset_Setup();
void Reset_Pulse_us(uint32_t us);

/* Cf Sel pin functions */
void CfSel_Setup();
void CfSel_On();
void CfSel_Off();

/* PWM pin functions */
void PWM_Setup();
void PWM_Config(uint32_t period_us, float dutyCycle);
void PWM_Start();
void PWM_Stop();

/* Internal and external ADC functions */
void ADC_Setup();
void ADC_Prepare();
int ADC_WaitSequence(uint32_t timeout);
void ADC_GetData(uint16_t newData[128]);
void ExternalADC_Setup();
void ExternalADC_Calibrate();
void ExternalADC_Enable();
void ExternalADC_Disable();
int16_t ADC_SingleConvertion();

void SetSPIFreq(uint32_t freq);

/* Conditioning circuit functions  */
void PGA_Setup();
void PGA_SetGain(const uint8_t g);
void Vref_Setup();
bool Vref_Set(uint32_t val);
bool Vref_TestDevice();

/* Analog output functions */ 
void AnalogOut_Setup(uint32_t freq);
void AnalogOut_SetFreq(uint32_t freq);
void AnalogOut_WriteWord(uint8_t value);
void AnalogOut_WriteArray(uint8_t *data, uint32_t n);

#endif
