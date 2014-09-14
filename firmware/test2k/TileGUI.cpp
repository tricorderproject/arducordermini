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
  selectedTile = 0;

  // Variables (rendering)
  GFX = GFXPtr;
  numTilePages = 0;
  
  // Initialize the page that each tile is on (populated by packTiles)
  for (int i=0; i<MAX_TILES; i++) {
    tilePages[i] = 0;
  }

}
    
// Destructor
TileGUI::~TileGUI() {

}

  
// Setup methods
// NOTE: Must still call initialize on tile after defining here. 
// NOTE: Must call packTiles() immediately after all tiles have been added and before rendering.
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

  
// Navigation Methods
boolean TileGUI::selectNextTile() {
  if (selectedTile < (numTiles-1)) {
    selectedTile += 1;
    return true;
  }  
  return false;
}

boolean TileGUI::selectPrevTile() {
  if (selectedTile > 0) {
    selectedTile -= 1;
    return true;
  }  
  return false;
}

  
// Render methods
void TileGUI::render() {  
//  Serial.println ("TileGUI::Rendering...");  
  // Find page of currently selected tile
  int curPage = tilePages[selectedTile];
    
  // Step 1: Background
  GFX->gradientRect(0, 0, GFX->width, GFX->height, 0, RGB(0, 0, 0));      // Clear framebuffer
      
  // Step 2: Render tile page counter
  #define TILE_COUNTER_SPACING  10
  int pageCounterX = (GFX->width / 2) - ((numTilePages * TILE_COUNTER_SPACING)/2);
  for (int i=0; i<=numTilePages; i++) {
    int x = pageCounterX + (i * TILE_COUNTER_SPACING);
    int y = 126;
    
    if (curPage != i) {
      GFX->fillRect(x-1, y-1, x + 1, y + 1, RGB(32, 32, 32));      // Dark box
    } else {
      GFX->fillRect(x-1, y-1, x + 1, y + 1, RGB(128, 128, 128));      // Light box
    }
  }
      
      
  // Step 3: Render tiles
  for (int i=0; i<numTiles; i++) {
    int16_t tileX = tileCoords[i].x;
    int16_t tileY = tileCoords[i].y;
//    Serial.print(i, DEC);
//    Serial.print(":  tileCoords ("); Serial.print(tileX, DEC); Serial.print(","); Serial.print(tileY, DEC); Serial.println(")");
    
    // Check if this tile is selcted (and should be highlighted)
    boolean isSelected = false;
    if (i == selectedTile) isSelected = true;
    
    // Check if tile is on the same page as the selected tile -- if so, render
    if (tilePages[i] == curPage) {
      tiles[i]->render(tileX, tileY, isSelected);
    }
  }
  
}

// packTiles() must be called after all tiles have been added and before rendering, and also after new tiles are added or rearranged
void TileGUI::packTiles() {
//  Serial.println ("packTiles::started...");
  // Step 1: Initialize/clear packing array
  for (int i=0; i<TILE_MAXGRIDX; i++) {
    for (int j=0; j<TILE_MAXGRIDY; j++) {
      pack[i][j] = -1;
    }
  }
  
  // Step 1A: Clear tile coordinates array
  for (int i=0; i<numTiles; i++) {
    tileCoords[i] = POINT{-1, -1};    // empty (unpopulated) point
  }

  // Step 1B: Clear the array that describes which page a tile appears on  
  for (int i=0; i<MAX_TILES; i++) {
    tilePages[i] = -1;
  }
  
  int8_t curPage = 0;
  // Step 2: Pack
  int i = 0;
  while (i < numTiles) {
//    Serial.print("trying to pack tile: "); Serial.println(i, DEC);
    
    // Step 3: Try to pack top-to-bottom, left-to-right      
    boolean packed = false;    
    for (int tY=0; tY<TILE_MAXGRIDY; tY++) {
      for (int tX=0; tX<TILE_MAXGRIDX; tX++) {
//        Serial.print("  checking ("); Serial.print(tX, DEC); Serial.print(","); Serial.print(tY, DEC); Serial.println(")");
        if (canTilePack(tX, tY, i) == true) {
//          Serial.println("canPack: true!");
          packed = true;
          int16_t tileX = TILE_SPACE + (tX * (TILE_SIZEX + TILE_SPACE));
          int16_t tileY = TILE_SPACE + (tY * (TILE_SIZEY + TILE_SPACE));
          tileCoords[i] = POINT{tileX, tileY};
          tilePages[i] = curPage;
        } else {
//          Serial.println("canPack: false!"); 
        }
        if (packed) break;
      }
      if (packed) break;
    }
    
    // Step 4: If we couldn't pack this tile, then we've reached our limit for this page -- reset the page and retry
    if (!packed) {
      curPage += 1;      
      // Clear pack array
      for (int i=0; i<TILE_MAXGRIDX; i++) {
        for (int j=0; j<TILE_MAXGRIDY; j++) {
          pack[i][j] = -1;
        }
      }

//      Serial.println ("packTiles::pack is full, moving to new page...");
    } else {
      // Packing completed successfully -- move on to packing next tile
      i += 1; 
    }
    
  } 
  
  // Store total number of tile pages
  numTilePages = curPage;
//  Serial.println ("packTiles:: completed...");
}

boolean TileGUI::canTilePack(int packX, int packY, int tileNum) {
//  Serial.println ("canTilePack::started...");
  // Fetch tile
  Tile* oneTile = tiles[tileNum];
  uint8_t tileSizeX = oneTile->gridSizeX;
  uint8_t tileSizeY = oneTile->gridSizeY;        

//  Serial.print ("tileSizeX: "); Serial.println(tileSizeX, DEC);
  
  // Check to see if tile fits
  for (int x=0; x<tileSizeX; x++) {
    for (int y=0; y<tileSizeY; y++) {
      int xC = x + packX;
      int yC = y + packY;
      if ((xC < TILE_MAXGRIDX) && (yC < TILE_MAXGRIDY)) {
         if (pack[xC][yC] != -1) {
           // This path on the pack has a tile in the way -- return false
//           Serial.println ("    canTilePack:: complete (tile can not pack)...");
           return false;
         }
      }
    }
  }
  
  // Did not collide with any existing tiles -- claim this space and return true
  for (int x=0; x<tileSizeX; x++) {
    for (int y=0; y<tileSizeY; y++) {
      int xC = x + packX;
      int yC = y + packY;
      pack[xC][yC] = tileNum;
    }
  }
//  Serial.println ("canTilePack:: complete (tile packed)");
  return true;
}  

    
// Debug 
void TileGUI::printDebug() {
  Serial.println("TileGUI::debugPrint() "); 
};  
