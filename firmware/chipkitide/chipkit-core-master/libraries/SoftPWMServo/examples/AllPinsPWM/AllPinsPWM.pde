/*
  ChipKIT MAX32 PWM test - all pins simultainously PWMing
 	
  This sketch fades LEDs up and down on digital pins 0 through 85, all at the same time.
  (note, some of these pins are not actually available on the MAX32 board) 
  This program was written to demonstrate the power of the PIC32 and its ability
  to do software PWM on all of its pins.
 	
  The circuit:
  * LEDs attached from pins 0 through 85 to ground.

  Written 8/14/22  by Brian Schmalz http://www.schmalzhaus.com
  This example code is in the public domain.
  Based on AnalogWriteMega example code  
*/

#include <SoftPWMServo.h>

// These constants won't change.  They're used to give names
// to the pins used:
const int lowestPin = 0;
// Use highestPin = 85 for the Max32 board, and highestPin = 41 for the Uno32
const int highestPin = 41;


void setup() {
  // The SoftPWMServo library sets any used pins to be outputs, so that's not needed here
}

void loop() {
  // fade the LED on thisPin from off to brightest:
  for (int brightness = 0; brightness < 255; brightness++) {
    // iterate over the pins:
    for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) { 
      SoftPWMServoPWMWrite(thisPin, brightness);
    } 
    delay(10);
  }
  // fade the LED on thisPin from brithstest to off:
  for (int brightness = 255; brightness >= 0; brightness--) {
    // iterate over the pins:
    for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) { 
      SoftPWMServoPWMWrite(thisPin, brightness);
    } 
    delay(10);
  } 
}
