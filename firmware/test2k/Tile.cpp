// Tile.cpp
#include <wprogram.h>
#include "Tile.h"
#include "Fonts.h"
#include "FramebufferGraphs.h"

// Constructor
// NOTE: If no bitmap is to be used, initialize tileBitmap == NULL. 
Tile::Tile(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, SensorBuffer* sb, FramebufferGFX* GFXPtr) {
  Initialize(tileName, col, tileBitmap, sb);

  // Variables (rendering)
  GFX = GFXPtr;
  
  // Live bitmaps (disabled by default)
  liveBitmapInt = NULL;
  liveBitmapSizeX = 0;
  liveBitmapSizeY = 0;  
  
  // Live graph (disabled by default)
  liveGraph = NULL;
  
}
    
Tile::Tile(FramebufferGFX* GFXPtr) {
  // Variables (rendering)
  GFX = GFXPtr;  
}

// Destructor
Tile::~Tile() {
}
  
void Tile::Initialize(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, SensorBuffer* sb) {
  // Variables (physical parameters)  
  setSize(1, 1);    // default size
  setColor(col);  
  
  // Variables (data)
  category = 0;
  setTileName(tileName);
  strcpy(text, "");
  strcpy(units, "");
  setSensorTextFormat(TEXT_INT);
  setSensorTextMinMaxRecent(DISP_RECENT);
  
  bitmap = tileBitmap;  
  setDataSource(sb);      
}
  
// Setup methods
// Set the tile size in grid units (e.g. 1x1, 1x2, 2x2)
void Tile::setSize(uint8_t x, uint8_t y) {
  gridSizeX = x;
  gridSizeY = y;
}

void Tile::setColor(uint16_t col) {
  color = col; 
}
  
void Tile::setText(char* tileText) {
  if (strlen(tileText) < TILE_MAXTEXTLENGTH) {
    strcpy(text, tileText); 
  } else {
    strncpy(text, tileText, TILE_MAXTEXTLENGTH-1);
    text[TILE_MAXTEXTLENGTH-1] = '\0';  // Add null manually
  }
}

void Tile::setTileName(char* tileName) {
  name = tileName;
}

void Tile::setUnitText(char* unitText) {
  if (strlen(unitText) < TILE_MAXTEXTLENGTH) {
    strcpy(units, unitText); 
  } else {
    strncpy(units, unitText, TILE_MAXTEXTLENGTH-1);
    units[TILE_MAXTEXTLENGTH-1] = '\0';  // Add null manually
  }
}

void Tile::setBitmap(const BITMAPSTRUCT* tileBitmap) {
  bitmap = tileBitmap; 
}
  
void Tile::setLiveBitmap(int16_t* liveBitmapPtr, uint8_t sizeX, uint8_t sizeY) {
  // Setup live bitmap variables
  liveBitmapInt = liveBitmapPtr;
  liveBitmapSizeX = sizeX;
  liveBitmapSizeY = sizeY;    
}  
  
void Tile::setLiveGraph(FramebufferGraphs* liveGraphSource) {
  // Setup live graph variables
  liveGraph = liveGraphSource; 
}
  
void Tile::setDataSource(SensorBuffer* sb) {
  sensorBuffer = sb;
}  
  
  
// Data methods
void Tile::updateTextFromData() {
  // Step 1: Don't update the text if a sensor buffer hasn't been specified
  if (sensorBuffer == NULL) {
    return;
  }
  
  // Step 2: Retrieve (min / max / most recent) data value in sensor buffer
  float data = 0;
  switch (sensorMinMaxRecent) {
    case DISP_MIN: 
      data = sensorBuffer->getMin();
      break;
    case DISP_MAX: 
      data = sensorBuffer->getMax();
      break;
    case DISP_RECENT:
    default:
      data = sensorBuffer->getMostRecentValue();
      break;
  }
  
  // Step 3: Write string representing that data
  char buffer[20];
  if (sensorTextFormat == TEXT_FLOAT1DEC) {
    // Float with 1 decimal place
    sprintf(buffer, "%.1f", data);
  } else if (sensorTextFormat == TEXT_FLOAT2DEC) {
    // Float with 2 decimal place
    sprintf(buffer, "%.2f", data);
  } else {
    // Integer
    sprintf(buffer, "%.0f", data);
  }
  // Append unit text (if applicable)
  strcat(buffer, units);  
  
  // Update tile text  
  setText(buffer);
}

// Set the display format of the sensor data (TEXT_INT, TEXT_FLOAT1DEC, TEXT_FLOAT2DEC)
void Tile::setSensorTextFormat(uint8_t mode) {
  sensorTextFormat = mode; 
}

// Set whether the min, max, or most recent value is displayed
void Tile::setSensorTextMinMaxRecent(uint8_t mode) {
  sensorMinMaxRecent = mode;
}


  
// Render methods
void Tile::render(int x, int y, boolean isSelected) {  
  // Background 
  uint16_t r = getRed(color);
  uint16_t g = getGreen(color);
  uint16_t b = getBlue(color);
  r += 64;
  g += 64;
  b += 64;
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;
  uint16_t color2 = RGB(r, g, b);
  int16_t tileWidth = (gridSizeX * TILE_SIZEX) + ((gridSizeX-1) * TILE_SPACE);
  int16_t tileHeight = (gridSizeY * TILE_SIZEY) + ((gridSizeY-1) * TILE_SPACE);
  GFX->gradientRect(x, y, x+tileWidth, y+tileHeight, 45, color, color2);    // small angle 

  // If tile is selected, then draw border
  if (isSelected) {
    GFX->drawRect(x-TILE_SELECTED_DELTA, y-TILE_SELECTED_DELTA, x+tileWidth+TILE_SELECTED_DELTA, y+tileHeight+TILE_SELECTED_DELTA, colorSelected);    // small angle 
  }

  // Draw background bitmap 
  // Note: First colour is transparent (0)
  if (bitmap != NULL) {
    GFX->displayFlashBitmap4Bit(x, y, bitmap, 0);
  }
  
  // Draw live bitmap 
  drawLiveBitmap(x, y);

  // Draw live graph
  drawLiveGraph(x, y);
  
  // Label text on the bottom
  GFX->drawJustifiedText(name, x, (x+tileWidth)-1, y+tileHeight-2, &Ubuntu10, JUST_RIGHT, RGB(255, 255, 255) );

  // Draw sensor text in the middle
  GFX->drawJustifiedText(text, x, (x+tileWidth)-1, y+((2*tileHeight)/3), &Ubuntu24, JUST_CENTER, RGB(255, 255, 255) );

  // Draw any notes about the samples that are displayed (min, max, etc)  
  switch (sensorMinMaxRecent) {
    case DISP_MIN: 
      GFX->drawJustifiedText("min", x, (x+tileWidth)-1, y+10-2, &Ubuntu10, JUST_RIGHT, RGB(255, 255, 255) );
      break;
    case DISP_MAX: 
      GFX->drawJustifiedText("max", x, (x+tileWidth)-1, y+10-2, &Ubuntu10, JUST_RIGHT, RGB(255, 255, 255) );
      break;
  }
  
  
}

void Tile::drawLiveBitmap(int x, int y) {
  int borderX = 6;
  int borderY = 10;
  int colorMapMode = COLORMAP_TEMP;
  
  // Step 1: Ensure live bitmap is enabled and points to a data source
  if (liveBitmapInt == NULL) {
    return;
  }
  
  // Step 2: Determine min/max values in the dataset
  int minVal = 99999;
  int maxVal = -99999;
  int idx = 0;
  for (int x=0; x<liveBitmapSizeX; x++) {
    for (int y=0; y<liveBitmapSizeY; y++) {   
      int value = liveBitmapInt[idx];
      if (value < minVal) minVal = value;
      if (value > maxVal) maxVal = value;
      idx += 1;
    }
  }
   
   
  // Step 3: Calculate graph dimensions
  int16_t tileWidth = (gridSizeX * TILE_SIZEX) + ((gridSizeX-1) * TILE_SPACE);
  int16_t tileHeight = (gridSizeY * TILE_SIZEY) + ((gridSizeY-1) * TILE_SPACE);
  int16_t pixelSizeX = (tileWidth-borderX) / liveBitmapSizeX;
  int16_t pixelSizeY = (tileHeight-borderY) / liveBitmapSizeY; 
  int16_t borderOffsetX = (tileWidth - (pixelSizeX * liveBitmapSizeX));
  int16_t borderOffsetY = (tileHeight - borderY - (pixelSizeY * liveBitmapSizeY)) / 2;   // 15 for the text at the bottom

  // Step 4: Draw bitmap
  idx = 0;
  for (int y=0; y<liveBitmapSizeY; y++) { 
    for (int x=0; x<liveBitmapSizeX; x++) {  

     
//     Serial.print("data: "); Serial.print(liveBitmapInt[idx], DEC); Serial.print("   value:"), Serial.println(value, DEC);
      unsigned int col = 0;
     
      if (colorMapMode == COLORMAP_TEMP) {
        // METHOD 1: Temperature color map
        // Convert temperature to color, using Hue/Saturation/Brightness conversion.
        // Note: 0 degrees C = 200 degrees Hue
        // -24C = 320 degrees Hue, +40C = 0 degrees Hue
        int value = liveBitmapInt[idx] / 100;   // Temps are stored as ints multiplied by 100 -- e.g. 15.80 degrees is 1580. 
        int degree = 200;
        if (value >= 0) {
          degree = 200 - (value * 5);
          if (degree < 0) degree = 0;
        } else {
          degree = 200 + (-value * 5);
          if (degree > 359) degree = 359;
        }
        col = HueToRGB(degree);
      } else {    
        // METHOD 2: Black and white, autoscaling
        int value = floor((float)(255*(liveBitmapInt[idx] - minVal)) / (float)(maxVal - minVal));    // scaled     
        col = RGB(value, value, value);
      }
      int xOffset = tileWidth - (x*pixelSizeX) - borderOffsetX;
      int yOffset = tileHeight - (y*pixelSizeY) - borderOffsetY - borderY;
     
      GFX->fillRect(x + xOffset, y + yOffset, x + xOffset + pixelSizeX, y + yOffset + pixelSizeY, col );     
      GFX->drawRect(x + xOffset, y + yOffset, x + xOffset + pixelSizeX, y + yOffset + pixelSizeY, RGB(0, 0, 0) );     
      idx += 1;
    }
  } 
  
}

void Tile::drawLiveGraph(int x, int y) {
  int borderX = 6;
  int borderY = 10;
  
  // Step 1: Ensure live bitmap is enabled and points to a data source
  if (liveGraph == NULL) {
    return;
  }
     
  // Step 2: Calculate graph dimensions
  int16_t tileWidth = (gridSizeX * TILE_SIZEX) + ((gridSizeX-1) * TILE_SPACE);
  int16_t tileHeight = (gridSizeY * TILE_SIZEY) + ((gridSizeY-1) * TILE_SPACE);
  int16_t graphWidth = tileWidth - borderX; 
  int16_t graphHeight = tileHeight - borderY;
  int16_t borderOffsetX = (borderX / 2);
  int16_t borderOffsetY = (borderY / 2);   // 15 for the text at the bottom

  // Step 3: Draw graph
  liveGraph->renderGraph(x + borderOffsetX, y + borderOffsetY, graphWidth, graphHeight);
  
}

    
// Debug 
void Tile::toString() {
  Serial.println("Tile::toString() "); 
};  
