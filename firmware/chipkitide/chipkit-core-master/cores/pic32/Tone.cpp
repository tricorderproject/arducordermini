//************************************************************************
//*	Tone.cpp
//*	
//*	Arduino core files for PIC32
//*	Copyright (c) 2010, 2011 by Mark Sproul
//*	
//*	
//************************************************************************
//*	Tone.cpp
//*	
//*	A Tone Generator Library
//*	
//*	Based on code by Brett Hagman
//*	
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General Public
//*	License along with this library; if not, write to the Free Software
//*	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//*	
//*	
//************************************************************************
//*	The original tone supported multiple timers and multiple pins
//*	the offical Arduino documentation does not
//*	I am writing this as per the docs, not per the original code
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 15,	2010	Started on Tone.cpp for PIC32
//*	Aug  7, 2011	<GeneApperson> Completed implementation for single tone.
//*	Oct  5,	2011	<MLS> Issue #132 Tone fails when the frequency is 0 fixed
//	Feb  6, 2013	<GeneApperson> Removed dependencies on the Microchip plib library
//************************************************************************


#define	LANGUAGE_C
#define	__LANGUAGE_C__

//#define DEBUG_TONE

#ifdef DEBUG_TONE
	#if (ARDUINO >= 100)
		#include <Arduino.h>
	#else
		#include <WProgram.h>
	#endif
	#include "HardwareSerial.h"
#endif

#include <p32xxxx.h>
#include <sys/attribs.h>

#include "wiring.h"

#define	OPT_SYSTEM_INTERNAL
#define OPT_BOARD_INTERNAL	//pull in internal symbol definitons
#include "p32_defs.h"
#include "pins_arduino.h"

extern "C" void __attribute__((interrupt(),nomips16)) Timer1Handler(void);

//	timerx_toggle_count:
//	> 0 - duration specified
//	= 0 - stopped
//	< 0 - infinitely (until stop() method called, or new play() called)
volatile long			timer1_toggle_count;
static uint8_t			tone_pin	=	255;
volatile p32_ioport * 	tone_pin_port;
volatile uint16_t		tone_pin_mask;

#if defined(DEAD)
	#define AVAILABLE_TONE_PINS 1

	const uint8_t	tone_pin_to_timer_PGM[]	=	{ 2 /*, 3, 4, 5, 1, 0 */ };
	static uint8_t tone_pins[AVAILABLE_TONE_PINS]	=	{ 255 /*, 255, 255, 255, 255, 255 */ };
#endif

// frequency (in hertz) and duration (in milliseconds).

//************************************************************************
void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
uint32_t tonePeriod;
uint8_t port;

	// Should have an error check here for pin number out of range.
	//*	there is no standard on the number of pins. Since we want this to work on all versions of the PIC32
	//*	I have set it to 112 for now which is the largest I/O pin count on a pic32
	if ((frequency > 0) && (_pin < (NUM_DIGITAL_PINS)))
	{
			
		// If a tone is currently playing on a different pin, the function is
		// documented to have no effect. If playing on the same pin, change
		// the frequency. If not currently playing, initialize the timer.
		// This is currently hard coded to use timer1.
		if (tone_pin == 255)
		{
			// No tone currently playing. Init the timer.
			T1CON = TACON_PS_256;
            setIntVector(_TIMER_1_VECTOR, Timer1Handler);
			clearIntFlag(_TIMER_1_IRQ);
			setIntPriority(_TIMER_1_VECTOR, _T1_IPL_IPC, _T1_SPL_IPC);
			setIntEnable(_TIMER_1_IRQ);
		}
		else if (_pin != tone_pin)
		{
			// Tone currently playing on another pin. ignore this call.
			return;
		}

		// Determine which port and bit are requested.
		tone_pin		=	_pin; 
		port			=	digitalPinToPort(_pin);
		tone_pin_port	=	(p32_ioport *)portRegisters(port);
		tone_pin_mask	=	digitalPinToBitMask(_pin);

		// Ensure that the pin is a digital output
		pinMode(_pin, OUTPUT);

		// Duration 0 means to play forever until stopped. Other values
		// mean to play for that many milliseconds.
		if (duration > 0)
		{
			timer1_toggle_count	=	(2 * frequency * duration) / 1000;
		}
		else
		{
			timer1_toggle_count	=	-1;
		}

		TMR1		= 0;
		PR1			= ((__PIC32_pbClk / 256) / 2 / frequency);
		T1CONSET	= TACON_ON;
	}
}

//************************************************************************
void disableTimer(uint8_t _timer)
{
    clearIntEnable(_TIMER_1_IRQ);
    T1CON		=	0;
    tone_pin	=	255;
    clearIntVector(_TIMER_1_VECTOR);
}

//************************************************************************
void noTone(uint8_t _pin)
{
int8_t _timer = 1;

	if (_pin == tone_pin)
	{
		digitalWrite(_pin, 0);
		disableTimer(_timer);
	}
}

//*******************************************************************************************
//*	we need the extern C so that the interrupt handler names dont get mangled by C++
extern "C"
{

//*	not done yet
//************************************************************************
void __attribute__((interrupt(),nomips16)) Timer1Handler(void)
{

	if (timer1_toggle_count != 0)
	{
		// toggle the pin
		// The PORTxINV register is at offset +3 from the PORTx register
		//*(tone_pin_port+3)	=	tone_pin_mask;
		tone_pin_port->lat.inv = tone_pin_mask;

		if (timer1_toggle_count > 0)
		{
			timer1_toggle_count--;
		}
	}
	else
	{
		disableTimer(1);
		// The PORTxCLR register is at offset +1 from the PORTx register
		//*(tone_pin_port+1)	=	tone_pin_mask;	// keep pin low after stop
		tone_pin_port->lat.clr = tone_pin_mask;
	}

	// clear the interrupt flag
	clearIntFlag(_TIMER_1_IRQ);
}

};	//*	extern "C"

