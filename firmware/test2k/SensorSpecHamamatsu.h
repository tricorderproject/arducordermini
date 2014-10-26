// SensorSpecHamamatsu.h
#if !defined(SENSOR_SPEC_C12666_h) 
#define SENSOR_SPEC_C12666_h

#include <wprogram.h>
#include "SensorBuffer.h"

// Number of spectral channels
#define SPEC_CHANNELS    256

// This is the maximum (ceiling) value from the spectrometer.  The 14-bit ADC should nominally give us values between 0 and 16384 (5V), 
// but the C12666 output ceils at approximately half that range.  In practice, I've found anything over 5800 means the value has likely ceiled
#define SPEC_MAX_VALUE        5800

// This is also called the 'offset output' 
#define SPEC_MIN_VALUE        950

// Wavelength of the first spectral channel (in hundreds of nanometers -- here 340nm)
#define SPEC_MINWAVELENGTH       34000
// Amount each spectral channel increases the wavelength bin (here 1.72nm)
#define SPEC_WAVELENGTH_DELTA    172

// Pin mappings
#define SPEC_GAIN        80
#define SPEC_EOS         81
#define SPEC_ST          46
#define SPEC_CLK         A5
#define SPEC_SPI_MISO    11
#define SPEC_SPI_CS      A3      
#define SPEC_SPI_CLK     38

// Output modes
#define SPEC_DATA        10
#define SPEC_BASELINE    20
#define SPEC_DELTA       30

// Averaging Queue
#define QUEUE_EMPTY      0
#define QUEUE_BASELINE   10

// Reflectance Difference Indicies
// Chlorophyll non-destructive index
#define CHL_NDI_R1      750
#define CHL_NDI_R2      705
// Photochemical reflectance index
#define PRI_R1      531
#define PRI_R2      570

class SensorSpecHamamatsu {
  // Variables  
  public:
  uint16_t data[SPEC_CHANNELS];
  uint16_t baseline[SPEC_CHANNELS];
  uint16_t average[SPEC_CHANNELS];
  uint16_t intTime;      // Integration (sampling) time    
  uint8_t gain;          // High/low gain
  int numAverages;       // number of averages (to increase stability)

  // Statistics
  uint16_t peakChannel;  // Value of highest data channel

  // Flags
  boolean dataOverexposed;
  boolean baselineOverexposed;
  boolean hasBaseline;
  uint8_t averageQueue;

  // Constructor/Destructor
  SensorSpecHamamatsu();
  ~SensorSpecHamamatsu();
  
  // Setup methods
  boolean begin();
  void setIntTime(uint16_t time);  
  void setGain(uint8_t highLow);  
  
  // Data methods
  void takeMeasurement();
  void takeBaseline();
  
  void takeMeasurementAveraging();
  void takeBaselineAveraging();
  boolean takeAverageMeasurement();
  
  boolean postProcessing(uint16_t* data);
  void populateSensorBuffer(SensorBuffer* sb, uint8_t mode);
  int spectralChannelToWavelength(int32_t channelNum); 
  int wavelengthToSpectralChannel(int32_t wavelength);
  
  float getReflectanceAtWavelength(int32_t wavelength);
  float getAbsorbanceAtWavelength(int32_t wavelength);
  float getBaselineExpProportion(int32_t wavelength);
 
  // Analysis methods
  float calculateReflectanceIndex(int32_t wavelength_1, int32_t wavelength_2);        
  
  // Low-level communication 
  uint16_t readAD7940();
  void readSpectrometer(uint16_t* data, boolean accumulateMode);    
    
  // Debug 
  void debugPrint();
};

#endif

