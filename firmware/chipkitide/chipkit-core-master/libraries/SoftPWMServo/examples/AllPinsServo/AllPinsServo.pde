/*
  ChipKIT MAX32 Servo test - all pins simultainously Servo-ing
 	
  This sketch uses all pins 0 through 85 as RC servo outputs. For each pin,
  we go from 1ms to 2ms and then back again, moving all servos back and forth.
  	
  The circuit:
  * RC servos attached from pins 0 through 85 to ground.

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
  // Go from 1ms to 2ms
  for (int pos = 1000; pos < 2000; pos += 10) {
    // iterate over the pins:
    for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) { 
      SoftPWMServoServoWrite(thisPin, pos);
    } 
    delay(25);
  }
  // And now from 2ms back to 1ms
  for (int pos = 2000; pos > 1000; pos -= 10) {
    // iterate over the pins:
    for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) { 
      SoftPWMServoServoWrite(thisPin, pos);
    } 
    delay(25);
  }
}
