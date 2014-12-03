// SSD1351.cpp

#include <plib.h>
#include <wprogram.h>

#include "SSD1351.h"


// Write command/data
   // D0-D7: Mapped to PMP (RE0-RE7)
   // Read/Write#: NWR (RD4)
   // Enable: NRD (RD5)
   // Chip Select: NCS1 (RD11)
   
#define OLED_DATA (BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6| BIT_7) // Port E
#define OLED_RW  BIT_4  // Port D
#define OLED_EN  BIT_5  // Port D
#define OLED_CS  BIT_11 // Port D
#define OLED_DC  BIT_2  // Port C

// Packs RGB values into a 16-bit RGB565 representation.  r, g, and b are between 255 (max) and 0 (min)
uint16_t RGB(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t c;
  c = (r >> 3) << 11;
  c += (g >> 2) << 5;
  c += b >> 3;
  return c;
}
// Decompose a packed RGB565 representation into its component colors (scaled to original 255-0, but last 2-3 bits will be 0)
uint8_t getRed(uint16_t col) {
  return (col >> 11) << 3;
}
uint8_t getGreen(uint16_t col) {
  return ((col & 0x07E0) >> 5) << 2;
}
uint8_t getBlue(uint16_t col) {
  return (col & 0x001F) << 3;
}

uint16_t HueToRGB(float h) {
  // Adapted from Schaller's course notes from the Rochester Institute of Technology
  // Hue: 0-359, Saturation and brightness both assumed to be 1
  // TODO: Make entirely integer arithmetic
  
  h /= 60;			// sector 0 to 5  
  int i = floor( h );
  int f = 255 * (h - i);	// factorial part of h
  
  float q = ( 255 - (255 * f) );
  float t = ( 255 - ( 255 - f ) );
  uint16_t p0 = 0;
  uint16_t q0 = floor(q);
  uint16_t t0 = floor(t);  
  uint16_t v0 = 255;
  
  switch( i ) {
    case 0:
      return RGB(v0, t0, p0);
    break;
    case 1:
      return RGB(q0, v0, p0);
    break;
    case 2:
      return RGB(p0, v0, t0);
    break;
    case 3:
      return RGB(p0, q0, v0);
    break;
    case 4:
      return RGB(t0, p0, v0);
    break;
    default:		// case 5:
      return RGB(v0, p0, q0);
    break;
  }
  
  return 0;
}



void SSD1351::writeCommand(uint8_t c) {
  while(mIsPMPBusy());                // Wait for PMP to be free
  //digitalWrite(SSD1351_DC, 0);        // Low -- command mode 
  mPORTCClearBits(OLED_DC);           // Low -- command mode 
  
//  PMPMasterWrite( c );                // write character   

  mPORTEWrite( (uint16_t)c );    // Setup data
  mPORTDClearBits(OLED_RW);      // RW# 0 (write mode)
  mPORTDSetBits(OLED_EN);      // EN 1 (enable)
  mPORTDClearBits(OLED_CS);      // CS active   
//  delay(1);
  mPORTDSetBits(OLED_CS);      // CS inactive  
  mPORTDClearBits(OLED_EN);      // EN 0 (disable) 
  
}

void SSD1351::writeData(uint8_t c) {
  while(mIsPMPBusy());                // Wait for PMP to be free
//  digitalWrite(SSD1351_DC, 1);        // High -- data mode 
  mPORTCSetBits(OLED_DC);           // Hight -- command mode 

//  PMPMasterWrite( c );                // write character

  mPORTEWrite( (uint16_t)c );    // Setup data
  mPORTDClearBits(OLED_RW);      // RW# 0 (write mode)
  mPORTDSetBits(OLED_EN);      // EN 1 (enable)
  mPORTDClearBits(OLED_CS);      // CS active   
//  delay(1);
  mPORTDSetBits(OLED_CS);      // CS inactive  
  mPORTDClearBits(OLED_EN);      // EN 0 (disable) 

}


// OLED 13V Boost regulator
void SSD1351::enableBoostRegulator() {
  digitalWrite(SSD1351_BOOST_EN, 1);
}

void SSD1351::disableBoostRegulator() {
  digitalWrite(SSD1351_BOOST_EN, 0);
}


// Initialization
void SSD1351::begin(void) {
  
  mPORTBSetBits(BIT_15);

  // Parallel Master Port (PMP) Initialization
  /*
  Serial.println (" * Configuring PMP");
  int PMP_CONTROL = PMP_ON | PMP_READ_WRITE_EN | PMP_CS2_CS1_EN | PMP_CS1_POL_LO | PMP_READ_POL_HI | PMP_WRITE_POL_HI;  
  int PMP_MODE = PMP_IRQ_OFF | PMP_AUTO_ADDR_OFF | PMP_DATA_BUS_8 | PMP_MODE_MASTER1 | PMP_WAIT_BEG_1 | PMP_WAIT_MID_2 | PMP_WAIT_END_1;
  int PMP_ADDRCFG = PMP_PEN_OFF;        // no address bits used
  int PMP_INTERRUPT = PMP_INT_OFF;      // no interrupts used
  mPMPOpen(PMP_CONTROL, PMP_MODE, PMP_ADDRCFG, PMP_INTERRUPT);   
  */
  
  // Bit-bang initialization
  PORTSetPinsDigitalOut(IOPORT_E, OLED_DATA);
  PORTSetPinsDigitalOut(IOPORT_D, OLED_RW);
  PORTSetPinsDigitalOut(IOPORT_D, OLED_EN);
  PORTSetPinsDigitalOut(IOPORT_D, OLED_CS);
  
  
  
  // Set pin tristates
  pinMode(SSD1351_DC, OUTPUT);
  pinMode(SSD1351_RESET, OUTPUT);
  pinMode(SSD1351_BOOST_EN, OUTPUT);
  
  // Disable OLED 13V boost supply 
  Serial.println (" * Disabling Boost Regulator");
  disableBoostRegulator();
  
  // Reset display
  Serial.println (" * Resetting display");  
  digitalWrite(SSD1351_RESET, 1); 
  delay(500);
  digitalWrite(SSD1351_RESET, 0); 
  delay(500);
  digitalWrite(SSD1351_RESET, 1); 
  delay(500);


    // Initialization Sequence
    Serial.println (" * Beginning initialization sequence");
    writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
    writeData(0x12);  
    writeCommand(SSD1351_CMD_COMMANDLOCK);  // set command lock
    writeData(0xB1);

    writeCommand(SSD1351_CMD_DISPLAYOFF);  		// 0xAE

    writeCommand(SSD1351_CMD_CLOCKDIV);  		// 0xB3
    writeCommand(0xF1);  						// 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    
    writeCommand(SSD1351_CMD_MUXRATIO);
    writeData(127);
    
    writeCommand(SSD1351_CMD_SETREMAP);
    writeData(0x74);
  
    writeCommand(SSD1351_CMD_SETCOLUMN);
    writeData(0x00);
    writeData(0x7F);
    writeCommand(SSD1351_CMD_SETROW);
    writeData(0x00);
    writeData(0x7F);

    writeCommand(SSD1351_CMD_STARTLINE); 		// 0xA1
    if (SSD1351_HEIGHT == 96) {
      writeData(96);
    } else {
      writeData(0);
    }


    writeCommand(SSD1351_CMD_DISPLAYOFFSET); 	// 0xA2
    writeData(0x0);

    writeCommand(SSD1351_CMD_SETGPIO);
    writeData(0x00);
    
    writeCommand(SSD1351_CMD_FUNCTIONSELECT);
    writeData(0x01); // internal (diode drop)
    //writeData(0x01); // external bias

//    writeCommand(SSSD1351_CMD_SETPHASELENGTH);
//    writeData(0x32);

    writeCommand(SSD1351_CMD_PRECHARGE);  		// 0xB1
    writeCommand(0x32);
 
    writeCommand(SSD1351_CMD_VCOMH);  			// 0xBE
    writeCommand(0x05);

    writeCommand(SSD1351_CMD_NORMALDISPLAY);  	// 0xA6

    writeCommand(SSD1351_CMD_CONTRASTABC);
    writeData(0xC8);
    writeData(0x80);
    writeData(0xC8);

    writeCommand(SSD1351_CMD_CONTRASTMASTER);
    writeData(0x0F);

    writeCommand(SSD1351_CMD_SETVSL );
    writeData(0xA0);
    writeData(0xB5);
    writeData(0x55);
    
    writeCommand(SSD1351_CMD_PRECHARGE2);
    writeData(0x01);
    
    // Clear framebuffer
    for (int i=0; i<(width*height); i++) {
      framebuffer[i] = 0;
    }
    
    // Update screen
    updateScreen();   

    // Enable OLED high voltage supply
    Serial.println (" * Enabling boost regulator");
    enableBoostRegulator();    
   
    Serial.println (" * Turning display on");    
    writeCommand(SSD1351_CMD_DISPLAYON);		//--turn on oled panel    
   
}

// Constructor
SSD1351::SSD1351() {
}

// Use
void SSD1351::TestPattern(uint8_t mode) {
    // Simple test pattern -- fade white in and out
    int delayTime = 1;
            
    // Display test pattern
    for (uint16_t c=0; c<255; c+= 1) {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        if (mode & B00000001) r = c;
        if (mode & B00000010) g = c;
        if (mode & B00000100) b = c;        
        fillRect(0, 0, 128, 128, RGB(r, g, b));
        updateScreen();
        
        delay(delayTime);
    }

    // Display test pattern
    for (uint16_t c=255; c>0; c-= 1) {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        if (mode & B00000001) r = c;
        if (mode & B00000010) g = c;
        if (mode & B00000100) b = c;        
        fillRect(0, 0, 128, 128, RGB(r, g, b));
        updateScreen();
        
        delay(delayTime);
    }  
}

uint16_t SSD1351::RGB565(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t c;
  c = r >> 3;
  c <<= 6;
  c |= g >> 2;
  c <<= 5;
  c |= b >> 3;

  return c;
}

void SSD1351::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) 
{	

  // Bound checking
  if ((x >= width) || (y >= height)) return;
  if (y+h > height) h = height;
  if (x+w > width)  w = width - x - 1;
  
/*
  Serial.print(x); Serial.print(", ");
  Serial.print(y); Serial.print(", ");
  Serial.print(w); Serial.print(", ");
  Serial.print(h); Serial.println(", ");
*/

/*
  // set location
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+w-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+h-1);
  // fill!
  writeCommand(SSD1351_CMD_WRITERAM);  

  for (uint16_t i=0; i < w*h; i++) {
    writeData(fillcolor >> 8);
    writeData(fillcolor);
  }
  */
  for (uint16_t hIdx=0; hIdx<h; hIdx+=1) {
    uint32_t fbIdx = fbY(y + hIdx);
    for (uint16_t wIdx=0; wIdx<w; wIdx+=1) {
      framebuffer[fbIdx] = color;
      fbIdx += 1;
    }      
  }
  
}


// Fast methods for finding a position in the framebuffer
uint32_t SSD1351::fbXY(uint16_t x, uint16_t y) {  
  return ((y * height) + x);
}

uint32_t SSD1351::fbY(uint16_t y) {
  return (y * height);
}


// Sets the (x, y) location in memory on the physical device (not the framebuffer)
void SSD1351::setXY(uint8_t x, uint8_t y) {
  // Bound checking
  if ((x >= width) || (y >= height)) return;
  
  // Set X location
  writeCommand(SSD1351_CMD_SETCOLUMN);  
  writeData(x);
  writeData(width-1);
  
  // Set Y Location
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(height-1);  
  
  // Setup SSD1351 for receiving pixel data
  writeCommand(SSD1351_CMD_WRITERAM);    
}


// Flips the backbuffer -- transfers the framebuffer contents to the actual display. 
void SSD1351::updateScreen() {  
  // Set location to (0, 0)
  setXY(0, 0);
  
  // Transfer contents of framebuffer to SSD1351 display  
  for (uint32_t i=0; i<(width*height); i++) {
    uint16_t pixel = framebuffer[i];    
    writeData( ((pixel >> 8) & 0x00FF) );
    writeData( (pixel & 0x00FF) );
  }  
}
