/************************************************************************/
/*																		*/
/*	Board_Data.c -- Board Customization Data for Digilent Cerebot MX3cK	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent Cerebot		*/
/* MX3cK board.															*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/28/2011(GeneA): Created by splitting data out of Board_Defs.h	*/
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
const uint32_t port_to_tris_PGM[] = {
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
** containing that pin.
*/
const uint8_t	digital_pin_to_port_PGM[] = {
	// Connector JA
	_IOPORT_PE,		//	0  RE0		PMD0/RE0
	_IOPORT_PE,		//	1  RE1		PMD1/RE1
	_IOPORT_PE,		//	2  RE2		PMD2/RE2
	_IOPORT_PE,		//	3  RE3		PMD3/RE3
	_IOPORT_PE,		//	4  RE4		PMD4/RE4
	_IOPORT_PE,		//	5  RE5		PMD5/RE5
	_IOPORT_PE,		//	6  RE6		PMD6/RE6
	_IOPORT_PE,		//	7  RE7		PMD7/RE7
	
	//Connector JB
	_IOPORT_PD,		//	8  RD9		IC2/U1CTS/INT2/RD9
	_IOPORT_PF,		//	9  RF3		U1TX/SDO1/RF3
	_IOPORT_PF,		//	10 RF2		U1RX/SDI1/RF2
	_IOPORT_PF,		//	11 RF6		U1RTS/SCK1/INT0/RF6
	_IOPORT_PD,		//	12 RD6		CN15/RD6
	_IOPORT_PD,		//	13 RD5		PMRD/CN14/RD5	
	_IOPORT_PD,		//	14 RD4		PMWR/OC5/IC5/CN13/RD4
	_IOPORT_PD,		//	15 RD7		CN16/RD7
	
	//Connector JC
	_IOPORT_PB,		//	16 RB8		U2CTS/C1OUT/AN8/RB8
	_IOPORT_PF,		//	17 RF5		U2TX/PMA8/SCL2/CN18/RF5
	_IOPORT_PF, 	//	18 RF4		U2RX/PMA9/SDA2/CN17/RF4
	_IOPORT_PB,		//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14
	_IOPORT_PB,		//	20 RB0		PGED1/PMA6/AN0/VREF+/CVREF+/CN2/RB0
	_IOPORT_PB,		//	21 RB1		AN1/VREF-/CVREF-/CN3/RB1
	_IOPORT_PD,		//	22 RD0		OC1/RD0
	_IOPORT_PD,		//	23 RD1		OC2/RD1
	
	//Connector JD
	_IOPORT_PB,		//	24 RB2		C2IN-/AN2/SS1/CN4/RB2
	_IOPORT_PD,		//	25 RD2		OC3/RD2
	_IOPORT_PD,		//	26 RD10		IC3/PMCS2/PMA15/INT3/RD10
	_IOPORT_PB,		//	27 RB9		PMA7/C2OUT/AN9/RB9
	_IOPORT_PB,		//	28 RB12		TCK/PMA11/AN12/RB12
	_IOPORT_PD,		//	29 RD3		OC4/RD3
	_IOPORT_PD,		//	30 RD11		IC4/PMCS1/PMA14/INT4/RD11
	_IOPORT_PB,		//	31 RB13		TDI/PMA10/AN13/RB13
	
	//Connector JE
	_IOPORT_PG,		//  32 RG9		PMA2/SS2/CN11/RG9
	_IOPORT_PG,		//	33 RG8		(MOSI) PMA3/SDO2/CN10/RG8
	_IOPORT_PG,		//	34 RG7		(MISO) PMA4/SDI1/CN9/RG7
	_IOPORT_PG,		//	35 RG6		SCK2/PMA5/CN8/RG6
	_IOPORT_PD,		//	36 RD8		IC1/RTCC/INT1/RD8
	_IOPORT_PB,		//	37 RB5		C1IN+/AN5/CN7/RB5
	_IOPORT_PB,		//	38 RB4		C1IN-/AN4/CN6/RB4
	_IOPORT_PB,		//	39 RB3		C2IN+/AN3/CN5/RB3
	
	//I2C connector J2
	_IOPORT_PG,		//	40 RG3		SDA1/RG3
	_IOPORT_PG,		//	41 RG2		SCL1/RG2
	
	//LEDs	
	_IOPORT_PF,		//	42 RF0		LED4
	_IOPORT_PF,		//	43 RF1		LED5
	
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t digital_pin_to_bit_mask_PGM[] = {
	//Connector JA
	_BV( 0 ) ,		//	0  RE0		PMD0/RE0
	_BV( 1 ) ,		//	1  RE1		PMD1/RE1
	_BV( 2 ) ,		//	2  RE2		PMD2/RE2
	_BV( 3 ) ,		//	3  RE3		PMD3/RE3
	_BV( 4 ) ,		//	4  RE4		PMD4/RE4
	_BV( 5 ) ,		//	5  RE5		PMD5/RE5
	_BV( 6 ) ,		//	6  RE6		PMD6/RE6
	_BV( 7 ) ,		//	7  RE7		PMD7/RE7
	
	//Connector JB
	_BV( 9 ) ,		//	8  RD9		IC2/U1CTS/INT2/RD9
	_BV( 3 ) ,		//	9  RF3		U1TX/SDO1/RF3
	_BV( 2 ) ,		//	10 RF2		U1RX/SDI1/RF2
	_BV( 6 ) ,		//	11 RF6		U1RTS/SCK1/INT0/RF6
	_BV( 6 ) ,		//	12 RD6		CN15/RD6
	_BV( 5 ) ,		//	13 RD5		PMRD/CN14/RD5	
	_BV( 4 ) ,		//	14 RD4		PMWR/OC5/IC5/CN13/RD4
	_BV( 7 ) ,		//	15 RD7		CN16/RD7
	
	//Connector JC
	_BV( 8 ) ,		//	16 RB8		U2CTS/C1OUT/AN8/RB8
	_BV( 5 ) ,		//	17 RF5		U2TX/PMA8/SCL2/CN18/RF5
	_BV( 4 ) , 		//	18 RF4		U2RX/PMA9/SDA2/CN17/RF4
	_BV( 14 ),		//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14
	_BV( 0 ) ,		//	20 RB0		PGED1/PMA6/AN0/VREF+/CVREF+/CN2/RB0
	_BV( 1 ) ,		//	21 RB1		AN1/VREF-/CVREF-/CN3/RB1
	_BV( 0 ) ,		//	22 RD0		OC1/RD0
	_BV( 1 ) ,		//	23 RD1		OC2/RD1
	
	//Connector JD
	_BV( 2 ) ,		//	24 RB2		C2IN-/AN2/SS1/CN4/RB2
	_BV( 2 ) ,		//	25 RD2		OC3/RD2
	_BV( 10 ) ,		//	26 RD10		IC3/PMCS2/PMA15/INT3/RD10
	_BV( 9 ) ,		//	27 RB9		PMA7/C2OUT/AN9/RB9
	_BV( 12 ) ,		//	28 RB12		TCK/PMA11/AN12/RB12
	_BV( 3 ) ,		//	29 RD3		OC4/RD3
	_BV( 11 ) ,		//	30 RD11		IC4/PMCS1/PMA14/INT4/RD11
	_BV( 13 ) ,		//	31 RB13		TDI/PMA10/AN13/RB13
	
	//Connector JE
	_BV( 9 ) ,		//  32 RG9		PMA2/SS2/CN11/RG9
	_BV( 8 ) ,		//	33 RG8		MOSI/RG8
	_BV( 7 ) ,		//	34 RG7		MISO/RG7
	_BV( 6 ) ,		//	35 RG6		SCK2/PMA5/CN8/RG6
	_BV( 8 ) ,		//	36 RD8		IC1/RTCC/INT1/RD8
	_BV( 5 ) ,		//	37 RB5		C1IN+/AN5/CN7/RB5
	_BV( 4 ) ,		//	38 RB4		C1IN-/AN4/CN6/RB4
	_BV( 3 ) ,		//	39 RB3		C2IN+/AN3/CN5/RB3
	
	//I2C Connector J2
	_BV( 3 ) ,		//	40 RG3		SDA1/RG3
	_BV( 2 ) ,		//	41 RG2		SCL1/RG2
	
	//LEDs	
	_BV( 0 ) ,		//	42 RF0		LED4
	_BV( 1 ) ,		//	43 RF1		LED5

};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t digital_pin_to_timer_PGM[] = {
	// Connector JA
	NOT_ON_TIMER,			//	0  RE0		PMD0/RE0
	NOT_ON_TIMER,			//	1  RE1		PMD1/RE1
	NOT_ON_TIMER,			//	2  RE2		PMD2/RE2
	NOT_ON_TIMER,			//	3  RE3		PMD3/RE3
	NOT_ON_TIMER,			//	4  RE4		PMD4/RE4
	NOT_ON_TIMER,			//	5  RE5		PMD5/RE5
	NOT_ON_TIMER,			//	6  RE6		PMD6/RE6
	NOT_ON_TIMER,			//	7  RE7		PMD7/RE7
	
	// Connector JB
	_TIMER_IC2,				//	8  RD9		IC2/U1CTS/INT2/RD9
	NOT_ON_TIMER,			//	9  RF3		U1TX/SDO1/RF3
	NOT_ON_TIMER,			//	10 RF2		U1RX/SDI1/RF2
	NOT_ON_TIMER,			//	11 RF6		U1RTS/SCK1/INT0/RF6
	NOT_ON_TIMER,			//	12 RD6		CN15/RD6
	NOT_ON_TIMER,			//	13 RD5		PMRD/CN14/RD5	
	_TIMER_OC5|_TIMER_IC5,	//	14 RD4		PMWR/OC5/IC5/CN13/RD4
	NOT_ON_TIMER,			//	15 RD7		CN16/RD7
	
	// Connector JC
	NOT_ON_TIMER,			//	16 RB8		U2CTS/C1OUT/AN8/RB8
	NOT_ON_TIMER,			//	17 RF5		U2TX/PMA8/SCL2/CN18/RF5
	NOT_ON_TIMER, 			//	18 RF4		U2RX/PMA9/SDA2/CN17/RF4
	NOT_ON_TIMER,			//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14
	NOT_ON_TIMER,			//	20 RB0		PGED1/PMA6/AN0/VREF+/CVREF+/CN2/RB0
	NOT_ON_TIMER,			//	21 RB1		AN1/VREF-/CVREF-/CN3/RB1
	_TIMER_OC1,				//	22 RD0		OC1/RD0
	_TIMER_OC2,				//	23 RD1		OC2/RD1
	
	// Connector JD
	NOT_ON_TIMER,			//	24 RB2		C2IN-/AN2/SS1/CN4/RB2
	_TIMER_OC3,				//	25 RD2		OC3/RD2
	_TIMER_IC3,				//	26 RD10		IC3/PMCS2/PMA15/INT3/RD10
	NOT_ON_TIMER,			//	27 RB9		PMA7/C2OUT/AN9/RB9
	NOT_ON_TIMER,			//	28 RB12		TCK/PMA11/AN12/RB12
	_TIMER_OC4,				//	29 RD3		OC4/RD3
	_TIMER_IC4,				//	30 RD11		IC4/PMCS1/PMA14/INT4/RD11
	NOT_ON_TIMER,			//	31 RB13		TDI/PMA10/AN13/RB13
	
	// Connector JE
	NOT_ON_TIMER,			//  32 RG9		PMA2/SS2/CN11/RG9
	NOT_ON_TIMER,			//	33 RG8		MOSI/RG8
	NOT_ON_TIMER,			//	34 RG7		MISO/RG7
	NOT_ON_TIMER,			//	35 RG6		SCK2/PMA5/CN8/RG6
	_TIMER_IC1,				//	36 RD8		IC1/RTCC/INT1/RD8
	NOT_ON_TIMER,			//	37 RB5		C1IN+/AN5/CN7/RB5
	NOT_ON_TIMER,			//	38 RB4		C1IN-/AN4/CN6/RB4
	NOT_ON_TIMER,			//	39 RB3		C2IN+/AN3/CN5/RB3
	
	// I2C Connector J2
	NOT_ON_TIMER,			//	40 RG3		SDA1/RG3
	NOT_ON_TIMER,			//	41 RG2		SCL1/RG2
	
	//LEDs	
	NOT_ON_TIMER,			//	42 RF0		LED4
	NOT_ON_TIMER,			//	43 RF1		LED5
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
const uint8_t digital_pin_to_analog_PGM[] = {
	// Connector JA
	NOT_ANALOG_PIN,		//	0  RE0		PMD0/RE0
	NOT_ANALOG_PIN,		//	1  RE1		PMD1/RE1
	NOT_ANALOG_PIN,		//	2  RE2		PMD2/RE2
	NOT_ANALOG_PIN,		//	3  RE3		PMD3/RE3
	NOT_ANALOG_PIN,		//	4  RE4		PMD4/RE4
	NOT_ANALOG_PIN,		//	5  RE5		PMD5/RE5
	NOT_ANALOG_PIN,		//	6  RE6		PMD6/RE6
	NOT_ANALOG_PIN,		//	7  RE7		PMD7/RE7
	
	// Connector JB
	NOT_ANALOG_PIN,		//	8  RD9		IC2/U1CTS/INT2/RD9
	NOT_ANALOG_PIN,		//	9  RF3		U1TX/SDO1/RF3
	NOT_ANALOG_PIN,		//	10 RF2		U1RX/SDI1/RF2
	NOT_ANALOG_PIN,		//	11 RF6		U1RTS/SCK1/INT0/RF6
	NOT_ANALOG_PIN,		//	12 RD6		CN15/RD6
	NOT_ANALOG_PIN,		//	13 RD5		PMRD/CN14/RD5	
	NOT_ANALOG_PIN,		//	14 RD4		PMWR/OC5/IC5/CN13/RD4
	NOT_ANALOG_PIN,		//	15 RD7		CN16/RD7
	
	// Connector JC
	_BOARD_AN0,			//	16 RB8		U2CTS/C1OUT/AN8/RB8
	NOT_ANALOG_PIN,		//	17 RF5		U2TX/PMA8/SCL2/CN18/RF5
	NOT_ANALOG_PIN, 	//	18 RF4		U2RX/PMA9/SDA2/CN17/RF4
	_BOARD_AN1,			//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14
	_BOARD_AN2,			//	20 RB0		PGED1/PMA6/AN0/VREF+/CVREF+/CN2/RB0
	_BOARD_AN3,			//	21 RB1		AN1/VREF-/CVREF-/CN3/RB1
	NOT_ANALOG_PIN,		//	22 RD0		OC1/RD0
	NOT_ANALOG_PIN,		//	23 RD1		OC2/RD1
	
	// Connector JD
	_BOARD_AN4,			//	24 RB2		C2IN-/AN2/SS1/CN4/RB2
	NOT_ANALOG_PIN,		//	25 RD2		OC3/RD2
	NOT_ANALOG_PIN,		//	26 RD10		IC3/PMCS2/PMA15/INT3/RD10
	_BOARD_AN5,			//	27 RB9		PMA7/C2OUT/AN9/RB9
	_BOARD_AN6,			//	28 RB12		TCK/PMA11/AN12/RB12
	NOT_ANALOG_PIN,		//	29 RD3		OC4/RD3
	NOT_ANALOG_PIN,		//	30 RD11		IC4/PMCS1/PMA14/INT4/RD11
	_BOARD_AN7,			//	31 RB13		TDI/PMA10/AN13/RB13
	
	// Connector JE
	NOT_ANALOG_PIN,		//  32 RG9		PMA2/SS2/CN11/RG9
	NOT_ANALOG_PIN,		//	33 RG8		MOSI/RG8
	NOT_ANALOG_PIN,		//	34 RG7		MISO/RG7
	NOT_ANALOG_PIN,		//	35 RG6		SCK2/PMA5/CN8/RG6
	NOT_ANALOG_PIN,		//	36 RD8		IC1/RTCC/INT1/RD8
	_BOARD_AN8,			//	37 RB5		C1IN+/AN5/CN7/RB5
	_BOARD_AN9,			//	38 RB4		C1IN-/AN4/CN6/RB4
	_BOARD_AN10,		//	39 RB3		C2IN+/AN3/CN5/RB3
	
	// I2C Connector J2
	NOT_ANALOG_PIN,		//	40 RG3		SDA1/RG3
	NOT_ANALOG_PIN,		//	41 RG2		SCL1/RG2
	
	//LEDs	
	NOT_ANALOG_PIN,		//	42 RF0		LED4
	NOT_ANALOG_PIN,		//	43 RF1		LED5
};

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
*/
const uint8_t analog_pin_to_channel_PGM[] =
{
			//*	chipKIT Pin		PIC32 Analog channel
	8,		//*	A0						AN8
	14,		//*	A1						AN14
	0,		//*	A2						AN0
	1,		//*	A3						AN1
	2,		//*	A4						AN2
	9,		//*	A5						AN9
	12,		//*	A6						AN12
	13,		//*	A7						AN5
	5,		//*	A8						AN13
	4,		//*	A9						AN5
	3,		//*	A10						AN4
};

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
