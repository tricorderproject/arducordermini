// Example code for the Hamamatsu C12666MA Micro Spectrometer (released ~December 2013)

#include <wprogram.h>
#include "SensorBuffer.h"
#include "SensorSpecHamamatsu.h"

SensorSpecHamamatsu sensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing... "); 

  sensor.begin();

  // Example 1: Calculate chlorophyll levels 
  Serial.println ("Send any key to take baseline measurement...");
  while(!Serial.available()) ; 
  while(Serial.available()) { Serial.read(); }
  
  sensor.takeBaseline();  
  
  Serial.println ("Send any key to take experimental measurement...");
  while(!Serial.available()); 
  while(Serial.available()) { Serial.read(); }
  sensor.takeMeasurement();
  
  sensor.debugPrint();
  
  Serial.print ("Chlorophyll non-descructive index: ");  
  float ChlNDI = sensor.calculateReflectanceIndex(CHL_NDI_R1, CHL_NDI_R2);
  Serial.println (ChlNDI, 3);

  Serial.print ("Photochemical reflectance Index: ");    
  float PRI = sensor.calculateReflectanceIndex(PRI_R1, PRI_R2);
  Serial.println (PRI, 3);


  Serial.println ("Send any key for continuous measurement...");
  while(!Serial.available()); 
  while(Serial.available()) { Serial.read(); }  

}

int count = 0;
void loop() {

  // Example 2: Continuous measurement
  Serial.print("Count: "); Serial.println(count, DEC);
  sensor.takeMeasurement();                 // Update every cycle
  //sensor.takeMeasurementAveraging();      // Updates once every 4 cycles, but better signal quality
  sensor.debugPrint();
  
  Serial.print ("Chlorophyll non-descructive index: ");  
  float ChlNDI = sensor.calculateReflectanceIndex(CHL_NDI_R1, CHL_NDI_R2);
  Serial.println (ChlNDI, 3);

  Serial.print ("Photochemical reflectance Index: ");    
  float PRI = sensor.calculateReflectanceIndex(PRI_R1, PRI_R2);
  Serial.println (PRI, 3);

  delay(1000);
  count += 1;
 
}
