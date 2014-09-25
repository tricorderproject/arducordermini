// SensorBuffer.cpp
// A generic ring buffer abstract data type for easily and (reasonably efficiently) storing data.  
// Accessible either by index (like an array), or by popping items off (like a queue), which
// makes it easy for the graphing routines to easily and efficiently display recent data from
// a streaming source. 

#include <wprogram.h>
#include "sensorbuffer.h"

// Constructor
SensorBuffer::SensorBuffer(uint32_t bufferSize) {
  validData = 0;
  ringReadIdx = 0;
  ringWriteIdx = 0;  
  ringStart = 0;                             // Start of the first (least recent) element in the ring buffer
  lastWriteIdx = 0;
  /*
  data = (float*) malloc(bufferSize);        // The heap is going to hate us...
  
  if (data != NULL) {                        // Check that allocation was successful
    size = bufferSize;                       // If allocation was successful, set size    
    setAll(0.0f);                            // Clear buffer, set all values to 0.0f (zero)
  } 
  */ 
  size = SENSOR_BUFFER_STATIC_SIZE;
  setAll(0.0f);

}
    
// Destructor
SensorBuffer::~SensorBuffer() {
  free(data);                                // Free dynamically allocated memory
}
  
// Size Functions
uint32_t SensorBuffer::getSize() {
  return size;
}

uint32_t SensorBuffer::getValidDataSize() {
  return validData; 
}
  
// Accessor methods
// Stack mode: Pop the next item from the ring buffer off the stack
float SensorBuffer::getNext() {
  float value = data[ringReadIdx];                // Get data at current location
  if (validData == size) {
    ringReadIdx = (ringReadIdx + 1) % size;       // Increment ring buffer
  } else {
    ringReadIdx = (ringReadIdx + 1) % validData;  // Increment ring buffer (only within the amount of data that's valid)
  }
  return value;
}

// Return the ring read pointer to the start index
void SensorBuffer::resetRingIdx() {
  ringReadIdx = ringStart;
}

// Array mode: retrieve data at a given index
float SensorBuffer::getIdx(uint32_t idx) {
  if (idx < size) {
    return data[idx];
  }
  return 0;
}

// Retrieve most recently written value
float SensorBuffer::getMostRecentValue() {
  return data[lastWriteIdx];
}
    
// Storage methods
// Add one value to the ring buffer
void SensorBuffer::put(float value) {  
  data[ringWriteIdx] = value;    // Write value
  lastWriteIdx = ringWriteIdx;
  ringWriteIdx = (ringWriteIdx + 1) % size;         // Increment ring buffer  
  if (validData < size) {                           // Increment the number of data elements that are valid (rather than default) values
    validData += 1;
  }  
  
  // Increment the start of the ring buffer (the oldest valid element)  
  if ((ringWriteIdx == ringStart) && (validData == size)) {
    ringStart = (ringStart + 1) % size;
  }
}

// Reset the data in the ring buffer to a single value (like zero)
void SensorBuffer::setAll(float value) {
  for (uint32_t i=0; i<size; i++) {        // Clear array
    data[i] = value;
  }  
  ringReadIdx = 0;
  ringWriteIdx = 0;
  validData = 0;
  ringStart = 0;
  lastWriteIdx = 0;
}


// Basic Summary Statistics methods
float SensorBuffer::getMin() {  
  float min = data[0];
  for (uint32_t i=1; i<validData; i++) {
    if (data[i] < min) {
      min = data[i];
    }
  }  
  return min;
}

float SensorBuffer::getMax() {  
  float max = data[0];
  for (uint32_t i=1; i<validData; i++) {
    if (data[i] > max) {
      max = data[i];
    }
  }  
  return max;
}

// Debug helper method: print the contents of the abtract data type to the serial console
void SensorBuffer::PrintContentsDEBUG() {
  Serial.println ("-----------------------------------");
  Serial.println ("SensorBuffer: ");
  
  Serial.print ("Size: ");
  Serial.println (size);
  
  Serial.print ("validData: ");
  Serial.println (validData);
  
  Serial.print ("ringReadIdx: ");
  Serial.println (ringReadIdx);
  
  Serial.print ("ringWriteIdx: ");
  Serial.println (ringWriteIdx);
  
  for (int32_t i=0; i<size; i++) {
    Serial.print ("  [");
    Serial.print (i);
    Serial.print ("]: ");
    Serial.print ( getIdx(i) );    
    
    // Display 10 values per line
    if ((i % 10) == 9) {
      Serial.println ("");
    }
  }  
  Serial.println ("");
  Serial.println ("-----------------------------------");  
    
}

