/*
  SD card datalogger
 
 This example shows how to log data from three analog sensors 
 to an SD card using the SD library.
 	
 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 created  24 Nov 2010
 updated 2 Dec 2010
 by Tom Igoe
 
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
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) {
      dataString += ","; 
    }
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}










