/*
  SD card basic file example
 
 This example shows how to create and destroy an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created   Nov 2010
 by David A. Mellis
 updated 2 Dec 2010
 by Tom Igoe
 
 - Cleaned up all SD examples included with MPIDE for consistency in defining CS pins
 revised  24 May 2013 by Jacob Christ

 This example code is in the public domain.
 	 
 */
#include <SD.h>

File myFile;

// On the Ethernet Shield, CS is pin 4. It's set as an output by default.
// Note that even if it's not used as the CS pin, the hardware SS pin 
// (10 on most Arduino boards, 53 on the Mega) must be left as an output 
// or the SD library functions will not work. 

// Default SD chip select for Uno and Mega type devices
const int chipSelect_SD_default = 10; // Change 10 to 53 for a Mega

// chipSelect_SD can be changed if you do not use default CS pin
const int chipSelect_SD = chipSelect_SD_default;

void setup()
{
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  // Make sure the default chip select pin is set to so that
  // shields that have a device that use the default CS pin
  // that are connected to the SPI bus do not hold drive bus
  pinMode(chipSelect_SD_default, OUTPUT);
  digitalWrite(chipSelect_SD_default, HIGH);

  pinMode(chipSelect_SD, OUTPUT);
  digitalWrite(chipSelect_SD, HIGH);

  if (!SD.begin(chipSelect_SD)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists: 
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");  
  }

  // delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")){ 
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");  
  }
}

void loop()
{
  // nothing happens after setup finishes.
}



