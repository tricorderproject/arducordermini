/************************************************************************/
/*  																	*/
/*	Board_Data.c --	Default Board Customization Data Declarations		*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with a generic board using a	*/
/* PIC32 part in a 64-pin package.										*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/28/2011(GeneA): Created by splitting data out of Board_Defs.h	*/
/*  03/11/2012(BrianS): Modified for Fubarino board                     */
/*	02/12/2013(GeneA): removed dependency on Microchip plib library		*/
/*  20/05/2013(): Modified for Olimex Pinguino32 board					*/
/*																		*/
/************************************************************************/
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA  02111-1307  USA
/************************************************************************/

#if !defined(BOARD_DATA_C)
#define BOARD_DATA_C

#include <inttypes.h>

/* ------------------------------------------------------------ */
/*					Data Tables									*/
/* ------------------------------------------------------------ */
/* The following declarations define data used in pin mapping.	*/
/* ------------------------------------------------------------ */

#if defined(OPT_BOARD_DATA)

/* ------------------------------------------------------------ */
/* This table is used to map from port number to the address of
** the TRIS register for the port. This is used for setting the
** pin direction.
*/
const uint32_t	port_to_tris_PGM[] = {
	NOT_A_PORT,				//index value 0 is not used

#if defined(_PORTA)
	(uint32_t)&TRISA,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTB)
	(uint32_t)&TRISB,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTC)
	(uint32_t)&TRISC,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTD)
	(uint32_t)&TRISD,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTE)
	(uint32_t)&TRISE,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTF)
	(uint32_t)&TRISF,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTG)
	(uint32_t)&TRISG,
#else
	NOT_A_PORT,
#endif

	NOT_A_PORT,
};

/* ------------------------------------------------------------ */
/* This table is used to map the digital pin number to the port
** containing that pin. The default mapping is to assign pin numbers
** for every possible port bit in order from PORTA to PORTG.
*/
const uint8_t	digital_pin_to_port_PGM[] = {

	// 15 arduino digital gpio
	_IOPORT_PD,	//  0  RD2  D0  U1RX/OC3/RD2
	_IOPORT_PD,	//  1  RD3  D1  U1TX/OC4/RD3
	_IOPORT_PD,	//  2  RD4  D2  OC5/IC5/PMWR/CN13/RD4 BUTTTON
	_IOPORT_PD,	//  3  RD5  D3  PMRD/CN14/RD5
	_IOPORT_PD,	//  4  RD6  D4  CN15/RD6
	_IOPORT_PD,	//  5  RD7  D5  CN16/RD7
	_IOPORT_PD,	//  6  RD8  D6  RTCC/IC1/INT1/RD8
	_IOPORT_PD,	//  7  RD11 D7  IC4/PMCS1/PMA14/INT4/RD11
	_IOPORT_PB,	//  8  RB14 D8  AN14/#U2RTS/PMALH/PMA1/RB14
	_IOPORT_PB,	//  9  RB15 D9  AN15/OCFB/PMALL/PMA0/CN12/RB15
	_IOPORT_PG,	//  10 RG9  D10 RG9/#SS2/PMA2/CN11
	_IOPORT_PG,	//  11 RG8  D11 RG8/SDO2/PMA3/CN10
	_IOPORT_PG,	//  12 RG7  D12 RG7/SDI2/PMA4/CN9
	_IOPORT_PG,	//  13 RG6  D13 RG6/SCK2/PMA5/CN8 LED1

	// 6 special purpose digital ports
	_IOPORT_PD,	//  14 RD1	LED2 #U1RTS/OC2/RD1 
	_IOPORT_PD,	//  15 RD9  SDA #U1CTS/SDA1/IC2/INT2/RD9
	_IOPORT_PD,	//  16 RD10 SCL SCL1/IC3/PMCS2/PMA15/INT3/RD10
	_IOPORT_PD,	//  17 RD0  BUT OC1/INT0/RD0 
	_IOPORT_PF,	//  18 RF4  RX2 SDA2/U2RX/PMA9/CN17/RF4 no onboard pullup!
	_IOPORT_PF,	//  19 RF5  TX2 SCL2/U2TX/PMA8/CN18/RF5 no onboard pullup!

	// 8 PortRE digital ports
	_IOPORT_PE,	//  20 RE0		RE0/PMD0
	_IOPORT_PE,	//  21 RE1		RE0/PMD1
	_IOPORT_PE,	//  22 RE2		RE0/PMD2
	_IOPORT_PE,	//  23 RE3		RE0/PMD3
	_IOPORT_PE,	//  24 RE4		RE0/PMD4
	_IOPORT_PE,	//  25 RE5		RE0/PMD5
	_IOPORT_PE,	//  26 RE6		RE0/PMD6
	_IOPORT_PE,	//  27 RE7		RE0/PMD7

	// 8 analog ports
    	_IOPORT_PB,	//  28 RB1  A0  PGEC1/AN1/VREF-/CVREF-/CN3/RB1
	_IOPORT_PB,	//  29 RB2  A1  AN2/C2IN-/CN4/RB2
	_IOPORT_PB,	//  30 RB3  A2  AN3/C2IN+/CN5/RB3
	_IOPORT_PB,	//  31 RB4  A3  AN4/C1IN-/CN6/RB4
	_IOPORT_PB,	//  32 RB8  A4  AN8/#U2CTS/C1OUT/RB8
	_IOPORT_PB,	//  33 RB9  A5  AN9/C2OUT/PMA7/RB9
	_IOPORT_PB,	//  34 RB10 A6  TMS/AN10/CVREFOUT/PMA13/RB10
	_IOPORT_PB,	//  35 RB11 A7  TDO/AN11/PMA12//RB11

};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {


	_BV( 2 ) ,	//  0  RD2  D0
	_BV( 3 ) ,	//  1  RD3  D1
	_BV( 4 ) ,	//  2  RD4  D2
	_BV( 5 ) ,	//  3  RD5  D3
	_BV( 6 ) ,	//  4  RD6  D4
	_BV( 7 ) ,	//  5  RD7  D5
	_BV( 8 ) ,	//  6  RD8  D6
	_BV( 11 ) ,	//  7  RD11 D7
	_BV( 14 ) ,	//  8  RB14 D8
	_BV( 15 ) ,	//  9  RB15 D9
 	_BV( 9 ) ,	//  10 RG9  D10
	_BV( 8 ) ,	//  11 RG8  D11
	_BV( 7 ) ,	//  12 RG7  D12
	_BV( 6 ) ,	//  13 RG6  D13

	_BV( 1 ) ,	//  14 RD1  LED2
	_BV( 9 ) ,	//  15 RD9  SDA
	_BV( 10 ) ,	//  16 RD10 SCL
	_BV( 0 ) ,	//  17 RD0	 BUTTON
	_BV( 4 ) ,	//  18 RF4  RX2
	_BV( 5 ) ,	//  19 RF5  TX2

	_BV( 0 ) ,	//  20 RE0  RE0/PMD0
	_BV( 1 ) ,	//  21 RE1	 RE0/PMD1
	_BV( 2 ) ,	//  22 RE2	 RE0/PMD2
	_BV( 3 ) ,	//  23 RE3	 RE0/PMD3
	_BV( 4 ) ,	//  24 RE4	 RE0/PMD4
	_BV( 5 ) ,	//  25 RE5	 RE0/PMD5
	_BV( 6 ) ,	//  26 RE6	 RE0/PMD6
	_BV( 7 ) ,	//  27 RE7	 RE0/PMD7

	_BV( 1 ) ,	//  28 RB1  AN0  PGEC1/AN1/VREF-/CVREF-/CN3/RB1
	_BV( 2 ) ,	//  29 RB2	 AN1  AN2/C2IN-/CN4/RB2
	_BV( 3 ) ,	//  30 RB3  AN2  AN3/C2IN+/CN5/RB3
	_BV( 4 ) ,	//  31 RB4  AN3  AN4/C1IN-/CN6/RB4
	_BV( 8 ) ,	//  32 RB8  AN4  AN8/#U2CTS/C1OUT/RB8
	_BV( 9 ) ,	//  33 RB9  AN5  AN9/C2OUT/PMA7/RB9
	_BV( 10 ) ,	//  34 RB11 AN6  TMS/AN10/CVREFOUT/PMA13/RB10
	_BV( 11 ) ,	//  35 RB10 AN7  TDO/AN11/PMA12//RB11
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t	digital_pin_to_timer_PGM[] = {
	_TIMER_OC3 ,	//  0  RD2  D0  U1RX/OC3/RD2
	_TIMER_OC4 ,	//  1  RD3  D1  U1TX/OC4/RD3
	_TIMER_OC5 | _TIMER_IC5,	//  2  RD4  D2  OC5/IC5/PMWR/CN13/RD4 BUTTTON
	NOT_ON_TIMER ,	//  3  RD5  D3  PMRD/CN14/RD5
	NOT_ON_TIMER ,	//  4  RD6  D4  CN15/RD6
	NOT_ON_TIMER ,	//  5  RD7  D5  CN16/RD7
	_TIMER_IC1 ,	//  6  RD8  D6  RTCC/IC1/INT1/RD8
	_TIMER_IC4 ,	//  7  RD11 D7  IC4/PMCS1/PMA14/INT4/RD11
	NOT_ON_TIMER ,	//  8  RB14 D8  AN14/#U2RTS/PMALH/PMA1/RB14
	NOT_ON_TIMER ,	//  9  RB15 D9  AN15/OCFB/PMALL/PMA0/CN12/RB15
	NOT_ON_TIMER ,	//  10 RG9  D10 RG9/#SS2/PMA2/CN11
	NOT_ON_TIMER ,	//  11 RG8  D11 RG8/SDO2/PMA3/CN10
	NOT_ON_TIMER ,	//  12 RG7  D12 RG7/SDI2/PMA4/CN9
	NOT_ON_TIMER ,	//  13 RG6  D13 RG6/SCK2/PMA5/CN8 LED1

	_TIMER_OC2 ,	//  14 RD1  LED2 #U1RTS/OC2/RD1
	_TIMER_IC2 ,	//  15 RD9  SDA1 #U1CTS/SDA1/IC2/INT2/RD9 
	_TIMER_IC3 ,	//  16 RD10 SCL1 SCL1/IC3/PMCS2/PMA15/INT3/RD10 
	_TIMER_OC1 ,	//  17 RD0	BUT	OC1/INT0/RD0 
	NOT_ON_TIMER ,	//  18 RF4  RX2 SDA2/U2RX/PMA9/CN17/RF4
	NOT_ON_TIMER ,	//  19 RF5  TX2 SCL2/U2TX/PMA8/CN18/RF5

	NOT_ON_TIMER ,	//  20 RE0  RE0/PMD0
	NOT_ON_TIMER ,	//  21 RE1	RE0/PMD1
	NOT_ON_TIMER ,	//  22 RE2	RE0/PMD2
	NOT_ON_TIMER ,	//  23 RE3	RE0/PMD3
	NOT_ON_TIMER ,	//  24 RE4	RE0/PMD4
	NOT_ON_TIMER ,	//  25 RE5	RE0/PMD5
	NOT_ON_TIMER ,	//  26 RE6	RE0/PMD6
	NOT_ON_TIMER ,	//  27 RE7	RE0/PMD7

	NOT_ON_TIMER ,	//  28 RB1  A0  PGEC1/AN1/VREF-/CVREF-/CN3/RB1
	NOT_ON_TIMER ,	//  29 RB2  A1  AN2/C2IN-/CN4/RB2
	NOT_ON_TIMER ,	//  30 RB3  A2  AN3/C2IN+/CN5/RB3
	NOT_ON_TIMER ,	//  31 RB4  A3  AN4/C1IN-/CN6/RB4
	NOT_ON_TIMER ,	//  32 RB8  A4  AN8/#U2CTS/C1OUT/RB8
	NOT_ON_TIMER ,	//  33 RB9  A5  AN9/C2OUT/PMA7/RB9
	NOT_ON_TIMER ,	//  34 RB10 A6  TMS/AN10/CVREFOUT/PMA13/RB10
	NOT_ON_TIMER ,	//  35 RB11 A7  TDO/AN11/PMA12//RB11

};


/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
//#if defined(_NOT_USED_)
const uint8_t digital_pin_to_analog_PGM[] = {
	NOT_ANALOG_PIN,	// 0
	NOT_ANALOG_PIN,	// 1
	NOT_ANALOG_PIN,	// 2
	NOT_ANALOG_PIN,	// 3
	NOT_ANALOG_PIN,	// 4
	NOT_ANALOG_PIN,	// 5
	NOT_ANALOG_PIN,	// 6
	NOT_ANALOG_PIN,	// 7
	NOT_ANALOG_PIN,	// 8
	NOT_ANALOG_PIN,	// 9
	NOT_ANALOG_PIN,	// 10
	NOT_ANALOG_PIN,	// 11
	NOT_ANALOG_PIN,	// 12
	NOT_ANALOG_PIN,	// 13

	NOT_ANALOG_PIN,	// 14
	NOT_ANALOG_PIN,	// 15
	NOT_ANALOG_PIN,	// 16
	NOT_ANALOG_PIN,	// 17
	NOT_ANALOG_PIN,	// 18
	NOT_ANALOG_PIN,	// 19

	NOT_ANALOG_PIN,	// 20 RE0  RE0/PMD0
	NOT_ANALOG_PIN,	// 21 RE1  RE0/PMD0
	NOT_ANALOG_PIN,	// 22 RE2  RE0/PMD0
	NOT_ANALOG_PIN,	// 23 RE3  RE0/PMD0
	NOT_ANALOG_PIN,	// 24 RE4  RE0/PMD0
	NOT_ANALOG_PIN,	// 25 RE5  RE0/PMD0
	NOT_ANALOG_PIN,	// 26 RE6  RE0/PMD0
	NOT_ANALOG_PIN,	// 27 RE7  RE0/PMD0

 	_BOARD_AN0,	// 28 RB1  A0  PGEC1/AN1/VREF-/CVREF-/CN3/RB1
	_BOARD_AN1,	// 29 RB2  A1  AN2/C2IN-/CN4/RB2
	_BOARD_AN2,	// 30 RB3  A2  AN3/C2IN+/CN5/RB3
	_BOARD_AN3,	// 31 RB4  A3  AN4/C1IN-/CN6/RB4
	_BOARD_AN4,	// 32 RB8  A4  AN8/#U2CTS/C1OUT/RB8
	_BOARD_AN5,	// 33 RB9  A5  AN9/C2OUT/PMA7/RB9
	_BOARD_AN6,	// 34 RB10 A6  TMS/AN10/CVREFOUT/PMA13/RB10
	_BOARD_AN7,	// 35 RB11 A7  TDO/AN11/PMA12//RB11
};
//#endif

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
** In the default case, where there is a one-to-one mapping, this
** table isn't needed as the analogInPinToChannel() macro is defined
** to provide the mapping.
*/
//#if defined(_NOT_USED_)
const uint8_t analog_pin_to_channel_PGM[] = {
			//*	Arduino Pin		PIC32 Analog channel
	1,		//*	A0				1 to 1 mapping
	2,		//*	A1
	3,		//*	A2
	4,		//*	A3
	8,		//*	A4
	9,		//*	A5
	10,		//*	A6
	11,		//*	A7
};
//#endif

/* ------------------------------------------------------------ */
/*		Include Files for Board Customization Functions			*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Board Customization Functions					*/
/* ------------------------------------------------------------ */
/*																*/
/* The following can be used to customize the behavior of some	*/
/* of the core API functions. These provide hooks that can be	*/
/* used to extend or replace the default behavior of the core	*/
/* functions. To use one of these functions, add the desired	*/
/* code to the function skeleton below and then set the value	*/
/* of the appropriate compile switch above to 1. This will		*/
/* cause the hook function to be compiled into the build and	*/
/* to cause the code to call the hook function to be compiled	*/
/* into the appropriate core function.							*/
/*																*/
/* ------------------------------------------------------------ */
/***	_board_init
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function is called from the core init() function.
**		This can be used to perform any board specific init
**		that needs to be done when the processor comes out of
**		reset and before the user sketch is run.
*/
#if	(OPT_BOARD_INIT != 0)

void _board_init(void) {

	/*	Turn off Secondary oscillator so pins can be used as GPIO
	*/
	OSCCONCLR	=	_OSCCON_SOSCEN_MASK;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_pinMode
**
**	Parameters:
**		pin		- digital pin number to configure
**		mode	- mode to which the pin should be configured
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the pinMode
**		function. It can perform any special processing needed
**		when setting the pin mode. If this function returns zero,
**		control will pass through the normal pinMode code. If
**		it returns a non-zero value the normal pinMode code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_pinMode(uint8_t pin, uint8_t mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_getPinMode
**
**	Parameters:
**		pin		- digital pin number
**		mode	- pointer to variable to receive mode value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the getPinMode
**		function. It can perform any special processing needed
**		when getting the pin mode. If this function returns zero,
**		control will pass through the normal getPinMode code. If
**		it returns a non-zero value the normal getPinMode code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_getPinMode(uint8_t pin, uint8_t * mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_digitalWrite
**
**	Parameters:
**		pin		- digital pin number
**		val		- value to write to the pin
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the digitalWrite
**		function. It can perform any special processing needed
**		in writing to the pin. If this function returns zero,
**		control will pass through the normal digitalWrite code. If
**		it returns a non-zero value the normal digitalWrite code isn't
**		executed.
*/#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_digitalWrite(uint8_t pin, uint8_t val) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_digitalRead
**
**	Parameters:
**		pin		- digital pin number
**		val		- pointer to variable to receive pin value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the digitalRead
**		function. It can perform any special processing needed
**		in reading from the pin. If this function returns zero,
**		control will pass through the normal digitalRead code. If
**		it returns a non-zero value the normal digitalRead code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_digitalRead(uint8_t pin, uint8_t * val) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogRead
**
**	Parameters:
**		pin		- analog channel number
**		val		- pointer to variable to receive analog value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogRead
**		function. It can perform any special processing needed
**		in reading from the pin. If this function returns zero,
**		control will pass through the normal analogRead code. If
**		it returns a non-zero value the normal analogRead code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_READ != 0)

int	_board_analogRead(uint8_t pin, int * val) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogReference
**
**	Parameters:
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogReference
**		function. It can perform any special processing needed
**		to set the reference voltage. If this function returns zero,
**		control will pass through the normal analogReference code. If
**		it returns a non-zero value the normal analogReference code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_READ != 0)

int	_board_analogReference(uint8_t mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogWrite
**
**	Parameters:
**		pin		- pin number
**		val		- analog value to write
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogWrite
**		function. It can perform any special processing needed
**		in writing to the pin. If this function returns zero,
**		control will pass through the normal analogWrite code. If
**		it returns a non-zero value the normal analogWrite code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_WRITE != 0)

int	_board_analogWrite(uint8_t pin, int val) {

	return 0;

}

#endif

#endif // OPT_BOARD_DATA

/* ------------------------------------------------------------ */

#endif	// BOARD_DATA_C

/************************************************************************/
