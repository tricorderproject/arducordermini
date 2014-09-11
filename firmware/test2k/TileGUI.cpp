// TileGUI.cpp
#include <wprogram.h>
#include "TileGUI.h"
#include "Tile.h"
#include "Bitmaps.h"
#include "Fonts.h"

// Constructor
// NOTE: If no bitmap is to be used, initialize tileBitmap == NULL. 
TileGUI::TileGUI(FramebufferGFX* GFXPtr) {  
  
  numTiles = 0;  
  selected = 0;
  
  // Variables (rendering)
  GFX = GFXPtr;
}
    
// Destructor
TileGUI::~TileGUI() {

}
  
// Setup methods
// NOTE: Must still call initialize on tile after defining here. 
Tile* TileGUI::addTile(uint8_t tileID) {
  // If the tile stack is full, return a null pointer
  if (numTiles >= (MAX_TILES-1)) {
    Serial.println ("ERROR: addTile: Can not add more tiles -- already at maximum number of tiles");
    return NULL;
  }

  // Add new tile
  tiles[numTiles] = new Tile(GFX);
  tileIDs[numTiles] = tileID;
  numTiles += 1;
 
  // Return pointer to new tile
  return tiles[numTiles-1];     
}

Tile* TileGUI::getTile(uint8_t tileID) {
  for (int i=0; i<numTiles; i++) {
    if (tileIDs[i] == tileID) {
      return tiles[i];
    } 
  }
  return NULL;
}
  
  
// Render methods
void TileGUI::render() {  
  
  // Background
  GFX->gradientRect(0, 0, GFX->width, GFX->height, 0, RGB(0, 0, 0));      // Clear framebuffer
  
  // Render tiles
  int16_t x = 10;
  int16_t y = TILE_SPACE;
  for (int i=0; i<numTiles; i++) {
    tiles[i]->render(x, y);
    y += (TILE_SIZEY + TILE_SPACE);
  }
  
  /*
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
  GFX->gradientRect(x, y, x+TILE_SIZEX, y+TILE_SIZEY, 45, color, color2);    // small angle 

  // Draw background bitmap 
  // Note: First colour is transparent (0)
  if (bitmap != NULL) {
    GFX->displayFlashBitmap4Bit(x, y, bitmap, 0);
  }
  
  // Label text on the bottom
  GFX->drawJustifiedText(name, x, (x+TILE_SIZEX)-1, y+TILE_SIZEY-2, &Ubuntu10, JUST_RIGHT, RGB(255, 255, 255) );

  // Draw sensor text in the middle
  GFX->drawJustifiedText(text, x, (x+TILE_SIZEX)-1, y+((2*TILE_SIZEY)/3), &Ubuntu24, JUST_CENTER, RGB(255, 255, 255) );
  */
}
    
// Debug 
void TileGUI::printDebug() {
  Serial.println("TileGUI::debugPrint() "); 
};  
