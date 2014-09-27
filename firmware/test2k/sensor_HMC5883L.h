// sensor_HMC5883L.cpp
#if !defined(SENSOR_HMC5883L_H) 
#define SENSOR_HMC5883L_H

// Pin definitions

// Defines
#define address_HMC5883L  0x1E         // 0011110b, I2C 7bit address of HMC5883

class SensorHMC5883L {
  public:
   float x,y,z; //triple axis data
  
   // Prototypes
   SensorHMC5883L();
   
   void init_HMC5883L();
   float read_HMC5883L();

};

#endif

