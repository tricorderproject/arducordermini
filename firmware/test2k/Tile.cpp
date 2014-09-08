// Tile.cpp
#include <wprogram.h>
#include "Tile.h"
#include "Fonts.h"

// Constructor
Tile::Tile(char* tileName, uint16_t col, FramebufferGFX* GFXPtr) {
  // Variables (physical parameters)
  setSize(1, 1);    // default size
  setColor(col);  
  
  // Variables (data)
  category = 0;
  name = tileName;
  strcpy(text, "");
  bitmap = NULL;
  
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
  
// Render methods
void Tile::render(int x, int y) {  
  // Background 
  GFX->gradientRect(x, y, x+TILE_SIZEX, y+TILE_SIZEY, 45, color, color);    // small angle 
  
  // Label text on the bottom
  GFX->drawText(name, x, y+TILE_SIZEY, &Ubuntu10, RGB(255, 255, 255) );
  
  // Center text
  int16_t length = GFX->textLength(text, &Ubuntu24);
  int16_t offset = (TILE_SIZEX - length) / 2;
  GFX->drawText(text, x + offset, y+((2*TILE_SIZEY)/3), &Ubuntu24, RGB(255, 255, 255) );
  
}
    
// Debug 
void Tile::toString() {
  Serial.println("Tile::toString() "); 
};  
