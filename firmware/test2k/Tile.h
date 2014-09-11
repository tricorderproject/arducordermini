// Tile.h
#if !defined(TILE_h) 
#define TILE_h

#include "BitmapStructure.h"
#include "FramebufferGFX.h"

#define SENSOR_BUFFER_STATIC_SIZE 100

#define TILE_SIZEX  50
#define TILE_SIZEY  50
#define TILE_SPACE  10
#define TILE_MAXTEXTLENGTH  10
class Tile {
  
  public:
  // Variables (physical parameters)
  uint8_t gridSizeX;
  uint8_t gridSizeY;
  uint16_t color;
  
  // Variables (data)
  uint8_t category;
  char* name;
  char text[TILE_MAXTEXTLENGTH];
  const BITMAPSTRUCT* bitmap;
  
  // Variables (rendering)
  FramebufferGFX* GFX;
  
  // Constructor/Destructor
  Tile(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, FramebufferGFX* GFXPtr);
  ~Tile();
  
  // Setup methods
  void setSize(uint8_t x, uint8_t y);
  void setColor(uint16_t col);  
  void setText(char* tileText);
  void setBitmap(const BITMAPSTRUCT* tileBitmap);
    
  // Render methods
  void render(int x, int y);
    
  // Debug 
  void toString();
};

#endif
