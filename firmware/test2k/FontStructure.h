// FontStructure.h
#if !defined(FONT_STRUCTURE_h) 
#define FONT_STRUCTURE_h

typedef struct fontstruct {
  uint8_t bpp;
  uint8_t pixelsPerByte;
  uint8_t spaceWidth;
  const uint8_t* sizesX;
  const uint8_t* sizesY;
  const uint16_t* characterOffsets;
  const uint8_t* fontData;
} FONTSTRUCT;

#endif


