// FontStructure.h
#if !defined(FONT_STRUCTURE_h) 
#define FONT_STRUCTURE_h

typedef struct fontstruct {
  uint8_t bpp;
  uint8_t pixelsPerByte;
  uint8_t spaceWidth;
  uint8_t* sizesX;
  uint8_t* sizesY;
  uint16_t* characterOffsets;
  uint8_t* fontData;
} FONTSTRUCT;

#endif


