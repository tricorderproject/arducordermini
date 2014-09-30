//************************************************************************
//*	wiring_analog.c
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
//*	Boston, MA 02111-1307 USA
//*	
//*	
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 15,	2010	<MLS> Started on wiring_analog.c
//*	Oct 17,	2010	<MLS> analogRead working
//*	Oct 19,	2010	<MLS> analogWrite (PWM) working
//*	Oct 19,	2010	<MLS> turnOffPWM moved to wiring_analog.c from wiring_digital.c
//*	Apr 26,	2011	<MLS> Errata sheet PIC32MX5XX-6XX-7XX Errata.pdf item #26
//*	May  5,	2011	<MLS> Uno board does not have 1 to 1 pin mapping for analog, added analogInPinToBit
//*	May 18,	2011	<MLS> JP4 on the uno board must be in the RD9 position for PWM to work on pin 10
//*	May 23,	2011	<MLS> Added support for pin numbers to be remaped to analog numbers, (left out in iniitial version)
//*	Aug  7,	2011	<MarcMaccomb> fixed bug in Anaglog Read (Issue (#67)
//*	Aug  7,	2011	<Gene Apperson> fixed bug in Anaglog Write (Issue #70)
//*	Aug  7,	2011	<Gene Apperson> Added necessary code for analogReference (Issue #69)
//* Nov 12, 2011	<Gene Apperson> modified for board variant support
//*	Jul 26, 2012	<GeneApperson> Added PPS support for PIC32MX1xx/MX2xx devices
//	Feb  6, 2013	<Gene Apperson> Removed dependencies on the Microchip plib library
//************************************************************************

#include <p32xxxx.h>

#include "wiring_private.h"

#define OPT_BOARD_INTERNAL	//pull in internal symbol definitons
#include "p32_defs.h"
#include "pins_arduino.h"

#define	PWM_TIMER_PERIOD	((__PIC32_pbClk / 256) / 490)

uint32_t	analog_reference = 0;	//default to AVDD, AVSS

uint8_t		pwm_active = 0;			//keeps track of active PWM outputs


//*********************************************************************
void analogReference(uint8_t mode)
{

#if (OPT_BOARD_ANALOG_READ != 0)
	/* Peform any board specific processing.
	*/
int _board_analogReference(uint8_t mode);

	if (_board_analogReference(mode) != 0)
	{
		return;
	}
#endif

	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
//	analog_reference	=	mode;
    switch(mode)
    {
        case EXTERNAL:		//select Vref+,AVSS
            analog_reference	=	0x2000;
            break;

        case EXTMINUS:		//select AVDD, Vref-
            analog_reference	=	0x4000;
            break;

        case EXTPLUSMINUS:	//select Vref+, Vref-
            analog_reference	=	0x6000;
            break;

        case DEFAULT:
        default:			//select AVDD, AVSS
            analog_reference	=	0x0000;
            break;
    }

}

//*********************************************************************
//*	Marc McComb Aug 2011
//*	Found bug with analogRead(). When using more than one ADC input in a program, 
//*	only one result will be read with that value being mirrored in the second result.
//*	I commented out the code using the Microchip PIC32 Peripheral Libraries and substituted 
//*	direct writes to the registers as shown below. This fixed all problems and works great:
//*********************************************************************
int analogRead(uint8_t pin)
{
	int analogValue;
	uint8_t	channelNumber;
	uint8_t ain;

	/* Check if pin number is in valid range.
	*/
	if (pin >= NUM_DIGITAL_PINS_EXTENDED)
	{
		return 0;
	}

#if (OPT_BOARD_ANALOG_READ != 0)
	/* Peform any board specific processing.
	*/
int _board_analogRead(uint8_t pin, int * val);
int	tmp;

	if (_board_analogRead(pin, &tmp) != 0)
	{
		return tmp;
	}
#endif		// OPT_BOARD_ANALOG_READ

	/* Pin number is allowed to be either the digital pin number or the
	** analog pin number. Map the input so that it is guaranteed to be
	** an analog pin number.
	*/
	ain = (pin < NUM_DIGITAL_PINS) ? digitalPinToAnalog(pin) : NOT_ANALOG_PIN;
	if (ain == NOT_ANALOG_PIN) {
		return 0;
	}

	/* Map the analog pin number to the correct analog mux channel in the
	** A/D converter. In some cases this is a direct mapping. In that case,
	** the conversion macro just returns it parameter.
	*/
	channelNumber = analogInPinToChannel(ain);

	/* Ensure that the pin associated with the analog channel is in analog
	** input mode, and select the channel in the input mux.
	*/
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	p32_ioport *	iop;
	uint16_t		bit;

	/* In MX1/MX2 devices, there is a control register ANSEL associated with
	**  each io port. We need to set the appropriate bit in the ANSEL register
	**  for the io port associated with this pin to ensure that it is in analog
	**  input mode.
	**
	** Obtain pointer to the registers for this io port.
	*/
	iop = portRegisters(digitalPinToPort(pin));

	/* Obtain bit mask for the specific bit for this pin.
	*/
	bit = digitalPinToBitMask(pin);

	/* Set the bit in the ANSELx register to ensure that the pin is in
	** analog input mode.
	*/
	iop->ansel.set = bit;
#else
	/* In the other PIC32 devices, all of the analog input capable pins are
	**  in PORTB, and the AD1PCFG register is used to set the pins associated
	**  with PORTB to analog input or digital input mode. Clear the appropriate
	**  bit in AD1PCFG.
	*/
	AD1PCFGCLR = (1 << channelNumber);
#endif		// defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

	AD1CHS = (channelNumber & 0xFFFF) << 16;
	AD1CON1	=	0; //Ends sampling, and starts converting

	/* Set up for manual sampling
	*/
	AD1CSSL	=	0;
	AD1CON3	=	0x0002;	//Tad = internal 6 Tpb
	AD1CON2	=	analog_reference;

	/* Turn on ADC
	*/
	AD1CON1SET	=	0x8000;
	
	/* Start sampling
	*/
	AD1CON1SET	=	0x0002;
	
	/* Delay for a bit
	*/
	delayMicroseconds(2);

	/* Start conversion
	*/
	AD1CON1CLR	=	0x0002;
	
	/* Wait for conversion to finish
	*/
	while (!(AD1CON1 & 0x0001));
	

	/* Read the ADC Value
	*/
	analogValue	=	ADC1BUF0;
	
	return (analogValue);
}

//*********************************************************************
//*	PWM output only works on the pins with hardware support. 
//*	These are defined in the appropriate pins_*.c file.
//*	For the rest of the pins, we default to digital output.
//*********************************************************************
//*	Gene Apperson Aug 2011
//*	analogWrite resets timer 2 each time it is called. 
//*	This causes the PWM to fail if it is called repeatedly with a short interval between calls.
//*	This is the suggested fixed version of analogWrite.
//*********************************************************************
void analogWrite(uint8_t pin, int val)
{
	uint16_t	timer;
	uint8_t		pwm_mask;
	p32_oc *	ocp;

	/* Check if pin number is in valid range.
	*/
	if (pin >= NUM_DIGITAL_PINS_EXTENDED)
	{
		return 0;
	}

#if (OPT_BOARD_ANALOG_WRITE != 0)
	/* Peform any board specific processing.
	*/
int	_board_analogWrite(uint8_t pin, int val);

	if (_board_analogWrite(pin, val) != 0)
	{
		return;
	}
#endif		// OPT_BOARD_ANALOG_WRITE

	/* Determine if this is actually a PWM capable pin or not.
	** The value in timer will be the output compare number associated with
	** the pin, or NOT_ON_TIMER if no OC is connected to the pin.
	** The values 0 or >=255 have the side effect of turning off PWM on
	** pins that are PWM capable.
	*/
	timer = digitalPinToTimerOC(pin) >> _BN_TIMER_OC;

	if ((timer == NOT_ON_TIMER) || (val == 0) || (val >= 255))
	{
		/* We're going to be setting the pin to a steady state.
		** Make sure it is set as a digital output. And then set
		** it LOW or HIGH depending on the value requested to be
		** written. The digitalWrite function has the side effect
		** of turning off PWM on the pin if it happens to be a
		** PWM capable pin.
		*/
		pinMode(pin, OUTPUT);

	    if (val < 128)
	    {
	        digitalWrite(pin, LOW);
	    }
	    else
	    {
	        digitalWrite(pin, HIGH);
	    }
	}

	else
	{
		/* It's a PWM capable pin. Timer 2 is used for the time base
		** for analog output, so if no PWM are currently active then
		** Timer 2 needs to be initialized
		*/
	    if (pwm_active == 0)
	    {
			T2CON = TBCON_PS_256;
			TMR2 = 0;
			PR2 = PWM_TIMER_PERIOD;
			T2CONSET = TBCON_ON;
	    }

		/* Generate bit mask for this output compare.
		*/
		pwm_mask = (1 << (timer - (_TIMER_OC1 >> _BN_TIMER_OC)));

		/* Obtain a pointer to the output compare being being used
		** NOTE: as of 11/15/2011 All existing PIC32 devices
		** (PIC32MX1XX/2XX/3XX/4XX/5XX/6XX/7XX) have the output compares
		** in consecutive locations. The base address is _OCMP1_BASE_ADDRESS
		** and the distance between their addresses is 0x200.
		*/
		ocp = (p32_oc *)(_OCMP1_BASE_ADDRESS + (0x200 * (timer - (_TIMER_OC1 >> _BN_TIMER_OC))));

		/* If the requested PWM isn't active, init its output compare. Enabling
		** the output compare takes over control of pin direction and forces the
		** pin to be an output.
		*/
		if ((pwm_active & pwm_mask) == 0) 
		{

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
			volatile uint32_t *	pps;
				
			/* On devices with peripheral pin select, it is necessary to connect
			** the output compare to the pin.
			*/
			pps = ppsOutputRegister(timerOCtoDigitalPin(timer));
			*pps = ppsOutputSelect(timerOCtoOutputSelect(timer));
#endif
	        ocp->ocxR.reg   = ((PWM_TIMER_PERIOD*val)/256);
			ocp->ocxCon.reg = OCCON_SRC_TIMER2 | OCCON_PWM_FAULT_DISABLE;
			ocp->ocxCon.set = OCCON_ON;

	        pwm_active |= pwm_mask;
	    }

		/* Set the duty cycle register for the requested output compare
		*/
		ocp->ocxRs.reg = ((PWM_TIMER_PERIOD*val)/256);

	}
}


//************************************************************************
void turnOffPWM(uint8_t timer)
{
	p32_oc *	ocp;

	/* Disable the output compare.
	*/
	ocp = (p32_oc *)(_OCMP1_BASE_ADDRESS + (0x200 * (timer - (_TIMER_OC1 >> _BN_TIMER_OC))));
	ocp->ocxCon.clr = OCCON_ON;

	// Turn off the bit saying that this PWM is active.
	pwm_active &= ~(1 << (timer - (_TIMER_OC1 >> _BN_TIMER_OC)));

	// If no PWM are active, turn off the timer.
	if (pwm_active == 0)
	{
    	T2CONCLR = TBCON_ON;
	}
}
