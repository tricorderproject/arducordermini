//************************************************************************
//*	Wiring_digital.c
//*
//*	Arduino core files for PIC32
//*		Copyright (c) 2010, 2011 by Mark Sproul
//*	
//*	
//************************************************************************
//*	this code is based on code Copyright (c) 2005-2006 David A. Mellis
//*	
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.//*	See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA  02111-1307  USA
//*	
//*	
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 12,	2010	<MLS> Got MPLAB X working on MacOSX 1.6 for the first time
//*	Oct 14,	2010	<MLS> Digital Write working
//*	Oct 15,	2010	<MLS> Digital Read working
//*	Oct 19,	2010	<MLS> turnOffPWM moved to wiring_analog.c
//*	Feb  6,	2011	<MLS> In order to use analog pins as digital, AD1PCFG must be set
//* Nov 12, 2011	<GeneApperson> revised for board variant support
//* Nov 16, 2011	<GeneApperson> revised to use p32_defs.h structure definitions
//*	Jul 26, 2012	<GeneApperson> Added PPS support for PIC32MX1xx/MX2xx devices
//************************************************************************

#define OPT_BOARD_INTERNAL	//pull in internal symbol definitons
#include <p32xxxx.h>
#include "p32_defs.h"
#include "wiring_private.h"
#include "pins_arduino.h"

//************************************************************************
void pinMode(uint8_t pin, uint8_t mode)
{
uint32_t				bit;
uint8_t					port;
volatile p32_ioport *	iop;
uint8_t		            timer;
uint32_t                cn;

	/* Check if pin number is in valid range.
	*/
	if (pin >= NUM_DIGITAL_PINS_EXTENDED)
	{
		return;
	}

#if (OPT_BOARD_DIGITAL_IO != 0)
	/* Peform any board specific processing.
	*/
int	_board_pinMode(uint8_t pin, uint8_t mode)

	if (_board_pinMode(pin, mode) != 0)
	{
		return;
	}
#endif	// OPT_BOARD_DIGITAL_IO

	//* Get the port number for this pin.
	if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
	{
		return;
	}

	//* Obtain pointer to the registers for this io port.
	iop = portRegisters(port);

	//* Obtain bit mask for the specific bit for this pin.
	bit = digitalPinToBitMask(pin);

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	volatile uint32_t *	pps;

	// The MX1xx/MX2xx support peripheral pin select (PPS). It is necessary
	// to ensure that the pin is mapped as a general purpose i/o and not
	// mapped to a peripheral.
	if (isPpsPin(pin))
	{
		pps = ppsOutputRegister(pin);
		*pps = ppsOutputSelect(PPS_OUT_GPIO);
	}

	// The MX1xx/MX2xx devices have an ANSELx register associated with
	// each io port that is used to control analog/digital mode of the
	// analog input capable pins.
	// Clear the bit in the ANSELx register to ensure that the pin is in
	// digital input mode.
	iop->ansel.clr = bit;
#else
	if (port == _IOPORT_PB)
	{
		//* The MX3xx-MX7xx PIC32 devices have all of the analog capable pins on
		//  PORTB. If this is a PORTB pin, we have to set it to digital mode.	
		//	You have to set the bit in the AD1PCFG for an analog pin to be used as a 
		//	digital input. They come up after reset as analog input with the digital 
		//	input disabled. For the PORTB pins you switch between analog input and 
		//	digital input using AD1PCFG.

		AD1PCFGSET = bit;

	}
#endif	// defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

	// Set the pin to the requested mode.
    switch (mode) {
        case INPUT:
        case INPUT_PULLUP:
        case INPUT_PULLDOWN:
        case INPUT_PULLUPDOWN:
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
            if (mode == INPUT_PULLUP) {
                iop->cnpu.set = bit;
                iop->cnpd.clr = bit;
            } else if (mode == INPUT_PULLDOWN) {
                iop->cnpu.clr = bit;
                iop->cnpd.set = bit;
            } else if (mode == INPUT_PULLUPDOWN) {
                iop->cnpu.set = bit;
                iop->cnpd.set = bit;
            } else {
                iop->cnpu.clr = bit;
                iop->cnpd.clr = bit;
            }
#else
            if (mode == INPUT_PULLUP) {
                cn = digitalPinToCN(pin);
                if (cn != NOT_CN_PIN) {
                    CNPUESET = cn;
                } 
            } else {
                cn = digitalPinToCN(pin);
                if (cn != NOT_CN_PIN) {
                    CNPUECLR = cn;
                } 
            }
#endif
            // continue into INPUT case
            //* Determine if this is an output compare pin. If so,
            //* we need to make sure PWM output is off.
            timer = digitalPinToTimerOC(pin) >> _BN_TIMER_OC;
            if (timer != NOT_ON_TIMER)
            {
                turnOffPWM(timer);
            }

            //*	May  1,	2011
            //*	according to item #26 in PIC32MX5XX-6XX-7XX Errata.pdf 
            //*	if we are setting to input, set the data bit to zero first
            iop->lat.clr  = bit;	//clear to output bit		
            iop->tris.set = bit;	//make the pin an input
            break;
        case OPEN:
            iop->tris.clr = bit;	//OPEN implies output, make the pin an output
            iop->odc.set  = bit;	//make the pin open drain
            break;
        default:
            // The behavior inherited from Arduino is that if INPUT wasn't
            // specified you get OUTPUT. That behavior is preserved rather
            // than error checking the input value.
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
            iop->cnpu.clr = bit;
            iop->cnpd.clr = bit;
#else
            cn = digitalPinToCN(pin);
            if (cn != NOT_CN_PIN) {
                CNPUECLR = cn;
            } 
#endif
            iop->tris.clr = bit;	//make the pin an output
            iop->odc.clr  = bit;	//make sure it isn't open drain
	}
}

//************************************************************************
uint8_t getPinMode(uint8_t pin)
{
uint8_t					mode;
uint32_t				bitMask;
uint8_t					port;
volatile p32_ioport *	iop;

	/* Check if pin number is in valid range.
	*/
	if (pin >= NUM_DIGITAL_PINS_EXTENDED)
	{
		return;
	}

#if (OPT_BOARD_DIGITAL_IO != 0)
	/* Peform any board specific processing.
	*/
int _board_getPinMode(uint8_t pin, uint8_t * val);
uint8_t		tmp;

	if (_board_getPinMode(pin, &tmp) != 0) 
	{
		return tmp;
	}
#endif	// OPT_BOARD_DIGITAL_IO
	
	mode	=	OUTPUT;

	//* Get the port number for this pin.
	if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
	{
		return mode;
	}

	//* Obtain pointer to the registers for this io port.
	iop = portRegisters(port);

	//* Obtain bit mask for the specific bit for this pin.
	bitMask = digitalPinToBitMask(pin);

	//* Determine the pin mode
	if ((iop->tris.reg & bitMask) != 0)
	{
		mode = INPUT;			//TRIS = 1 -> INPUT
	}
	else
	{
		if ((iop->odc.reg & bitMask) != 0)
		{
			mode = OPEN;		//TRIS = 0 and ODC = 1 -> OPEN
		}
		else
		{
			mode = OUTPUT;		//TRIS = 0 and ODC = 0 -> OUTPUT
		}
	} 

 	return(mode);
 }


//************************************************************************
//*	LAT and PORT function identically for writing.  
//*	Reading from PORT gives you a snapshot of the actual pins state regardless of how, 
//*	if at all, the PIC is trying to drive them.  
//*	Reading from LAT gives you the values last written to the pins, whether thru LAT or PORT.
//************************************************************************
void digitalWrite(uint8_t pin, uint8_t val)
{
volatile p32_ioport *	iop;
uint8_t					port;
uint16_t				bit;
uint8_t					timer;
uint32_t                cn;

	/* Check if pin number is in valid range.
	*/
	if (pin >= NUM_DIGITAL_PINS_EXTENDED)
	{
		return;
	}

#if (OPT_BOARD_DIGITAL_IO != 0)
	/* Peform any board specific processing.
	*/
int	_board_digitalWrite(uint8_t pin, uint8_t val);

	if (_board_digitalWrite(pin, val) != 0)
	{
		return;
	}
#endif		// OPT_BOARD_DIGITAL_IO

	//* Get the port number for this pin.
	if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
	{
		return;
	}

	//* Obtain pointer to the registers for this io port.
	iop = portRegisters(port);

	//* Obtain bit mask for the specific bit for this pin.
	bit = digitalPinToBitMask(pin);

    //* If the port is in input mode and we write a value to it
    //* we must be enabling or disabling the internal pull-up
    //* resistor.  Only works for pins that have an associated
    //* change notification pin.
    if (iop->tris.reg & bit) {
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
        if (val == LOW) {
            iop->cnpu.clr = bit;
            iop->cnpd.clr = bit;
        } else {
            iop->cnpu.set = bit;
            iop->cnpd.clr = bit;
        }
#else
        cn = digitalPinToCN(pin);
        if (cn != NOT_CN_PIN) {
            if (val == LOW) {
                CNPUECLR = cn;
            } else {
                CNPUESET = cn;
            }
        }
#endif

    } else {
        //* Determine if this is an output compare pin. If so,
        //* we need to make sure PWM output is off.
        timer = digitalPinToTimerOC(pin);
        if (timer != NOT_ON_TIMER)
        {
            turnOffPWM(timer);
        }

        //* Set the pin state
        if (val == LOW)
        {
            iop->lat.clr = bit;
        }
        else
        {
            iop->lat.set = bit;
        }
    }
}

//************************************************************************
int digitalRead(uint8_t pin)
{
volatile p32_ioport *	iop;
uint8_t					timer;
uint16_t				bit;
uint8_t					port;
int						highLow;

	/* Check if pin number is in valid range.
	*/
	if (pin >= NUM_DIGITAL_PINS_EXTENDED)
	{
		return;
	}

#if (OPT_BOARD_DIGITAL_IO != 0)
	/* Peform any board specific processing.
	*/
int	_board_digitalRead(uint8_t pin, uint8_t * val);
uint8_t	tmp;

	if (_board_digitalRead(pin, &tmp) != 0)
	{
		return tmp;
	}
#endif		// OPT_BOARD_DIGITAL_IO

	//* Get the port number for this pin.
	if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
	{
		return LOW;
	}

	//* Obtain pointer to the registers for this io port.
	iop = (p32_regset *)portRegisters(port);

	//* Obtain bit mask for the specific bit for this pin.
	bit = digitalPinToBitMask(pin);

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	// The MX1xx-MX2xx devices have an ANSELx register associated with
	// each io port that is used to control analog/digital mode of the
	// analog input capable pins.
	// Clear the bit in the ANSELx register to ensure that the pin is in
	// digital input mode.
	iop->ansel.clr = bit;
#else
	if (port == _IOPORT_PB)
	{
		//* The MX3xx-MX7xx PIC32 devices have all of the analog capable pins on
		//  PORTB. If this is a PORTB pin, we have to set it to digital mode.	
		//	You have to set the bit in the AD1PCFG for an analog pin to be used as a 
		//	digital input. They come up after reset as analog input with the digital 
		//	input disabled. For the PORTB pins you switch between analog input and 
		//	digital input using AD1PCFG.

		AD1PCFGSET = bit;

	}
#endif	// defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

	//* Get the pin state.
	if ((iop->port.reg & bit) != 0) 
	{
		highLow	=	HIGH;
	}
	else
	{
		highLow	=	LOW;
	}

	return(highLow);
}
