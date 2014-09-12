// TileGUI.h

#if !defined(TILE_GUI_h) 
#define TILE_GUI_h

#include "BitmapStructure.h"
#include "FramebufferGFX.h"
#include "Tile.h"

// Defines
#define MAX_TILES  10
#define TILE_MAXGRIDX  2
#define TILE_MAXGRIDY  2

// Tile IDs
#define TILE_BLANK          0
#define TILE_ATMTEMP        1
#define TILE_ATMHUMIDITY    2
#define TILE_ATMPRESSURE    3

// Supporting Structs
typedef struct point {
  int16_t x;
  int16_t y;
} POINT;

// Class
class TileGUI {
  
  public:
  // Variables (tiles)
  Tile* tiles[MAX_TILES];
  int8_t tileIDs[MAX_TILES];
  int8_t numTiles;
  
  int8_t selected; 
    
  // Variables (rendering)
  FramebufferGFX* GFX;
  int8_t pack[TILE_MAXGRIDX][TILE_MAXGRIDY];  
  POINT tileCoords[MAX_TILES];
  int8_t lastTilePacked;
  
  // Constructor/Destructor
  TileGUI(FramebufferGFX* GFXPtr);
  ~TileGUI();
  
  // Setup methods
  Tile* addTile(uint8_t tileID);
  Tile* getTile(uint8_t tileID);
      
  // Render methods
  void render();
  void packTiles2x2(int firstTile);
  boolean canTilePack(int packX, int packY, int tileNum);
  
  // Debug 
  void printDebug();
};


#endif
