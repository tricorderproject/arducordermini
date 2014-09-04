// FrameBufferGFX.cpp
// This is a library of graphics primitives that draw to a framebuffer rather than directly to the display. 
// Many of these graphics primitives are adapted from the Adafruit GFX library (https://github.com/adafruit/Adafruit-GFX-Library/)  
// The license text from the original Adafruit Graphics Library is reproduced below: 
//
// ---------------------------------------------------------------------------
// Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
//
// Copyright (c) 2012 Adafruit Industries.  All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Written by Limor Fried/Ladyada for Adafruit Industries.
// BSD license, check license.txt for more information.
// All text above must be included in any redistribution.
// ---------------------------------------------------------------------------

#include "FramebufferGFX.h"

#include <wprogram.h>
#include <SD.h>
#include "FramebufferGFX.h"

// Constructor
FramebufferGFX::FramebufferGFX(SSD1351* displayPtr) {
  display = displayPtr;
  width = display->width;
  height = display->height;   
  
  dashedLinePeriod = 0;
  dashedLineCount = 0;
}


/*
 *  SUPER-LOW LEVEL 
 */ 

// Update framebuffer
void FramebufferGFX::updateScreen() {
  display->updateScreen();
}

// Fast methods for finding a position in the framebuffer
inline uint32_t FramebufferGFX::fbXY(uint16_t x, uint16_t y) {  
  return ((y * display->height) + x);
}

inline uint32_t FramebufferGFX::fbY(uint16_t y) {
  return (y * display->height);
}

/*
 *  SETTINGS THAT EFFECT GRAPHICS PRIMITIVES
 */ 
// Draw lines as dashed.  dashDistance sets the period (0 = solid, 1 = every other pixel, 2 = every 2 pixels, etc)
void FramebufferGFX::setDashedLines(uint8_t dashDistance) {
  dashedLinePeriod = dashDistance;
  dashedLineCount = 0;
}

// Draw lines as solid.  Disables setDashedLines (same as calling mkDashedLines(0) )
void FramebufferGFX::setSolidLines() {
  dashedLinePeriod = 0; 
}

inline bool FramebufferGFX::drawDashedPixel() {
  // Always draw pixels if dashed lines are disabled.  
  if (dashedLinePeriod == 0) {
    return true;
  }
  
  // Draw pixels when dashedLineCount decreases to 0. 
  if (dashedLineCount == 0) {
    dashedLineCount = dashedLinePeriod;      // Reset counter
    return true;
  }
  
  // Else: We're not on a solid pixel, so decrease the counter and return false. 
  dashedLineCount -= 1;
  return false;
}

/*
 *  GRAPHICS PRIMITIVES
 */ 

inline void FramebufferGFX::drawPixel(uint16_t x, uint16_t y, uint16_t color) {
  display->framebuffer[ display->fbXY(x, y) ] = color;
}

// Lines
void FramebufferGFX::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  // Adafruit: Bresenham's algorithm - thx wikpedia  
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (drawDashedPixel() == true) {
      if (steep) {
        drawPixel(y0, x0, color);
      } else {
        drawPixel(x0, y0, color);
      }
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }  
}

void FramebufferGFX::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  uint32_t pos = fbXY(x, y);  
  for (uint32_t i=0; i<h*width; i+= width) {
    display->framebuffer[pos + i] = color;
  }  
}

void FramebufferGFX::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  uint32_t pos = fbXY(x, y);  
  for (uint8_t i=0; i<w; i++) {
    display->framebuffer[pos + i] = color;
  }
}


// Rectangles
void FramebufferGFX::drawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t w = x1 - x0;
  int16_t h = y1 - y0;
  int16_t x = x0;
  int16_t y = y0;
  if (x0 > x1) {
    x = x1;
    w = -w;
  }
  if (y0 > y1) {
    y = y1;
    h = -h;
  }
  
  // (x, y) is lower corner
  drawFastHLine(x, y, w, color);             // top
  drawFastHLine(x, y + h, w, color);         // bottom  
  drawFastVLine(x, y, h, color);             // left 
  drawFastVLine(x + w, y, h, color);         // right  
}

void FramebufferGFX::fillRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  int16_t w = x1 - x0;
  int16_t h = y1 - y0;
  int16_t x = x0;
  int16_t y = y0;
  if (x0 > x1) {
    x = x1;
    w = -w;
  }
  if (y0 > y1) {
    y = y1;
    h = -h;
  }
  
  // (x, y) is lower corner.  draw fill lines from top to bottom.   
  for (int16_t i=0; i<h; i++) {
    drawFastHLine(x, y + i, w, color);
  }
}

// Circles
void FramebufferGFX::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  // From Adafruit library
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }  
}

void FramebufferGFX::drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) {
  // From Adafruit library 
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }  
}

void FramebufferGFX::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
  // From Adafruit library
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);  
}

void FramebufferGFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) {
  // From Adafruit library
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }  
}

// Triangles
void FramebufferGFX::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  // From Adafruit library
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);  
}

void FramebufferGFX::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
  // From Adafruit library
  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    drawFastHLine(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    drawFastHLine(a, y, b-a+1, color);
  }  
}

// Rounded rectangles
void FramebufferGFX::drawRoundRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t r, uint16_t color) {
  // From Adafruit library (modified)
  int16_t w = x1 - x0;
  int16_t h = y1 - y0;
  int16_t x = x0;
  int16_t y = y0;
  if (x0 > x1) {
    x = x1;
    w = -w;
  }
  if (y0 > y1) {
    y = y1;
    h = -h;
  }
  
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r, color); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x    , y+r  , h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1, color);
  drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r    , y+h-r-1, r, 8, color);  
}

void FramebufferGFX::fillRoundRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t r, uint16_t color) {
  // From Adafruit library (modified)
  int16_t w = x1 - x0;
  int16_t h = y1 - y0;
  int16_t x = x0;
  int16_t y = y0;
  if (x0 > x1) {
    x = x1;
    w = -w;
  }
  if (y0 > y1) {
    y = y1;
    h = -h;
  }
  
  // smarter version
  fillRect(x+r, y, x1-r, y1, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);  
}


/*
 *  POSTERIZED FLASH BITMAP FUNCTIONS
 */ 
// These functions read a bitmap stored in flash as a static array exported into a header file
void FramebufferGFX::displayFlashBitmap4Bit(int x, int y, uint16_t bitmapWidth, uint16_t bitmapHeight, uint16_t *bitmapPalette, uint8_t *bitmapData) {
    int idx = 0;
    for (uint16_t by=0; by<bitmapHeight; by++) {      
      for (uint16_t bx=0; bx<bitmapWidth; bx+=2) {      
        uint8_t twoPixels = bitmapData[idx];
        uint16_t pixel1 = bitmapPalette[(twoPixels & 0xF0) >> 4];
        uint16_t pixel2 = bitmapPalette[(twoPixels & 0x0F)];
        
//        uint32_t pos = display->fbXY(x + col, y + row);      
//        display->framebuffer[pos] = RGB(r, g, b);
        if (((x + bx > 0) && (x + bx < display->width)) && ((y + by > 0) && (y + by < display->height))) {          
          drawPixel(x + bx, y + by, pixel1);
          drawPixel(x + bx + 1, y + by, pixel2);        
        }    
        idx += 1;
      }
    }
}


/*
 *  BITMAP FUNCTIONS (adapted from Adafruit Library)
 */ 

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t FramebufferGFX::read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t FramebufferGFX::read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}


int FramebufferGFX::loadImageBMP(const char * fileName, uint16_t x, uint16_t y) {
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  bool     flip    = true;        // BMP is stored bottom-to-top


  // Open requested file on SD card
  if ((bmpFile = SD.open(fileName)) == NULL) {
    Serial.print("loadImage: file not found: ");
    Serial.println(fileName);
    return -1; // load error
  }
      
  // Parse BMP header
  if(read16(bmpFile) != 0x4D42) { // BMP signature
    Serial.println("loadImage: file doesn't look like a BMP");
    return -1;
  }
  
  Serial.print("File size: "); Serial.println(read32(bmpFile));
  (void)read32(bmpFile); // Read & ignore creator bytes
  bmpImageoffset = read32(bmpFile); // Start of image data
  Serial.print("Image Offset: "); Serial.println(bmpImageoffset, DEC);
  // Read DIB header
  Serial.print("Header size: "); Serial.println(read32(bmpFile));
  bmpWidth  = read32(bmpFile);
  bmpHeight = read32(bmpFile);
  if(read16(bmpFile) != 1) { // # planes -- must be '1'
    Serial.println("loadImage: invalid n. of planes");
    return -1;
  }
  
  bmpDepth = read16(bmpFile); // bits per pixel
  Serial.print("Bit Depth: "); Serial.println(bmpDepth);
  if((bmpDepth != 24) || (read32(bmpFile) != 0)) { // 0 = uncompressed {
    Serial.println("loadImage: invalid pixel format");
    return -1;
  }

  Serial.print("Image size: ");
  Serial.print(bmpWidth);
  Serial.print('x');
  Serial.println(bmpHeight);

  // BMP rows are padded (if needed) to 4-byte boundary
  rowSize = (bmpWidth * 3 + 3) & ~3;

  // If bmpHeight is negative, image is in top-down order.
  // This is not canon but has been observed in the wild.
  if(bmpHeight < 0) {
    bmpHeight = -bmpHeight;
    flip      = false;
  }
  
  
  uint16_t w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0;
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer

  // Crop area to be loaded
  w = bmpWidth;
  h = bmpHeight;
  if((x+w-1) >= display->width)  w = display->width  - x;
  if((y+h-1) >= display->height) h = display->height - y;

  // Read bitmap data
  for (row=0; row<h; row++) { // For each scanline...
    // Seek to start of scan line.  It might seem labor-
    // intensive to be doing this on every line, but this
    // method covers a lot of gritty details like cropping
    // and scanline padding.  Also, the seek only takes
    // place if the file position actually needs to change
    // (avoids a lot of cluster math in SD library).
    if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
      pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
    else     // Bitmap is stored top-to-bottom
      pos = bmpImageoffset + row * rowSize;
    if(bmpFile.position() != pos) { // Need seek?
      bmpFile.seek(pos);
      buffidx = sizeof(sdbuffer); // Force buffer reload
    }

    for (col=0; col<w; col++) { // For each pixel...
      // Time to read more pixel data?
      if (buffidx >= sizeof(sdbuffer)) { // Indeed
        bmpFile.read(sdbuffer, sizeof(sdbuffer));
        buffidx = 0; // Set index to beginning
      }

      // Convert pixel from BMP to TFT format, push to display
      b = sdbuffer[buffidx++];
      g = sdbuffer[buffidx++];
      r = sdbuffer[buffidx++];
      //pushColor(tft.Color565(r,g,b));
      uint32_t pos = display->fbXY(x + col, y + row);      
      display->framebuffer[pos] = RGB(r, g, b);

      
    } // end pixel

  } // end scanline

  // Success  
  return 0;
}

