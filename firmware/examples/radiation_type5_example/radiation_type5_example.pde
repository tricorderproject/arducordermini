// Example code for the Interrupt-driven Radiation Watch Type 5 library
// This code is interrupt driven, so everything happens in the background. 
#include <wprogram.h>
#include "SensorBuffer.h"
#include "SensorRadiation.h"

SensorBuffer sbRad(100);
SensorRadiation sensorRadiation(&sbRad);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing... "); 

  // Initialize radiation sensor
  setupRadiationISR(&sensorRadiation);     // MUST be called before begin()
  sensorRadiation.begin();

}

void loop() {
  // Display counts per minute (cpm)
  float cpm = sensorRadiation.calculateCPM();
  Serial.print ("CPM: ");  
  Serial.println(cpm, DEC);
  
  // Display pulse width histogram
  sensorRadiation.debugPrint();
  
  delay(2000);

}
