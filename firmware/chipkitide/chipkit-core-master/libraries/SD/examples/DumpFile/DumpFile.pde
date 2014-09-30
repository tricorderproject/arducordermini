/*
  SD card file dump
 
 This example shows how to read a file from the SD card using the
 SD library and send it over the serial port.
 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created  22 December 2010

 - Cleaned up all SD examples included with MPIDE for consistency in defining CS pins
 revised  24 May 2013 by Jacob Christ
 
 This example code is in the public domain.
 	 
 */

#include <SD.h>

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.

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
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect_SD)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}

void loop()
{
}

