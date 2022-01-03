#ifndef DEVICE_SCPI_H
#define DEVICE_SCPI_H

#include "Arduino.h"
#include "myDrivers.h"
#include "DeviceFunctions.h"

#define DEBUG__

extern "C" 
{ 
  #include "myUtils.h"
  #include "scpi.h" 
}

#define GBL_IDN "IDN"
#define GBL_RST "RST"
#define GBL_ECHO "ECHO"

#ifdef DEBUG__
#define GBL_PRINT_THIS "printThisNode"
#define GBL_PRINT_ALL "printAllNodes"
#define GBL_PRINT_THIS_SHORT "pThis"
#define GBL_PRINT_ALL_SHORT "pAll"
#endif

#define CMD_CONF_SHORT     "CONF"
#define CMD_CONF           "CONFigure"
#define SUB_CMD_DEFAULT    "default"
#define SUB_CMD_CLK        "clock"
#define SUB_CMD_INT_T      "intg"
#define SUB_CMD_CSEL       "csel"
#define SUB_CMD_N_CH       "n_ch"
#define SUB_CMD_CH_LMT     "ch_lmt"
#define SUB_CMD_CH_EQUAL   "ch_equal"
#define SUB_CMD_PWM_PERIOD "PWM_PERIOD"
#define SUB_CMD_PWM_DUTY   "PWM_DUTY"
#define SUB_CMD_PWM_STATE  "PWM_STATE"

#define SUB_CMD_PGA_GAIN   "pga_gain"
#define SUB_CMD_PGA_VREF   "pga_vref"
#define SUB_CMD_PGA_CONF   "pga_conf"
#define SUB_CMD_ADC_EXT    "adc_ext"
#define SUB_CMD_SPI_FREQ   "spi_freq"

#define CMD_MEAS_SHORT     "MEAS"
#define CMD_MEAS           "MEASure"
#define SUB_CMD_SINGLE     "single"
#define SUB_CMD_CONTINUOUS "cont"
#define SUB_CMD_INTERVAL   "interval"
#define SUB_CMD_TIMEOUT    "timeout"
#define SUB_CMD_ANALOG_OUT "anlg_out"
#define SUB_CMD_ANALOG_FREQ "anlg_freq"
#define SUB_CMD_STRING      "string"
#define SUB_CMD_BYTES       "bytes"

// TODO: GET CAPTURE COUNT
#ifdef DEBUG__
#define CMD_TEST           "TEST"
#define SUB_CMD_RST_PULSE  "resetPulse"
#define SUB_CMD_PWM_PULSE  "PWM_PULSE"

#define SUB_CMD_ANALOG_SET "anlg_val"
#define SUB_CMD_ADC_CONV   "adc_conv"
#define SUB_CMD_ADC_CAL    "adc_cal"
#define SUB_CMD_I2C_TEST   "i2c_dac"
#endif


void SCPI_Setup();
bool SCPI_IsEchoOn();


#endif
