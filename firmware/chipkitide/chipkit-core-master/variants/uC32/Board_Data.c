/************************************************************************/
/*																		*/
/*	Board_Data.c -- Board Customization Data for Digilent chipKIT uC32	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2012, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent chipKIT		*/
/* Uno32 board.															*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	04/18/2012(GeneA): Created											*/
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
const uint8_t digital_pin_to_port_PGM[] = {
	_IOPORT_PF,		//	0 RF2		U1RX/SDI1/RF2
	_IOPORT_PF,		//	1 RF3		U1TX/SDO1/RF3
	_IOPORT_PD,		//	2 RD8		IC1/RTCC/INT1/RD8
	_IOPORT_PD,		//	3 RD0		OC1/RD0
	_IOPORT_PF,		//	4 RF1		RF1
	_IOPORT_PD,		//	5 RD1		OC2/RD1
	_IOPORT_PD,		//	6 RD2		OC3/RD2
	_IOPORT_PD,		//	7 RD9		IC2/U1CTS/INT2/RD9
	_IOPORT_PD,		//	8 RD10		IC3/PMCS2/PMA15/INT3/RD10
	_IOPORT_PD,		//	9 RD3		OC4/RD3
	_IOPORT_PD,		//	10 RD4		PMWR/OC5/IC5/CN13/RD4
	_IOPORT_PG,		//	11 RG8		(SDO2/PMA3/CN10/RG8) or (SDI2/PMA5/CN9/RG7)
	_IOPORT_PG,		//	12 RG7		(SDI2/PMA5/CN9/RG7) or (SDO2/PMA3/CN10/RG8)
	_IOPORT_PG,		//	13 RG6		SCK2/PMA5/CN8/RG6		LD4
	_IOPORT_PB,		//	14 RB2		C2IN-/AN2/SS1/CN4/RB2
	_IOPORT_PB,		//	15 RB4		C1IN-/AN4/CN6/RB4
	_IOPORT_PB,		//	16 RB8		U2CTS/C1OUT/AN8/RB8
	_IOPORT_PB,		//	17 RB10		TMS/CVREFOUT/PMA13/AN10/RB10
	_IOPORT_PB,		//	18 RB12		TCK/PMA11/AN12/RB12
	_IOPORT_PB,		//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14

	_IOPORT_PB,		//	20 RB3		C2IN+/AN3/CN5/RB3
	_IOPORT_PB,		//	21 RB5		C1IN+/AN5/CN7/RB5
	_IOPORT_PB,		//	22 RB9		PMA7/C2OUT/AN9/RB9
	_IOPORT_PB,		//	23 RB11		TDO/PMA12/AN11/RB11
	_IOPORT_PB,		//	24 RB13		TDI/PMA10/AN13/RB13
	_IOPORT_PB,		//	25 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15

	_IOPORT_PE,		//	26 RE0		PMD0/RE0
	_IOPORT_PE,		//	27 RE1		PMD1/RE1
	_IOPORT_PE,		//	28 RE2		PMD2/RE2
	_IOPORT_PE,		//	29 RE3		PMD3/RE3
	_IOPORT_PE,		//	30 RE4		PMD4/RE4
	_IOPORT_PE,		//	31 RE5		PMD5/RE5
	_IOPORT_PE,		//	32 RE6		PMD6/RE6
	_IOPORT_PE,		//	33 RE7		PMD7/RE7
	_IOPORT_PD,		//	34 RD5		PMRD/CN14/RD5
	_IOPORT_PD,		//	35 RD11		IC4/PMCS1/PMA14/INT4/RD11
	_IOPORT_PD,		//	36 RD6		CN15/RD6
	_IOPORT_PD,		//	37 RD7		CN16/RD7
	_IOPORT_PF,		//	38 RF6		U1RTS/BCLK1/SCK1/INT0/RF6
	_IOPORT_PF,		//	39 RF4		PMA9/U2RX/SDA2/CN17/RF4
	_IOPORT_PF,		//	40 RF5		PMA8/U2TX/SCL2/CN18/RF5
	_IOPORT_PB,		//	41 RB1		PGC1/AN1/VREF-/CVREF-/CN3/RB1
	_IOPORT_PB,		//	42 RB0		PGED1/PMA6/AN0/VREF+/CVREF+/CN2/RB0

	_IOPORT_PF,		//	43 RF0		RF0						LD5
	_IOPORT_PG,		//	44 RG9		SS2/PMA2/CN11/RG9
	_IOPORT_PG,		//	45 RG3		SDA1/RG3
	_IOPORT_PG,		//	46 RG2		SCL1/RG2
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t digital_pin_to_bit_mask_PGM[] =
{
	_BV( 2 ),		//	0 RF2		U1RX/SDI1/RF2
	_BV( 3 ),		//	1 RF3		U1TX/SDO1/RF3
	_BV( 8 ),		//	2 RD8		IC1/RTCC/INT1/RD8
	_BV( 0 ),		//	3 RD0		OC1/RD0
	_BV( 1 ),		//	4 RF1		RF1
	_BV( 1 ),		//	5 RD1		OC2/RD1
	_BV( 2 ),		//	6 RD2		OC3/RD2
	_BV( 9 ),		//	7 RD9		IC2/U1CTS/INT2/RD9
	_BV( 10 ),		//	8 RD10		IC3/PMCS2/PMA15/INT3/RD10
	_BV( 3 ),		//	9 RD3		OC4/RD3
	_BV( 4 ),		//	10 RD4		PMWR/OC5/IC5/CN13/RD4
	_BV( 8 ),		//	11 RG8		(SDO2/PMA3/CN10/RG8) or (SDI2/PMA5/CN8/RG7)
	_BV( 7 ),		//	12 RG7		(SDI2/PMA5/CN8/RG7) or (SDO2/PMA3/CN10/RG8)
	_BV( 6 ),		//	13 RG6		SCK2/PMA5/CN8/RG6		LD4
	_BV( 2 ),		//	14 RB2		C2IN-/AN2/SS1/CN4/RB2
	_BV( 4 ),		//	15 RB4		C1IN-/AN4/CN6/RB4
	_BV( 8 ),		//	16 RB8		U2CTS/C1OUT/AN8/RB8
	_BV( 10 ),		//	17 RB10		TMS/CVREFOUT/PMA13/AN10/RB10
	_BV( 12 ),		//	18 RB12		TCK/PMA11/AN12/RB12
	_BV( 14 ),		//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14
	_BV( 3 ),		//	20 RB3		C2IN+/AN3/CN5/RB3
	_BV( 5 ),		//	21 RB5		C1IN+/AN5/CN7/RB5
	_BV( 9 ),		//	22 RB9		PMA7/C2OUT/AN9/RB9
	_BV( 11 ),		//	23 RB11		TDO/PMA12/AN11/RB11
	_BV( 13 ),		//	24 RB13		TDI/PMA10/AN13/RB13
	_BV( 15 ),		//	25 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15
	_BV( 0 ),		//	26 RE0		PMD0/RE0
	_BV( 1 ),		//	27 RE1		PMD1/RE1
	_BV( 2 ),		//	28 RE2		PMD2/RE2
	_BV( 3 ),		//	29 RE3		PMD3/RE3
	_BV( 4 ),		//	30 RE4		PMD4/RE4
	_BV( 5 ),		//	31 RE5		PMD5/RE5
	_BV( 6 ),		//	32 RE6		PMD6/RE6
	_BV( 7 ),		//	33 RE7		PMD7/RE7
	_BV( 5 ),		//	34 RD5		PMRD/CN14/RD5
	_BV( 11 ),		//	35 RD11		IC4/PMCS1/PMA14/INT4/RD11
	_BV( 6 ),		//	36 RD6		CN15/RD6
	_BV( 7 ),		//	37 RD7		CN16/RD7
	_BV( 6 ),		//	38 RF6		U1RTS/BCLK1/SCK1/INT0/RF6
	_BV( 4 ),		//	39 RF4		PMA9/U2RX/SDA2/CN17/RF4
	_BV( 5 ),		//	40 RF5		PMA8/U2TX/SCL2/CN18/RF5
	_BV( 1 ),		//	41 RB1		PGC1/AN1/VREF-/CVREF-/CN3/RB1
	_BV( 0 ),		//	42 RB0		PGED1/PMA6/AN0/VREF+/CVREF+/CN2/RB0

	_BV( 0 ),		//	43 RF0		RF0						LD5
	_BV( 9 ),		//	44 RG9		SS2/PMA2/CN11/RG9
	_BV( 3 ),		//	45 RG3		SDA1/RG3
	_BV( 2 ),		//	46 RG2		SCL1/RG2

};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t digital_pin_to_timer_PGM[] =
{
	NOT_ON_TIMER,			//	0 RF2		U1RX/SDI1/RF2
	NOT_ON_TIMER,			//	1 RF3		U1TX/SDO1/RF3
	_TIMER_IC1,				//	2 RD8		IC1/RTCC/INT1/RD8
	_TIMER_OC1,				//	3 RD0		OC1/RD0
	NOT_ON_TIMER,			//	4 RF1		RF1
	_TIMER_OC2,				//	5 RD1		OC2/RD1
	_TIMER_OC3,				//	6 RD2		OC3/RD2
	_TIMER_IC2,				//	7 RD9		IC2/U1CTS/INT2/RD9
	_TIMER_IC3,				//	8 RD10		IC3/PMCS2/PMA15/INT3/RD10
	_TIMER_OC4,				//	9 RD3		OC4/RD3
	_TIMER_OC5|_TIMER_IC5,	//	10 RD4		PMWR/OC5/IC5/CN13/RD4
	NOT_ON_TIMER,			//	11 RG8		(SDO2/PMA3/CN10/RG8) or (SDI2/PMA5/CN8/RG7)
	NOT_ON_TIMER,			//	12 RG7		(SDI2/PMA5/CN8/RG7) or (SDO2/PMA3/CN10/RG8)
	NOT_ON_TIMER,			//	13 RG6		SCK2/PMA5/CN8/RG6
	NOT_ON_TIMER,			//	14 RB2		C2IN-/AN2/SS1/CN4/RB2
	NOT_ON_TIMER,			//	15 RB4		C1IN-/AN4/CN6/RB4
	NOT_ON_TIMER,			//	16 RB8		U2CTS/C1OUT/AN8/RB8
	NOT_ON_TIMER,			//	17 RB10		TMS/CVREFOUT/PMA13/AN10/RB10
	NOT_ON_TIMER,			//	18 RB12		TCK/PMA11/AN12/RB12
	NOT_ON_TIMER,			//	19 RB14		PMALH/PMA1/U2RTS/AN14/RB14

	NOT_ON_TIMER,			//	20 RB3		C2IN+/AN3/CN5/RB3
	NOT_ON_TIMER,			//	21 RB5		C1IN+/AN5/CN7/RB5
	NOT_ON_TIMER,			//	22 RB9		PMA7/C2OUT/AN9/RB9
	NOT_ON_TIMER,			//	23 RB11		TDO/PMA12/AN11/RB11
	NOT_ON_TIMER,			//	24 RB13		TDI/PMA10/AN13/RB13
	NOT_ON_TIMER,			//	25 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15

	NOT_ON_TIMER,			//	26 RE0		PMD0/RE0
	NOT_ON_TIMER,			//	27 RE1		PMD1/RE1
	NOT_ON_TIMER,			//	28 RE2		PMD2/RE2
	NOT_ON_TIMER,			//	29 RE3		PMD3/RE3
	NOT_ON_TIMER,			//	30 RE4		PMD4/RE4
	NOT_ON_TIMER,			//	31 RE5		PMD5/RE5
	NOT_ON_TIMER,			//	32 RE6		PMD6/RE6
	NOT_ON_TIMER,			//	33 RE7		PMD7/RE7
	NOT_ON_TIMER,			//	34 RD5		PMRD/CN14/RD5
	_TIMER_IC4,				//	35 RD11		IC4/PMCS1/PMA14/INT4/RD11
	NOT_ON_TIMER,			//	36 RD6		CN15/RD6
	NOT_ON_TIMER,			//	37 RD7		CN16/RD7
	NOT_ON_TIMER,			//	38 RF6		U1RTS/BCLK1/SCK1/INT0/RF6
	NOT_ON_TIMER,			//	39 RF4		PMA9/U2RX/SDA2/CN17/RF4
	NOT_ON_TIMER,			//	40 RF5		PMA8/U2TX/SCL2/CN18/RF5
	NOT_ON_TIMER,			//	41 RB1		PGC1/EMUC1/AN1/VREF-/CVREF-/CN3/RB1
	NOT_ON_TIMER,			//	42 RB0		PGD1/EMUD1/PMA6/AN0/VREF+/CVREF+/CN2/RB0

	NOT_ON_TIMER,			//	43 RF0		RF0
	NOT_ON_TIMER,			//	44 RG9		SS2/PMA2/CN11/RG9
	NOT_ON_TIMER,			//	45 RG3		SDA1/RG3
	NOT_ON_TIMER,			//	46 RG2		SCL1/RG2

};

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
*/
const uint8_t analog_pin_to_channel_PGM[] =
{
			//*	chipKIT Pin		PIC32 Analog channel
	2,		//*	A0						AN2
	4,		//*	A1						AN4
	8,		//*	A2						AN8
	10,		//*	A3						AN10
	12,		//*	A4						AN12
	14,		//*	A5						AN14
	3,		//*	A6						AN3
	5,		//*	A7						AN5
	9,		//*	A8						AN9
	11,		//*	A9						AN11
	13,		//*	A10						AN13
	15,		//*	A11						AN15

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
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

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
