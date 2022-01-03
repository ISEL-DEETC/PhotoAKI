#ifndef DEVICE_FUNCTIONS_H
#define DEVICE_FUNCTIONS_H

#include "Arduino.h"
#include "myDrivers.h"

extern "C" 
{ 
  #include "myUtils.h"
}

/* Device configuration struct*/

typedef struct{
  uint32_t clockFrequency;
  uint32_t integrationTime_us;
  uint32_t acqInterval_ms;
  uint32_t acqTimeout_ms;
  uint32_t pwm_period_us;
  uint32_t pga_vref_mV;
  uint32_t SPIfrequency;
  uint32_t analogOutFreq;
  uint8_t nChannels;
  uint8_t channelLimits[256];
  uint8_t pwm_dutycycle;
  uint8_t pga_gainSel;
  bool cselPin;
  bool continuousModeOn;
  bool equalChannels;
  bool pwm_on;
  bool analogOutOn;
  bool externalADC;
  bool strNotBytes;
}SysCfgTypedef;

#define DEFAULT_CHANNEL_LIMITS            {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, \
                                          10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19, \
                                          20,20,21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28,29,29, \
                                          30,30,31,31,32,32,33,33,34,34,35,35,36,36,37,37,38,38,39,39, \
                                          40,40,41,41,42,42,43,43,44,44,45,45,46,46,47,47,48,48,49,49, \
                                          50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,57,58,58,59,59, \
                                          60,60,61,61,62,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69, \
                                          70,70,71,71,72,72,73,73,74,74,75,75,76,76,77,77,78,78,79,79, \
                                          80,80,81,81,82,82,83,83,84,84,85,85,86,86,87,87,88,88,89,89, \
                                          90,90,91,91,92,92,93,93,94,94,95,95,96,96,97,97,98,98,99,99, \
                                          100,100,101,101,102,102,103,103,104,104,105,105,106,106,107,107,108,108,109,109, \
                                          110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119, \
                                          120,120,121,121,122,122,123,123,124,124,125,125,126,126,127,127} 

const SysCfgTypedef defaultConfig = {100000, 10, 1000, 1000, 1000, 1700, 10000000, 10000, 128, DEFAULT_CHANNEL_LIMITS, 50, 0, false, false, false, false, true, false, true};

/* Device Functions */ 
void Device_InitialSetup();

uint32_t Device_Clock(uint32_t val_hz);
uint32_t Device_IntgTime(uint32_t val_ms);
bool Device_CfSel(bool val_bool);
uint8_t Device_Channels(uint8_t val);
int Device_ChannelLimits(uint8_t ch, uint8_t inf_lmt, uint8_t up_lmt);
bool Device_EqualChannels(bool val);
uint32_t Device_PWMPeriod(uint32_t val_us);
uint8_t Device_PWMDutyCycle(uint8_t val);
bool Device_PWMState(bool val);
uint8_t Device_PGAGain(uint8_t val);
uint32_t Device_PGAVref(uint32_t val);
void Device_PGAConfig(uint32_t gain);
bool Device_ExternalADC(bool val);
uint32_t Device_SPIFrequency(uint32_t val);
bool Device_ContinuousMode(bool val);
uint32_t Device_MeasureInterval(uint32_t val_ms);
uint32_t Device_MeasureTimeout(uint32_t val_ms);
bool Device_AnalogOutput(bool val);
uint32_t Device_AnalogOutFrequency(uint32_t val_hz);
bool Device_OutputModeString(bool val);

uint32_t Device_GetClock();
uint32_t Device_GetIntgTime();
bool Device_GetCfSel();
uint8_t Device_GetChannels();
uint8_t Device_GetChannelUpperLimit(uint8_t ch);
uint8_t Device_GetChannelLowerLimit(uint8_t ch);
bool Device_GetEqualChannels();
uint32_t Device_GetPWMPeriod();
uint8_t Device_GetPWMDutyCycle();
bool Device_GetPWMState();
uint8_t Device_GetPGAGain();
uint32_t Device_GetPGAVref();
bool Device_GetExternalADC();
uint32_t Device_GetSPIFrequency();
bool Device_GetContinuousMode();
uint32_t Device_GetMeasureInterval();
uint32_t Device_GetMeasureTimeout();
bool Device_GetAnalogOutput();
uint32_t Device_GetAnalogOutFrequency();
bool Device_GetOutputModeString();

void Device_SetConfig(const SysCfgTypedef *sConfig);

int Device_Acquisition();
void Device_Process();
void Device_Transmit();
void Device_ContAcquisition();

#endif
