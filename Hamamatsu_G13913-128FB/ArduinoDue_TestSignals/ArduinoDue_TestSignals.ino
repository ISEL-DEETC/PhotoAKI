/*
 * Código elaborado para a placa do Arduino DUE. 
 * 22 December 2021
 * 
 * It generates a test video signal together with single pulse and trigger auxiliary signals.
 * The test signal is selected by bringing the corresponding pin to logic value '0'.
 * Avaiable signals are:
 * - Ramp, from 2.5 to 0.55 V (lower voltage limited by Arduino Due's DAC range, otherwise would be 0.3 V)
 * - Abs(Sine) with two peaks, with varying phase, from 2.5 to 1.5 V
 * - Sync signal, with logic value '1' for pixels 1, 64 and 128 corresponding time slots, logic value '0' otherwise
 * 
 * Inputting a clock signal on PIN_CLOCK will generate a test signal at the given input frequency up to ~50 kHz 
 * (limited by arduino due processing and interrupt handling capability), otherwise a frequency of 10 kHz will be used
 * 
 */

// Alguns pinos livres do arduino DUE
#define PC0   31
#define PC1   33
#define PC2   34
#define PC3   35
#define PC4   36
#define PC5   37
#define PC6   38
#define PC7   39
#define PC8   40
#define PC9   41

// Alocação dos pinos do sensor a simular
#define PIN_RAMP        PC0
#define PIN_SINE        PC1
#define PIN_SYNCTEST    PC3
#define PIN_VIDEO       DAC1
#define PIN_ADC_START   PC5
#define PIN_ADC_TRIG    PC7
#define PIN_CLOCK       PC9

#define HALF_CLOCK_PERIOD 50 //us -> 10k Hz

// Constantes 
#define VOLTS_MAX       3.3 // unused
#define VOLTS_DARK      2.5 // unused
#define VOLTS_SAT       0.3 // unused
#define BITS_DAC        12
#define DAC_MAX_VAL     4095
#define DAC_MAX_VOLTAGE 2.82 // typ 2.75
#define DAC_MIN_VOLTAGE 0.58 // typ 5.5
#define DAC_VOLTAGE_RANGE (DAC_MAX_VOLTAGE-DAC_MIN_VOLTAGE)

#define VoltsToDAC(x) ((( x>DAC_MIN_VOLTAGE? x-DAC_MIN_VOLTAGE : 0)/DAC_VOLTAGE_RANGE > 1 ? DAC_MAX_VAL :  (x>DAC_MIN_VOLTAGE ? x-DAC_MIN_VOLTAGE : 0))/DAC_VOLTAGE_RANGE*DAC_MAX_VAL ) 

#define SINE_AMPLITUDE 1
#define SINE_OFFSET    1.5

volatile uint16_t testSignalPulse[128];
volatile uint16_t testSignalRamp[128];
volatile uint16_t testSignalSine[128];

volatile bool clockTickUp;
volatile bool clockTickDown;
volatile bool useExternal;

void Clk_IRQ(){
  if(digitalRead(PIN_CLOCK) == HIGH)
  {
    clockTickUp = true;
  }
  else
  {
    clockTickDown = true;
  }
  useExternal = true;
}


void setup() {
  analogWriteResolution(BITS_DAC);
  pinMode(PIN_RAMP, INPUT_PULLUP);
  pinMode(PIN_SINE, INPUT_PULLUP);
  pinMode(PIN_SYNCTEST, INPUT_PULLUP);
  pinMode(PIN_ADC_START, OUTPUT);
  pinMode(PIN_ADC_TRIG, OUTPUT);
  pinMode(PIN_CLOCK, INPUT);
  
  attachInterrupt(PIN_CLOCK, Clk_IRQ, CHANGE );
  
  for(int i = 0; i<128; ++i){ 
    testSignalPulse[i] = (i == 0 || i == 63 || i == 127) * DAC_MAX_VAL;
    testSignalRamp[i] = VoltsToDAC( DAC_MIN_VOLTAGE + (2.5 - DAC_MIN_VOLTAGE)*(1-i/128.0) );
    testSignalSine[i] = VoltsToDAC( abs( sin( 2*3.1415 * 1 * i/128.0 ))*SINE_AMPLITUDE + SINE_OFFSET); // 2.5V to 1.5 V
  }
  
  clockTickUp = false;
  clockTickDown = false;
  useExternal = false;
}


static uint32_t time_last;
static int32_t phase = 0;
static uint32_t count = 0;

void loop() {

  if(useExternal){
    clockTickUp = false;
    clockTickDown = false;
    
    if(digitalRead(PIN_RAMP)==LOW)
    {
      while(!clockTickUp);
      digitalWrite(PIN_ADC_START, HIGH);
      clockTickUp = false;
      
      while(!clockTickDown);
      digitalWrite(PIN_ADC_START, LOW);
      clockTickDown = false;
  
      for(int i = 0; i<128; ++i)
      {
        while(!clockTickUp);
        analogWrite(PIN_VIDEO, testSignalRamp[i]);
        clockTickUp = false;
  
        while(!clockTickDown);
        digitalWrite(PIN_ADC_TRIG, HIGH);
        digitalWrite(PIN_ADC_TRIG, LOW);
        clockTickDown = false;
      }
    }
    else if(digitalRead(PIN_SINE)==LOW)
    {
      while(!clockTickUp);
      digitalWrite(PIN_ADC_START, HIGH);
      clockTickUp = false;
      
      while(!clockTickDown);
      digitalWrite(PIN_ADC_START, LOW);
      clockTickDown = false;
  
      for(int i = 0; i<128; ++i)
      {
        while(!clockTickUp);
        analogWrite(PIN_VIDEO, testSignalSine[i]);
        clockTickUp = false;
  
        while(!clockTickDown);
        digitalWrite(PIN_ADC_TRIG, HIGH);
        digitalWrite(PIN_ADC_TRIG, LOW);
        clockTickDown = false;
      }

      while(!clockTickUp);
      while(!clockTickDown);
      analogWrite(PIN_VIDEO, 0);
    }
    else if(digitalRead(PIN_SYNCTEST)==LOW)
    {
      while(!clockTickUp);
      digitalWrite(PIN_ADC_START, HIGH);
      clockTickUp = false;
      
      while(!clockTickDown);
      digitalWrite(PIN_ADC_START, LOW);
      clockTickDown = false;
  
      for(int i = 0; i<128; ++i)
      {
        while(!clockTickUp);
        analogWrite(PIN_VIDEO, testSignalPulse[i]);
        clockTickUp = false;
  
        while(!clockTickDown);
        digitalWrite(PIN_ADC_TRIG, HIGH);
        digitalWrite(PIN_ADC_TRIG, LOW);
        clockTickDown = false;
      }
    }
  }
  else
  {
     if(digitalRead(PIN_RAMP)==LOW)
    {

      digitalWrite(PIN_ADC_START, HIGH);
      delayMicroseconds(HALF_CLOCK_PERIOD);
      digitalWrite(PIN_ADC_START, LOW);
      delayMicroseconds(HALF_CLOCK_PERIOD);
  
      for(int i = 0; i<128; ++i)
      {
        analogWrite(PIN_VIDEO, testSignalRamp[i]);
        delayMicroseconds(HALF_CLOCK_PERIOD);
        digitalWrite(PIN_ADC_TRIG, HIGH);
        digitalWrite(PIN_ADC_TRIG, LOW);
        delayMicroseconds(HALF_CLOCK_PERIOD);
      }
    }
    else if(digitalRead(PIN_SINE)==LOW)
    {
      digitalWrite(PIN_ADC_START, HIGH);
      delayMicroseconds(HALF_CLOCK_PERIOD);
      digitalWrite(PIN_ADC_START, LOW);
      delayMicroseconds(HALF_CLOCK_PERIOD);
  
      for(int i = 0; i<128; ++i)
      {
        analogWrite(PIN_VIDEO, testSignalSine[i]);
        delayMicroseconds(HALF_CLOCK_PERIOD);
        digitalWrite(PIN_ADC_TRIG, HIGH);
        digitalWrite(PIN_ADC_TRIG, LOW);
        delayMicroseconds(HALF_CLOCK_PERIOD);
      }
        delayMicroseconds(HALF_CLOCK_PERIOD);
        delayMicroseconds(HALF_CLOCK_PERIOD);
        analogWrite(PIN_VIDEO, 0);
  
    }
    else if(digitalRead(PIN_SYNCTEST)==LOW)
    {
      digitalWrite(PIN_ADC_START, HIGH);
      delayMicroseconds(HALF_CLOCK_PERIOD);
      digitalWrite(PIN_ADC_START, LOW);
      delayMicroseconds(HALF_CLOCK_PERIOD);
  
      for(int i = 0; i<128; ++i)
      {
        analogWrite(PIN_VIDEO, testSignalPulse[i]);
        delayMicroseconds(HALF_CLOCK_PERIOD);
        digitalWrite(PIN_ADC_TRIG, HIGH);
        digitalWrite(PIN_ADC_TRIG, LOW);
        delayMicroseconds(HALF_CLOCK_PERIOD);
      }
    }
  }
  for(int i = 0; i<128; ++i){
    testSignalSine[i] = VoltsToDAC( abs( sin( 2*3.1415 * i/128.0 + phase*3.1416/180))*SINE_AMPLITUDE + SINE_OFFSET); // 2.5V to 1.5 V
  }
  phase = 180*sin(2*3.1416 * count/300.0);
  count = (count+1)%300;
}
