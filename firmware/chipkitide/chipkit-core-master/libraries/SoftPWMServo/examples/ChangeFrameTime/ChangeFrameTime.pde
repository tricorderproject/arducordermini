// Change Frame Time demonstration using SoftPWMServo library
// by Brian Schmalz http://www.schmalzhaus.com
// This example code is in the public domain.

// Normally, the SoftPWMServo lirbary uses a 2ms 'frame time'.
// The frame time is the time between rising edges of the PWM output.
// To produce RC Servo output, the library executes a normal PWM output
// on a pin (from 0ms to frame time in length) and then waits for 
// a certain number of frames to go by (with no output) and then
// sends the pulse again. The number of frames from servo rising
// edge to rising edge can also be set using the SoftPWMServoServoFrames()
// call.

// So this frame time, normally 2ms, can be made almost arbitrariliy 
// small or large. The most interesting use of this functionality would be
// to extend the maximum pulse width so that RC servo output can use
// pulses longer than 2ms. There are many servos that need pulses longer
// than 2ms in order to reach full travel.

// So if we want to make our frame time 4ms, then we can have pulses that
// range in duration from 0ms to 4ms, which should be enough for any servo.
// We will also want to shorten the ServoFrames value - for example, if we
// set FrameTime to 4ms, and ServoFrames to 5, then there would be 20ms between
// each rising edge of the servo pulses.

// This little exapmle shows how this is done.

#include <SoftPWMServo.h> 

int pos = 0;         // variable to store the servo position, in microseconds
const int pin = 10;  // Choose _any_ pin number on your board
 
void setup() 
{
  // The Write() calls normally call Init(), but since we're doing some setup
  // before we do a Write(), we need to do this Init() call ourselves here.
  SoftPWMServoInit(); 
  
  // Set the FrameTime (in 40MHz ticks) to 4ms
  SoftPWMServoSetFrameTime(usToTicks(4000));

  // And set the frames between rising edges to 5 (20ms)
  SoftPWMServoSetServoFrames(5);
} 
 
void loop() 
{ 
  for(pos = 500; pos < 3500; pos += 10)  // goes from .5ms to 3.5ms in steps of 10us
  {
    SoftPWMServoServoWrite(pin, pos);     // tell servo to go to position in variable 'pos' 
    delay(25);                            // waits 25ms for the servo to reach the position 
  } 
} 
