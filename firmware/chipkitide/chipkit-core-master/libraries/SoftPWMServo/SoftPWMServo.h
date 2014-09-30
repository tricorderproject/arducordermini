/*
  SoftPWMServo.h - Interrupt driven Servo and PWM library for MPIDE
  Copyright (c) 2011 Brian Schmalz.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* 
  This library allows simultainous PWM or Servo outupt on any or all pins
  of a PIC32 based system. Because the pin transisions are driven by software,
  there are limits to how accurate the pulses are, but for almost all uses,
  this library will work just fine, even with a large number of pins being
  used for PWM or Servo. Also, this library does add CPU load to the system,
  which is proportional to the number of pins being used for PWM or Servo output.
  
  Please see the accompanying README.TXT file for more information and 
  explination about how the internals of the library work.
*/

/*
  Change List:
  08/17/2011 : version 1.0 release
  
  08/22/2011 : Version 1.1 release
    * Fixed math bug where every 107s the overflow of the CoreTimer would cause 
      bad pulse outputs.
    * Internal optomization : removal of explicit Active bit : a pin's existance
      in the linked list of active pins now defines its active status
    * Switched from generic LATch registers to SET and CLR for a slight speed
      improvement
*/

#ifndef SoftPWMServo_h
#define SoftPWMServo_h

#ifndef WProgram_h
	#include	"WProgram.h"
#endif

#include <inttypes.h>

#define SOFTPWMSERVO_VERSION  1.1      // software version of this library
#define SOFTPWMSERVO_MAX_PINS (86)     // Max number of pins the library can handle
#define SOFTPWMSERVO_ERROR    (-1)     // Returned when a function fails
#define SOFTPWMSERVO_OK       (0)      // Returned when a function passes
#define SOFTPWMSERVO_SERVO    (1)      // Used to enable a pin for servo operation
#define SOFTPWMSERVO_PWM      (0)      // Used to enable a pin for PWM operation

// Used in determining the default FrameTime. How many frames per second do you want?
#define DEFAULT_FRAMES_PER_SECOND           (500)
// Number of 40MHz CoreTimer ticks of the default frame time
#define SOFTPWMSERVO_DEFAULT_FRAME_TIME     (F_CPU / 2 / DEFAULT_FRAMES_PER_SECOND)
// How many CoreTimer ticks are there per microsecond
#define CORE_TICKS_PER_US                   (F_CPU / 2 / 1000000)
// Default number of frames between servo rising edges
#define SOFTPWMSERVO_DEFAULT_SERVO_FRAMES   (10)
// converts microseconds to 40MHz CoreTimer ticks
#define usToTicks(_us)    (CORE_TICKS_PER_US * _us)
// converts from 40MHz ticks to microseconds
#define ticksToUs(_ticks) (((uint32_t)_ticks ) / (float)CORE_TICKS_PER_US)

/*
 * Initalizes the SoftPWMServo library. It clears out all internal variables
 * to their default states, and hooks the SoftPWMServo CoreTimer ISR function
 * into the main CoreTimer interrupt
 *
 * Call this function before calling any others from this library (optional,
 * as SoftPWMServoPinEnable and SoftPWMServoWrite calls will call this function
 * on their own if necessary.)
 *
 * Returns: SOFTPWMSERVO_OK
 */
int32_t SoftPWMServoInit(void);

/*
 * Removes the SoftPWMServo CoreTimer ISR function hook from the main CoreTimer
 * ISR in wiring.c
 *
 * Call this if you want to remove all vestiges of this library from your running
 * program.
 *
 * Returns: SOFTPWMSERVO_OK
 */
int32_t SoftPWMServoUnload(void);

/*
 * Sets up a particular pin for use with the SoftPWMServo library.
 *
 * Pin: A valid pin number for the board you are using (0 to 
 *    SOFTPWMSERVO_MAX_PINS)
 * PinType: Either SOFTPWMSERVO_SERVO or SOFTPWMSERVO_PWM, indicating
 *    what you want to do with this particular pin.
 *
 * Call this function before you begin to use a pin with any of the
 * SoftPWMServoWrite calls. (Optional, because all of the Write calls
 * will call this function if it needs to be called.)
 *
 * Returns SOFTPWMSERVO_OK
 *
 */
int32_t SoftPWMServoPinEnable(uint32_t Pin, bool PinType);

/*
 * Disables a pin from use by the SoftPWMServo library
 *
 * Pin: A valid pin number for the board you are using
 *
 * Call this function to completely turn off any use by the library
 * of the given pin.
 *
 * Returns SOFTPWMSERVO_OK
 *
 */
int32_t SoftPWMServoPinDisable(uint32_t Pin);

/*
 * Sets a particular pin to have a new PWM or Servo pulse high-time
 * and sets the pin to be a Servo or PWM pin.
 *
 * Pin: A valid pin number for the board you are using
 * Value: The number of 40MHz CoreTimer ticks you want this pin to be
 *   in the high state
 * PinType: Either SOFTPWMSERVO_SERVO or SOFTPWMSERVO_PWM to set the
 *   type of output you want this pin to have
 * 
 * This function is called internally by ServoWrite and PWMWrite.
 * You do not need to call it unless you want full control over
 * the pin's high time. This function allows you to specify the
 * high time of the pin in 40MHz units. 
 *
 * Returns: SOFTPWMSERVO_OK on success, and SOFTPWMSERVO_ERROR on error
 *
 */
int32_t SoftPWMServoRawWrite(uint32_t Pin, uint32_t Value, bool PinType);

/*
 * Sets a particular pin to have a new Servo pulse high-time
 * and sets the pin to be a Servo pin.
 *
 * Pin: A valid pin number for the board you are using
 * Value: The time, in microseconds, that you want the servo pulse
 *   to be high for.
 * 
 * Use this function to set a pin to be a servo output, and specify
 * the pin's pulse width in microseconds. Note that if Value is
 * greater than the current FrameTime (normally around 2ms) then
 * FrameTime is used (since that's the longest pulse that can be
 * generated.) Use SoftPWMServoSetFrameTime() to use a longer frame
 * time if you need your servo to go further.
 *
 * Returns: SOFTPWMSERVO_OK
 *
 */
int32_t SoftPWMServoServoWrite(uint32_t Pin, float Value);

/*
 * Sets a particular pin to have a new PWM pulse width
 * and sets the pin to be a PWM pin.
 *
 * Pin: A valid pin number for the board you are using
 * Value: A value from 0 to 255 representing the %100 of time you want
 *   your pin to stay high.
 * 
 * Use this function to set a pin to be a PWM pin, and specify its
 * pulse width. Equvilent to the normal analogWrite() call.
 *
 * Returns: SOFTPWMSERVO_OK
 *
 */
int32_t SoftPWMServoPWMWrite(uint32_t Pin, uint8_t Value);

/*
 * Returns the current pulse width, in 40MHz ticks, of Pin.
 *
 * Pin: A valid pin number for the board you are using
 *
 * Returns: Current pulse width for this pin
 *
 */
int32_t SoftPWMServoRawRead(uint32_t Pin);

/*
 * Returns the current pulse width, in microseconds, of Pin.
 *
 * Pin: A valid pin number for the board you are using
 *
 * Returns: Current pulse width for this pin
 *
 */
float SoftPWMServoServoRead(uint32_t Pin);

/*
 * Returns the current pulse width, from 0 to 255, of Pin.
 *
 * Pin: A valid pin number for the board you are using
 *
 * Returns: Current pulse width for this pin
 *
 */
int8_t SoftPWMServoPWMRead(uint32_t Pin);

/*
 * Sets a new frame time, in 40MHz ticks for the library
 *
 * NewTime: New frame time, in 40MHz ticks
 *
 * Returns: SOFTPWMSERVO_OK
 *
 */

 int32_t SoftPWMServoSetFrameTime(uint32_t NewTime);
/*
 * Sets a new value for how manuy frames between rising edges
 * of the servo pins.
 *
 * NewTime: New frame count, in frames
 *
 * Returns: SOFTPWMSERVO_OK
 *
 */
int32_t SoftPWMServoSetServoFrames(uint32_t NewFrameCount);
#endif