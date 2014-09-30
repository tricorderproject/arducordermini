/************************************************************************/
/*																		*/
/*	Board_Data.c --	Board Customization Data for Digilent Cerebot MX7cK	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent Cerebot		*/
/* MX7cK board.															*/
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
** containing that pin.
*/
const uint8_t	digital_pin_to_port_PGM[] = {
    // Connector JA
	_IOPORT_PB,		//  0 RB2 		AN2/C2IN-/CN4/RB2
	_IOPORT_PB,		//  1 RB3		AN3/C2IN+/CN5/RB3
	_IOPORT_PB,		//  2 RB4		AN4/C1IN-/CN6/RB4
	_IOPORT_PB,		//  3 RB6		AN6/PGEC2/OCFA/RB6
	_IOPORT_PB,		//  4 RB7		AN7/PGED2/RB7
	_IOPORT_PB,		//  5 RB8		AN8/C1OUT/RB8
	_IOPORT_PB,		//  6 RB9		AN9/C2OUT/RB9
	_IOPORT_PB,		//  7 RB10		AN10/PMA13/RB10

    // Connector JB
	_IOPORT_PE,		//  8 RE0		PMD0/RE0
	_IOPORT_PE,		//  9 RE1		PMD1/RE1
	_IOPORT_PE,		// 10 RE2		PMD2/RE2
	_IOPORT_PE,		// 11 RE3		PMD3/RE3
	_IOPORT_PE,		// 12 RE4		PMD4/RE4
	_IOPORT_PE,		// 13 RE5		PMD5/RE5
	_IOPORT_PE,		// 14 RE6		PMD6/RE6
	_IOPORT_PE,		// 15 RE7		PMD7/RE7
	
    // Connector JC
	_IOPORT_PC,		// 16 RC1		T2CK/RC1
	_IOPORT_PG,		// 17 RG0		PMD8/RG0
	_IOPORT_PG,		// 18 RG1		PMD9/RG1
	_IOPORT_PD,		// 19 RD7		PMD15/CN16/RD7
	_IOPORT_PB,		// 20 RB15		AN15/PMA0/CN12
	_IOPORT_PD,		// 21 RD5		PMRD/CN14/RD5
	_IOPORT_PD,		// 22 RD4		PMWR/OC5/CN13/RD4
	_IOPORT_PB,		// 23 RB14		AN14/PMA1/RB14

    // Connector JD
	_IOPORT_PD,		// 24 RD9		SS1/IC2/RD9
	_IOPORT_PD,		// 25 RD0		SDO1/OC1/INT0/RD0
	_IOPORT_PC,		// 26 RC4		T5CK/SDI1/RC4
	_IOPORT_PD,		// 27 RD10		SCK1/IC3/RD10
	_IOPORT_PD,		// 28 RD1		OC2/RD1
	_IOPORT_PD,		// 29 RD2		OC3/RD2
	_IOPORT_PD,		// 30 RD3		OC4/RD3
	_IOPORT_PD,		// 31 RD12		IC5/PMD12/RD12

    // Connector JE
	_IOPORT_PD,		// 32 RD14		SS1A/U1ACTS/CN20/RD14
	_IOPORT_PF,		// 33 RF8		SCL1A/SDO1A/U1ATX/RF8
	_IOPORT_PF,		// 34 RF2		SDA1A/SDI1A/U1ARX/RF2
	_IOPORT_PD,		// 35 RD15		SCK1A/U1ARTS/CN21/RD15
	_IOPORT_PE,		// 36 RE8		INT1/RE8
	_IOPORT_PA,		// 37 RA7		TRD3/RA7
	_IOPORT_PA,		// 38 RA9		VREF-/CVREF-/PMA7/RA9
	_IOPORT_PA,		// 39 RA10		VREF+/CVREF+/PMA6/RA10    
    
    // Connector JF
	_IOPORT_PF,		// 40 RF12		SS3A/U3ACTS/RF12
	_IOPORT_PF,		// 41 RF5		SDO3A/U3ATX/CN18/RF5
	_IOPORT_PF,		// 42 RF4		SDI3A/U3ARX/CN17/RF4
	_IOPORT_PF,		// 43 RF13		SCK3A/U3ARTS/RF13
	_IOPORT_PE,		// 44 RE9		INT2/RE9
	_IOPORT_PA,		// 45 RA1		TCK/RA1
	_IOPORT_PA,		// 46 RA4		TDI/RA4
	_IOPORT_PA,		// 47 RA5		TDO/RA5	
	
	//BUTTONS
	_IOPORT_PG,		// 48 BTN1		ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	_IOPORT_PG,		// 49 BTN2		ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	_IOPORT_PA,		// 50 BTN3		TMS/RA0	
	
	//LEDS
	_IOPORT_PG,		// 51 LD1		TRD1/RG12
	_IOPORT_PG,		// 52 LD2		TRD0/RG13
	_IOPORT_PG,		// 53 LD3		TRD2/RG14
	_IOPORT_PG,		// 54 LD4		AERXERR/RG15
	
	//J8 I2C PORT 2 
	_IOPORT_PA,		// 55 RA2		SCL2/RA2
	_IOPORT_PA,		// 56 RA3		SDA2/RA3	
	
	//J7 I2C PORT 1
	_IOPORT_PA,		// 57 RA14		SCL1/INT3/RA14
	_IOPORT_PA,		// 58 RA15		SDA1/INT4/RA15	
	
	//MISC
	_IOPORT_PB,		// 59 RB5		AN5/C1IN+/VBUSON/CN7/RB5 (P32_VBUSON)
	_IOPORT_PD		// 60 RD13		ETXD3/PMD13/CN19/RD13 (P32_USBOC)
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {
   // Connector JA
	_BV( 2 ) ,	//  0 RB2 		AN2/C2IN-/CN4/RB2
	_BV( 3 ) ,	//  1 RB3		AN3/C2IN+/CN5/RB3
	_BV( 4 ) ,	//  2 RB4		AN4/C1IN-/CN6/RB4
	_BV( 6 ) ,	//  3 RB6		AN6/PGEC2/OCFA/RB6
	_BV( 7 ) ,	//  4 RB7		AN7/PGED2/RB7
	_BV( 8 ) ,	//  5 RB8		AN8/C1OUT/RB8
	_BV( 9 ) ,	//  6 RB9		AN9/C2OUT/RB9
	_BV( 10 ) ,	//  7 RB10		AN10/PMA13/RB10

    // Connector JB
	_BV( 0 ) ,	//  8 RE0		PMD0/RE0
	_BV( 1 ) ,	//  9 RE1		PMD1/RE1
	_BV( 2 ) ,	// 10 RE2		PMD2/RE2
	_BV( 3 ) ,	// 11 RE3		PMD3/RE3
	_BV( 4 ) ,	// 12 RE4		PMD4/RE4
	_BV( 5 ) ,	// 13 RE5		PMD5/RE5
	_BV( 6 ) ,	// 14 RE6		PMD6/RE6
	_BV( 7 ) ,	// 15 RE7		PMD7/RE7
	
    // Connector JC
	_BV( 1 ) ,	// 16 RC1		T2CK/RC1
	_BV( 0 ) ,	// 17 RG0		PMD8/RG0
	_BV( 1 ) ,	// 18 RG1		PMD9/RG1
	_BV( 7 ) ,	// 19 RD7		PMD15/CN16/RD7
	_BV( 15 ) ,	// 20 RB15		AN15/PMA0/CN12
	_BV( 5 ) ,	// 21 RD5		PMRD/CN14/RD5
	_BV( 4 ) ,	// 22 RD4		PMWR/OC5/CN13/RD4
	_BV( 14 ) ,	// 23 RB14		AN14/PMA1/RB14

    // Connector JD
	_BV( 9 ) ,	// 24 RD9		SS1/IC2/RD9
	_BV( 0 ) ,	// 25 RD0		SDO1/OC1/INT0/RD0
	_BV( 4 ) ,	// 26 RC4		T5CK/SDI1/RC4
	_BV( 10 ) ,	// 27 RD10		SCK1/IC3/RD10
	_BV( 1 ) ,	// 28 RD1		OC2/RD1
	_BV( 2 ) ,	// 29 RD2		OC3/RD2
	_BV( 3 ) ,	// 30 RD3		OC4/RD3
	_BV( 12 ) ,	// 31 RD12		IC5/PMD12/RD12

    // Connector JE
	_BV( 14 ) ,	// 32 RD14		SS1A/U1ACTS/CN20/RD14
	_BV( 8 ) ,	// 33 RF8		SCL1A/SDO1A/U1ATX/RF8
	_BV( 2 ) ,	// 34 RF2		SDA1A/SDI1A/U1ARX/RF2
	_BV( 15 ) ,	// 35 RD15		SCK1A/U1ARTS/CN21/RD15
	_BV( 8 ) ,	// 36 RE8		INT1/RE8
	_BV( 7 ) ,	// 37 RA7		TRD3/RA7
	_BV( 9 ) ,	// 38 RA9		VREF-/CVREF-/PMA7/RA9
	_BV( 10 ) ,	// 39 RA10		VREF+/CVREF+/PMA6/RA10    
    
    // Connector JF
	_BV( 12 ) ,	// 40 RF12		SS3A/U3ACTS/RF12
	_BV( 5 ) ,	// 41 RF5		SDO3A/U3ATX/CN18/RF5
	_BV( 4 ) ,	// 42 RF4		SDI3A/U3ARX/CN17/RF4
	_BV( 13 ) ,	// 43 RF13		SCK3A/U3ARTS/RF13
	_BV( 9 ) ,	// 44 RE9		INT2/RE9
	_BV( 1 ) ,	// 45 RA1		TCK/RA1
	_BV( 4 ) ,	// 46 RA4		TDI/RA4
	_BV( 5 ) ,	// 47 RA5		TDO/RA5	
	
	//BUTTONS
	_BV( 6 ) ,	// 48 BTN1		ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	_BV( 7 ) ,	// 49 BTN2		ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	_BV( 0 ) ,	// 50 BTN3		TMS/RA0	
	
	//LEDS
	_BV( 12 ) ,	// 51 LD1		TRD1/RG12
	_BV( 13 ) ,	// 52 LD2		TRD0/RG13
	_BV( 14 ) ,	// 53 LD3		TRD2/RG14
	_BV( 15 ) ,	// 54 LD4		AERXERR/RG15
	
	//J8 /I2C PORT 2 
	_BV( 2 ) ,	// 55 SCL2		SCL2/RA2
	_BV( 3 ) ,	// 56 SDA2		SDA2/RA3	
	
	//J7 /I2C PORT 1
	_BV( 14 ) ,	// 57 SCL1		SCL1/INT3/RA14
	_BV( 15 ) ,	// 58 SDA1		SDA1/INT4/RA15	
	
	//MISC
	_BV( 5 ) ,	// 59 RB5		AN5/C1IN+/VBUSON/CN7/RB5 (P32_VBUSON)
	_BV( 13 ) 	// 60 RD13		ETXD3/PMD13/CN19/RD13 (P32_USBOC)
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t	digital_pin_to_timer_PGM[] = {
    // Connector JA
	NOT_ON_TIMER,		//  0 RB2 		AN2/C2IN-/CN4/RB2
	NOT_ON_TIMER,		//  1 RB3		AN3/C2IN+/CN5/RB3
	NOT_ON_TIMER,		//  2 RB4		AN4/C1IN-/CN6/RB4
	NOT_ON_TIMER,		//  3 RB6		AN6/PGEC2/OCFA/RB6
	NOT_ON_TIMER,		//  4 RB7		AN7/PGED2/RB7
	NOT_ON_TIMER,		//  5 RB8		AN8/C1OUT/RB8
	NOT_ON_TIMER,		//  6 RB9		AN9/C2OUT/RB9
	NOT_ON_TIMER,		//  7 RB10		AN10/PMA13/RB10

    // Connector JB
	NOT_ON_TIMER,		//  8 RE0		PMD0/RE0
	NOT_ON_TIMER,		//  9 RE1		PMD1/RE1
	NOT_ON_TIMER,		// 10 RE2		PMD2/RE2
	NOT_ON_TIMER,		// 11 RE3		PMD3/RE3
	NOT_ON_TIMER,		// 12 RE4		PMD4/RE4
	NOT_ON_TIMER,		// 13 RE5		PMD5/RE5
	NOT_ON_TIMER,		// 14 RE6		PMD6/RE6
	NOT_ON_TIMER,		// 15 RE7		PMD7/RE7
	
    // Connector JC
	_TIMER_TCK2,		// 16 RC1		T2CK/RC1
	NOT_ON_TIMER,		// 17 RG0		PMD8/RG0
	NOT_ON_TIMER,		// 18 RG1		PMD9/RG1
	NOT_ON_TIMER,		// 19 RD7		PMD15/CN16/RD7
	NOT_ON_TIMER,		// 20 RB15		AN15/PMA0/CN12
	NOT_ON_TIMER,		// 21 RD5		PMRD/CN14/RD5
	_TIMER_OC5,			// 22 RD4		PMWR/OC5/CN13/RD4
	NOT_ON_TIMER,		// 23 RB14		AN14/PMA1/RB14

    // Connector JD
	_TIMER_IC2,			// 24 RD9		SS1/IC2/RD9
	_TIMER_OC1,			// 25 RD0		SDO1/OC1/INT0/RD0
	_TIMER_TCK5,		// 26 RC4		T5CK/SDI1/RC4
	_TIMER_IC3,			// 27 RD10		SCK1/IC3/RD10
	_TIMER_OC2,			// 28 RD1		OC2/RD1
	_TIMER_OC3,			// 29 RD2		OC3/RD2
	_TIMER_OC4,			// 30 RD3		OC4/RD3
	_TIMER_IC5,			// 31 RD12		IC5/PMD12/RD12

    // Connector JE
	NOT_ON_TIMER,		// 32 RD14		SS1A/U1ACTS/CN20/RD14
	NOT_ON_TIMER,		// 33 RF8		SCL1A/SDO1A/U1ATX/RF8
	NOT_ON_TIMER,		// 34 RF2		SDA1A/SDI1A/U1ARX/RF2
	NOT_ON_TIMER,		// 35 RD15		SCK1A/U1ARTS/CN21/RD15
	NOT_ON_TIMER,		// 36 RE8		INT1/RE8
	NOT_ON_TIMER,		// 37 RA7		TRD3/RA7
	NOT_ON_TIMER,		// 38 RA9		VREF-/CVREF-/PMA7/RA9
	NOT_ON_TIMER,		// 39 RA10		VREF+/CVREF+/PMA6/RA10    
    
    // Connector JF
	NOT_ON_TIMER,		// 40 RF12		SS3A/U3ACTS/RF12
	NOT_ON_TIMER,		// 41 RF5		SDO3A/U3ATX/CN18/RF5
	NOT_ON_TIMER,		// 42 RF4		SDI3A/U3ARX/CN17/RF4
	NOT_ON_TIMER,		// 43 RF13		SCK3A/U3ARTS/RF13
	NOT_ON_TIMER,		// 44 RE9		INT2/RE9
	NOT_ON_TIMER,		// 45 RA1		TCK/RA1
	NOT_ON_TIMER,		// 46 RA4		TDI/RA4
	NOT_ON_TIMER,		// 47 RA5		TDO/RA5	
	
	//BUTTONS
	NOT_ON_TIMER,		// 48 BTN1		ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	NOT_ON_TIMER,		// 49 BTN2		ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	NOT_ON_TIMER,		// 50 BTN3		TMS/RA0	
	
	//LEDS
	NOT_ON_TIMER,		// 51 LD1		TRD1/RG12
	NOT_ON_TIMER,		// 52 LD2		TRD0/RG13
	NOT_ON_TIMER,		// 53 LD3		TRD2/RG14
	NOT_ON_TIMER,		// 54 LD4		AERXERR/RG15
	
	//J8 /I2C PORT 2 
	NOT_ON_TIMER,		// 55 SCL2		SCL2/RA2
	NOT_ON_TIMER,		// 56 SDA2		SDA2/RA3	
	
	//J7 /I2C PORT 1
	NOT_ON_TIMER,		// 57 SCL1		SCL1/INT3/RA14
	NOT_ON_TIMER,		// 58 SDA1		SDA1/INT4/RA15	
	
	//MISC
	NOT_ON_TIMER,		// 59 RB5		AN5/C1IN+/VBUSON/CN7/RB5 (P32_VBUSON)
	NOT_ON_TIMER		// 60 RD13		ETXD3/PMD13/CN19/RD13 (P32_USBOC)
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
const uint8_t digital_pin_to_analog_PGM[] = {
    // Connector JA
	_BOARD_AN0,			//  0 RB2 		AN2/C2IN-/CN4/RB2
	_BOARD_AN1,			//  1 RB3		AN3/C2IN+/CN5/RB3
	_BOARD_AN2,			//  2 RB4		AN4/C1IN-/CN6/RB4
	_BOARD_AN3,			//  3 RB6		AN6/PGEC2/OCFA/RB6
	_BOARD_AN4,			//  4 RB7		AN7/PGED2/RB7
	_BOARD_AN5,			//  5 RB8		AN8/C1OUT/RB8
	_BOARD_AN6,			//  6 RB9		AN9/C2OUT/RB9
	_BOARD_AN7,			//  7 RB10		AN10/PMA13/RB10

    // Connector JB
	NOT_ANALOG_PIN,		//  8 RE0		PMD0/RE0
	NOT_ANALOG_PIN,		//  9 RE1		PMD1/RE1
	NOT_ANALOG_PIN,		// 10 RE2		PMD2/RE2
	NOT_ANALOG_PIN,		// 11 RE3		PMD3/RE3
	NOT_ANALOG_PIN,		// 12 RE4		PMD4/RE4
	NOT_ANALOG_PIN,		// 13 RE5		PMD5/RE5
	NOT_ANALOG_PIN,		// 14 RE6		PMD6/RE6
	NOT_ANALOG_PIN,		// 15 RE7		PMD7/RE7
	
    // Connector JC
	NOT_ANALOG_PIN,		// 16 RC1		T2CK/RC1
	NOT_ANALOG_PIN,		// 17 RG0		PMD8/RG0
	NOT_ANALOG_PIN,		// 18 RG1		PMD9/RG1
	NOT_ANALOG_PIN,		// 19 RD7		PMD15/CN16/RD7
	_BOARD_AN8,			// 20 RB15		AN15/PMA0/CN12
	NOT_ANALOG_PIN,		// 21 RD5		PMRD/CN14/RD5
	NOT_ANALOG_PIN,		// 22 RD4		PMWR/OC5/CN13/RD4
	_BOARD_AN9,			// 23 RB14		AN14/PMA1/RB14

    // Connector JD
	NOT_ANALOG_PIN,		// 24 RD9		SS1/IC2/RD9
	NOT_ANALOG_PIN,		// 25 RD0		SDO1/OC1/INT0/RD0
	NOT_ANALOG_PIN,		// 26 RC4		T5CK/SDI1/RC4
	NOT_ANALOG_PIN,		// 27 RD10		SCK1/IC3/RD10
	NOT_ANALOG_PIN,		// 28 RD1		OC2/RD1
	NOT_ANALOG_PIN,		// 29 RD2		OC3/RD2
	NOT_ANALOG_PIN,		// 30 RD3		OC4/RD3
	NOT_ANALOG_PIN,		// 31 RD12		IC5/PMD12/RD12

    // Connector JE
	NOT_ANALOG_PIN,		// 32 RD14		SS1A/U1ACTS/CN20/RD14
	NOT_ANALOG_PIN,		// 33 RF8		SCL1A/SDO1A/U1ATX/RF8
	NOT_ANALOG_PIN,		// 34 RF2		SDA1A/SDI1A/U1ARX/RF2
	NOT_ANALOG_PIN,		// 35 RD15		SCK1A/U1ARTS/CN21/RD15
	NOT_ANALOG_PIN,		// 36 RE8		INT1/RE8
	NOT_ANALOG_PIN,		// 37 RA7		TRD3/RA7
	NOT_ANALOG_PIN,		// 38 RA9		VREF-/CVREF-/PMA7/RA9
	NOT_ANALOG_PIN,		// 39 RA10		VREF+/CVREF+/PMA6/RA10    
    
    // Connector JF
	NOT_ANALOG_PIN,		// 40 RF12		SS3A/U3ACTS/RF12
	NOT_ANALOG_PIN,		// 41 RF5		SDO3A/U3ATX/CN18/RF5
	NOT_ANALOG_PIN,		// 42 RF4		SDI3A/U3ARX/CN17/RF4
	NOT_ANALOG_PIN,		// 43 RF13		SCK3A/U3ARTS/RF13
	NOT_ANALOG_PIN,		// 44 RE9		INT2/RE9
	NOT_ANALOG_PIN,		// 45 RA1		TCK/RA1
	NOT_ANALOG_PIN,		// 46 RA4		TDI/RA4
	NOT_ANALOG_PIN,		// 47 RA5		TDO/RA5	
	
	//BUTTONS
	NOT_ANALOG_PIN,		// 48 BTN1		ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	NOT_ANALOG_PIN,		// 49 BTN2		ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	NOT_ANALOG_PIN,		// 50 BTN3		TMS/RA0	
	
	//LEDS
	NOT_ANALOG_PIN,		// 51 LD1		TRD1/RG12
	NOT_ANALOG_PIN,		// 52 LD2		TRD0/RG13
	NOT_ANALOG_PIN,		// 53 LD3		TRD2/RG14
	NOT_ANALOG_PIN,		// 54 LD4		AERXERR/RG15
	
	//J8 /I2C PORT 2 
	NOT_ANALOG_PIN,		// 55 SCL2		SCL2/RA2
	NOT_ANALOG_PIN,		// 56 SDA2		SDA2/RA3	
	
	//J7 /I2C PORT 1
	NOT_ANALOG_PIN,		// 57 SCL1		SCL1/INT3/RA14
	NOT_ANALOG_PIN,		// 58 SDA1		SDA1/INT4/RA15	
	
	//MISC
	NOT_ANALOG_PIN,		// 59 RB5		AN5/C1IN+/VBUSON/CN7/RB5 (P32_VBUSON)
	NOT_ANALOG_PIN		// 60 RD13		ETXD3/PMD13/CN19/RD13 (P32_USBOC)
};

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
*/
const uint8_t analog_pin_to_channel_PGM[] =
{
			//*	chipKIT Pin		PIC32 Analog channel
	2,		//*	A0						AN2
	3,		//*	A1						AN3
	4,		//*	A2						AN4
	6,		//*	A3						AN6
	7,		//*	A4						AN7
	8,		//*	A5						AN8
	9,		//*	A6						AN9
	10,		//*	A7						AN10
	15,		//*	A8						AN15
	14		//*	A9						AN14
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
