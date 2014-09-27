/*************************************************** 
  This is a library for the MPR121 12-Channel Capacitive Sensor

  Designed specifically to work with the MPR121 breakout from Adafruit
  ----> https://www.adafruit.com/products/1982

  These sensors use I2C to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>

// The default I2C address
#define MPR121_I2CADDR_DEFAULT 0x5A

#define MPR121_TOUCHSTATUS_L 0x00
#define MPR121_TOUCHSTATUS_H 0x01
#define MPR121_FILTDATA_0L  0x04
#define MPR121_FILTDATA_0H  0x05
#define MPR121_BASELINE_0   0x1E
#define MPR121_MHDR         0x2B
#define MPR121_NHDR         0x2C
#define MPR121_NCLR         0x2D
#define MPR121_FDLR         0x2E
#define MPR121_MHDF         0x2F
#define MPR121_NHDF         0x30
#define MPR121_NCLF         0x31
#define MPR121_FDLF         0x32
#define MPR121_NHDT         0x33
#define MPR121_NCLT         0x34
#define MPR121_FDLT         0x35

#define MPR121_TOUCHTH_0    0x41
#define MPR121_RELEASETH_0    0x42
#define MPR121_DEBOUNCE 0x5B
#define MPR121_CONFIG1 0x5C
#define MPR121_CONFIG2 0x5D
#define MPR121_CHARGECURR_0 0x5F
#define MPR121_CHARGETIME_1 0x6C
#define MPR121_ECR 0x5E
#define MPR121_AUTOCONFIG0 0x7B
#define MPR121_AUTOCONFIG1 0x7C
#define MPR121_UPLIMIT   0x7D
#define MPR121_LOWLIMIT  0x7E
#define MPR121_TARGETLIMIT  0x7F

#define MPR121_GPIODIR  0x76
#define MPR121_GPIOEN  0x77
#define MPR121_GPIOSET  0x78
#define MPR121_GPIOCLR  0x79
#define MPR121_GPIOTOGGLE  0x7A

#define MPR121_SOFTRESET 0x80

#define MPR121_BUTTON_PRESS_THRESH  10

//.. thru to 0x1C/0x1D
class Adafruit_MPR121 {
 public:
  // Variables
  int16_t wheelBaseline[8];
  uint8_t wheelPads;
  int16_t wheelDegreeOffset;
  int16_t lastWheelAngle;
  
  // Hardware I2C
  Adafruit_MPR121(void);

  boolean begin(uint8_t i2caddr = MPR121_I2CADDR_DEFAULT);

  uint16_t filteredData(uint8_t t);
  uint16_t  baselineData(uint8_t t);

  void initTouchWheel(uint8_t numWheelPads, int16_t degreeOffset);
  void takeWheelBaseline(void);
  int16_t getWheelAngle(void);
  int16_t getWheelIncrement(void);

  boolean isButtonPressed(uint8_t channel);

  uint8_t readRegister8(uint8_t reg);
  uint16_t readRegister16(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t value);
  uint16_t touched(void);
  void setThreshholds(uint8_t touch, uint8_t release);

 private:
  int8_t _i2caddr;
};

