// SensorRadiation.cpp
// An Arduino/Chipkit driver for the Radiation Watch Type 5 high energy particle detector.
// Peter Jansen, September/2014. 
// -------------------------------------------------------------------------------------------------------------
#include <wprogram.h>
#include "SensorRadiation.h"

// Global pointer to radiation sensor class -- required because interrupt service routines can't be within classes.
SensorRadiation* sensorRadiationGlobal;

// Constructor/Destructor
SensorRadiation::SensorRadiation(SensorBuffer* sb) {  
  // Pin modes
  pinMode(RAD_SIG, INPUT);
  pinMode(RAD_NOISE, INPUT);
  
  // Sensor buffer
  sbRadCounts = sb; 
  
  // Counts
  countStart = 0;
  curCount = 0;
  
  // Default settings
  setIntegrationTime(1000);       // 1 second
}

SensorRadiation::~SensorRadiation() {
  
}
  
// Setup methods
boolean SensorRadiation::begin() {
  curCount = 0;
  countStart = millis();
  enableInterrupt();
}

void SensorRadiation::enableInterrupt() {
  // On the rising edge of a radiation signal, enter detectStartISR
  attachInterrupt(RAD_INT, detectStartISR, RISING);
}
 
void SensorRadiation::suspendInterrupt() {
  detachInterrupt(RAD_INT);
}
  
void SensorRadiation::setIntegrationTime(uint16_t time) {
  // Set integration time, in milliseconds
  intTime = time;  
}
  
void SensorRadiation::clearSpectrum() {
  for (int i=0; i<RAD_SPEC_BINS; i++) {
    spectralBins[i] = 0;
  }
}  
  
// Data methods
void SensorRadiation::addCount(uint16_t pulseWidth) {
  //Serial.println ("count: "); 
  //Serial.println(pulseWidth, DEC);
  // Step 1: Counts per minute
  unsigned long curTimeMS = millis();
  
  // Bound checking -- if something strange happened like the ISR being disabled for more than a minute, then clear the buffer and start fresh
  if ((curTimeMS - countStart) > 100000) {
    sbRadCounts->setAll(0.0f);
    countStart = curTimeMS;
  }
  
  // Check if we're in the current integration time slot, or not
  // If we're not, make up for the empty time slots
  while (1) {   
//    Serial.print("  curTimeMS: "); Serial.println(curTimeMS);
//    Serial.print("  countStart: "); Serial.println(countStart);
//    Serial.print("  curCount: "); Serial.println (curCount, DEC);
    if ((curTimeMS - countStart) < intTime) {
//      Serial.println ("   ### CURRENT TIME BIN");
      break;
    }        
    
    // The ISR didn't fire for a while, signifying that no radiation was detected for a period of time.  Fill the time between then and now with zeros.
    sbRadCounts->put(curCount);    
    countStart += intTime;
    curCount = 0;
  }
//  Serial.println ("**** OUT");
  // Now at current time -- increment count for this integration time by 1
  curCount += 1;
  
  
  // Step 2: Spectroscopy
  // Spectral counts tend to be between 0 and 300 microseconds.  Here we put them in 4uS bins, since the math is quick.
  uint16_t binNum = pulseWidth >> 2;    // Shift right by 2 -- quick divide by 4
  if (binNum >= RAD_SPEC_BINS) {
    binNum = RAD_SPEC_BINS-1;
  }
  spectralBins[binNum] += 1;
  
}

float SensorRadiation::calculateCPM() {
  uint32_t numCounts = 0;
  // Step 1: Check for edge case where there is no data yet
  if (sbRadCounts->getValidDataSize() == 0) return 0.0f;
  
  // Step 2: Sum all the counts per integration time bin
  for (int i=0; i<sbRadCounts->getValidDataSize(); i++) {
    numCounts += floor(sbRadCounts->getNext());
  }
  
  Serial.print("numCounts: ");
  Serial.println(numCounts, DEC);
  // Step 3: Calculate SPM
  float cpm = ((float)numCounts / (float)(intTime * sbRadCounts->getValidDataSize())) * 60000.0f;  
  return cpm;
}

void SensorRadiation::populateSensorBufferSpectrum(SensorBuffer* sb) {
  // This function populates a SensorBuffer with spectral data (resampled to buffer size). 
  // Step 1: Clear data
  sb->setAll(0.0f);
  
  // Step 2: Determine if the sensor buffer is large enough to hold the entire spectrum, or if we have to resample
  int sbSize = sb->getSize();
  float sbPerChannel = 1.0f;
  if (sbSize < RAD_SPEC_BINS) {
    sbPerChannel = (float)RAD_SPEC_BINS / (float)sbSize;
  }
  
  // Step 3: Populate data, resampling if required
  float resampleCounter = sbPerChannel;
  uint16_t maxSample = 0; 
  // Measurement data
  for (int i=0; i<RAD_SPEC_BINS; i++) {
    maxSample = max(maxSample, spectralBins[i]);
    if (i > floor(resampleCounter)) {
      sb->put( (float)maxSample ); // / maxVal );
      resampleCounter += sbPerChannel;
      maxSample = 0;
    }
  }

}
 
         
// Debug 
void SensorRadiation::debugPrint() {

  Serial.println ("Radiation level Spectroscopy (microsecond bins): ");
  for (int i=0; i<RAD_SPEC_BINS; i++) {
//    Serial.print(i, DEC); Serial.print(": ");
    Serial.print(i*4, DEC); Serial.print(" ");
    Serial.println(spectralBins[i]);
  }
  
  float cpm = calculateCPM();
  Serial.print ("CPM: ");  
  Serial.println(cpm, DEC);
}



// ******************************************  
//   Interrupt Service Routine
// ******************************************  
void setupRadiationISR(SensorRadiation* sr) {
  // Must be called after instantiating sensorRadiation, and before begin(), to initialize ISR
  sensorRadiationGlobal = sr;  
}

void detectStartISR() {
  // Interrupt service routine: Activates on the rising edge of a radiation pulse
  
  // Measure pulse length
  // Step 1: record start time
  unsigned long timeStart = micros();
  
  // Step 2: wait for falling edge
  while (digitalRead(RAD_SIG) == HIGH) {
    // do nothing    
  }
  unsigned long timeEnd = micros();

  // Step 3: Measure difference, and store as count  
  uint16_t delta = timeEnd - timeStart;  
  sensorRadiationGlobal->addCount(delta);
  
}

 
