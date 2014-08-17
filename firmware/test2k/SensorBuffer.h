// SensorBuffer.h
#if !defined(SENSOR_BUFFER_h) 
#define SENSOR_BUFFER_h

#define SENSOR_BUFFER_STATIC_SIZE 100

class SensorBuffer {
  
  public:
  // Variables
  uint32_t validData;
  uint32_t ringReadIdx;
  uint32_t ringWriteIdx; 
  uint32_t ringStart; 
  uint32_t size;
    
//  float* data;
  float data[SENSOR_BUFFER_STATIC_SIZE];
    
  // Constructor/Destructor
  SensorBuffer(uint32_t bufferSize);
  ~SensorBuffer();
  
  // Size Functions
  uint32_t getSize();
  uint32_t getValidDataSize();
  
  // Accessor methods
  float getNext();
  void resetRingIdx();
  float getIdx(uint32_t idx);
  
  // Storage methods
  void put(float value);
  void setAll(float value);
  
  // Statistics methods
  float getMin();
  float getMax();
  
  // Debug 
  void PrintContentsDEBUG();
};

#endif
