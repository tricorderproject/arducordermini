// Tile.cpp
#include <wprogram.h>
#include "Tile.h"
#include "Fonts.h"

// Constructor
// NOTE: For no bitmap, initialize tileBitmap == NULL. 
Tile::Tile(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, FramebufferGFX* GFXPtr) {
  // Variables (physical parameters)
  setSize(1, 1);    // default size
  setColor(col);  
  
  // Variables (data)
  category = 0;
  name = tileName;
  strcpy(text, "");
  bitmap = tileBitmap;
  
  // Variables (rendering)
  GFX = GFXPtr;
}
    
// Destructor
Tile::~Tile() {

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
  
// Render methods
void Tile::render(int x, int y) {  
  // Background 
  Serial.println (" -- Background");
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
  Serial.println (" -- Draw Gradient");
  GFX->gradientRect(x, y, x+TILE_SIZEX, y+TILE_SIZEY, 45, color, color2);    // small angle 

  // Draw background bitmap 
  // Note: First colour is transparent (0)
  Serial.println (" -- Bitmap Check");
  if (bitmap != NULL) {
    Serial.println (" -- Bitmap");
    GFX->displayFlashBitmap4Bit(x, y, bitmap, 0);
  }
  
  Serial.println (" -- Label Text");  
  // Label text on the bottom
  GFX->drawJustifiedText(name, x, (x+TILE_SIZEX)-1, y+TILE_SIZEY-2, &Ubuntu10, JUST_RIGHT, RGB(255, 255, 255) );

  Serial.println (" -- Sensor Text");  
  // Draw sensor text in the middle
  GFX->drawJustifiedText(text, x, (x+TILE_SIZEX)-1, y+((2*TILE_SIZEY)/3), &Ubuntu24, JUST_CENTER, RGB(255, 255, 255) );
  
  Serial.println (" -- Complete");
  
}
    
// Debug 
void Tile::toString() {
  Serial.println("Tile::toString() "); 
};  
