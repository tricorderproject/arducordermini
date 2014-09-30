/************************************************************************/
/*																		*/
/*	Board_Data.c --	Board Customization Data for Digilent Cerebot MX4cK	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent Cerebot		*/
/* MX4cK board.															*/
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
	_IOPORT_PE,		//  0 RE0 		PMD0
	_IOPORT_PE,		//  1 RE1		PMD1
	_IOPORT_PE,		//  2 RE2		PMD2
	_IOPORT_PE,		//  3 RE3		PMD3
	_IOPORT_PE,		//  4 RE4		PMD4
	_IOPORT_PE,		//  5 RE5		PMD5
	_IOPORT_PE,		//  6 RE6		PMD6
	_IOPORT_PE,		//  7 RE7		PMD7

    // Connector JB
	_IOPORT_PG,		//  8 RG9		PMA2/SS2/CN11/RG9
	_IOPORT_PG,		//  9 RG8		PMA3/SDO2/CN10/RG8
	_IOPORT_PG,		// 10 RG7		PMA4/SDI2/CN9/RG7
	_IOPORT_PG,		// 11 RG6		PMA5/SCK2/CN8/RG6
	_IOPORT_PB,		// 12 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15 or SCL1/INT3/RA14 (Selected with JP3)
	_IOPORT_PD,		// 13 RD5		PMRD/CN14/RD5
	_IOPORT_PD,		// 14 RD4		PMWR/OC5/CN13
	_IOPORT_PB,		// 15 RB14		PMALH/PMA1/AN14/RB14

    // Connector JC
	_IOPORT_PG,		// 16 RG12		TRD1/RG12				(S1)
	_IOPORT_PG,		// 17 RG13		TRD0/RG13				(S2)
	_IOPORT_PG,		// 18 RG14		TRD2/RG14				(S3)
	_IOPORT_PG,		// 19 RG15		RG15					(S4)
	_IOPORT_PG,		// 20 RG0		PMD8/RG0				(S5)
	_IOPORT_PG,		// 21 RG1		PMD9/RG1				(S6)
	_IOPORT_PF,		// 22 RF0		PMD11/RF0				(S7)
	_IOPORT_PF,		// 23 RF1		PMD10/RF1				(S8)

    // Connector JD
	_IOPORT_PD,		// 24 RD7		PMD15/CN16/RD7
	_IOPORT_PD,		// 25 RD1		OC2/RD1
	_IOPORT_PD,		// 26 RD9		TC2/SS1/RD9
	_IOPORT_PC,		// 27 RC1		T2CK/RC1
	_IOPORT_PD,		// 28 RD6		PMD14/CN15/RD6
	_IOPORT_PD,		// 29 RD2		OC3/RD2
	_IOPORT_PD,		// 30 RD10		IC3/SCK1/PMCS2/PMA15/RD10
	_IOPORT_PC,		// 31 RC2		T3CK/RC2

    // Connector JE
	_IOPORT_PD,		// 32 RD14		CN20/U1CTS/RD14
	_IOPORT_PF,		// 33 RF8		U1TX/RF8
	_IOPORT_PF,		// 34 RF2		U1RX/RF2
	_IOPORT_PD,		// 35 RD15		U1RTS/BCLK1/CN21/RD15
	_IOPORT_PE,		// 36 RE9		INT2/RE9
	_IOPORT_PD,		// 37 RD3		OC4/RD3
	_IOPORT_PD,		// 38 RD11		IC4/PMCS1/PMA14/RD11
	_IOPORT_PC,		// 39 RC3		T4CK/RC3    
    
    // Connector JF
	_IOPORT_PA,		// 40 RA14		SCL1/INT3/RA14
	_IOPORT_PA,		// 41 RA15		SDA1/INT4/RA15
	_IOPORT_PA,		// 42 RA6		TRCLK/RA6				(BTN1)
	_IOPORT_PA,		// 43 RA7		TRD3/RA7				(BTN2)
	_IOPORT_PA,		// 44 RA0		TMS/RA0
	_IOPORT_PA,		// 45 RA1		TCK/RA1
	_IOPORT_PA,		// 46 RA4		TDI/RA4
	_IOPORT_PA,		// 47 RA5		TDO/RA5

    // Connector JH
	_IOPORT_PF,		// 48 RF12		U2CTS/RF12
	_IOPORT_PF,		// 49 RF5		PMA8/U2TX/CN18/RF5
	_IOPORT_PF,		// 50 RF4		PMA9/U2RX/CN17/RF4
	_IOPORT_PF,		// 51 RF13		U2RTS/BCLK2/RF13
	_IOPORT_PE,		// 52 RE8		INT1/RE8
	_IOPORT_PD,		// 53 RD0		SDO1/OC1/INT0/RD0
	_IOPORT_PD,		// 54 RD8		IC1/RTCC/RD8
	_IOPORT_PD,		// 55 RD13		PMD13/CN19/RD13
    
    // Connector JJ
	_IOPORT_PB,		// 56 RB0		PGD1/FMUD1/AN0/CN2/RB0
	_IOPORT_PB,		// 57 RB1		PGC1/FMUC1/AN1/CN3/RB1
	_IOPORT_PB,		// 58 RB2		C2IN-/AN2/CN4/RB2
	_IOPORT_PB,		// 59 RB3		C2IN+/AN3/CN5/RB3
	_IOPORT_PB,		// 60 RB4		C1IN-/AN4/CN6/RB4
	_IOPORT_PB,		// 61 RB5		C1IN+/AN5/CN7/RB5
	_IOPORT_PB,		// 62 RB8		C1OUT/AN8/RB8
	_IOPORT_PB,		// 63 RB9		C2OUT/AN9/RB9

    // Connector JK
	_IOPORT_PB,		// 64 RB10		CVREFOUT/PMA13/AN10/RB10	(LD1)
	_IOPORT_PB,		// 65 RB11		PMA12/AN11/RB11				(LD2)
	_IOPORT_PB,		// 66 RB12		PMA11/AN12/RB12				(LD3)
	_IOPORT_PB,		// 67 RB13		PMA10/AN13/RB13				(LD4)
	_IOPORT_PA,		// 68 RA9		PMA7/VREF-/CVREF-/RA9
	_IOPORT_PA,		// 69 RA10		PMA6/VREF+/CVREF+/RA10
	_IOPORT_PD,		// 70 RD12		PMD12/IC5/RD12
	_IOPORT_PC,		// 71 RC4		SDI1/T5CK/RC4
	
	//J6 /I2C PORT 2
	_IOPORT_PA,		// 72 RA2		SCL2/RA2
	_IOPORT_PA		// 73 RA3		SDA2/RA3
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {
    // Connector JA
	_BV( 0 ) ,	// 0 RE 0		PMD0
	_BV( 1 ) ,	// 1 RE 1		PMD1		
	_BV( 2 ) ,	// 2 RE 2		PMD2
	_BV( 3 ) ,	// 3 RE 3		PMD3
	_BV( 4 ) ,	// 4 RE 4		PMD4
	_BV( 5 ) ,	// 5 RE 5		PMD5
	_BV( 6 ) ,	// 6 RE 6		PMD6
	_BV( 7 ) ,	// 7 RE 7		PMD7

    // Connector JB
	_BV( 9 ) ,	// 8 RG9		PMA2/SS2/CN11/RG9
	_BV( 8 ) ,	// 9 RG8		PMA3/SDO2/CN10/RG8
	_BV( 7 ) ,	// 10 RG7		PMA4/SDI2/CN9/RG7
	_BV( 6 ) ,	// 11 RG6		PMA5/SCK2/CN8/RG6
	_BV( 15 ) ,	// 12 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15 or SCL1/INT3/RA14 (Selected with JP3)
	_BV( 5 ) ,	// 13 RD5		PMRD/CN14/RD5
	_BV( 4 ) ,	// 14 RD4		PMWR/OC5/CN13
	_BV( 14 ) ,	// 15 RB14		PMALH/PMA1/AN14/RB14

    // Connector JC
	_BV( 12 ) ,	// 16 RG12		TRD1/RG12
	_BV( 13 ) ,	// 17 RG13		TRD0/RG13
	_BV( 14 ) ,	// 18 RG14		TRD2/RG14
	_BV( 15 ) ,	// 19 RG15		RG15		
	_BV( 0 ) ,	// 20 RG0		PMD8/RG0
	_BV( 1 ) ,	// 21 RG1		PMD9/RG1
	_BV( 0 ) ,	// 22 RF0		PMD11/RF0
	_BV( 1 ) ,	// 23 RF1		PMD10/RF1

    // Connector JD
	_BV( 7 ) ,	// 24 RD7		PMD15/CN16/RD7
	_BV( 1 ) ,	// 25 RD1		OC2/RD1
	_BV( 9 ) ,	// 26 RD9		TC2/SS1/RD9
	_BV( 1 ) ,	// 27 RC1		T2CK/RC1
	_BV( 6 ) ,	// 28 RD6		PMD14/CN15/RD6
	_BV( 2 ) ,	// 29 RD2		OC3/RD2
	_BV( 10 ) ,	// 30 RD10		IC3/SCK1/PMCS2/PMA15/RD10
	_BV( 2 ) ,	// 31 RC2		T3CK/RC2

    // Connector JE
	_BV( 14 ) ,	// 32 RD14		CN20/U1CTS/RD14
	_BV( 8 ) ,	// 33 RF8		U1TX/RF8
	_BV( 2 ) ,	// 34 RF2		U1RX/RF2
	_BV( 15 ) ,	// 35 RD15		U1RTS/BCLK1/CN21/RD15
	_BV( 9 ) ,	// 36 RE9		INT2/RE9
	_BV( 3 ) ,	// 37 RD3		OC4/RD3
	_BV( 11 ) ,	// 38 RD11		IC4/PMCS1/PMA14/RD11
	_BV( 3 ) ,	// 39 RC3		T4CK/RC3

    // Connector JF
	_BV( 14 ) ,	// 40 RA14		SCL1/INT3/RA14
	_BV( 15 ) ,	// 41 RA15		SDA1/INT4/RA15
	_BV( 6 ) ,	// 42 RA6		TRCLK/RA6
	_BV( 7 ) ,	// 43 RA7		TRD3/RA7
	_BV( 0 ) ,	// 44 RA0		TMS/RA0
	_BV( 1 ) ,	// 45 RA1		TCK/RA1
	_BV( 4 ) ,	// 46 RA4		TDI/RA4
	_BV( 5 ) ,	// 47 RA5		TDO/RA5

    // Connector JH
	_BV( 12 ) ,	// 48 RF12		U2CTS/RF12
	_BV( 5 ) ,	// 49 RF5		PMA8/U2TX/CN18/RF5
	_BV( 4 ) ,	// 50 RF4		PMA9/U2RX/CN17/RF4
	_BV( 13 ) ,	// 51 RF13		U2RTS/BCLK2/RF13
	_BV( 8 ) ,	// 52 RE8		INT1/RE8
	_BV( 0 ) ,	// 53 RD0		SDO1/OC1/INT0/RD0
	_BV( 8 ) ,	// 54 RD8		IC1/RTCC/RD8
	_BV( 13 ) ,	// 55 RD13		PMD13/CN19/RD13

    // Connector JJ
	_BV( 0 ) ,	// 56 RB0		PGD1/FMUD1/AN0/CN2/RB0
	_BV( 1 ) ,	// 57 RB1		PGC1/FMUC1/AN1/CN3/RB1
	_BV( 2 ) ,	// 58 RB2		C2IN-/AN2/CN4/RB2
	_BV( 3 ) ,	// 59 RB3		C2IN+/AN3/CN5/RB3
	_BV( 4 ) ,	// 60 RB4		C1IN-/AN4/CN6/RB4
	_BV( 5 ) ,	// 61 RB5		C1IN+/AN5/CN7/RB5
	_BV( 8 ) ,	// 62 RB8		C1OUT/AN8/RB8
	_BV( 9 ) ,	// 63 RB9		C2OUT/AN9/RB9

    // Connector JK
	_BV( 10 ) ,	// 64 RB10		CVREFOUT/PMA13/AN10/RB10
	_BV( 11 ) ,	// 65 RB11		PMA12/AN11/RB11
	_BV( 12 ) ,	// 66 RB12		PMA11/AN12/RB12
	_BV( 13 ) ,	// 67 RB11		PMA10/AN13/RB13
	_BV( 9 ) ,	// 68 RA9		PMA7/VREF-/CVREF-/RA9
	_BV( 10 ) ,	// 69 RA10		PMA6/VREF+/CVREF+/RA10
	_BV( 12 ) ,	// 70 RD12		PMD12/IC5/RD12
	_BV( 4 ) ,	// 71 RC4		SDI1/T5CK/RC4
	
	//J6 /I2C PORT 2
	_BV( 2 ) ,	// 72 RA2		SCL2/RA2
	_BV( 3 ) 	// 73 RA3		SDA2/RA3	
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t	digital_pin_to_timer_PGM[] = {
    // Connector JA
	NOT_ON_TIMER,	// 0 RE 0		PMD0
	NOT_ON_TIMER,	// 1 RE 1		PMD1		
	NOT_ON_TIMER,	// 2 RE 2		PMD2
	NOT_ON_TIMER,	// 3 RE 3		PMD3
	NOT_ON_TIMER,	// 4 RE 4		PMD4
	NOT_ON_TIMER,	// 5 RE 5		PMD5
	NOT_ON_TIMER,	// 6 RE 6		PMD6
	NOT_ON_TIMER,	// 7 RE 7		PMD7

    // Connector JB
	NOT_ON_TIMER,	// 8 RG9		PMA2/SS2/CN11/RG9
	NOT_ON_TIMER,	// 9 RG8		PMA3/SDO2/CN10/RG8
	NOT_ON_TIMER,	// 10 RG7		PMA4/SDI2/CN9/RG7
	NOT_ON_TIMER,	// 11 RG6		PMA5/SCK2/CN8/RG6
	NOT_ON_TIMER,	// 12 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15 or SCL1/INT3/RA14 (Selected with JP3)
	NOT_ON_TIMER,	// 13 RD5		PMRD/CN14/RD5
	_TIMER_OC5,		// 14 RD4		PMWR/OC5/CN13
	NOT_ON_TIMER,	// 15 RB14		PMALH/PMA1/AN14/RB14

    // Connector JC
	NOT_ON_TIMER,	// 16 RG12		TRD1/RG12
	NOT_ON_TIMER,	// 17 RG13		TRD0/RG13
	NOT_ON_TIMER,	// 18 RG14		TRD2/RG14
	NOT_ON_TIMER,	// 19 RG15		RG15		
	NOT_ON_TIMER,	// 20 RG0		PMD8/RG0
	NOT_ON_TIMER,	// 21 RG1		PMD9/RG1
	NOT_ON_TIMER,	// 22 RF0		PMD11/RF0
	NOT_ON_TIMER,	// 23 RF1		PMD10/RF1

    // Connector JD
	NOT_ON_TIMER,	// 24 RD7		PMD15/CN16/RD7
	_TIMER_OC2,		// 25 RD1		OC2/RD1
	_TIMER_IC2,		// 26 RD9		IC2/SS1/RD9
	_TIMER_TCK2,	// 27 RC1		T2CK/RC1
	NOT_ON_TIMER,	// 28 RD6		PMD14/CN15/RD6
	_TIMER_OC3,		// 29 RD2		OC3/RD2
	_TIMER_IC3,		// 30 RD10		IC3/SCK1/PMCS2/PMA15/RD10
	_TIMER_TCK3,	// 31 RC2		T3CK/RC2

    // Connector JE
	NOT_ON_TIMER,	// 32 RD14		CN20/U1CTS/RD14
	NOT_ON_TIMER,	// 33 RF8		U1TX/RF8
	NOT_ON_TIMER,	// 34 RF2		U1RX/RF2
	NOT_ON_TIMER,	// 35 RD15		U1RTS/BCLK1/CN21/RD15
	NOT_ON_TIMER,	// 36 RE9		INT2/RE9
	_TIMER_OC4,		// 37 RD3		OC4/RD3
	_TIMER_IC4,		// 38 RD11		IC4/PMCS1/PMA14/RD11
	_TIMER_TCK4,	// 39 RC3		T4CK/RC3

    // Connector JF
	NOT_ON_TIMER,	// 40 RD14		SCL1/INT3/RA14
	NOT_ON_TIMER,	// 41 RA15		SDA1/INT4/RA15
	NOT_ON_TIMER,	// 42 RA6		TRCLK/RA6
	NOT_ON_TIMER,	// 43 RA7		TRD3/RA7
	NOT_ON_TIMER,	// 44 RA0		TMS/RA0
	NOT_ON_TIMER,	// 45 RA1		TCK/RA1
	NOT_ON_TIMER,	// 46 RA4		TDI/RA4
	NOT_ON_TIMER,	// 47 RA5		TDO/RA5

    // Connector JH
	NOT_ON_TIMER,	// 48 RF12		U2CTS/RF12
	NOT_ON_TIMER,	// 49 RF5		PMA8/U2TX/CN18/RF5
	NOT_ON_TIMER,	// 50 RF4		PMA9/U2RX/CN17/RF4
	NOT_ON_TIMER,	// 51 RF13		U2RTS/BCLK2/RF13
	NOT_ON_TIMER,	// 52 RE8		INT1/RE8
	_TIMER_OC1,		// 53 RD0		SDO1/OC1/INT0/RD0
	_TIMER_IC1,		// 54 RD8		IC1/RTCC/RD8
	NOT_ON_TIMER,	// 55 RD13		PMD13/CN19/RD13

    // Connector JJ
	NOT_ON_TIMER,	// 56 RB0		PGD1/FMUD1/AN0/CN2/RB0
	NOT_ON_TIMER,	// 57 RB1		PGC1/FMUC1/AN1/CN3/RB1
	NOT_ON_TIMER,	// 58 RB2		C2IN-/AN2/CN4/RB2
	NOT_ON_TIMER,	// 59 RB3		C2IN+/AN3/CN5/RB3
	NOT_ON_TIMER,	// 60 RB4		C1IN-/AN4/CN6/RB4
	NOT_ON_TIMER,	// 61 RB5		C1IN+/AN5/CN7/RB5
	NOT_ON_TIMER,	// 62 RB8		C1OUT/AN8/RB8
	NOT_ON_TIMER,	// 63 RB9		C2OUT/AN9/RB9

    // Connector JK
	NOT_ON_TIMER,	// 64 RB10		CVREFOUT/PMA13/AN10/RB10
	NOT_ON_TIMER,	// 65 RB11		PMA12/AN11/RB11
	NOT_ON_TIMER,	// 66 RB12		PMA11/AN12/RB12
	NOT_ON_TIMER,	// 67 RB13		PMA10/AN13/RB13
	NOT_ON_TIMER,	// 68 RA9		PMA7/VREF-/CVREF-/RA9
	NOT_ON_TIMER,	// 69 RA10		PMA6/VREF+/CVREF+/RA10
	_TIMER_IC5,		// 70 RD12		PMD12/IC5/RD12
	_TIMER_TCK5,	// 71 RC4		SDI1/T5CK/RC4	
	
	//J6 /I2C PORT 2
	NOT_ON_TIMER,	// 72 RA2		SCL2/RA2
	NOT_ON_TIMER	// 73 RA3		SDA2/RA3
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
const uint8_t digital_pin_to_analog_PGM[] = {
    // Connector JA
	NOT_ANALOG_PIN,	// 0 RE 0		PMD0
	NOT_ANALOG_PIN,	// 1 RE 1		PMD1		
	NOT_ANALOG_PIN,	// 2 RE 2		PMD2
	NOT_ANALOG_PIN,	// 3 RE 3		PMD3
	NOT_ANALOG_PIN,	// 4 RE 4		PMD4
	NOT_ANALOG_PIN,	// 5 RE 5		PMD5
	NOT_ANALOG_PIN,	// 6 RE 6		PMD6
	NOT_ANALOG_PIN,	// 7 RE 7		PMD7

    // Connector JB
	NOT_ANALOG_PIN,	// 8 RG9		PMA2/SS2/CN11/RG9
	NOT_ANALOG_PIN,	// 9 RG8		PMA3/SDO2/CN10/RG8
	NOT_ANALOG_PIN,	// 10 RG7		PMA4/SDI2/CN9/RG7
	NOT_ANALOG_PIN,	// 11 RG6		PMA5/SCK2/CN8/RG6
	_BOARD_AN12,	// 12 RB15		PMALL/PMA0/AN15/OCFB/CN12/RB15
	NOT_ANALOG_PIN,	// 13 RD5		PMRD/CN14/RD5
	NOT_ANALOG_PIN,	// 14 RD4		PMWR/OC5/CN13
	_BOARD_AN13,	// 15 RB14		PMALH/PMA1/AN14/RB14

    // Connector JC
	NOT_ANALOG_PIN,	// 16 RG12		TRD1/RG12
	NOT_ANALOG_PIN,	// 17 RG13		TRD0/RG13
	NOT_ANALOG_PIN,	// 18 RG14		TRD2/RG14
	NOT_ANALOG_PIN,	// 19 RG15		RG15		
	NOT_ANALOG_PIN,	// 20 RG0		PMD8/RG0
	NOT_ANALOG_PIN,	// 21 RG1		PMD9/RG1
	NOT_ANALOG_PIN,	// 22 RF0		PMD11/RF0
	NOT_ANALOG_PIN,	// 23 RF1		PMD10/RF1

    // Connector JD
	NOT_ANALOG_PIN,	// 24 RD7		PMD15/CN16/RD7
	NOT_ANALOG_PIN,	// 25 RD1		OC2/RD1
	NOT_ANALOG_PIN,	// 26 RD9		TC2/SS1/RD9
	NOT_ANALOG_PIN,	// 27 RC1		T2CK/RC1
	NOT_ANALOG_PIN,	// 28 RD6		PMD14/CN15/RD6
	NOT_ANALOG_PIN,	// 29 RD2		OC3/RD2
	NOT_ANALOG_PIN,	// 30 RD10		IC3/SCK1/PMCS2/PMA15/RD10
	NOT_ANALOG_PIN,	// 31 RC2		T3CK/RC2

    // Connector JE
	NOT_ANALOG_PIN,	// 32 RD14		CN20/U1CTS/RD14
	NOT_ANALOG_PIN,	// 33 RF8		U1TX/RF8
	NOT_ANALOG_PIN,	// 34 RF2		U1RX/RF2
	NOT_ANALOG_PIN,	// 35 RD15		U1RTS/BCLK1/CN21/RD15
	NOT_ANALOG_PIN,	// 36 RE9		INT2/RE9
	NOT_ANALOG_PIN,	// 37 RD3		OC4/RD3
	NOT_ANALOG_PIN,	// 38 RD11		IC4/PMCS1/PMA14/RD11
	NOT_ANALOG_PIN,	// 39 RC3		T4CK/RC3

    // Connector JF
	NOT_ANALOG_PIN,	// 40 RD14		SCL1/INT3/RA14
	NOT_ANALOG_PIN,	// 41 RA15		SDA1/INT4/RA15
	NOT_ANALOG_PIN,	// 42 RA6		TRCLK/RA6
	NOT_ANALOG_PIN,	// 43 RA7		TRD3/RA7
	NOT_ANALOG_PIN,	// 44 RA0		TMS/RA0
	NOT_ANALOG_PIN,	// 45 RA1		TCK/RA1
	NOT_ANALOG_PIN,	// 46 RA4		TDI/RA4
	NOT_ANALOG_PIN,	// 47 RA5		TDO/RA5

    // Connector JH
	NOT_ANALOG_PIN,	// 48 RF12		U2CTS/RF12
	NOT_ANALOG_PIN,	// 49 RF5		PMA8/U2TX/CN18/RF5
	NOT_ANALOG_PIN,	// 50 RF4		PMA9/U2RX/CN17/RF4
	NOT_ANALOG_PIN,	// 51 RF13		U2RTS/BCLK2/RF13
	NOT_ANALOG_PIN,	// 52 RE8		INT1/RE8
	NOT_ANALOG_PIN,	// 53 RD0		SDO1/OC1/INT0/RD0
	NOT_ANALOG_PIN,	// 54 RD8		IC1/RTCC/RD8
	NOT_ANALOG_PIN,	// 55 RD13		PMD13/CN19/RD13

    // Connector JJ
	_BOARD_AN0,		// 56 RB0		PGD1/FMUD1/AN0/CN2/RB0
	_BOARD_AN1,		// 57 RB1		PGC1/FMUC1/AN1/CN3/RB1
	_BOARD_AN2,		// 58 RB2		C2IN-/AN2/CN4/RB2
	_BOARD_AN3,		// 59 RB3		C2IN+/AN3/CN5/RB3
	_BOARD_AN4,		// 60 RB4		C1IN-/AN4/CN6/RB4
	_BOARD_AN5,		// 61 RB5		C1IN+/AN5/CN7/RB5
	_BOARD_AN6,		// 62 RB8		C1OUT/AN8/RB8
	_BOARD_AN7,		// 63 RB9		C2OUT/AN9/RB9

    // Connector JK
	_BOARD_AN8,		// 64 RB10		CVREFOUT/PMA13/AN10/RB10
	_BOARD_AN9,		// 65 RB11		PMA12/AN11/RB11
	_BOARD_AN10,	// 66 RB12		PMA11/AN12/RB12
	_BOARD_AN11,	// 67 RB13		PMA10/AN13/RB13
	NOT_ANALOG_PIN,	// 68 RA9		PMA7/VREF-/CVREF-/RA9
	NOT_ANALOG_PIN,	// 69 RA10		PMA6/VREF+/CVREF+/RA10
	NOT_ANALOG_PIN,	// 70 RD12		PMD12/IC5/RD12
	NOT_ANALOG_PIN,	// 71 RC4		SDI1/T5CK/RC4	
	
	//J6 /I2C PORT 2
	NOT_ANALOG_PIN,	// 72 RA2		SCL2/RA2
	NOT_ANALOG_PIN	// 73 RA3		SDA2/RA3
};

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
*/
const uint8_t analog_pin_to_channel_PGM[] =
{
			//*	chipKIT Pin		PIC32 Analog channel
	0,		//*	A0						AN0
	1,		//*	A1						AN1
	2,		//*	A2						AN2
	3,		//*	A3						AN3
	4,		//*	A4						AN4
	5,		//*	A5						AN5
	8,		//*	A6						AN8
	9,		//*	A7						AN9
	10,		//*	A8						AN10
	11,		//*	A9						AN11
	12,		//*	A10						AN12
	13,		//*	A11						AN13
	15,		//* A12						AN15
	14		//* A13						AN14
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
