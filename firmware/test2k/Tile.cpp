// Tile.cpp
#include <wprogram.h>
#include "Tile.h"
#include "Fonts.h"

// Constructor
// NOTE: If no bitmap is to be used, initialize tileBitmap == NULL. 
Tile::Tile(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, SensorBuffer* sb, FramebufferGFX* GFXPtr) {
  Initialize(tileName, col, tileBitmap, sb);
  
  // Variables (rendering)
  GFX = GFXPtr;
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
  name = tileName;
  strcpy(text, "");
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
    tileText[TILE_MAXTEXTLENGTH-1] = '\0';  // Add null manually
  }
}

void Tile::setBitmap(const BITMAPSTRUCT* tileBitmap) {
  bitmap = tileBitmap; 
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
  
  // Step 2: Retrieve most recent data value
  float data = sensorBuffer->getMostRecentValue();
  
  // Step 3: Write string representing that data
  char buffer[10];
  sprintf(buffer, "%.1f", data);
  setText(buffer);
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
  
  // Label text on the bottom
  GFX->drawJustifiedText(name, x, (x+tileWidth)-1, y+tileHeight-2, &Ubuntu10, JUST_RIGHT, RGB(255, 255, 255) );

  // Draw sensor text in the middle
  GFX->drawJustifiedText(text, x, (x+tileWidth)-1, y+((2*tileHeight)/3), &Ubuntu24, JUST_CENTER, RGB(255, 255, 255) );
  
}
    
// Debug 
void Tile::toString() {
  Serial.println("Tile::toString() "); 
};  
