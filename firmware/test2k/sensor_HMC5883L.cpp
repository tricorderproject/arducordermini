// sensor_HMC5883L.cpp

#include <wprogram.h>
#include <Wire.h>

#include "sensor_HMC5883L.h"

// Constructor
SensorHMC5883L::SensorHMC5883L() {
  x = 0;
  y = 0;
  z = 0; 
}

// Initialize sensor
void SensorHMC5883L::init_HMC5883L() {
  Serial.println ("Initializing HMC5883L... ");
  // Put the HMC5883 IC into the correct operating mode  
  Wire.beginTransmission(address_HMC5883L);   // open communication with HMC5883
  Wire.write(0x02);                           // select mode register
  Wire.write(0x00);                           // continuous measurement mode
  Wire.endTransmission();  
  
  Serial.println ("Initialization complete. ");  
}

// Read sensor and update internal values
float SensorHMC5883L::read_HMC5883L() {
  int16_t x0, y0, z0;
  //Serial.println ("Reading HMC5883L..."); 

  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address_HMC5883L);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
   
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address_HMC5883L, 6);
  if(6<=Wire.available()){
    x0 = Wire.read()<<8; //X msb
    x0 |= Wire.read(); //X lsb
    z0 = Wire.read()<<8; //Z msb
    z0 |= Wire.read(); //Z lsb
    y0 = Wire.read()<<8; //Y msb
    y0 |= Wire.read(); //Y lsb
  }
  
  // Convert to microtesla
  float convFactor = 10.9;     // 1090 LSB / Gauss, Convert to uTesla
  x = (float)x0/convFactor;
  y = (float)y0/convFactor;
  z = (float)z0/convFactor;
  
  // Return length
  float length = sqrt(((float)x * (float)x) + ((float)y * (float)y) + ((float)z * (float)z));
  
/*  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.print(z);
  Serial.print("  length: ");
  Serial.println(length);
*/

  return length;
}

