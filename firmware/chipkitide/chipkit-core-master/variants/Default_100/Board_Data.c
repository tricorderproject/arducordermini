/************************************************************************/
/*																		*/
/*	Board_Data.c --	Default Board Customization Declarations			*/
/*																		*/
/************************************************************************/
/*	Author:		Gene Apperson											*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with a generic board using a	*/
/* PIC32 part in a 100-pin package.										*/
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
** containing that pin. The default mapping is to assign pin numbers
** for every possible port bit in order from PORTA to PORTG.
*/
const uint8_t	digital_pin_to_port_PGM[] = {
#if defined(_PORTA)
	_IOPORT_PA,		// 0 RA 0
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
	_IOPORT_PA,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif

#if defined(_PORTB)
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
	_IOPORT_PB,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif

#if defined(_PORTC)
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
	_IOPORT_PC,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif

#if defined(_PORTD)
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
	_IOPORT_PD,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif

#if defined(_PORTE)
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
	_IOPORT_PE,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif

#if defined(_PORTF)
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
	_IOPORT_PF,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif

#if defined(_PORTG)
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
	_IOPORT_PG,
#else
	NOT_A_PIN,	//	0
	NOT_A_PIN,	//	1
	NOT_A_PIN,	//	2
	NOT_A_PIN,	//	3
	NOT_A_PIN,	//	4
	NOT_A_PIN,	//	5
	NOT_A_PIN,	//	6
	NOT_A_PIN,	//	7
	NOT_A_PIN,	//	8
	NOT_A_PIN,	//	9
	NOT_A_PIN,	//	10
	NOT_A_PIN,	//	11
	NOT_A_PIN,	//	12
	NOT_A_PIN,	//	13
	NOT_A_PIN,	//	14
	NOT_A_PIN,	//	15
#endif
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {
//#ifdef _PORTA
	_BV( 0 ) ,	// 0 RA 0
	_BV( 1 ) ,	// 1 RA 1
	_BV( 2 ) ,	// 2 RA 2
	_BV( 3 ) ,	// 3 RA 3
	_BV( 4 ) ,	// 4 RA 4
	_BV( 5 ) ,	// 5 RA 5
	_BV( 6 ) ,	// 6 RA 6
	_BV( 7 ) ,	// 7 RA 7
	_BV( 8 ) ,	// 8 RA 8
	_BV( 9 ) ,	// 9 RA 9
	_BV( 10 ) ,	// 10 RA 10
	_BV( 11 ) ,	// 11 RA 11
	_BV( 12 ) ,	// 12 RA 12
	_BV( 13 ) ,	// 13 RA 13
	_BV( 14 ) ,	// 14 RA 14
	_BV( 15 ) ,	// 15 RA 15
//#endif

//#ifdef _PORTB
	_BV( 0 ) ,	// 16 RB 0
	_BV( 1 ) ,	// 17 RB 1
	_BV( 2 ) ,	// 18 RB 2
	_BV( 3 ) ,	// 19 RB 3
	_BV( 4 ) ,	// 20 RB 4
	_BV( 5 ) ,	// 21 RB 5
	_BV( 6 ) ,	// 22 RB 6
	_BV( 7 ) ,	// 23 RB 7
	_BV( 8 ) ,	// 24 RB 8
	_BV( 9 ) ,	// 25 RB 9
	_BV( 10 ) ,	// 26 RB 10
	_BV( 11 ) ,	// 27 RB 11
	_BV( 12 ) ,	// 28 RB 12
	_BV( 13 ) ,	// 29 RB 13
	_BV( 14 ) ,	// 30 RB 14
	_BV( 15 ) ,	// 31 RB 15
//#endif

//#ifdef _PORTC
	_BV( 0 ) ,	// 32 RC 0
	_BV( 1 ) ,	// 33 RC 1
	_BV( 2 ) ,	// 34 RC 2
	_BV( 3 ) ,	// 35 RC 3
	_BV( 4 ) ,	// 36 RC 4
	_BV( 5 ) ,	// 37 RC 5
	_BV( 6 ) ,	// 38 RC 6
	_BV( 7 ) ,	// 39 RC 7
	_BV( 8 ) ,	// 40 RC 8
	_BV( 9 ) ,	// 41 RC 9
	_BV( 10 ) ,	// 42 RC 10
	_BV( 11 ) ,	// 43 RC 11
	_BV( 12 ) ,	// 44 RC 12
	_BV( 13 ) ,	// 45 RC 13
	_BV( 14 ) ,	// 46 RC 14
	_BV( 15 ) ,	// 47 RC 15
//#endif

//#ifdef _PORTD
	_BV( 0 ) ,	// 48 RD 0
	_BV( 1 ) ,	// 49 RD 1
	_BV( 2 ) ,	// 50 RD 2
	_BV( 3 ) ,	// 51 RD 3
	_BV( 4 ) ,	// 52 RD 4
	_BV( 5 ) ,	// 53 RD 5
	_BV( 6 ) ,	// 54 RD 6
	_BV( 7 ) ,	// 55 RD 7
	_BV( 8 ) ,	// 56 RD 8
	_BV( 9 ) ,	// 57 RD 9
	_BV( 10 ) ,	// 58 RD 10
	_BV( 11 ) ,	// 59 RD 11
	_BV( 12 ) ,	// 60 RD 12
	_BV( 13 ) ,	// 61 RD 13
	_BV( 14 ) ,	// 62 RD 14
	_BV( 15 ) ,	// 63 RD 15
//#endif

//#ifdef _PORTE
	_BV( 0 ) ,	// 64 RE 0
	_BV( 1 ) ,	// 65 RE 1
	_BV( 2 ) ,	// 66 RE 2
	_BV( 3 ) ,	// 67 RE 3
	_BV( 4 ) ,	// 68 RE 4
	_BV( 5 ) ,	// 69 RE 5
	_BV( 6 ) ,	// 70 RE 6
	_BV( 7 ) ,	// 71 RE 7
	_BV( 8 ) ,	// 72 RE 8
	_BV( 9 ) ,	// 73 RE 9
	_BV( 10 ) ,	// 74 RE 10
	_BV( 11 ) ,	// 75 RE 11
	_BV( 12 ) ,	// 76 RE 12
	_BV( 13 ) ,	// 77 RE 13
	_BV( 14 ) ,	// 78 RE 14
	_BV( 15 ) ,	// 79 RE 15
//#endif

//#ifdef _PORTF
	_BV( 0 ) ,	// 80 RF 0
	_BV( 1 ) ,	// 81 RF 1
	_BV( 2 ) ,	// 82 RF 2
	_BV( 3 ) ,	// 83 RF 3
	_BV( 4 ) ,	// 84 RF 4
	_BV( 5 ) ,	// 85 RF 5
	_BV( 6 ) ,	// 86 RF 6
	_BV( 7 ) ,	// 87 RF 7
	_BV( 8 ) ,	// 88 RF 8
	_BV( 9 ) ,	// 89 RF 9
	_BV( 10 ) ,	// 90 RF 10
	_BV( 11 ) ,	// 91 RF 11
	_BV( 12 ) ,	// 92 RF 12
	_BV( 13 ) ,	// 93 RF 13
	_BV( 14 ) ,	// 94 RF 14
	_BV( 15 ) ,	// 95 RF 15
//#endif

//#ifdef _PORTG
	_BV( 0 ) ,	// 96 RG 0
	_BV( 1 ) ,	// 97 RG 1
	_BV( 2 ) ,	// 98 RG 2
	_BV( 3 ) ,	// 99 RG 3
	_BV( 4 ) ,	// 100 RG 4
	_BV( 5 ) ,	// 101 RG 5
	_BV( 6 ) ,	// 102 RG 6
	_BV( 7 ) ,	// 103 RG 7
	_BV( 8 ) ,	// 104 RG 8
	_BV( 9 ) ,	// 105 RG 9
	_BV( 10 ) ,	// 106 RG 10
	_BV( 11 ) ,	// 107 RG 11
	_BV( 12 ) ,	// 108 RG 12
	_BV( 13 ) ,	// 109 RG 13
	_BV( 14 ) ,	// 110 RG 14
	_BV( 15 ) ,	// 111 RG 15
//#endif
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t	digital_pin_to_timer_PGM[] = {
//#ifdef _PORTA
	NOT_ON_TIMER ,	// 0 RA 0
	NOT_ON_TIMER ,	// 1 RA 1
	NOT_ON_TIMER ,	// 2 RA 2
	NOT_ON_TIMER ,	// 3 RA 3
	NOT_ON_TIMER ,	// 4 RA 4
	NOT_ON_TIMER ,	// 5 RA 5
	NOT_ON_TIMER ,	// 6 RA 6
	NOT_ON_TIMER ,	// 7 RA 7
	NOT_ON_TIMER ,	// 8 RA 8
	NOT_ON_TIMER ,	// 9 RA 9
	NOT_ON_TIMER ,	// 10 RA 10
	NOT_ON_TIMER,	// 11 RA 11
	NOT_ON_TIMER ,	// 12 RA 12
	NOT_ON_TIMER ,	// 13 RA 13
	NOT_ON_TIMER ,	// 14 RA 14
	NOT_ON_TIMER ,	// 15 RA 15
//#endif

//#ifdef _PORTB
	NOT_ON_TIMER ,	// 16 RB 0
	NOT_ON_TIMER ,	// 17 RB 1
	NOT_ON_TIMER ,	// 18 RB 2
	NOT_ON_TIMER ,	// 19 RB 3
	NOT_ON_TIMER ,	// 20 RB 4
	NOT_ON_TIMER ,	// 21 RB 5
	NOT_ON_TIMER ,	// 22 RB 6
	NOT_ON_TIMER ,	// 23 RB 7
	NOT_ON_TIMER ,	// 24 RB 8
	NOT_ON_TIMER ,	// 25 RB 9
	NOT_ON_TIMER ,	// 26 RB 10
	NOT_ON_TIMER,	// 27 RB 11
	NOT_ON_TIMER ,	// 28 RB 12
	NOT_ON_TIMER ,	// 29 RB 13
	NOT_ON_TIMER ,	// 30 RB 14
	NOT_ON_TIMER ,	// 31 RB 15
//#endif

//#ifdef _PORTC
	NOT_ON_TIMER ,	// 32 RC 0
	_TIMER_TCK2 ,	// 33 RC 1
	_TIMER_TCK3 ,	// 34 RC 2
	_TIMER_TCK4 ,	// 35 RC 3
	_TIMER_TCK5 ,	// 36 RC 4
	NOT_ON_TIMER ,	// 37 RC 5
	NOT_ON_TIMER ,	// 38 RC 6
	NOT_ON_TIMER ,	// 39 RC 7
	NOT_ON_TIMER ,	// 40 RC 8
	NOT_ON_TIMER ,	// 41 RC 9
	NOT_ON_TIMER ,	// 42 RC 10
	NOT_ON_TIMER,	// 43 RC 11
	NOT_ON_TIMER ,	// 44 RC 12
	NOT_ON_TIMER ,	// 45 RC 13
	_TIMER_TCK1 ,	// 46 RC 14
	NOT_ON_TIMER ,	// 47 RC 15
//#endif

//#ifdef _PORTD
	_TIMER_OC1 ,	// 48 RD 0
	_TIMER_OC2 ,	// 49 RD 1
	_TIMER_OC3 ,	// 50 RD 2
	_TIMER_OC4 ,	// 51 RD 3
	_TIMER_OC5 ,	// 52 RD 4
	NOT_ON_TIMER ,	// 53 RD 5
	NOT_ON_TIMER ,	// 54 RD 6
	NOT_ON_TIMER ,	// 55 RD 7
	_TIMER_IC1 ,	// 56 RD 8
	_TIMER_IC2 ,	// 57 RD 9
	_TIMER_IC3 ,	// 58 RD 10
	_TIMER_IC4,		// 59 RD 11
	_TIMER_IC5 ,	// 60 RD 12
	NOT_ON_TIMER ,	// 61 RD 13
	NOT_ON_TIMER ,	// 62 RD 14
	NOT_ON_TIMER ,	// 63 RD 15
//#endif

//#ifdef _PORTE
	NOT_ON_TIMER ,	// 64 RE 0
	NOT_ON_TIMER ,	// 65 RE 1
	NOT_ON_TIMER ,	// 66 RE 2
	NOT_ON_TIMER ,	// 67 RE 3
	NOT_ON_TIMER ,	// 68 RE 4
	NOT_ON_TIMER ,	// 69 RE 5
	NOT_ON_TIMER ,	// 70 RE 6
	NOT_ON_TIMER ,	// 71 RE 7
	NOT_ON_TIMER ,	// 72 RE 8
	NOT_ON_TIMER ,	// 73 RE 9
	NOT_ON_TIMER ,	// 74 RE 10
	NOT_ON_TIMER,	// 75 RE 11
	NOT_ON_TIMER ,	// 76 RE 12
	NOT_ON_TIMER ,	// 77 RE 13
	NOT_ON_TIMER ,	// 78 RE 14
	NOT_ON_TIMER ,	// 79 RE 15
//#endif

//#ifdef _PORTF
	NOT_ON_TIMER ,	// 80 RF 0
	NOT_ON_TIMER ,	// 81 RF 1
	NOT_ON_TIMER ,	// 82 RF 2
	NOT_ON_TIMER ,	// 83 RF 3
	NOT_ON_TIMER ,	// 84 RF 4
	NOT_ON_TIMER ,	// 85 RF 5
	NOT_ON_TIMER ,	// 86 RF 6
	NOT_ON_TIMER ,	// 87 RF 7
	NOT_ON_TIMER ,	// 88 RF 8
	NOT_ON_TIMER ,	// 89 RF 9
	NOT_ON_TIMER ,	// 90 RF 10
	NOT_ON_TIMER,	// 91 RF 11
	NOT_ON_TIMER ,	// 92 RF 12
	NOT_ON_TIMER ,	// 93 RF 13
	NOT_ON_TIMER ,	// 94 RF 14
	NOT_ON_TIMER ,	// 95 RF 15
//#endif

//#ifdef _PORTG
	NOT_ON_TIMER ,	// 96 RG 0
	NOT_ON_TIMER ,	// 97 RG 1
	NOT_ON_TIMER ,	// 98 RG 2
	NOT_ON_TIMER ,	// 99 RG 3
	NOT_ON_TIMER ,	// 100 RG 4
	NOT_ON_TIMER ,	// 101 RG 5
	NOT_ON_TIMER ,	// 102 RG 6
	NOT_ON_TIMER ,	// 103 RG 7
	NOT_ON_TIMER ,	// 104 RG 8
	NOT_ON_TIMER ,	// 105 RG 9
	NOT_ON_TIMER ,	// 106 RG 10
	NOT_ON_TIMER,	// 107 RG 11
	NOT_ON_TIMER ,	// 108 RG 12
	NOT_ON_TIMER ,	// 109 RG 13
	NOT_ON_TIMER ,	// 110 RG 14
	NOT_ON_TIMER ,	// 111 RG 15
//#endif
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
#if defined(_NOT_USED_)
const uint8_t digital_pin_to_analog_PGM[] = {
//#ifdef _PORTA
	NOT_ANALOG_PIN,	// 0 RA 0
	NOT_ANALOG_PIN,	// 1 RA 1
	NOT_ANALOG_PIN,	// 2 RA 2
	NOT_ANALOG_PIN,	// 3 RA 3
	NOT_ANALOG_PIN,	// 4 RA 4
	NOT_ANALOG_PIN,	// 5 RA 5
	NOT_ANALOG_PIN,	// 6 RA 6
	NOT_ANALOG_PIN,	// 7 RA 7
	NOT_ANALOG_PIN,	// 8 RA 8
	NOT_ANALOG_PIN,	// 9 RA 9
	NOT_ANALOG_PIN,	// 10 RA 10
	NOT_ANALOG_PIN,	// 11 RA 11
	NOT_ANALOG_PIN,	// 12 RA 12
	NOT_ANALOG_PIN,	// 13 RA 13
	NOT_ANALOG_PIN,	// 14 RA 14
	NOT_ANALOG_PIN,	// 15 RA 15
//#endif

//#ifdef _PORTB
	_BOARD_AN0,		// 0 RB 0
	_BOARD_AN1,		// 1 RB 1
	_BOARD_AN2,		// 2 RB 2
	_BOARD_AN3,		// 3 RB 3
	_BOARD_AN4,		// 4 RB 4
	_BOARD_AN5,		// 5 RB 5
	_BOARD_AN6,		// 6 RB 6
	_BOARD_AN7,		// 7 RB 7
	_BOARD_AN8,		// 8 RB 8
	_BOARD_AN9,		// 9 RB 9
	_BOARD_AN10,	// 10 RB 10
	_BOARD_AN11,	// 11 RB 11
	_BOARD_AN12,	// 12 RB 12
	_BOARD_AN13,	// 13 RB 13
	_BOARD_AN14,	// 14 RB 14
	_BOARD_AN15,	// 15 RB 15
//#endif

//#ifdef _PORTC
	NOT_ANALOG_PIN,	// 0 RC 0
	NOT_ANALOG_PIN,	// 1 RC 1
	NOT_ANALOG_PIN,	// 2 RC 2
	NOT_ANALOG_PIN,	// 3 RC 3
	NOT_ANALOG_PIN,	// 4 RC 4
	NOT_ANALOG_PIN,	// 5 RC 5
	NOT_ANALOG_PIN,	// 6 RC 6
	NOT_ANALOG_PIN,	// 7 RC 7
	NOT_ANALOG_PIN,	// 8 RC 8
	NOT_ANALOG_PIN,	// 9 RC 9
	NOT_ANALOG_PIN,	// 10 RC 10
	NOT_ANALOG_PIN,	// 11 RC 11
	NOT_ANALOG_PIN,	// 12 RC 12
	NOT_ANALOG_PIN,	// 13 RC 13
	NOT_ANALOG_PIN,	// 14 RC 14
	NOT_ANALOG_PIN,	// 15 RC 15
//#endif

//#ifdef _PORTD
	NOT_ANALOG_PIN,	// 0 RD 0
	NOT_ANALOG_PIN,	// 1 RD 1
	NOT_ANALOG_PIN,	// 2 RD 2
	NOT_ANALOG_PIN,	// 3 RD 3
	NOT_ANALOG_PIN,	// 4 RD 4
	NOT_ANALOG_PIN,	// 5 RD 5
	NOT_ANALOG_PIN,	// 6 RD 6
	NOT_ANALOG_PIN,	// 7 RD 7
	NOT_ANALOG_PIN,	// 8 RD 8
	NOT_ANALOG_PIN,	// 9 RD 9
	NOT_ANALOG_PIN,	// 10 RD 10
	NOT_ANALOG_PIN,	// 11 RD 11
	NOT_ANALOG_PIN,	// 12 RD 12
	NOT_ANALOG_PIN,	// 13 RD 13
	NOT_ANALOG_PIN,	// 14 RD 14
	NOT_ANALOG_PIN,	// 15 RD 15
//#endif

//#ifdef _PORTE
	NOT_ANALOG_PIN,	// 0 RE 0
	NOT_ANALOG_PIN,	// 1 RE 1
	NOT_ANALOG_PIN,	// 2 RE 2
	NOT_ANALOG_PIN,	// 3 RE 3
	NOT_ANALOG_PIN,	// 4 RE 4
	NOT_ANALOG_PIN,	// 5 RE 5
	NOT_ANALOG_PIN,	// 6 RE 6
	NOT_ANALOG_PIN,	// 7 RE 7
	NOT_ANALOG_PIN,	// 8 RE 8
	NOT_ANALOG_PIN,	// 9 RE 9
	NOT_ANALOG_PIN,	// 10 RE 10
	NOT_ANALOG_PIN,	// 11 RE 11
	NOT_ANALOG_PIN,	// 12 RE 12
	NOT_ANALOG_PIN,	// 13 RE 13
	NOT_ANALOG_PIN,	// 14 RE 14
	NOT_ANALOG_PIN,	// 15 RE 15
//#endif

//#ifdef _PORTF
	NOT_ANALOG_PIN,	// 0 RF 0
	NOT_ANALOG_PIN,	// 1 RF 1
	NOT_ANALOG_PIN,	// 2 RF 2
	NOT_ANALOG_PIN,	// 3 RF 3
	NOT_ANALOG_PIN,	// 4 RF 4
	NOT_ANALOG_PIN,	// 5 RF 5
	NOT_ANALOG_PIN,	// 6 RF 6
	NOT_ANALOG_PIN,	// 7 RF 7
	NOT_ANALOG_PIN,	// 8 RF 8
	NOT_ANALOG_PIN,	// 9 RF 9
	NOT_ANALOG_PIN,	// 10 RF 10
	NOT_ANALOG_PIN,	// 11 RF 11
	NOT_ANALOG_PIN,	// 12 RF 12
	NOT_ANALOG_PIN,	// 13 RF 13
	NOT_ANALOG_PIN,	// 14 RF 14
	NOT_ANALOG_PIN,	// 15 RF 15
//#endif

//#ifdef _PORTG
	NOT_ANALOG_PIN,	// 0 RG 0
	NOT_ANALOG_PIN,	// 1 RG 1
	NOT_ANALOG_PIN,	// 2 RG 2
	NOT_ANALOG_PIN,	// 3 RG 3
	NOT_ANALOG_PIN,	// 4 RG 4
	NOT_ANALOG_PIN,	// 5 RG 5
	NOT_ANALOG_PIN,	// 6 RG 6
	NOT_ANALOG_PIN,	// 7 RG 7
	NOT_ANALOG_PIN,	// 8 RG 8
	NOT_ANALOG_PIN,	// 9 RG 9
	NOT_ANALOG_PIN,	// 10 RG 10
	NOT_ANALOG_PIN,	// 11 RG 11
	NOT_ANALOG_PIN,	// 12 RG 12
	NOT_ANALOG_PIN,	// 13 RG 13
	NOT_ANALOG_PIN,	// 14 RG 14
	NOT_ANALOG_PIN,	// 15 RG 15
//#endif
};
#endif

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
** In the default case, where there is a one-to-one mapping, this
** table isn't needed as the analogInPinToChannel() macro is defined
** to provide the mapping.
*/
#if defined(_NOT_USED_)
const uint8_t analog_pin_to_channel_PGM[] = {
			//*	Arduino Pin		PIC32 Analog channel
	0,		//*	A0				1 to 1 mapping
	1,		//*	A1
	2,		//*	A2
	3,		//*	A3
	4,		//*	A4
	5,		//*	A5
	6,		//*	A6
	7,		//*	A7
	8,		//*	A8
	9,		//*	A9
	10,		//*	A10
	11,		//*	A11
	12,		//*	A12
	13,		//*	A13
	14,		//*	A14
	15,		//*	A15
};
#endif

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
