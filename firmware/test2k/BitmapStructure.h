// BitmapStructure.h
#if !defined(BITMAP_STRUCTURE_h) 
#define BITMAP_STRUCTURE_h

typedef struct bitmapstruct {
  uint16_t width;
  uint16_t height;
  uint8_t bpp;
  const uint16_t* palette;
  const uint8_t* data;
} BITMAPSTRUCT;

#endif


