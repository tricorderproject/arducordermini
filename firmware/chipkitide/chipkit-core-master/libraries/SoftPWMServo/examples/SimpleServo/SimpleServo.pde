// Simple Servo demonstration using SoftPWMServo library
// by Brian Schmalz http://www.schmalzhaus.com
// This example code is in the public domain.

// We take a pin (could be any pin) and use it as a servo
// output. We sweep from 1ms pulse to 2ms pulse to show
// that the servo can be controled.

// Note that you could easily write a little function to 
// convert from 'desired angle in degrees' to 'microseconds'
// so that you could specify a degree value to your servo.

#include <SoftPWMServo.h> 

int pos = 0;         // variable to store the servo position, in microseconds
const int pin = 10;  // Choose _any_ pin number on your board
 
void setup() 
{ 
} 
 
void loop() 
{ 
  for(pos = 1000; pos < 2000; pos += 10)  // goes from 1ms to 2ms
  {                                       // in steps of 10us
    SoftPWMServoServoWrite(pin, pos);     // tell servo to go to position in variable 'pos' 
    delay(25);                            // waits 25ms for the servo to reach the position 
  } 
} 
