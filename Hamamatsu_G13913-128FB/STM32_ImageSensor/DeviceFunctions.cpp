#include "DeviceFunctions.h"

/***********************************************************************/
/************************* FUNCOES DE CONFIGURAÇÃO  ********************/
/***********************************************************************/

static uint16_t acquiredData[128];
static float fProcessedData[128];
static uint16_t processedData[128];
static uint8_t processedDataDAC[128];
static SysCfgTypedef currentConfig = defaultConfig;


void Device_InitialSetup()
{
  SPI.begin();  
  PWM_Setup();
  Reset_Setup();
  CfSel_Setup();
  Clock_Setup(defaultConfig.clockFrequency);
  PGA_Setup();
  Vref_Setup();
  ADC_Setup();
  ExternalADC_Setup();
  AnalogOut_Setup(defaultConfig.analogOutFreq);

  Device_SetConfig(&defaultConfig);
  Clock_Start();
}



void Device_SetConfig(const SysCfgTypedef *sConfig){
  currentConfig = *sConfig;
  
  SetSPIFreq(currentConfig.SPIfrequency);
  
  Clock_Freq((float)(currentConfig.clockFrequency));
  
  if(currentConfig.cselPin){
    CfSel_On();
  }else{
    CfSel_Off();
  }

  PWM_Config(currentConfig.pwm_period_us, currentConfig.pwm_dutycycle/100.0);
  if(currentConfig.pwm_on)
    PWM_Start();
  else
    PWM_Stop();

  PGA_SetGain(currentConfig.pga_gainSel);
  Vref_Set(currentConfig.pga_vref_mV);
  
  AnalogOut_SetFreq(currentConfig.analogOutFreq);

  if(currentConfig.externalADC)
    ExternalADC_Enable();
  else
    ExternalADC_Disable();
}


uint32_t Device_Clock(uint32_t val_hz)
{
  if(val_hz > 2000000)
    val_hz = 2000000;
  else if (val_hz < 300)
    val_hz = 300;
    
  currentConfig.clockFrequency = val_hz;
  Clock_Freq(currentConfig.clockFrequency);
  
  return currentConfig.clockFrequency;
}

uint32_t Device_IntgTime(uint32_t val_us)
{
  if(val_us > 5000000)
    val_us = 5000000;
  else if (val_us < 1)
    val_us = 1;
  
  currentConfig.integrationTime_us = val_us;

  return currentConfig.integrationTime_us;
}

bool Device_CfSel(bool val_bool)
{
  if(val_bool)
  {
    CfSel_On();
    currentConfig.cselPin = true;
  }
  else
  {
    CfSel_Off();
    currentConfig.cselPin = false;
  }
  return currentConfig.cselPin;
}

uint8_t Device_Channels(uint8_t val)
{
  if(val > 128)
  {
    val = 128;
  }
  else if(val < 1)
  {
    val = 1;
  }
  
  currentConfig.nChannels = val;

  if(currentConfig.equalChannels)
  {
    Device_EqualChannels(true);
  }

  return currentConfig.nChannels;
}

int Device_ChannelLimits(uint8_t ch, uint8_t inf_lmt, uint8_t up_lmt)
{
  if(ch > 127 || inf_lmt > 127 || up_lmt > 127 || inf_lmt > up_lmt)
  {
    return -1;
  }
  
  currentConfig.channelLimits[ch*2] = inf_lmt;
  currentConfig.channelLimits[ch*2+1] = up_lmt;

  currentConfig.equalChannels = false;

  return 0;
}


bool Device_EqualChannels(bool val)
{
  if(val){
    uint32_t ch_width = 128/currentConfig.nChannels;
  
    for(uint32_t ch=0; ch<currentConfig.nChannels; ++ch)
    {
      currentConfig.channelLimits[ch*2] = ch*ch_width;
      currentConfig.channelLimits[ch*2+1] = (ch+1)*ch_width -1;
    }
    currentConfig.equalChannels = true;
  }
  else
  {
    currentConfig.equalChannels = false;
  }
  
  return currentConfig.equalChannels;
}

uint32_t Device_PWMPeriod(uint32_t val_us)
{
  if(val_us > 200000)
  {
    val_us = 200000;
  }
  else if(val_us < 2)
  {
    val_us = 2;
  }
   
  currentConfig.pwm_period_us = val_us;
  PWM_Config(currentConfig.pwm_period_us, currentConfig.pwm_dutycycle/100.0);

  return currentConfig.pwm_period_us;
}

uint8_t Device_PWMDutyCycle(uint8_t val)
{
  if(val > 100)
  {
    val = 100;
  }
  
  currentConfig.pwm_dutycycle = val;
  PWM_Config(currentConfig.pwm_period_us, currentConfig.pwm_dutycycle/100.0);

  return currentConfig.pwm_dutycycle;
}

bool Device_PWMState(bool val)
{
  if(val)
  {
    PWM_Start();
    currentConfig.pwm_on = true;
  }
  else
  {
    PWM_Stop();
    currentConfig.pwm_on = false;
  }
  return  currentConfig.pwm_on;  
}

uint8_t Device_PGAGain(uint8_t val)
{
  switch(val)
  {
    default:
    case 1:
       currentConfig.pga_gainSel = 0;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 1;
    case 2:
       currentConfig.pga_gainSel = 1;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 2;     
    case 4:
       currentConfig.pga_gainSel = 2;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 4;     
    case 5:
       currentConfig.pga_gainSel = 3;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 5; 
    case 8:
       currentConfig.pga_gainSel = 4;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 8; 
    case 10:
       currentConfig.pga_gainSel = 5;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 10; 
    case 16:
       currentConfig.pga_gainSel = 6;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 16;       
    case 32:
       currentConfig.pga_gainSel = 7;
       PGA_SetGain(currentConfig.pga_gainSel);
       return 32;                              
  }
  
}

uint32_t Device_PGAVref(uint32_t val)
{
   if(val > 3300)
   {
     val = 3300;
   }
   currentConfig.pga_vref_mV = val;
   Vref_Set(currentConfig.pga_vref_mV);

   return currentConfig.pga_vref_mV;
}

void Device_PGAConfig(uint32_t gain)
{
  uint32_t optVref[] = {1700, 1700, 2233, 2300, 2386, 2411, 2447, 2474};
  Device_PGAGain(gain);
  Device_PGAVref(optVref[currentConfig.pga_gainSel]);
}

bool Device_ExternalADC(bool val)
{
  if(val)
  {
    ExternalADC_Enable();
    currentConfig.externalADC = true;
  }
  else
  {
    ExternalADC_Disable();
    currentConfig.externalADC = false;
  }

  return currentConfig.externalADC;
}

uint32_t Device_SPIFrequency(uint32_t val)
{
  if(val > 50000000)
  {
    val = 50000000;
  }
  else if( val < 100000)
  {
    val = 100000;
  }
  
  currentConfig.SPIfrequency = val;
  SetSPIFreq(currentConfig.SPIfrequency);

  return currentConfig.SPIfrequency;
}

bool Device_ContinuousMode(bool val)
{
  currentConfig.continuousModeOn = val;

  return currentConfig.continuousModeOn;
}

uint32_t Device_MeasureInterval(uint32_t val_ms)
{
  if(val_ms > 300000)
  {
    val_ms = 300000;
  }
  else if(val_ms < 10)
  {
    val_ms = 10;
  }
  currentConfig.acqInterval_ms = val_ms;

  return currentConfig.acqInterval_ms;
}

uint32_t Device_MeasureTimeout(uint32_t val_ms)
{
  currentConfig.acqTimeout_ms = val_ms;

  return currentConfig.acqTimeout_ms;
}

bool Device_AnalogOutput(bool val)
{
  currentConfig.analogOutOn = val;

  return currentConfig.analogOutOn;
}

uint32_t Device_AnalogOutFrequency(uint32_t val_hz)
{
  if(val_hz > 100000)
  {
    val_hz = 100000;
  }
  else if (val_hz < 1000)
  {
    val_hz = 1000;
  }
  
  currentConfig.analogOutFreq = val_hz;
  AnalogOut_SetFreq(currentConfig.analogOutFreq);

  return currentConfig.analogOutFreq;
}

bool Device_OutputModeString(bool val)
{
  currentConfig.strNotBytes = val;
  
  return currentConfig.strNotBytes;
}

// Get functions

uint32_t Device_GetClock()
{
  return currentConfig.clockFrequency;
}

uint32_t Device_GetIntgTime()
{   
  return currentConfig.integrationTime_us;

} 
bool Device_GetCfSel()
{
  return currentConfig.cselPin;
} 

uint8_t Device_GetChannels()
{
  return currentConfig.nChannels;
} 

uint8_t Device_GetChannelUpperLimit(uint8_t ch)
{
  return currentConfig.channelLimits[ch*2+1];
}

uint8_t Device_GetChannelLowerLimit(uint8_t ch)
{
   return currentConfig.channelLimits[ch*2];
}

bool Device_GetEqualChannels()
{
  return currentConfig.equalChannels;
} 
  
uint32_t Device_GetPWMPeriod()
{
  return currentConfig.pwm_period_us;
  } 
  
uint8_t Device_GetPWMDutyCycle()
{   
  return currentConfig.pwm_dutycycle;
} 

bool Device_GetPWMState()
{
  return currentConfig.pwm_on;
} 

uint8_t Device_GetPGAGain()
{   
  uint8_t gains[] = {1,2,4,5,8,10,16,32};
  return gains[currentConfig.pga_gainSel];
} 

uint32_t Device_GetPGAVref()
{   
  return currentConfig.pga_vref_mV;
} 

bool Device_GetExternalADC()
{   
  return currentConfig.externalADC;
}

uint32_t Device_GetSPIFrequency()
{   
  return currentConfig.SPIfrequency;
} 

bool Device_GetContinuousMode()
{   
  return currentConfig.continuousModeOn;
} 

uint32_t Device_GetMeasureInterval()
{   
  return currentConfig.acqInterval_ms;
} 

uint32_t Device_GetMeasureTimeout()
{   
  return currentConfig.acqTimeout_ms;
} 

bool Device_GetAnalogOutput()
{   
  return currentConfig.analogOutOn;
} 

uint32_t Device_GetAnalogOutFrequency()
{   
  return currentConfig.analogOutFreq;
} 

bool Device_GetOutputModeString()
{   
  return currentConfig.strNotBytes;
} 

/***********************************************************************/
/************* FUNÃ‡Ã•ES DE PROCESSAMENTO E TRANSMISSAO  *****************/
/***********************************************************************/


static uint32_t time_i, time_f;

int Device_Acquisition(){
  ADC_Prepare();

  Reset_Pulse_us(currentConfig.integrationTime_us);
  uint32_t time_i = millis();
  
  if(!currentConfig.pwm_on){ // If PWM was already active, it remains active.
    PWM_Start();
    while(millis()-time_i < (currentConfig.integrationTime_us / 1000));
    PWM_Stop();
  }
  
  int ret = ADC_WaitSequence(currentConfig.acqTimeout_ms);

  switch(ret){
    case 0:
      delay(2); // Fix bug where data was from previous acquisition
      ADC_GetData(acquiredData);
      return 0;
    case 1:
    default:
      if(currentConfig.strNotBytes)
        Serial.println("Error");
      else
      {
        Serial.write(0xff); // 
      }
      return 1;
    case 2:
      if(currentConfig.strNotBytes)
        Serial.println("Timeout");
      else
      {
        Serial.write(0xfe); // 
      }
      return 2;
  }
}

void Device_Process(){
    
    for(uint8_t ch = 0; ch < currentConfig.nChannels; ++ch){
      uint32_t sum = 0;
      uint8_t start_pixel = currentConfig.channelLimits[2*ch    ];
      uint8_t end_pixel   = currentConfig.channelLimits[2*ch + 1];
      for(uint8_t j = start_pixel; j <= end_pixel; ++j){
        sum += acquiredData[j];
      }
      
      if(currentConfig.externalADC){
        if(currentConfig.analogOutOn){
          processedDataDAC[ch] = (uint8_t) ((sum/(end_pixel + 1 - start_pixel)) >> 7); // tensao media em 8 bits para DAC
        }
        processedData[ch] = sum/(end_pixel + 1 - start_pixel); // tensao mÃ©dia
      }
      else
      {
        if(currentConfig.analogOutOn){
          processedDataDAC[ch] = (uint8_t) ((sum/(end_pixel + 1 - start_pixel)) >> 4); // tensao media em 8 bits para DAC
        }
        processedData[ch] = (sum/(end_pixel + 1 - start_pixel)) << 3; // media normalizada para 15 bits
      }
      fProcessedData[ch] = processedData[ch]*ADC_REF_MILIVOLT/(float)EXT_ADC_MAX_VAL;
    }
}

void Device_Transmit(){

  if(currentConfig.strNotBytes)
  {
    for(int i=0; i<currentConfig.nChannels; ++i)
    {
      Serial.println(fProcessedData[i]);
    }
    Serial.println("End");
  }
  else
  {
    Serial.write((uint8_t)currentConfig.nChannels);
    for(int i=0; i<currentConfig.nChannels; ++i)
    {
      Serial.write((uint8_t)(processedData[i]>>8));
      Serial.write((uint8_t)processedData[i]);
    }
  }
  
  if(currentConfig.analogOutOn){
    AnalogOut_WriteArray(processedDataDAC, currentConfig.nChannels);
  }
}

void Device_ContAcquisition()
{
  static uint32_t acqTime;
  if(currentConfig.continuousModeOn)
  {
    if(millis()-acqTime > (int)(currentConfig.acqInterval_ms) )
    {
      acqTime = millis();
      if(Device_Acquisition() == 0)
      {
        Device_Process();
        Device_Transmit();
      }
    }
  }
}
