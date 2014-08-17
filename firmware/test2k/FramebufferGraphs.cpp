// FramebufferGraphs.cpp

#include <wprogram.h>
#include "FramebufferGraphs.h"
#include "FramebufferGFX.h"

// Constructor
FramebufferGraphs::FramebufferGraphs(FramebufferGFX* GFXPtr) { 
  GFX = GFXPtr;
  
  // Initialize/clear the list of data series
  clearSeries();
}
 
/*
 *  SERIES
 */ 

// Remove all the series from the current graph
void FramebufferGraphs::clearSeries() {
  for (int i=0; i<MAX_SERIES; i++) {
    series[i] = 0;
    seriesColours[i] = 0;
    numSeries = 0;
  } 
  min = 0.0f;
  max = 0.0f;
}
    
int FramebufferGraphs::addSeries(SensorBuffer* sb, uint16_t colour) {
  // Check that we haven't reached the maximum number of series
  if (numSeries >= MAX_SERIES) {
    return -1;
  }
      
  // Add series
  series[numSeries] = sb;
  seriesColours[numSeries] = colour;
  numSeries += 1;      
    
  // Return series ID
  return (numSeries-1);
}  
      
// Updates the min/max member variables with the global min/max across all series
void FramebufferGraphs::findMinMaxSeries() {
  for (int i=0; i<numSeries; i++) {
    // Find min/max of series to be added
    float seriesMin = series[i]->getMin();
    float seriesMax = series[i]->getMax();
  
    // Adjust global min/max based on series min/max
    if (i == 0) {
      min = seriesMin;
      max = seriesMax;
    } else {
      if (max < seriesMax) max = seriesMax;
      if (min > seriesMin) min = seriesMin; 
    }
  }
}
      
/*
 *  USER-LEVEL DRAWING FUNCTIONS
 */ 
void FramebufferGraphs::drawGraph(int16_t x, int16_t y, int16_t w, int16_t h, SensorBuffer* sb) {
   
  // Step 2: Draw data
  
  // Place ring buffer at start of data
  sb->resetRingIdx();
  
  // Find horizontal scale -- if there's more data than pixels, we'll have to scale the line down
  float hscale = 1.0f;  
  int32_t dataSize = sb->getValidDataSize();
  if (dataSize > w) {
    hscale = w / dataSize;
  }
  
  // Find vertical scale
  float max = sb->getMax();
  float min = sb->getMin();
  float vscale = (float)h / (max - min);    
  
/*
  Serial.print ("min: ");
  Serial.println (min);
  Serial.print ("max: ");
  Serial.println (max);
  Serial.print ("vscale: ");
  Serial.println (vscale);
  Serial.print ("hscale: ");
  Serial.println (hscale);  
*/

  int16_t prev_x = 0;
  int16_t prev_y = h - (int16_t)floor((sb->getNext() - min) * vscale);
  
  uint16_t col = RGB(0, 0, 255); 
  
  // Draw dashed lines for this series
  GFX->setDashedLines(2);
  
  for (int32_t i=1; i<dataSize-1; i++) {    
    int16_t xd = (int16_t)floor((float)i * hscale);
    int16_t yd = h - (int16_t)floor((sb->getNext() - min) * vscale);
        
    if (i == (dataSize-1)) {            // Change color of most recent line to something different
      col = RGB(255, 0, 255);
    }
       
    GFX->drawLine(x + prev_x, y + prev_y, x + xd, y + yd, RGB(0, 0, 255));
    prev_x = xd;
    prev_y = yd;     
/*    
  Serial.print ("xd: ");
  Serial.println (xd);
  Serial.print ("yd: ");
  Serial.println (yd);
*/    
  }

  // Return to drawing solid lines
  GFX->setSolidLines();
  
  // Step 1: Draw Axes
  GFX->drawFastHLine(x, y+h+1, w, RGB(255, 255, 255));
  GFX->drawFastVLine(x, y, h, RGB(255, 255, 255));
  
}


void FramebufferGraphs::renderGraph(int16_t x, int16_t y, int16_t w, int16_t h) {  
  // Find min/max across series
  findMinMaxSeries();
  
  // Draw individual data series
  for (int i=0; i<numSeries; i++) {
    drawGraphSeries(x, y, w, h, min, max, seriesColours[i], 0, series[i]);
  }  
  
  // Draw graph axes
  GFX->drawFastHLine(x, y+h+1, w, RGB(255, 255, 255));
  GFX->drawFastVLine(x, y, h, RGB(255, 255, 255));  
  
}

// User-level drawing functions
void FramebufferGraphs::drawGraphSeries(int16_t x, int16_t y, int16_t w, int16_t h, float minVal, float maxVal, uint16_t colour, uint8_t dashedLine, SensorBuffer* sb) {
   
  // Step 2: Draw data
  
  // Place ring buffer at start of data
  sb->resetRingIdx();
  
  // Find horizontal scale -- if there's more data than pixels, we'll have to scale the line down
  float hscale = 1.0f;  
  int32_t dataSize = sb->getValidDataSize();
  if (dataSize > w) {
    hscale = w / dataSize;
  }
  
  // Find vertical scale
  float vscale = (float)h / (maxVal - minVal);    

  // Draw Series
  int16_t prev_x = 0;
  int16_t prev_y = h - (int16_t)floor((sb->getNext() - minVal) * vscale);  
  
  // Draw dashed lines for this series
  GFX->setDashedLines(dashedLine);  
  for (int32_t i=1; i<dataSize-1; i++) {    
    int16_t xd = (int16_t)floor((float)i * hscale);
    int16_t yd = h - (int16_t)floor((sb->getNext() - minVal) * vscale);
        
    GFX->drawLine(x + prev_x, y + prev_y, x + xd, y + yd, colour);
    prev_x = xd;
    prev_y = yd;     
  }

  // Return to drawing solid lines
  GFX->setSolidLines();    
}

