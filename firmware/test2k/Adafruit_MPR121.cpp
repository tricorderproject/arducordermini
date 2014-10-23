/*************************************************** 
  This is a library for the MPR121 I2C 12-chan Capacitive Sensor

  Designed specifically to work with the MPR121 sensor from Adafruit
  ----> https://www.adafruit.com/products/1982

  These sensors use I2C to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  Modified by Peter Jansen to include support for capacitive touch wheels. 
 ****************************************************/

#include "Adafruit_MPR121.h"

Adafruit_MPR121::Adafruit_MPR121() {
}

boolean Adafruit_MPR121::begin(uint8_t i2caddr) {
  Wire.begin();
    
  _i2caddr = i2caddr;

  // soft reset
  writeRegister(MPR121_SOFTRESET, 0x63);
  delay(1);
  for (uint8_t i=0; i<0x7F; i++) {
  //  Serial.print("$"); Serial.print(i, HEX); 
  //  Serial.print(": 0x"); Serial.println(readRegister8(i));
  }
  

  writeRegister(MPR121_ECR, 0x0);

  uint8_t c = readRegister8(MPR121_CONFIG2);
  
  if (c != 0x24) return false;


  setThreshholds(12, 6);
  writeRegister(MPR121_MHDR, 0x01);
  writeRegister(MPR121_NHDR, 0x01);
  writeRegister(MPR121_NCLR, 0x0E);
  writeRegister(MPR121_FDLR, 0x00);

  writeRegister(MPR121_MHDF, 0x01);
  writeRegister(MPR121_NHDF, 0x05);
  writeRegister(MPR121_NCLF, 0x01);
  writeRegister(MPR121_FDLF, 0x00);

  writeRegister(MPR121_NHDT, 0x00);
  writeRegister(MPR121_NCLT, 0x00);
  writeRegister(MPR121_FDLT, 0x00);

  writeRegister(MPR121_DEBOUNCE, 0);
  writeRegister(MPR121_CONFIG1, 0x10); // default, 16uA charge current
  writeRegister(MPR121_CONFIG2, 0x20); // 0.5uS encoding, 1ms period

//  writeRegister(MPR121_AUTOCONFIG0, 0x8F);

//  writeRegister(MPR121_UPLIMIT, 150);
//  writeRegister(MPR121_TARGETLIMIT, 100); // should be ~400 (100 shifted)
//  writeRegister(MPR121_LOWLIMIT, 50);
  // enable all electrodes
  writeRegister(MPR121_ECR, 0x8F);  // start with first 5 bits of baseline tracking 

  return true;
}

void Adafruit_MPR121::setThreshholds(uint8_t touch, uint8_t release) {
  for (uint8_t i=0; i<12; i++) {
    writeRegister(MPR121_TOUCHTH_0 + 2*i, touch);
    writeRegister(MPR121_RELEASETH_0 + 2*i, release);
  }
}

uint16_t  Adafruit_MPR121::filteredData(uint8_t t) {
  if (t > 12) return 0;
  return readRegister16(MPR121_FILTDATA_0L + t*2);
}

uint16_t  Adafruit_MPR121::baselineData(uint8_t t) {
  if (t > 12) return 0;
  uint16_t bl = readRegister8(MPR121_BASELINE_0 + t);
  return (bl << 2);
}

uint16_t  Adafruit_MPR121::touched(void) {
  uint16_t t = readRegister16(MPR121_TOUCHSTATUS_L);

  return t & 0x0FFF;
}

/*********************************************************************/
// Touch Wheel
void Adafruit_MPR121::initTouchWheel(uint8_t numWheelPads, int16_t degreeOffset) {
  wheelPads = numWheelPads;
  wheelDegreeOffset = degreeOffset;
  lastWheelAngle = -1;
}

void Adafruit_MPR121::takeWheelBaseline(void) {
  for (uint8_t i=0; i<8; i++) {
    wheelBaseline[i] = filteredData(i);
  }   
}

int16_t Adafruit_MPR121::getWheelAngle(void) {
  // Retrieve difference scores
  int16_t wheelDeltas[8];
  for (uint8_t i=0; i<wheelPads; i++) {
    wheelDeltas[i] = wheelBaseline[i] - filteredData(i);
  } 


  // Display deltas (debug)
/*  
  Serial.print ("baselines: \t");
  for (uint8_t i=0; i<13; i++) {
    Serial.print(filteredData(i), DEC);
    Serial.print("\t");
  } 
  Serial.println ("");
  
  Serial.print ("deltas: \t");
  for (uint8_t i=0; i<wheelPads; i++) {
    Serial.print(wheelDeltas[i], DEC);
    Serial.print("\t");
  } 
  Serial.println ("");
*/

  // Find maximum delta
  int16_t maxVal = 1;  
  int16_t maxIdx = -1;
  for (uint8_t i=0; i<wheelPads; i++) {
     if (wheelDeltas[i] > maxVal) {
       maxVal = wheelDeltas[i];
       maxIdx = i;
     }
  } 
  
  // If there are no significant deltas (ie no strong touch signals), return -1 (no touch wheel activity)
  if (maxVal < 2) {    // was <20
    return -1;
  }

  // Find neighbouring values
  int16_t v1Idx = (maxIdx-1);
  if (v1Idx < 0) v1Idx += wheelPads;      // Handle the negitive modulo
    
  int16_t v1 = wheelDeltas[v1Idx];                   // Pad before
  int16_t v2 = wheelDeltas[maxIdx];                  // Pad with highest value
  int16_t v3 = wheelDeltas[(maxIdx+1) % wheelPads];  // Pad after
  float sum = v1 + v2 + v3;
  
  // Proportions
  float c1 = v1 / sum;
  float c2 = v2 / sum;
  float c3 = v3 / sum;
  
  // Offset
//  float offset = c2 + c3;                // Offset (-0.5 .. +0.5)
  float offset = 0;
  if (c1 > c3) {
    offset = -c1;
  } else {
    offset = c3;
  }
  float offsetPad = (float)(maxIdx) + offset;    // Offset relative to pad (e.g. for a 8 pad wheel, 0-7, representing 0-360 degrees)
  if (offsetPad < 0) offsetPad += wheelPads;     // Bound check incase we go negitive for half of the first wheel
  
  // Calculate the touch position (in degrees)
  int16_t degree = floor( (offsetPad / wheelPads) * 360.0f ) - wheelDegreeOffset;
  if (degree < 0) degree += 360;
  if (degree > 360) degree -= 360;
    
  return degree;
}


int16_t Adafruit_MPR121::getWheelIncrement(void) {
  int16_t curWheelAngle = getWheelAngle();
  int16_t wheelAnglePerTick = 90;
  
  // Case 1: Wheel is not being touched)
  if (curWheelAngle == -1) {
    lastWheelAngle = curWheelAngle;
    return 0;
  }
  
  // Case 2: Wheel has just started being touched
  if ((lastWheelAngle == -1) && (curWheelAngle > -1)) {
    lastWheelAngle = curWheelAngle;
    return 0;
  }
  
  // Case 3: Wheel was touched previously, and is currently being touched
  // Special case: if current wheel angle and previous angle differ by more than 180, then a large move was made, or we're straddling 
  // the 359/0 boundary. Let's make the math easier.
  int16_t curWheelAngleAdj = curWheelAngle;
  if (curWheelAngleAdj < (lastWheelAngle - 180)) {
    curWheelAngleAdj += 360;
  } else if (curWheelAngleAdj > (lastWheelAngle + 180)) {
    curWheelAngleAdj -= 360;
  }

  Serial.print ("   lastWheelAngle: ");  Serial.println(lastWheelAngle, DEC);
  Serial.print ("   curWheelAngleAdj: ");  Serial.println(curWheelAngleAdj, DEC);  
  int16_t delta = (curWheelAngleAdj - lastWheelAngle) / wheelAnglePerTick;
  Serial.print ("   delta: ");  Serial.println(delta, DEC);  
  
  if (delta != 0) {
    // If we've made a movement that counts for at least one tick, then update lastWheelAngle to reflect the new position of the pointer
    lastWheelAngle = curWheelAngle;    
  }
  
  
  // Return the number of inrement/decrement moves we've made  (or 0 if we haven't made any)
  return delta;
  
}

/*********************************************************************/
// Push buttons
// For momentary pushbuttons, wired as open/momentarily closed to ground
/*********************************************************************/
boolean Adafruit_MPR121::isButtonPressed(uint8_t channel) {
  if (filteredData(channel) < MPR121_BUTTON_PRESS_THRESH) {
    return true;
  } 
  return false;
}


/*********************************************************************/
// Low Level Communications
/*********************************************************************/

uint8_t Adafruit_MPR121::readRegister8(uint8_t reg) {
    Wire.beginTransmission(_i2caddr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_i2caddr, 1);
    return ( Wire.read());
}

uint16_t Adafruit_MPR121::readRegister16(uint8_t reg) {
    Wire.beginTransmission(_i2caddr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_i2caddr, 2);
    uint16_t v = Wire.read();
    v |=  ((uint16_t) Wire.read()) << 8;
    return v;
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void Adafruit_MPR121::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)(value));
    Wire.endTransmission(true);
}
