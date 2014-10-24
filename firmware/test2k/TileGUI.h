// TileGUI.h

#if !defined(TILE_GUI_h) 
#define TILE_GUI_h

#include "BitmapStructure.h"
#include "FramebufferGFX.h"
#include "Tile.h"

// Defines
#define MAX_TILES  30
#define TILE_MAXGRIDX  2
#define TILE_MAXGRIDY  2

// Tile IDs
#define TILE_BLANK          0
#define TILE_ATMTEMP        1
#define TILE_ATMHUMIDITY    2
#define TILE_ATMPRESSURE    3

#define TILE_GAS_CO         10
#define TILE_GAS_NO2        11
#define TILE_GAS_NH3        12

#define TILE_MAGFIELD       20
#define TILE_MAGDIR         21

#define TILE_LIGHTNING_STR  30
#define TILE_LIGHTNING_DIS  31

#define TILE_RADIATION_CPM  40

#define TILE_THERMAL_CAM    50

#define TILE_LINEAR_POL     60

#define TILE_UV             70

#define TILE_SPECTROMETER   80

#define TILE_IMU_ACCEL      90
#define TILE_IMU_GYRO       91
#define TILE_ALTITUDE       92

#define TILE_AUDIO_MIC      100

#define TILE_UTIL_PLOTLY    110
#define TILE_UTIL_WIFI      111

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
  
  int8_t selectedTile; 
    
  // Variables (rendering)
  FramebufferGFX* GFX;
  int8_t pack[TILE_MAXGRIDX][TILE_MAXGRIDY];  
  POINT tileCoords[MAX_TILES];
  int8_t tilePages[MAX_TILES];
  int8_t numTilePages;
    
  // Constructor/Destructor
  TileGUI(FramebufferGFX* GFXPtr);
  ~TileGUI();
  
  // Navigation methods
  boolean selectNextTile();
  boolean selectPrevTile();  
  int8_t getSelectedTileID();  
  
  // Setup methods
  Tile* addTile(uint8_t tileID);
  Tile* getTile(uint8_t tileID);
  boolean isTileOnScreen(uint8_t tileID);
      
  // Render methods
  void render();
  void packTiles();
  boolean canTilePack(int packX, int packY, int tileNum);
  
  // Debug 
  void printDebug();
};


#endif
