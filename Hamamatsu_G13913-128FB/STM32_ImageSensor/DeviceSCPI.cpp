
#include "DeviceSCPI.h"

static bool scpi_echo;

/***********************************************************************/
/******************** SETUP DOS COMANDOS SCPI  *************************/
/***********************************************************************/


void RST_Func(char *arg){
  Serial.println("RESET...");
  HAL_NVIC_SystemReset();
}

void IDN_Func(char *arg){
  Serial.println("Image sensor controller");
}

void EchoEnDis(char *arg){
  scpi_echo = ReadTrueOrFalse(arg);
}

void EchoState(char *arg){
  Serial.println(scpi_echo?"ON":"OFF");
}

void DoNothing(char * arg){}

/* Measure commands (measurement parameters, data acquisition) */

void Meas_IntervalSet(char *arg){
  Device_MeasureInterval(ReadPositiveNumber(arg));
}

void Meas_IntervalQuery(char *arg){
  Serial.println(Device_GetMeasureInterval());
}

void Measure_Single(char * arg){
  if(Device_Acquisition() == 0){ // se != 0 -> erro
    Device_Process();
    Device_Transmit();
  }
}

void Measure_ContinuousSet(char * arg){
  Device_ContinuousMode(ReadTrueOrFalse(arg));
}
 
void Measure_ContinuousQuery(char *arg){
   Serial.println(Device_GetContinuousMode()?"ON":"OFF");
}

void Meas_TimeoutSet(char *arg){
  Device_MeasureTimeout(ReadPositiveNumber(arg));
}

void Meas_TimeoutQuery(char *arg){
  Serial.println(Device_GetMeasureTimeout());
}

void Meas_AnalogOutSet(char *arg){
  Device_AnalogOutput(ReadTrueOrFalse(arg));
}

void Meas_AnalogOutQuery(char *arg){
  Serial.println(Device_GetAnalogOutput()?"ON":"OFF");
}

void Meas_AnalogOutFrequencySet(char *arg){
  Device_AnalogOutFrequency(ReadPositiveNumber(arg));
}

void Meas_AnalogOutFrequencyQuery(char *arg){
  Serial.println(Device_GetAnalogOutFrequency());
}

void Meas_SetString(char *arg)
{
  Device_OutputModeString(true);
}

void Meas_QueryString(char *arg)
{
  Serial.println(Device_GetOutputModeString());
}

void Meas_SetBytes(char *arg)
{
   Device_OutputModeString(false);
}

void Meas_QueryBytes(char *arg)
{
  Serial.println(!Device_GetOutputModeString());
}


/* Configuration commands (image sensor clock frequency, integration time... PWM parameters, signal conditioning, etc...) */


void Conf_Default(char * arg){
  Device_SetConfig(&defaultConfig);
}

void Conf_ClockSet(char *arg){
  Device_Clock(ReadPositiveNumber(arg));
}

void Conf_ClockQuery(char *arg){
  Serial.println(Device_GetClock());
}

void Conf_IntTimeSet(char *arg){
  Device_IntgTime(ReadPositiveNumber(arg));
}

void Conf_IntTimeQuery(char *arg){
  Serial.println(Device_GetIntgTime());
}

void Conf_PWM_PeriodSet(char *arg){
  Device_PWMPeriod(ReadPositiveNumber(arg));
}

void Conf_PWM_DutySet(char *arg){
  Device_PWMDutyCycle(ReadPositiveNumber(arg));
}

void Conf_PWM_PeriodQuery(char *arg){
  Serial.println(Device_GetPWMPeriod());
}

void Conf_PWM_DutyQuery(char *arg){  
  Serial.println(Device_GetPWMDutyCycle());
}

void Conf_PWM_State(char *arg){
  Device_PWMState(ReadTrueOrFalse(arg));
}

void Query_PWM_State(char *arg){
  Serial.println(Device_GetPWMState()?"ON":"OFF");
}

void Conf_CSelSet(char *arg){
  Device_CfSel(ReadTrueOrFalse(arg));
}

void Conf_CSelQuery(char *arg){
  Serial.println(Device_GetCfSel()?"HIGH":"LOW");
}

void Conf_NChannelsSet(char *arg){
  Device_Channels(ReadPositiveNumber(arg));
}

void Conf_NChannelsQuery(char *arg){
  Serial.println(Device_GetChannels());
}

void Conf_ChLimitsSet(char *arg){
  uint32_t ch, inf_lmt, up_lmt;

  ch = ReadPositiveNumber(arg) & 0x7f;
  arg = FindNextComma(arg) + 1;
  inf_lmt = ReadPositiveNumber(arg) & 0x7f;
  arg = FindNextComma(arg) + 1;
  up_lmt = ReadPositiveNumber(arg) & 0x7f;

  Device_ChannelLimits(ch, inf_lmt, up_lmt);
  
}

void Conf_ChLimitsQuery(char *arg){
  uint32_t ch;
  ch = ReadPositiveNumber(arg) & 0x7f;
  Serial.println(Device_GetChannelLowerLimit(ch));
  Serial.println(Device_GetChannelUpperLimit(ch));
}

void Conf_EqualChannels(char *arg){
  Device_EqualChannels(true);
}

void Conf_EqualChannelsQuery(char *arg)
{
  Serial.println(Device_GetEqualChannels()?"ON":"OFF");
}

void Conf_PGA_GainSet(char * arg){
  Device_PGAGain(ReadPositiveNumber(arg));
}

void Conf_PGA_GainQuery(char *arg){
  Serial.println(Device_GetPGAGain());
}

void Conf_VrefSet(char *arg){
   Device_PGAVref(ReadPositiveNumber(arg));
}

void Conf_VrefQuery(char *arg){
  Serial.println(Device_GetPGAVref());
}

void Conf_PGA_Configure(char *arg){
  Device_PGAConfig(ReadPositiveNumber(arg));
}

void Conf_ExternalADCSet(char *arg){
  Device_ExternalADC(ReadTrueOrFalse(arg));
}

void Conf_ExternalADCQuery(char *arg){
  Serial.println(Device_GetExternalADC()?"ON":"OFF");
}

void Conf_SPIFreqSet(char *arg){
  Device_SPIFrequency(ReadPositiveNumber(arg));
}

void Conf_SPIQuery(char *arg){
  Serial.println(Device_GetSPIFrequency());
}


#ifdef DEBUG__
void SCPI_PrintNodes(NodeTypedef *p){
  Serial.println(p->nodeName);
  for(int i = 0; i< p->nChilds; ++i){
    Serial.print("In ");
    Serial.print(p->nodeName);
    Serial.println(":");
    SCPI_PrintNodes(p->childNodes[i]);
  }
}

void PrintAllNodes(char *arg){
  SCPI_PrintNodes(SCPI_GetRootNode());  
}

void PrintCurrentNode(char *arg){
  Serial.print("Current node is ");
  Serial.println(SCPI_GetCurrentNode()->nodeName);
}

/* Test commands */

void TestRSTPulse(char *arg){
  uint32_t us = ReadPositiveNumber(arg);
  Reset_Pulse_us(us);
}

void Test_PWMPulse(char *arg){
  uint32_t ms = ReadPositiveNumber(arg);
  if(ms>5000)
    ms = 5000;
  PWM_Start();
  delay(ms);
  PWM_Stop();
}

void Test_AnalogSetLevel(char *arg){
  uint32_t val = ReadPositiveNumber(arg);
  if(val > 3300)
    val = 3300;
  AnalogOut_WriteWord(val*255/3300);
}

void Test_ADC_Conv(char *arg)
{
  Serial.println(ADC_SingleConvertion());
}


void Test_I2C_DAC(char *arg)
{
  Serial.println(Vref_TestDevice()?"passed":"failed");
}


void Test_ADC_Cal(char *arg)
{
  ExternalADC_Calibrate();
}

#endif

void SCPI_Setup(){
  SCPI_Initialize();
  
  SCPI_AddNode(SCPI_GetCommonNode(), GBL_RST,  NULL, RST_Func, DoNothing);
  SCPI_AddNode(SCPI_GetCommonNode(), GBL_IDN,  NULL, IDN_Func, IDN_Func);
  SCPI_AddNode(SCPI_GetCommonNode(), GBL_ECHO, NULL,  EchoEnDis,  EchoState);

  NodeTypedef * root = SCPI_GetRootNode();
  SCPI_AddNode(root, CMD_CONF, CMD_CONF_SHORT, DoNothing, DoNothing);
  SCPI_AddNode(root, CMD_MEAS, CMD_MEAS_SHORT, DoNothing, DoNothing);
 

  NodeTypedef *confNode, *measNode;
  confNode = GetNodeIn(root,CMD_CONF);
  SCPI_AddNode(confNode, SUB_CMD_DEFAULT, "def",  Conf_Default,    DoNothing);
  SCPI_AddNode(confNode, SUB_CMD_CLK,     NULL,  Conf_ClockSet,   Conf_ClockQuery);
  SCPI_AddNode(confNode, SUB_CMD_INT_T,   NULL,  Conf_IntTimeSet, Conf_IntTimeQuery);
  SCPI_AddNode(confNode, SUB_CMD_CSEL,    NULL,  Conf_CSelSet,    Conf_CSelQuery);
  SCPI_AddNode(confNode, SUB_CMD_N_CH,    NULL,  Conf_NChannelsSet, Conf_NChannelsQuery);
  SCPI_AddNode(confNode, SUB_CMD_CH_LMT,  NULL,  Conf_ChLimitsSet,   Conf_ChLimitsQuery);
  SCPI_AddNode(confNode, SUB_CMD_CH_EQUAL, NULL,  Conf_EqualChannels,   Conf_EqualChannelsQuery);
  SCPI_AddNode(confNode, SUB_CMD_PWM_PERIOD, NULL, Conf_PWM_PeriodSet,  Conf_PWM_PeriodQuery);
  SCPI_AddNode(confNode, SUB_CMD_PWM_DUTY,  NULL,  Conf_PWM_DutySet,   Conf_PWM_DutyQuery);
  SCPI_AddNode(confNode, SUB_CMD_PWM_STATE, NULL,  Conf_PWM_State,    Query_PWM_State);

  SCPI_AddNode(confNode, SUB_CMD_PGA_GAIN,  NULL,  Conf_PGA_GainSet,        Conf_PGA_GainQuery);
  SCPI_AddNode(confNode, SUB_CMD_PGA_VREF,  NULL,  Conf_VrefSet,         Conf_VrefQuery);
  SCPI_AddNode(confNode, SUB_CMD_PGA_CONF,  NULL,  Conf_PGA_Configure,         DoNothing);
  SCPI_AddNode(confNode, SUB_CMD_ADC_EXT,  NULL,   Conf_ExternalADCSet,     Conf_ExternalADCQuery);
  SCPI_AddNode(confNode, SUB_CMD_SPI_FREQ,  NULL,  Conf_SPIFreqSet,         Conf_SPIQuery);

  SCPI_AddNode(confNode, SUB_CMD_ANALOG_OUT,  NULL,  Meas_AnalogOutSet,  Meas_AnalogOutQuery);
  SCPI_AddNode(confNode, SUB_CMD_ANALOG_FREQ,  NULL,  Meas_AnalogOutFrequencySet,  Meas_AnalogOutFrequencyQuery);

  measNode = GetNodeIn(root,CMD_MEAS);
  SCPI_AddNode(measNode, SUB_CMD_SINGLE,   NULL,  Measure_Single,        DoNothing);
  SCPI_AddNode(measNode, SUB_CMD_INTERVAL,     "intv",  Meas_IntervalSet, Meas_IntervalQuery);
  SCPI_AddNode(measNode, SUB_CMD_CONTINUOUS,    NULL,  Measure_ContinuousSet, Measure_ContinuousQuery);
  SCPI_AddNode(measNode, SUB_CMD_TIMEOUT,  NULL,  Meas_TimeoutSet,  Meas_TimeoutQuery);

  SCPI_AddNode(measNode, SUB_CMD_STRING,  NULL,  Meas_SetString,  Meas_QueryString);
  SCPI_AddNode(measNode, SUB_CMD_BYTES,  NULL,  Meas_SetBytes,  Meas_QueryBytes);


#ifdef DEBUG__
  NodeTypedef *testNode;
  SCPI_AddNode(root, CMD_TEST,  NULL,  DoNothing,  DoNothing);
  testNode  = GetNodeIn(root,CMD_TEST);
  SCPI_AddNode(testNode, SUB_CMD_RST_PULSE, NULL,  TestRSTPulse,     DoNothing);
  SCPI_AddNode(testNode, SUB_CMD_PWM_PULSE,  NULL, Test_PWMPulse,    DoNothing);
  SCPI_AddNode(testNode, SUB_CMD_ANALOG_SET, NULL, Test_AnalogSetLevel,    DoNothing);
  SCPI_AddNode(testNode, SUB_CMD_ADC_CONV,  NULL,  Test_ADC_Conv,    DoNothing);
  SCPI_AddNode(testNode, SUB_CMD_ADC_CAL,  NULL,   Test_ADC_Cal,    DoNothing);
  SCPI_AddNode(testNode, SUB_CMD_I2C_TEST,  NULL,  Test_I2C_DAC,    DoNothing);

  SCPI_AddNode(SCPI_GetCommonNode(), GBL_PRINT_ALL,  GBL_PRINT_ALL_SHORT,  PrintAllNodes,  DoNothing);
  SCPI_AddNode(SCPI_GetCommonNode(), GBL_PRINT_THIS, GBL_PRINT_THIS_SHORT,  PrintCurrentNode,  DoNothing);
  
#endif
  
}

bool SCPI_IsEchoOn()
{
  return scpi_echo;
}
