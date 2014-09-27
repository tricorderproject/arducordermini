// FramebufferGraphs.h
#if !defined(FRAMEBUFFER_GRAPHS_h) 
#define FRAMEBUFFER_GRAPHS_h

#include "FramebufferGFX.h"
#include "SensorBuffer.h"


#define MAX_SERIES   10

#define LABELMODE_NONE      0
#define LABELMODE_MINMAX    10


class FramebufferGraphs {
 public:  
  FramebufferGFX* GFX;                  // Graphics routines (lines, circles, etc)
  
  // Series information 
  SensorBuffer* series[MAX_SERIES];
  uint16_t  seriesColours[MAX_SERIES];
  uint8_t numSeries; 
  float min;
  float max;
 
  uint8_t labelMode;
  
  // Constructor
  FramebufferGraphs(FramebufferGFX* GFXPtr);

  // Functions    
  void clearSeries();
  int addSeries(SensorBuffer* sb, uint16_t colour);
  void findMinMaxSeries();  
  void setLabelMode(uint8_t mode);
  
  
  void renderGraph(int16_t x, int16_t y, int16_t w, int16_t h);    
    
  void drawGraph(int16_t x, int16_t y, int16_t w, int16_t h, SensorBuffer* sb);  

  void drawGraphSeries(int16_t x, int16_t y, int16_t w, int16_t h, float minVal, float maxVal, uint16_t colour, uint8_t dashedLine, SensorBuffer* sb);
     
 private:
 
     
};


#endif

