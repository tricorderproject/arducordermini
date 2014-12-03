// BitmapHuffmanStructure.h
#if !defined(BITMAP_HUFFMAN_STRUCTURE_h) 
#define BITMAP_HUFFMAN_STRUCTURE_h

typedef struct bitmaphuffmanstruct {
  uint16_t width;
  uint16_t height;
  uint8_t bpc;
  const uint32_t* tree;
  const uint32_t* data;
} BITMAPHUFFMANSTRUCT;

#endif


