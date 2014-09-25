// SensorMLX90620.h
#if !defined(SENSOR_MLX90620_h) 
#define SENSOR_MLX90620_h

#include <wprogram.h>

#define ADDRESS_MLX90620           0x60
#define ADDRESS_MLX90620_EEPROM    0x50
#define MLX90620_SIZEX  16
#define MLX90620_SIZEY  4

class SensorMLX90620 {
  public:
  int16_t image[MLX90620_SIZEX][MLX90620_SIZEY];
  int16_t minTemp;
  int16_t maxTemp;
  float tAmbient;
  
  private:
  byte eepromData[256];
  
  // Constants calculated from the calibration data stored in the EEPROM
  // See section 7.3 of the MLX90620 datasheet for more information
  int16_t v_th, a_cp, b_cp, tgc, b_i_scale;
  float k_t1, k_t2, emissivity;
  int16_t a_ij[64], b_ij[64];

  
  public:
  // Variables  

  // Constructor/Destructor
  SensorMLX90620();
  ~SensorMLX90620();
  
  // Setup methods
  boolean begin();
  void initializeConstants();
  void setFramerate(uint8_t framerate);    
  
  // Data methods
  void updateAmbientTemperature();
  void updateThermalImage(); 

    
  // Low-level communication 
  uint16_t readRegister16(uint8_t reg);
  
  void writeConfigRegister(uint8_t framerate);
  void writeTrimmingRegister(uint8_t value);
  
  void readEEPROM();
  
  // Debug 
  void debugPrint();
};

// Constants
// These values are calculated using equation 7.3.3.2
// They are constants and can be calculated using Nathan Seidles' MLX90620_alphaCalculator sketch
// Here we store them as a const, so that they occupy program memory rather than RAM
const float mlx90620_alpha_ij[64] = {
  1.66583E-8, 1.85792E-8, 1.78807E-8, 1.57270E-8, 1.87538E-8, 2.05582E-8, 1.98597E-8, 1.81717E-8, 
  2.05582E-8, 2.21880E-8, 2.27119E-8, 1.96269E-8, 2.27701E-8, 2.45745E-8, 2.45745E-8, 2.10239E-8, 
  2.43417E-8, 2.62044E-8, 2.59715E-8, 2.31776E-8, 2.50402E-8, 2.77178E-8, 2.74267E-8, 2.46328E-8, 
  2.57969E-8, 2.83580E-8, 2.76596E-8, 2.50984E-8, 2.60297E-8, 2.88237E-8, 2.86491E-8, 2.57387E-8, 
  2.62044E-8, 2.86491E-8, 2.85909E-8, 2.50402E-8, 2.62626E-8, 2.90565E-8, 2.85909E-8, 2.50402E-8, 
  2.55059E-8, 2.83580E-8, 2.78924E-8, 2.57387E-8, 2.52730E-8, 2.76596E-8, 2.74267E-8, 2.52730E-8, 
  2.41089E-8, 2.62044E-8, 2.66700E-8, 2.45745E-8, 2.27701E-8, 2.57387E-8, 2.55059E-8, 2.31194E-8, 
  2.12567E-8, 2.41089E-8, 2.41089E-8, 2.21880E-8, 1.92194E-8, 2.27119E-8, 2.21880E-8, 2.05582E-8, 
};

// Register Map
#define REG_OSC_TRIM               0xF7

#define CAL_ACP           0xD4
#define CAL_BCP           0xD5
#define CAL_alphaCP_L     0xD6
#define CAL_alphaCP_H     0xD7
#define CAL_TGC           0xD8
#define CAL_BI_SCALE      0xD9

#define VTH_L             0xDA
#define VTH_H             0xDB
#define KT1_L             0xDC
#define KT1_H             0xDD
#define KT2_L             0xDE
#define KT2_H             0xDF

// Common sensitivity coefficients
#define CAL_A0_L          0xE0
#define CAL_A0_H          0xE1
#define CAL_A0_SCALE      0xE2
#define CAL_DELTA_A_SCALE 0xE3
#define CAL_EMIS_L        0xE4
#define CAL_EMIS_H        0xE5


#endif

