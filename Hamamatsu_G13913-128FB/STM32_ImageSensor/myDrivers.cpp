#include "myDrivers.h"
#include "stm32f1xx_hal_exti.h"


static uint32_t spiFreq = 10000000;
void SetSPIFreq(uint32_t freq){
  spiFreq = freq;
}

/***********************************************************************/
/******************* FUNÇÕES DE CONTROLO DO SENSOR *********************/
/***********************************************************************/


void Clock_Setup(float freq){
  
  if(freq < 300)
    freq = 300;
  else if(freq > 2e6)
    freq = 2e6;
 
  /* Clock enable */  
  __HAL_RCC_TIM3_CLK_ENABLE();

  /* Pin GPIO Config*/
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin = GPIO_PIN_0;
  gpio_init.Mode   = GPIO_MODE_AF_PP;
  gpio_init.Pull   = GPIO_NOPULL;
  gpio_init.Speed  = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &gpio_init);

  /* Timer config */
  TIM3->CR1 = 0;
  TIM3->CR2 = 0;
  TIM3->CCR3 = 0;
  TIM3->CCMR2 = 0b011 << 4; // 011 - OC1REF toggles when TIMx_CNT=TIMx_CCR1
  TIM3->CCER = 1 << 8; // Capture/Compare 3 output enable
  TIM3->CNT = 0;
  TIM3->PSC = (uint16_t)((18e6/freq)-1);
  TIM3->ARR = 1;
 
  AFIO->MAPR |= (0b10 << 10); // REMAP TIM3 CH2 to PB5, avoid conflict with SPI1 MISO
}

void Clock_Start(){
  TIM3->CR1 |= 1; 
}
void Clock_Stop(){
  TIM3->CR1 &= ~1; 
}
void Clock_Freq(float freq){
  if(freq < 300)
    freq = 300;
  else if(freq > 2e6)
    freq = 2e6;
  TIM3->PSC = (uint16_t)((18e6/freq)-1);
}

void Reset_Setup(){
  __HAL_RCC_TIM2_CLK_ENABLE();
 
  /* Pin GPIO Config*/
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin = GPIO_PIN_3;
  gpio_init.Mode   = GPIO_MODE_AF_PP;
  gpio_init.Pull   = GPIO_NOPULL;
  gpio_init.Speed  = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOA, &gpio_init);

  TIM2->CCMR2 = 0b111 << 12 | 1<<10;  // PWM MODE 2, ch active while TIMx_CNT > TIMx_CCRx in upcounting, fast enable
  TIM2->CCER = 1 << 12; // OUTPUT ENABLE CH4
  TIM2->CR2 = 0;
  TIM2->CR1 = 1<<3; // OPM
}


void Reset_Pulse_us(uint32_t us){
  if(us > 5000000)
    us = 5000000;
  
  if(us > 1000)
  {
    TIM2->PSC = 7199; // base temporal de 100 microssegundo
    TIM2->ARR = us/100;
  }
  else
  {
    TIM2->PSC = 71; // base temporal de 1/2 microssegundo
    TIM2->ARR = us;
  }
  TIM2->CNT = 0;
  TIM2->CCR4 = 1; //
  TIM2->CR1 |= 1; // CEN
}

void CfSel_Setup(){
  pinMode(PIN_CSEL, OUTPUT);
}

void CfSel_On(){
  digitalWrite(PIN_CSEL, HIGH);
}

void CfSel_Off(){
 digitalWrite(PIN_CSEL, LOW);
}

/***********************************************************************/
/**************** FUNÇÕES DE CONTROLO DA FONTE DE LUZ ******************/
/***********************************************************************/

void PWM_Setup(){
  __HAL_RCC_TIM4_CLK_ENABLE();

  /* Pin GPIO Config*/
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin = GPIO_PIN_7;
  gpio_init.Mode   = GPIO_MODE_AF_PP;
  gpio_init.Pull   = GPIO_NOPULL;
  gpio_init.Speed  = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &gpio_init);

  TIM4->PSC = (uint16_t)(72e0-1); // base temporal de 1 microssegundo
  TIM4->CNT = 0;
  TIM4->ARR = 1000;
  TIM4->CCR2 = 1; 
  TIM4->EGR |= 1; // UPDATE GENERATION
  TIM4->CCMR1 = 0b110 << 12 | 1<<10;  // PWM MODE 1, ch active while TIMx_CNT < TIMx_CCRx in upcounting, fast enable
  TIM4->CCER = 0;
  TIM4->CR2 = 0;

}

void PWM_Config(uint32_t period_us, float dutyCycle){
  TIM4->CNT = 0;
  TIM4->ARR = period_us - 1; 
  TIM4->CCR2 = period_us*dutyCycle;
}

void PWM_Start(){
  TIM4->CCER = 1 << 4;
  TIM4->CR1 = 1; // CEN
}

void PWM_Stop(){
  TIM4->CCER = 0;
  TIM4->CR1 = 0; // CEN
}



/***********************************************************************/
/*************************** FUNÇÕES DO ADC ****************************/
/***********************************************************************/
volatile uint16_t data[128];
volatile uint16_t data_i = 0;
volatile bool sequence_finish;
volatile bool sequence_error;
static bool externalADC = false;
static ADC_HandleTypeDef hadc;
static EXTI_HandleTypeDef hexti;

void ADC_Start_IRQ(){
  data_i = 0;
}

void Setup_ADC_StartPin(){
  pinMode(PIN_ADC_START, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(PIN_ADC_START), ADC_Start_IRQ, FALLING); 
}

void ADC_Setup(){

  externalADC = false;
  sequence_finish = true;
  sequence_error = false;
  
  /* Config. Clock ADC */
  RCC_PeriphCLKInitTypeDef PeriphClkInit;
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
  RCC->APB2ENR |= 1 << 9;

  /* Config. ADC */
  hadc.Instance = ADC1;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE; // discarded
  hadc.Init.NbrOfDiscConversion = 1; // discarded
  hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_EXT_IT11; // ADC_SOFTWARE_START;

  HAL_NVIC_SetPriority(ADC1_2_IRQn, 2, 1);
  HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

  /* Config. canal ADC */ 
  ADC_ChannelConfTypeDef ADC_channel_config;
  ADC_channel_config.Channel = ADC_CHANNEL_9;
  ADC_channel_config.Rank = ADC_REGULAR_RANK_1;
  ADC_channel_config.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

  HAL_ADC_Init(&hadc);
  HAL_ADC_ConfigChannel(&hadc, &ADC_channel_config);

  /* Config Pin Input */   
  GPIO_InitTypeDef gpio_init;
  gpio_init.Pin    = GPIO_PIN_1;
  gpio_init.Mode   = GPIO_MODE_ANALOG;
  gpio_init.Pull   = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &gpio_init);

  /* Config EXTI pin PB11*/
  GPIO_InitTypeDef pin_b11_init;
  pin_b11_init.Pin    = GPIO_PIN_11;
  pin_b11_init.Mode   = GPIO_MODE_INPUT;
  pin_b11_init.Pull   = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &pin_b11_init);

  /* Config EXTI */
  EXTI_ConfigTypeDef extiConfig;
  extiConfig.Line = EXTI_LINE_11;
  extiConfig.Mode = EXTI_MODE_EVENT;// | EXTI_MODE_INTERRUPT;
  extiConfig.Trigger = EXTI_TRIGGER_RISING;
  extiConfig.GPIOSel = EXTI_GPIOB; //EXTI_GPIOA
  HAL_EXTI_SetConfigLine(&hexti, &extiConfig );

  /* Pin com interrupção que provoca inicio da captura */
  Setup_ADC_StartPin(); 
}

extern "C"
{
  void ADC1_2_IRQHandler(void){
    if( !sequence_finish && !externalADC){
      data[data_i++] = HAL_ADC_GetValue(&hadc);
      if(data_i >= 128){
         HAL_ADC_Stop_IT(&hadc);
         sequence_finish = true;
      }
    }else{
      HAL_ADC_GetValue(&hadc);
    }
    HAL_NVIC_ClearPendingIRQ(ADC1_2_IRQn);
  }
}

void ADC_Prepare(){
  sequence_finish = false; 
  sequence_error = false;
  data_i = 0;
  if(externalADC)
  {
    SPI.beginTransaction(SPISettings(spiFreq, MSBFIRST, SPI_MODE1));
    digitalWrite(PIN_MOSI, HIGH); // SDI signal high during whole cycle
    digitalWrite(PIN_CS_ADC, LOW); // Chip select on.
  }else
  {
    HAL_ADC_Start_IT(&hadc);
  }
}

int ADC_WaitSequence(uint32_t timeout){
  uint32_t ini = millis();
  while( (millis()-ini < timeout))
  {
    if(sequence_error == true){
      return 1;
    }
    if(sequence_finish == true){
      return 0;
    }
  }
  return 2; // timeout
}

void ADC_GetData(uint16_t newData[128]){
  for(int i=0; i<128; ++i){
    newData[i] = data[i];
  }
}

int16_t ADC_SingleConvertion(){
  if(externalADC)
  {
    uint16_t sample = 0;
    
    digitalWrite(PIN_CS_ADC, LOW); // Chip select on. First sample will be taken on rising edge
  
    SPI.beginTransaction(SPISettings(spiFreq, MSBFIRST, SPI_MODE1));
    digitalWrite(PIN_MOSI, HIGH);
    delayMicroseconds(10);
    SPI.transfer(0xff); // Read garbage
    SPI.transfer(0xff);

    digitalWrite(PIN_CS_ADC, HIGH); // CONVST signal, sample is hold and converstion starts
    digitalWrite(PIN_CS_ADC, LOW); // chip select, data transfer
    delayMicroseconds(10);
    sample = SPI.transfer(0xff) << 8;
    sample += SPI.transfer(0xff);

    SPI.endTransaction();
    digitalWrite(PIN_CS_ADC, HIGH); // last convertion, CS HIGH to free SPI 

    return sample;
  }
  else
  {
    HAL_ADC_Start(&hadc);
    if(HAL_ADC_PollForConversion(&hadc, 1000) == HAL_OK){
      return HAL_ADC_GetValue(&hadc) << 3;
    }else{
      return -1;
    }
  }
}

void ExternalADCTrig_IRQ(){
    if( !sequence_finish && externalADC){
      digitalWrite(PIN_CS_ADC, HIGH); // CONVST signal, sample is hold and conversion starts
      digitalWrite(PIN_CS_ADC, LOW); // chip select, data transfer
      delayMicroseconds(2);//delayMicroseconds(extADCdelay);
      data[data_i] = SPI.transfer(0xff) << 8;
      data[data_i] += SPI.transfer(0xff);
      if(++data_i >= 128){
         sequence_finish = true;
         SPI.endTransaction();
         digitalWrite(PIN_CS_ADC, HIGH); // last convertion, CS HIGH to free SPI 
      }
    }
}

void ExternalADC_Setup(){
  pinMode(PIN_ADC_TRIG, INPUT_PULLUP);
  pinMode(PIN_CS_ADC, OUTPUT);
}

void ExternalADC_Calibrate()
{
  SPI.beginTransaction(SPISettings(spiFreq, MSBFIRST, SPI_MODE1));
  digitalWrite(PIN_MOSI, HIGH); // SDI high during whole process
  
  digitalWrite(PIN_CS_ADC,LOW); // force low to high transistion for conversion
  digitalWrite(PIN_CS_ADC,HIGH); 

  digitalWrite(PIN_CS_ADC,LOW); // Data reading
  delayMicroseconds(5);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  
  for(uint16_t i = 0; i < 128; ++i){ // 1024 clocks during CNVST = LOW for calibration command
    SPI.transfer(0xff);
  }

  delay(550); // tCAL ~ 500ms
  
  digitalWrite(PIN_CS_ADC, HIGH);
  SPI.endTransaction();
}

void ExternalADC_Enable(){
  sequence_finish = true;
  HAL_ADC_Stop_IT(&hadc);
  HAL_NVIC_ClearPendingIRQ(ADC1_2_IRQn);
  externalADC = true;
  attachInterrupt(digitalPinToInterrupt(PIN_ADC_TRIG), ExternalADCTrig_IRQ, RISING);
}

void ExternalADC_Disable(){
  sequence_finish = true;
  externalADC = false;
  detachInterrupt(digitalPinToInterrupt(PIN_ADC_TRIG));
  ADC_Setup();
}


/***********************************************************************/
/************ FUNÇÕES DO ACONDICIONAMENTO DO SINAL *********************/
/***********************************************************************/

// PGA pode usar modo SPI 0,0 ou 1,1
const uint8_t PGA_INSTR_SHUTDOWN = 0b00100000; 
const uint8_t PGA_INSTR_GAIN     = 0b01000000; 

void PGA_Setup(){
  pinMode(PIN_CS_PGA, OUTPUT);
  digitalWrite(PIN_CS_PGA, HIGH);
  PGA_SetGain(0);
}

void PGA_SetGain(const uint8_t gainSel){
  digitalWrite(PIN_CS_PGA, LOW);

  SPI.beginTransaction(SPISettings(spiFreq, MSBFIRST, SPI_MODE0));
  SPI.transfer( PGA_INSTR_GAIN );
  SPI.transfer( gainSel & 0b111 );
  SPI.endTransaction();  
  
  digitalWrite(PIN_CS_PGA,HIGH);
}


/** Soft I2C **/
#define GPOD_10MHZ      0b0101
#define GPIO_OUT_2MHz   0b0001
#define GPIO_IN_PULLUP  0b1000
#define SET_SCL_HIGH     (GPIOB->ODR |= 1<<8)
#define SET_SCL_LOW      (GPIOB->ODR &= ~(1<<8))
#define SET_SDA_HIGH     (GPIOB->ODR |= 1<<9)
#define SET_SDA_LOW      (GPIOB->ODR &= ~(1<<9))
#define DELAY_QUARTER_I2C    (delayMicroseconds(3)) // 12 us total clock period -> 83kHz

//#define SOFTI2C_OD_FOR_ACK_ONLY

void SoftI2C_Setup(){
  GPIOB->CRH &= ~(0xFF);
#ifdef SOFTI2C_OD_FOR_ACK_ONLY
  GPIOB->CRH |= GPIO_OUT_2MHz | GPIO_OUT_2MHz << 4 ; // PB8 PB9
#else
  GPIOB->CRH |= GPOD_10MHZ | GPOD_10MHZ << 4 ; // PB8 PB9
#endif
  SET_SDA_HIGH;
  SET_SCL_HIGH;
}

void SoftI2C_Start(){
  //SDA E SCL HIGH
  DELAY_QUARTER_I2C;
  DELAY_QUARTER_I2C;
  SET_SDA_LOW;
  DELAY_QUARTER_I2C;
  DELAY_QUARTER_I2C;
}

void SoftI2C_Stop(){
  SET_SCL_LOW;
  DELAY_QUARTER_I2C;
  DELAY_QUARTER_I2C;
  SET_SDA_LOW;
  DELAY_QUARTER_I2C;
  DELAY_QUARTER_I2C;
  SET_SCL_HIGH;
  DELAY_QUARTER_I2C;
  DELAY_QUARTER_I2C;
  SET_SDA_HIGH;
}

bool SoftI2C_ReadAck(){
#ifdef SOFTI2C_OD_FOR_ACK_ONLY
  GPIOB->CRH &= ~(0xF<<4);
  GPIOB->CRH |= GPIO_IN_PULLUP << 4 ; // PB9
#else
  SET_SDA_HIGH;
#endif
  SET_SCL_LOW;
  DELAY_QUARTER_I2C;
  DELAY_QUARTER_I2C;
  SET_SCL_HIGH;
  DELAY_QUARTER_I2C;
  uint8_t ack = (GPIOB->IDR & (1<<9)) >> 9; // read PB9
  DELAY_QUARTER_I2C;
  SET_SCL_LOW;
#ifdef SOFTI2C_OD_FOR_ACK_ONLY
  GPIOB->CRH &= ~(0xF<<4);
  GPIOB->CRH |=  GPIO_OUT_2MHz << 4 ; // PB9
#endif
  return ack == 0;
}

void SoftI2C_SendByte(uint8_t data){
  for(int8_t i=7; i >= 0; --i){
    SET_SCL_LOW;
    DELAY_QUARTER_I2C;
    ((data & 1<<i) >> i)?SET_SDA_HIGH:SET_SDA_LOW;
    DELAY_QUARTER_I2C;
    SET_SCL_HIGH;
    DELAY_QUARTER_I2C;
    DELAY_QUARTER_I2C;
  }
}


bool SoftI2C_Send(uint8_t addr, uint8_t *pData, uint8_t n_bytes){

  SoftI2C_Start();
  SoftI2C_SendByte(addr << 1);
  if(!SoftI2C_ReadAck()){
    SoftI2C_Stop();
    return false;
  }
  for(int i = 0; i< n_bytes; ++i){
    SoftI2C_SendByte(pData[i]);
    if(!SoftI2C_ReadAck()){
      SoftI2C_Stop();
      return false;
    }
  }
  SoftI2C_Stop();
  return true;
}

bool SoftI2C_DeviceReady(uint8_t addr){

  SoftI2C_Start();
  SoftI2C_SendByte(addr << 1);
  bool ack = SoftI2C_ReadAck();
  SoftI2C_Stop();

  return ack;
}

/** MCP4725 - DAC 12 bits para deslocamento de nivel **/
#define DAC_7BIT_ADD  0b1100010    //0b1100110 chip anterior
#define DAC_WRITE_CMD 0b01000000   //WRITE, PD MODE 0
#define DAC_MAX_MV 3300.0
#define DAC_MAX_BIN 4096.0


void Vref_Setup(){
  SoftI2C_Setup();
}

bool Vref_Set(uint32_t milivolts){

  if(milivolts > 3299){
    milivolts = 3299;
  }
  uint16_t value = (uint16_t)(DAC_MAX_BIN/DAC_MAX_MV*milivolts + 0.5) & 0x0fff;
  uint8_t data[3];
  data[0] = DAC_WRITE_CMD;
  data[1] = (uint8_t)(value >> 4);
  data[2] = (uint8_t)(value << 4);
    
  return SoftI2C_Send(DAC_7BIT_ADD, data, 3);
}

bool Vref_TestDevice()
{
  return SoftI2C_DeviceReady(DAC_7BIT_ADD);
}


/***********************************************************************/
/*************************** FUNÇÕES DO DAC ****************************/
/***********************************************************************/

static uint32_t AnalogOutFrequency = 1000;

void AnalogOut_Setup(uint32_t freq)
{
  pinMode(PIN_DAC_0, OUTPUT);
  pinMode(PIN_DAC_1, OUTPUT);
  pinMode(PIN_DAC_2, OUTPUT);
  pinMode(PIN_DAC_3, OUTPUT);
  pinMode(PIN_DAC_4, OUTPUT);
  pinMode(PIN_DAC_5, OUTPUT);
  pinMode(PIN_DAC_6, OUTPUT);
  pinMode(PIN_DAC_7, OUTPUT);
  pinMode(PIN_CS_DAC, OUTPUT);

  AnalogOutFrequency = freq; 
  AnalogOut_WriteWord(0);
}

void AnalogOut_SetFreq(uint32_t freq)
{
  if(freq > 100000)
    freq = 100000;
  else if(freq < 1000)
    freq = 1000;
  
  AnalogOutFrequency = freq;  
}

void AnalogOut_WriteWord(uint8_t value)
{
  digitalWrite(PIN_DAC_7, value & (1<<7));
  digitalWrite(PIN_DAC_6, value & (1<<6));
  digitalWrite(PIN_DAC_5, value & (1<<5));
  digitalWrite(PIN_DAC_4, value & (1<<4));
  digitalWrite(PIN_DAC_3, value & (1<<3));
  digitalWrite(PIN_DAC_2, value & (1<<2));  
  digitalWrite(PIN_DAC_1, value & (1<<1));
  digitalWrite(PIN_DAC_0, value & (1));
  
  digitalWrite(PIN_CS_DAC, LOW);
  delayMicroseconds(1);
  digitalWrite(PIN_CS_DAC, HIGH);
}

void AnalogOut_WriteArray(uint8_t *data, uint32_t n)
{
  AnalogOut_WriteWord(255);
  delayMicroseconds(1*1e6/AnalogOutFrequency);
  AnalogOut_WriteWord(0);
  delayMicroseconds(1*1e6/AnalogOutFrequency);
  AnalogOut_WriteWord(255);
  delayMicroseconds(1*1e6/AnalogOutFrequency);
  AnalogOut_WriteWord(0);
  delayMicroseconds(1*1e6/AnalogOutFrequency);
  for(uint32_t i = 0; i<n; ++i){
    AnalogOut_WriteWord(data[i]);
    delayMicroseconds(1e6/AnalogOutFrequency);
  }
  AnalogOut_WriteWord(0);
}
