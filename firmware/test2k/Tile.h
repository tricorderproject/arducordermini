// Tile.h
#if !defined(TILE_h) 
#define TILE_h

#include "BitmapStructure.h"
#include "FramebufferGFX.h"
#include "FramebufferGraphs.h"
#include "SensorBuffer.h"

#define SENSOR_BUFFER_STATIC_SIZE 100

#define TILE_SIZEX  50
#define TILE_SIZEY  50
#define TILE_SPACE  10                        // space between tiles
#define TILE_MAXTEXTLENGTH  10
#define TILE_SELECTED_DELTA  2                // "selected" border distance off tile
#define colorSelected RGB(128, 128, 128)

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
  SensorBuffer* sensorBuffer;
  
  // Live bitmaps
  int16_t* liveBitmapInt;
  uint8_t liveBitmapSizeX;
  uint8_t liveBitmapSizeY;
  
  // Live graphs
  FramebufferGraphs* liveGraph;
  
  // Variables (rendering)
  FramebufferGFX* GFX;
  
  // Constructor/Destructor
  Tile(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, SensorBuffer* sb, FramebufferGFX* GFXPtr);
  Tile(FramebufferGFX* GFXPtr);
  ~Tile();
  
  // Setup methods
  void Initialize(char* tileName, uint16_t col, const BITMAPSTRUCT* tileBitmap, SensorBuffer* sb);
  void setSize(uint8_t x, uint8_t y);
  void setColor(uint16_t col);  
  void setText(char* tileText);
  void setBitmap(const BITMAPSTRUCT* tileBitmap);
  void setLiveBitmap(int16_t* liveBitmap, uint8_t sizeX, uint8_t sizeY);
  void setLiveGraph(FramebufferGraphs* liveGraphSource);
  void setDataSource(SensorBuffer* sb);
  
  // Data methods
  void updateTextFromData();
  
  // Render methods
  void render(int x, int y, boolean isSelected);
  void drawLiveBitmap(int x, int y);
  void drawLiveGraph(int x, int y);

  // Debug 
  void toString();
};


// Color map IDs

#define COLORMAP_TEMP     10

#endif
