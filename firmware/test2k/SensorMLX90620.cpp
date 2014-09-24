// SensorMLX90620.cpp
// A lightweight Arduino/ChipKit driver for the MLX90620 16x4 Thermal Imager. 
// Peter Jansen, Sept/2014
// Makes use of the standard Wire library, since older drivers were based off the external I2CMaster library.
// This requires that the platform you're using supports repeated stop (endTransmission(bool) ) functionality.
// This code makes use of some of the equations and register maps from Nathan Seidle's library 
// (available at https://github.com/nseidle/MLX90620_Example/blob/master/MLX90620_Example.ino), which itself
// is based on maxbot and IlBaboomba's code from the arduino forums.

#include <wprogram.h>
#include <Wire.h>
#include "SensorMLX90620.h"


// Constructor
SensorMLX90620::SensorMLX90620() {
  // Initialize variables 
  for (int i=0; i<MLX90620_SIZEX; i++) {
    for (int j=0; j<MLX90620_SIZEY; j++) {
      image[i][j] = 0;
    }
  }  
  
  minTemp = 0;
  maxTemp = 0;

}

// Destructor
SensorMLX90620::~SensorMLX90620() {  
}


// Sensor Initialization
boolean SensorMLX90620::begin() {
//  Wire.begin();
  
  delay(50);
  // Read EEPROM configuration data
  readEEPROM();
  delay(50);     
  // Initialize constants using EEPROM data
  initializeConstants();
  
  // Set oscillator trim value
  writeTrimmingRegister( eepromData[REG_OSC_TRIM] );
  delay(10);
  
  // Set Default Framerate
  writeConfigRegister(4);
  delay(10);
    
  // Read ambient temperature
  updateAmbientTemperature();
//  Serial.print("Ambient Temperature: ");
//  Serial.println(tAmbient);
  delay(10);

  // Populate first thermal image
  updateThermalImage();
  delay(10);
  
  // Optional: Display first thermal image to serial console
  //debugPrint();
    
}

// Value values are 0 (0.5fps), 1 (1fps), 2, 4, 6, 8, 16
void SensorMLX90620::setFramerate(uint8_t framerate) {
  writeConfigRegister(framerate); 
}

// Data methods
void SensorMLX90620::updateAmbientTemperature() {
  uint16_t ptat = readRegister16(0x90);    // Read register 0x90 
  
  // Calculate ambient temperature
  tAmbient = (-k_t1 + sqrt(pow(k_t1, 2) - (4 * k_t2 * (v_th - (float)ptat)))) / (2*k_t2) + 25;
}



void SensorMLX90620::updateThermalImage() {
  // Read the compensation pixel
  int16_t pixelComp = readRegister16(0x91);
  float v_cp_off_comp = (float)pixelComp - (a_cp + (b_cp/pow(2, b_i_scale)) * (tAmbient - 25));
  
  // Read the thermal image data
  uint8_t idx = 0;
  for (int x=0; x<MLX90620_SIZEX; x++) {
    for (int y=0; y<MLX90620_SIZEY; y++) {
      // Step 1: Read raw pixel value
      int16_t pixelRaw = readRegister16(idx); 
    
      // Step 2: Convert raw pixel value to temperature using calibration data
      // Calculate Offset Compensation 
      float v_ir_off_comp = pixelRaw - (a_ij[idx] + (float)(b_ij[idx]/pow(2, b_i_scale)) * (tAmbient - 25)); 
      // Calculate Thermal Gradien Compensation (TGC)
      float v_ir_tgc_comp = v_ir_off_comp - ( ((float)tgc/32) * v_cp_off_comp); 
      // Calculate Emissivity Compensation
      float v_ir_comp = v_ir_tgc_comp / emissivity;

      float temperature = sqrt( sqrt( (v_ir_comp/mlx90620_alpha_ij[idx]) + pow(tAmbient + 273.15, 4) )) - 273.15;    
    
      // Step 3: Store pixel value
      // Note: these are stored as int16_t's instead of floats, for space.  The value is multiplied by 10
      //       to include the first decimal place. 
      image[x][y] = floor(temperature * 10);
    
      // Increment index
      idx += 1;
    }   
  }
 
}

// Initialization
void SensorMLX90620::initializeConstants() {
  // This function is from Nathan Seidle's MLX90620 library code
  
  v_th = 256 * eepromData[VTH_H] + eepromData[VTH_L];
  k_t1 = (256 * eepromData[KT1_H] + eepromData[KT1_L]) / 1024.0; //2^10 = 1024
  k_t2 = (256 * eepromData[KT2_H] + eepromData[KT2_L]) / 1048576.0; //2^20 = 1,048,576
  emissivity = ((unsigned int)256 * eepromData[CAL_EMIS_H] + eepromData[CAL_EMIS_L]) / 32768.0;
  
  a_cp = eepromData[CAL_ACP];
  if(a_cp > 127) a_cp -= 256; //These values are stored as 2's compliment. This coverts it if necessary.

  b_cp = eepromData[CAL_BCP];
  if(b_cp > 127) b_cp -= 256;

  tgc = eepromData[CAL_TGC];
  if(tgc > 127) tgc -= 256;

  b_i_scale = eepromData[CAL_BI_SCALE];

  for (int i=0; i<64; i++) {
    //Read the individual pixel offsets
    a_ij[i] = eepromData[i]; 
    if(a_ij[i] > 127) a_ij[i] -= 256; //These values are stored as 2's compliment. This coverts it if necessary.

    //Read the individual pixel offset slope coefficients
    b_ij[i] = eepromData[0x40 + i]; //Bi(i,j) begins 64 bytes into EEPROM at 0x40
    if(b_ij[i] > 127) b_ij[i] -= 256;
  }
    
}

// Low-level communication
uint16_t SensorMLX90620::readRegister16(uint8_t reg) {
    Wire.beginTransmission(ADDRESS_MLX90620);
    Wire.write(0x02);      // Opcode to read    
    Wire.write(reg);       // Register
    Wire.write(0x01);      // Address step is 0
    Wire.write(0x01);      // Number of reads is 1    
    Wire.endTransmission(false);
    
    Wire.requestFrom(ADDRESS_MLX90620, 2);
    uint16_t v = Wire.read();    // LSByte
//    Serial.print ("v = "); Serial.println(v, HEX);
    v |=  ((uint16_t) Wire.read()) << 8;  // MSByte
//    Serial.print ("v = "); Serial.println(v, HEX);    
    return v;
}

void SensorMLX90620::writeConfigRegister(uint8_t framerate) {
    // Step 1: Determine framerate
    byte lsb = 0;
    switch (framerate) {
      case 0:
        lsb = 0b0001111;
        break;
      case 1:
        lsb = 0b0001110;
        break;
      case 2: 
        lsb = 0b0001101;
        break;
      case 4:
        lsb = 0b0001100;
        break;
      case 8:
        lsb = 0b0001011;
        break;
      case 16:
        lsb = 0b00001011;
        break;
      default:
        lsb = 0x00001110;      // default is 1 fps
        break;
    }
    byte msb = 0b01110100; // x111.01xx, Assumes NA = 0, ADC low reference enabled, Ta Refresh rate of 2Hz
    
    // Write configuration register
    Wire.beginTransmission(ADDRESS_MLX90620);
    Wire.write(0x03);      // Opcode to write configuration register
    Wire.write(lsb - 0x55);      // check byte
    Wire.write(lsb);
    Wire.write(msb - 0x55);      // check byte
    Wire.write(msb);
    Wire.endTransmission(true);
}

void SensorMLX90620::writeTrimmingRegister(uint8_t value) {    
    // Write oscillator trimming register
    Wire.beginTransmission(ADDRESS_MLX90620);
    Wire.write(0x04);      // Opcode to write trimming register
    Wire.write(value - 0xAA);      // check byte
    Wire.write(value);      
    Wire.write(0x56);     
    Wire.write(0x00);
    Wire.endTransmission(true);
}


// Read the entire EEPROM
void SensorMLX90620::readEEPROM() {
    Wire.beginTransmission(ADDRESS_MLX90620_EEPROM);
    Wire.write(0x00);
    Wire.endTransmission(false);
    
    // We request each byte from the EEPROM individually so that we don't exceed the I2C's read buffer size
    for (int i=0; i<=255; i++) {
      Wire.requestFrom(ADDRESS_MLX90620_EEPROM, 1);
      eepromData[i] = Wire.read(); 
//      Serial.print (i, DEC); Serial.print(":"); Serial.print(eepromData[i], DEC); 
//      Serial.println ("");
    }

}

// Debug
// Prints the entire image array
void SensorMLX90620::debugPrint() {
  char buffer[10];
  
  Serial.println ("MLX90620 Image Array:");
  
  for (int y=0; y<MLX90620_SIZEY; y++) {
    for (int x=0; x<MLX90620_SIZEX; x++) {
      sprintf(buffer, "%4i", image[x][y]);
      Serial.print(buffer);
      Serial.print("  ");      
    }
    Serial.println ("");
  }
  
}
