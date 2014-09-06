// SSD1351.h
#if !defined(SSD1351_h) 
#define SSD1351_h

#include <wprogram.h>

#define SSD1351_WIDTH      128
#define SSD1351_HEIGHT     128  
#define SSD1351_BITDEPTH   2    // 2 bits per pixel (16-bit, RGB565)

// Macros for framebuffer location

uint16_t RGB(uint16_t r, uint16_t g, uint16_t b);
uint8_t getRed(uint16_t col);
uint8_t getGreen(uint16_t col);
uint8_t getBlue(uint16_t col);

class SSD1351 {
 public:
  static const uint8_t width = SSD1351_WIDTH;
  static const uint8_t height = SSD1351_HEIGHT;
  static const uint8_t bpp = SSD1351_BITDEPTH;
  
  uint16_t framebuffer[width * height];
 

  // Constructor
  SSD1351();

  // Initialization
  void begin(void);

  // High-level
  uint32_t fbXY(uint16_t x, uint16_t y);
  uint32_t fbY(uint16_t y);
  void setXY(uint8_t x, uint8_t y);
  void updateScreen();
  
  void TestPattern(uint8_t mode);
  uint16_t RGB565(uint8_t r, uint8_t g, uint8_t b);
  void fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
  
  // Low-level interface
  void writeData(uint8_t d);
  void writeCommand(uint8_t c);

  void enableBoostRegulator();
  void disableBoostRegulator();  

 private:
   // Pins
   // BS0/BS1 = 0b11 (68x interface)
   
   // D0-D7: Mapped to PMP (RE0-RE7)
   // Read/Write#: NWR (RD4)
   // Enable: NRD (RD5)
   // Chip Select: NCS1 (RD11)
   
   // Reset: Pin 23 (RC3)
   // D/C: Pin 22 (RC2)
   // OLED 13V Boost: Pin 28 (RG15)
   
};

// Pinout
#define SSD1351_RESET       23
#define SSD1351_DC          22
#define SSD1351_BOOST_EN    28

// SSD1351 Commands (from Adafruit SSD1351 library)
#define SSD1351_CMD_SETCOLUMN 		0x15
#define SSD1351_CMD_SETROW    		0x75
#define SSD1351_CMD_WRITERAM   		0x5C
#define SSD1351_CMD_READRAM   		0x5D
#define SSD1351_CMD_SETREMAP 		0xA0
#define SSD1351_CMD_STARTLINE 		0xA1
#define SSD1351_CMD_DISPLAYOFFSET 	0xA2
#define SSD1351_CMD_DISPLAYALLOFF 	0xA4
#define SSD1351_CMD_DISPLAYALLON  	0xA5
#define SSD1351_CMD_NORMALDISPLAY 	0xA6
#define SSD1351_CMD_INVERTDISPLAY 	0xA7
#define SSD1351_CMD_FUNCTIONSELECT 	0xAB
#define SSD1351_CMD_DISPLAYOFF 		0xAE
#define SSD1351_CMD_DISPLAYON     	0xAF
#define SSD1351_CMD_PRECHARGE 		0xB1
#define SSD1351_CMD_DISPLAYENHANCE	0xB2
#define SSD1351_CMD_CLOCKDIV 		0xB3
#define SSD1351_CMD_SETVSL 		0xB4
#define SSD1351_CMD_SETGPIO 		0xB5
#define SSD1351_CMD_PRECHARGE2 		0xB6
#define SSD1351_CMD_SETGRAY 		0xB8
#define SSD1351_CMD_USELUT 		0xB9
#define SSD1351_CMD_PRECHARGELEVEL 	0xBB
#define SSD1351_CMD_VCOMH 		0xBE
#define SSD1351_CMD_CONTRASTABC		0xC1
#define SSD1351_CMD_CONTRASTMASTER	0xC7
#define SSD1351_CMD_MUXRATIO            0xCA
#define SSD1351_CMD_COMMANDLOCK         0xFD
#define SSD1351_CMD_HORIZSCROLL         0x96
#define SSD1351_CMD_STOPSCROLL          0x9E
#define SSD1351_CMD_STARTSCROLL         0x9F


#endif
