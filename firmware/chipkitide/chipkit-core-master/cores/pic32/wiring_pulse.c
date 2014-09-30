/*
  wiring_pulse.c - pulseIn() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/
//************************************************************************
//*	Edit History
//************************************************************************
//*	Jul 25,	2011	<MLS> Modifing for 16 bit I/O ports on pic32 chip
//* Nov 12, 2011	<GeneApperson> revise for board variant support
//* Nov 16, 2011	<GeneApperson> revised to use p32_defs.h structure definitions
//*	Nov 25,	2011	<MLS> Fixed pulsIn as per Issue#63
//************************************************************************

#define OPT_BOARD_INTERNAL	//pull in internal symbol definitons
#include	"wiring_private.h"
#include	"p32_defs.h"
#include	"pins_arduino.h"

//************************************************************************
//*	Measures the length (in microseconds) of a pulse on the pin; state is HIGH
//*	or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
//*	to 3 minutes in length, but must be called at least a few dozen microseconds
//*	before the start of the pulse.
//************************************************************************
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
int16_t	bit;
int16_t	port;
int16_t	stateMask;
unsigned long width;
unsigned long	numloops;
unsigned long	maxloops;


	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution. calling
	// digitalRead() instead yields much coarser resolution.

	bit			=	digitalPinToBitMask(pin);

	port		=	digitalPinToPort(pin);
	stateMask	=	(state ? bit : 0);
	width		=	0;	// keep initialization out of time critical area

	// convert the timeout from microseconds to a number of times through
	// the initial loop; it takes 16 clock cycles per iteration.
	numloops	=	0;
	maxloops	=	microsecondsToClockCycles(timeout/7) + 10;

	// wait for any previous pulse to end
	while ((*portInputRegister(port) & bit) == stateMask)
	{
		if (numloops++ == maxloops)
			return(0);
	}

	// wait for the pulse to start
	while ((*portInputRegister(port) & bit) != stateMask)
	{
		if (numloops++ == maxloops)
			return(0);
	}
		
	width	=	micros();
	// wait for the pulse to stop
	while ((*portInputRegister(port) & bit) == stateMask)
	{
		if (numloops++ == maxloops)
			return(0);
	}
	width	=	micros()-width;

	// convert the reading to microseconds. The loop has been determined
	// to be 20 clock cycles long and have about 16 clocks between the edge
	// and the start of the loop. There will be some error introduced by
	// the interrupt handlers.

	return (width+4);

}

