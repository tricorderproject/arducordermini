// Simple PWM demonstration using SoftPWMServo library
// by Brian Schmalz http://www.schmalzhaus.com
// This example code is in the public domain.

// We take 3 pins (could be any at all) and slowly
// ramp them up from 0% to 100%. You could put
// red, green and blue LEDs on these pins and have a neat
// little color fader.

#include <SoftPWMServo.h>
 
// Pick 3 pins, any 3 pins, and use them for our PWM output
const int PinOne = 10;
const int PinTwo = 35;
const int PinThree = 22;

// Start each pin out at a different PWM value
char PinOneValue = 0;
char PinTwoValue = 100;
char PinThreeValue = 200;
 
void setup() 
{ 
} 
 
void loop() 
{ 
  // Set each of our three pins as PWM outputs, with their respective values
  SoftPWMServoPWMWrite(PinOne, PinOneValue);
  SoftPWMServoPWMWrite(PinTwo, PinTwoValue);
  SoftPWMServoPWMWrite(PinThree, PinThreeValue);
  
  // Incriment each PWM value - they will roll over after 255 due to being chars
//  PinOneValue++;
//  PinTwoValue++;
//  PinThreeValue++;

  // Wait just a tad so we don't go too fast.  
  delay(15);
}
