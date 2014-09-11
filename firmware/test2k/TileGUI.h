// TileGUI.h

#if !defined(TILE_GUI_h) 
#define TILE_GUI_h

#include "BitmapStructure.h"
#include "FramebufferGFX.h"
#include "Tile.h"

#define MAX_TILES  10

// Tile IDs
#define TILE_BLANK          0
#define TILE_ATMTEMP        1
#define TILE_ATMHUMIDITY    2
#define TILE_ATMPRESSURE    3


class TileGUI {
  
  public:
  // Variables (tiles)
  Tile* tiles[MAX_TILES];
  int8_t tileIDs[MAX_TILES];
  int8_t numTiles;
  
  int8_t selected;
    
  // Variables (rendering)
  FramebufferGFX* GFX;
  
  // Constructor/Destructor
  TileGUI(FramebufferGFX* GFXPtr);
  ~TileGUI();
  
  // Setup methods
  Tile* addTile(uint8_t tileID);
  Tile* getTile(uint8_t tileID);
      
  // Render methods
  void render();
    
  // Debug 
  void printDebug();
};

#endif
