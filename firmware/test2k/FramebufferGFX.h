#if !defined(FRAMEBUFFER_GFX_H) 
#define FRAMEBUFFER_GFX_H

#include <wprogram.h>
#include "SSD1351.h"
#include "BitmapStructure.h"
#include "FontStructure.h"

#include <SD.h>

#define swap(a, b) { int16_t t = a; a = b; b = t; }

#define BUFFPIXEL 20

// Font renderer justifications
#define JUST_LEFT 1
#define JUST_RIGHT 2
#define JUST_CENTER 3

class FramebufferGFX {
 public:
  uint8_t width; 
  uint8_t height;
  SSD1351* display;
 
  uint8_t dashedLinePeriod;
  uint8_t dashedLineCount;
  
  // Member functions
  
  // Constructor
  FramebufferGFX(SSD1351* displayPtr);

  // Super low-level
  void updateScreen();  
  uint32_t fbXY(uint16_t x, uint16_t y);
  uint32_t fbY(uint16_t y);

  // Settings
  void setDashedLines(uint8_t dashDistance);
  void setSolidLines();
  bool drawDashedPixel();
  
  // Low-level graphics primitives
  void drawPixel(uint16_t x, uint16_t y, uint16_t color);

  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
  void drawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  void fillRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
  void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
  void drawRoundRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t r, uint16_t color);
  void fillRoundRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t r, uint16_t color);

  // Gradient primitives
  void gradientRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t col1, uint16_t col2);
  void gradientRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int8_t gAngle, uint16_t col1, uint16_t col2);
  
  // Bitmap functions (flash)
  void displayFlashBitmap4Bit(int x, int y, const BITMAPSTRUCT* bitmap, int8_t transparentIdx);
  
  // Bitmap functions (SD card)
  uint16_t read16(File f);
  uint32_t read32(File f);
  int loadImageBMP(const char* fileName, uint16_t x, uint16_t y);
  
  // Font renderer functions
  void drawText(char* text, int16_t xOffset, int16_t yOffset, const FONTSTRUCT* font, uint16_t col);
  void drawJustifiedText(char* text, int16_t xStart, int16_t xEnd, int16_t yOffset, const FONTSTRUCT* font, uint8_t mode, uint16_t col);
  uint8_t drawChar(uint8_t c, int16_t x, int16_t y, const FONTSTRUCT* font, uint16_t col);
  int16_t textLength(char* text, const FONTSTRUCT* font);
  
};




#endif
