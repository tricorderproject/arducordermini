// SensorSpecHamamatsu.cpp
// An Arduino/Chipkit driver for the new Hamamatsu C12666MA Micro Spectrometer (released ~December 2013)
// Peter Jansen, September/2014. 
// -------------------------------------------------------------------------------------------------------------
// Nominally, the entire measurement process can be completed in a few lines of code:
//  SensorSpecHamamatsu sensor;
//  sensor.takeMeasurement();
//  sensor.debugPrint();
// There are also methods to control the integration (sample) time, the gain, and to convert the measurement
// into a SensorBuffer storage class.
// -------------------------------------------------------------------------------------------------------------

#include <wprogram.h>
#include "SensorSpecHamamatsu.h"

// Constructor
SensorSpecHamamatsu::SensorSpecHamamatsu() {
  // Initialize arrays
  for (int i=0; i<SPEC_CHANNELS; i++) {
    baseline[i] = 0;
    data[i] = 0; 
  }  
  
  peakChannel = 0;
  baselineOverexposed = false;
  dataOverexposed = 0;
}

// Destructor
SensorSpecHamamatsu::~SensorSpecHamamatsu() {
}
  
// Setup methods
/*
#define SPEC_GAIN        80
#define SPEC_EOS         81
#define SPEC_ST          46
#define SPEC_CLK         A5
#define SPEC_SPI_MISO    11
#define SPEC_SPI_CS      A3      
#define SPEC_SPI_CLK     38
*/
boolean SensorSpecHamamatsu::begin(){
  // Setup pins
  pinMode(SPEC_EOS, INPUT);
  pinMode(SPEC_GAIN, OUTPUT);
  pinMode(SPEC_ST, OUTPUT);
  pinMode(SPEC_CLK, OUTPUT);
  
  pinMode(SPEC_SPI_MISO, INPUT);
  pinMode(SPEC_SPI_CS, OUTPUT);
  pinMode(SPEC_SPI_CLK, OUTPUT);
  
  // Default settings
  digitalWrite(SPEC_GAIN, HIGH);
  digitalWrite(SPEC_ST, HIGH);  
  digitalWrite(SPEC_CLK, HIGH);  
  digitalWrite(SPEC_SPI_CS, HIGH);  
  digitalWrite(SPEC_SPI_CLK, HIGH);  
  
  setGain(1);
  setIntTime(100);
}

void SensorSpecHamamatsu::setIntTime(uint16_t time) {
  // Set the integration (or sample collection) time, in milliseconds
  // 60ms might be about the shortest integration time with the current ADC timings
  intTime = time;
}

void SensorSpecHamamatsu::setGain(uint8_t highLow) {
  // Gain is either 0 (low gain) or 1 (high gain)
  gain = highLow;
  if (gain == 0) {
    digitalWrite(SPEC_GAIN, 0);
  } else {
    digitalWrite(SPEC_GAIN, 1);
  }
}
  
// Data methods
void SensorSpecHamamatsu::takeMeasurement() {
  Serial.println ("Starting measurement...");
  readSpectrometer(&data[0]);
  Serial.println ("Measurement complete...");
  dataOverexposed = postProcessing(&data[0]);
  
  // Find peak channel value
  uint16_t maxValue = 0;
  for (int i=0; i<SPEC_CHANNELS; i++) {
    if (data[i] > maxValue) {
      peakChannel = i;
      maxValue = data[i];
    }
  }
}

void SensorSpecHamamatsu::takeBaseline() {
  readSpectrometer(&baseline[0]);  
  baselineOverexposed = postProcessing(&baseline[0]);
}

boolean SensorSpecHamamatsu::postProcessing(uint16_t* data) {  
  boolean flagOverexposed = false;
  
  for (int i=0; i<SPEC_CHANNELS; i++) {
    // Check for overexposure
    if (data[i] > SPEC_MAX_VALUE) flagOverexposed = true;
    // Subtract the offset
    data[i] = data[i] - SPEC_MIN_VALUE;
  }
  
  return flagOverexposed;
}

void SensorSpecHamamatsu::populateSensorBuffer(SensorBuffer* sb, uint8_t mode) {
  // This function populates a SensorBuffer with spectrometer data (resampled to buffer size). 
  // MODE is either SPEC_DATA, SPEC_BASELINE, or SPEC_DELTA (data - baseline)
  // Step 1: Clear data
  sb->setAll(0.0f);
  int maxVal = SPEC_MAX_VALUE - SPEC_MIN_VALUE;      // Maximum possible value to attain
  int sbSize = sb->getSize();
  float sbPerChannel = 1.0f;
  if (sbSize < SPEC_CHANNELS) {
    sbPerChannel = (float)SPEC_CHANNELS / (float)sbSize;
  }
  
  float resampleCounter = sbPerChannel;
  uint16_t maxSample = 0;
  
  if (mode == SPEC_DATA) {
    // Measurement data
    for (int i=0; i<SPEC_CHANNELS; i++) {
      maxSample = max(maxSample, data[i]);
      if (i > floor(resampleCounter)) {
        sb->put( (float)maxSample ); // / maxVal );
        resampleCounter += sbPerChannel;
        maxSample = 0;
      }
    }
  } else if (mode == SPEC_BASELINE) {
    // Baseline data
    for (int i=0; i<SPEC_CHANNELS; i++) {
      maxSample = max(maxSample, baseline[i]);
      if (i > floor(resampleCounter)) {
        sb->put( (float)maxSample ); // / maxVal );
        resampleCounter += sbPerChannel;
        maxSample = 0;
      }
    }
  } else {
    // Measurement - baseline
    for (int i=0; i<SPEC_CHANNELS; i++) {
      maxSample = max(maxSample, data[i] - baseline[i]);
      if (i > floor(resampleCounter)) {
        sb->put( (float)maxSample ); // / maxVal );
        resampleCounter += sbPerChannel;
        maxSample = 0;
      }
    }    
  }
    
}
    
int SensorSpecHamamatsu::spectralChannelToWavelength(int32_t channelNum) {
  // A quick way to calculate which wavelength each spectral channel represents.
  // This is only a first approximation -- the actual equation requires some overhead, but this is an okay first pass for now.
  uint32_t wavelength = (uint32_t)SPEC_MINWAVELENGTH + (channelNum * (uint32_t)SPEC_WAVELENGTH_DELTA);
  return wavelength / 100;    
}
    
// Low-level communication 
uint16_t SensorSpecHamamatsu::readAD7940() {
  uint16_t value = 0;
  uint16_t delay_time = 2;
  // Idle
  digitalWrite(SPEC_SPI_CS, HIGH);   
  digitalWrite(SPEC_SPI_CLK, HIGH);  
    
  // Enable
  digitalWrite(SPEC_SPI_CS, LOW);    
  
  // Read 16 bits
  for (int i=0; i<16; i++) {
    char bit = digitalRead(SPEC_SPI_MISO);
    digitalWrite(SPEC_SPI_CLK, LOW);  
//    delayMicroseconds(delay_time);

    value = value << 1;    
    value = value + (bit & 0x01);   
    digitalWrite(SPEC_SPI_CLK, HIGH);     
//    delayMicroseconds(delay_time);    
  }
  // Disable
  digitalWrite(SPEC_SPI_CS, HIGH);    
//  delayMicroseconds(delay_time);
  
  return value;    
}


void SensorSpecHamamatsu::readSpectrometer(uint16_t* data) {
  int delay_time = 35;     // delay per half clock (in microseconds).  This ultimately conrols the integration time. 
  int idx = 0;
  int read_time = 35;      // Amount of time that the readAD7940() procedure takes (in microseconds)
  
  // Step 1: start leading clock pulses
  for (int i=0; i<SPEC_CHANNELS; i++) {
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);  
  }
  
  // Step 2: Send start pulse to signal start of integration/light collection
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, LOW);
  delayMicroseconds(delay_time);  
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, HIGH);
  delayMicroseconds(delay_time);  
  
  // Step 3: Integration time -- sample for a period of time determined by the intTime parameter
  int blockTime = delay_time * 8;
  int numIntegrationBlocks = (intTime * 1000) / blockTime;
  for (int i=0; i<numIntegrationBlocks; i++) {
    // Four clocks per pixel  
    // First block of 2 clocks -- measurement
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);      
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);    
    
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);      
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);    
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);      
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);        
  }


  // Step 4: Send start pulse to signal end of integration/light collection
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, LOW);
  delayMicroseconds(delay_time);  
  digitalWrite(SPEC_CLK, LOW);
  delayMicroseconds(delay_time);
  digitalWrite(SPEC_CLK, HIGH);
  digitalWrite(SPEC_ST, HIGH);
  delayMicroseconds(delay_time);  

  // Step 5: Read Data 2 (this is the actual read, since the spectrometer has now sampled data)
  idx = 0;
  for (int i=0; i<SPEC_CHANNELS; i++) {
    // Four clocks per pixel  
    // First block of 2 clocks -- measurement
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);      
    digitalWrite(SPEC_CLK, LOW);
    
    // Analog value is valid on low transition
    data[idx] = readAD7940();
    idx += 1;
    if (delay_time > read_time) delayMicroseconds(delay_time-read_time);     // Read takes about 135uSec    
    
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);

    // Second block of 2 clocks -- idle
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);      
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);      
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);    
  }

  // Step 6: trailing clock pulses
  for (int i=0; i<SPEC_CHANNELS; i++) {
    digitalWrite(SPEC_CLK, LOW);
    delayMicroseconds(delay_time);
    digitalWrite(SPEC_CLK, HIGH);
    delayMicroseconds(delay_time);  
  }
  
}
    
// Debug 
void SensorSpecHamamatsu::debugPrint() {
  Serial.println ("Spectral Channel, Baseline, Data");
  for (int i=0; i<SPEC_CHANNELS; i++) {
    Serial.print(i, DEC); Serial.print(": "); 
    Serial.print(spectralChannelToWavelength(i), DEC); Serial.print(" ");    
    Serial.print(baseline[i], DEC); Serial.print(" ");    
    Serial.print(data[i], DEC); Serial.print(" ");
    Serial.println("");    
  }
  
}

