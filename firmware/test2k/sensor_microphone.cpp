// sensor_microphone.cpp

#include <wprogram.h>
#include "sensor_microphone.h"

// Constructor
SensorMicrophone::SensorMicrophone() {
  
}

// Initialize sensor
uint16_t SensorMicrophone::readValue() { 
  return analogRead(PIN_MICROPHONE);    
}

