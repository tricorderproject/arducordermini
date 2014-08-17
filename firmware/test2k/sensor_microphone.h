// sensor_microphone.h

#if !defined(SENSOR_MICROPHONE_H) 
#define SENSOR_MICROPHONE_H

// Pin definitions

// Defines
#define PIN_MICROPHONE A10

class SensorMicrophone {
  public:
  
   // Prototypes   
   // Constructor
   SensorMicrophone();
   
   // Read values
   uint16_t readValue();
   
};

#endif

