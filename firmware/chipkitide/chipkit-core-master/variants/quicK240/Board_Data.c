/************************************************************************/
/*																		*/
/*	Board_Data.c -- Board Customization Data for Digilent chipKIT Max32	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent chipKIT		*/
/* Max32 board.															*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/28/2011(GeneA): Created by splitting data out of Board_Defs.h	*/
/*	03/31/2012(GeneA): added support for second LED on Rev D boards		*/
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
	_IOPORT_PF,		//	0 RF2	SDA1A/SDI1A/U1ARX/RF2
	_IOPORT_PF,		//	1 RF8	SCL1A/SDO1A/U1ATX/RF8
	_IOPORT_PE,		//	2 RE8	AERXD0/INT1/RE8
	_IOPORT_PD,		//	3 RD0	SDO1/OC1/INT0/RD0
	_IOPORT_PC,		//	4 RC14	SOSCO/T1CK/CN0/RC14
	_IOPORT_PD,		//	5 RD1	OC2/RD1
	_IOPORT_PD,		//	6 RD2	OC3/RD2
	_IOPORT_PE,		//	7 RE9	AERXD1/INT2/RE9
	_IOPORT_PD,		//	8 RD12	ETXD2/IC5/PMD12/RD12
	_IOPORT_PD,		//	9 RD3	OC4/RD3
	_IOPORT_PD,		//	10 RD4	OC5/PMWR/CN13/RD4
	_IOPORT_PC,		//	11 RC4	T5CK/SDI1/RC4
	_IOPORT_PA,		//	12 RA2	SCL2/RA2
	_IOPORT_PA,		//	13 RA3	SDA2/RA3
	_IOPORT_PF,		//	14 RF13	AC1TX/SCK3A/U3BTX/U3ARTS/RF13
	_IOPORT_PF,		//	15 RF12	AC1RX/SS3A/U3BRX/U3ACTS/RF12
	_IOPORT_PF,		//	16 RF5	SCL3A/SDO3A/U3ATX/PMA8/CN18/RF5
	_IOPORT_PF,		//	17 RF4	SDA3A/SDI3A/U3ARX/PMA9/CN17/RF4
	_IOPORT_PD,		//	18 RD15	AETXD1/SCK1A/U1BTX/U1ARTS/CN21/RD15
	_IOPORT_PD,		//	19 RD14	AETXD0/SS1A/U1BRX/U1ACTS/CN20/RD14
	_IOPORT_PA,		//	20 RA15	AETXEN/SDA1/INT4/RA15
	_IOPORT_PA,		//	21 RA14	AETXCLK/SCL1/INT3/RA14
	_IOPORT_PC,		//	22 RC2	T3CK/AC2TX/RC2
	_IOPORT_PC,		//	23 RC3	T4CK/AC2RX/RC3
	_IOPORT_PC,		//	24 VBUS
	_IOPORT_PF,		//	25 RF3	USBID/RF3
	_IOPORT_PG,		//	26 RG3	D-/RG3
	_IOPORT_PG,		//	27 RG2	D+/RG2
	_IOPORT_PG,		//	28 RG15
	_IOPORT_PG,		//	29 RG7	ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	_IOPORT_PE,		//	30 RE7	PMD7/RE7
	_IOPORT_PE,		//	31 RE6	PMD6/RE6
	_IOPORT_PE,		//	32 RE5	PMD5/RE5
	_IOPORT_PE,		//	33 RE4	PMD4/RE4
	_IOPORT_PE,		//	34 RE3	PMD3/RE3
	_IOPORT_PE,		//	35 RE2	PMD2/RE2
	_IOPORT_PE,		//	36 RE1	PMD1/RE1
	_IOPORT_PE,		//	37 RE0	PMD0/RE0
	_IOPORT_PD,		//	38 RD10	SCK1/IC3/PMCS2/PMA15/RD10
	_IOPORT_PD,		//	39 RD5	PMRD/CN14/RD5
	_IOPORT_PB,		//	40 RB11	AN11/EREXERR/AETXERR/PMA12/RB11
	_IOPORT_PB,		//	41 RB13	AN13/ERXD1/AECOL/PMA10/RB13
	_IOPORT_PB,		//	42 RB12	AN12/ERXD0/AECRS/PMA11/RB12
	_IOPORT_PG,		//	43 RG8	ERXDV/AERXDV/ECRSDV/AECRSDV/SCL2A/SDO2A/U2ATX/PMA3/CN10/RG8
	_IOPORT_PA,		//	44 RA10	VREF+/CVREF+/AERXD3/PMA6/RA10
	_IOPORT_PF,		//	45 RF0	C1RX/ETXD1/PMD11/RF0
	_IOPORT_PF,		//	46 RF1	C1TX/ETXD0/RMD10/RF1
	_IOPORT_PD,		//	47 RD6	ETXEN/PMD14/CN15/RD6
	_IOPORT_PD,		//	48 RD8	PTCC/EMDIO/AEMDIO/IC1/RD8
	_IOPORT_PD,		//	49 RD11	EMDC/AEMDC/IC4/PMCS1/PMA14/RD11
	_IOPORT_PG,		//	50 RG7	ECRS/SDA2/SDI2A/U2ARX/PMA4/CN9/RG7
	_IOPORT_PG,		//	51 RG8
	_IOPORT_PG,		//	52 RG6	ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	_IOPORT_PG,		//	53 RG9	ERXCLK/AERXCLK/EREFCLK/AEREFCLK/SS2A/U2BRX/U2ACTS/PMA2/CN11/RG9
	//*	the analog ports start with 54
	_IOPORT_PB,		//	54	RB0	PGED1/AN0/CN2/RB0
	_IOPORT_PB,		//	55	RB1	PGEC1/AN1/CN3/RB1
	_IOPORT_PB,		//	56	RB2	AN2/C2IN-/CN4/RB2
	_IOPORT_PB,		//	57	RB3	AN3/C2IN+/CN5/RB3
	_IOPORT_PB,		//	58	RB4	AN4/C1IN-/CN6/RB4
	_IOPORT_PB,		//	59	RB5	AN5/C1IN+/VBUSON/CN7/RB5
	_IOPORT_PB,		//	60	RB6	PGEC2/AN6/OCFA/RB6
	_IOPORT_PB,		//	61	RB7	PGED2/AN7/RB7
	_IOPORT_PB,		//	62	RB8	AN8/C1OUT/RB8
	_IOPORT_PB,		//	63	RB9	AN9/C2OUT/RB9
	_IOPORT_PB,		//	64	RB10	AN10/CVREFOUT/PMA13/RB10
	_IOPORT_PB,		//	65	RB11	AN11/EREXERR/AETXERR/PMA12/RB11
	_IOPORT_PB,		//	66	RB12	AN13/ERXD1/AECOL/PMA10/RB13
	_IOPORT_PB,		//	67	RB13	AN12/ERXD0/AECRS/PMA11/RB12
	_IOPORT_PB,		//	68	RB14	AN14/ERXD2/AETXD3/PMALH/PMA1/RB14
	_IOPORT_PB,		//	69	RB15	AN15/ERXD3/AETXD2/OCFB/PMALL/PMA0/CN12/RB15

	//*	Pic32 EXTRAS start here (with #70)
	_IOPORT_PA,		//	70 RA0	TMS/RA0
	_IOPORT_PA,		//	71 RA1	TCK/RA1
	_IOPORT_PA,		//	72 RA4	TDI/RA4
	_IOPORT_PA,		//	73 RA5	TDO/RA5
	_IOPORT_PD,		//	74 RD9	SS1/IC2/RD9
	_IOPORT_PC,		//	75 RC13	SOSCI/CN1/RC13
	_IOPORT_PD,		//	76 RD13	ETXD3/PMD13/CN19/RD13
	_IOPORT_PD,		//	77 RD7	ETXCLK/PMD15/CN16/RD7
	_IOPORT_PG,		//	78 RG1	C2TX/ETXERR/PMD9/RG1
	_IOPORT_PG,		//	79 RG0	C2RX/PMD8/RG0
	_IOPORT_PA,		//	80 RA6	TRCLK/RA6
	_IOPORT_PA,		//	81 RA7	TRD3/RA7
	_IOPORT_PG,		//	82 RG14	TRD2/RG14
	_IOPORT_PG,		//	83 RG12	TRD1/RG12
	_IOPORT_PG,		//	84 RG13	TRD0/RG13
	_IOPORT_PA,		//	85 RA9	VREF-/CVREF0/AERXD2/PMA7/RA9
	_IOPORT_PC,		//	86 RC1	T2CK/RC1
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t digital_pin_to_bit_mask_PGM[] = {
	_BV( 2 ),		//	0 RF2	SDA1A/SDI1A/U1ARX/RF2
	_BV( 8 ),		//	1 RF8	SCL1A/SDO1A/U1ATX/RF8
	_BV( 8 ),		//	2 RE8	AERXD0/INT1/RE8
	_BV( 0 ),		//	3 RD0	SDO1/OC1/INT0/RD0
	_BV( 14 ),		//	4 RC14	SOSCO/T1CK/CN0/RC14
	_BV( 1 ),		//	5 RD1	OC2/RD1
	_BV( 2 ),		//	6 RD2	OC3/RD2
	_BV( 9 ),		//	7 RE9	AERXD1/INT2/RE9
	_BV( 12 ),		//	8 RD12	ETXD2/IC5/PMD12/RD12
	_BV( 3 ),		//	9 RD3	OC4/RD3
	_BV( 4 ),		//	10 RD4	OC5/PMWR/CN13/RD4
	_BV( 4 ),		//	11 RC4	T5CK/SDI1/RC4
	_BV( 2 ),		//	12 RA2	SCL2/RA2
	_BV( 3 ),		//	13 RA3	SDA2/RA3
	_BV( 13 ),		//	14 RF13	AC1TX/SCK3A/U3BTX/U3ARTS/RF13
	_BV( 12 ),		//	15 RF12	AC1RX/SS3A/U3BRX/U3ACTS/RF12
	_BV( 5 ),		//	16 RF5	SCL3A/SDO3A/U3ATX/PMA8/CN18/RF5
	_BV( 4 ),		//	17 RF4	SDA3A/SDI3A/U3ARX/PMA9/CN17/RF4
	_BV( 15 ),		//	18 RD15	AETXD1/SCK1A/U1BTX/U1ARTS/CN21/RD15
	_BV( 14 ),		//	19 RD14	AETXD0/SS1A/U1BRX/U1ACTS/CN20/RD14
	_BV( 15 ),		//	20 RA15	AETXEN/SDA1/INT4/RA15
	_BV( 14 ),		//	21 RA14	AETXCLK/SCL1/INT3/RA14
	_BV( 2 ),		//	22 RC2	T3CK/AC2TX/RC2
	_BV( 3 ),		//	23 RC3	T4CK/AC2RX/RC3
	_BV( 0 ),		//	24 VBUS
	_BV( 3 ),		//	25 RF3	USBID/RF3
	_BV( 3 ),		//	26 RG3	D-/RG3
	_BV( 2 ),		//	27 RG2	D+/RG2
	_BV( 15 ),		//	28 RG15
	_BV( 7 ),		//	29 RG7	ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	_BV( 7 ),		//	30 RE7	PMD7/RE7
	_BV( 6 ),		//	31 RE6	PMD6/RE6
	_BV( 5 ),		//	32 RE5	PMD5/RE5
	_BV( 4 ),		//	33 RE4	PMD4/RE4
	_BV( 3 ),		//	34 RE3	PMD3/RE3
	_BV( 2 ),		//	35 RE2	PMD2/RE2
	_BV( 1 ),		//	36 RE1	PMD1/RE1
	_BV( 0 ),		//	37 RE0	PMD0/RE0
	_BV( 10 ),		//	38 RD10	SCK1/IC3/PMCS2/PMA15/RD10
	_BV( 5 ),		//	39 RD5	PMRD/CN14/RD5
	_BV( 11 ),		//	40 RB11	AN11/EREXERR/AETXERR/PMA12/RB11
	_BV( 13 ),		//	41 RB13	AN13/ERXD1/AECOL/PMA10/RB13
	_BV( 12 ),		//	42 RB12	AN12/ERXD0/AECRS/PMA11/RB12
	_BV( 8 ),		//	43 RG8	ERXDV/AERXDV/ECRSDV/AECRSDV/SCL2A/SDO2A/U2ATX/PMA3/CN10/RG8
	_BV( 10 ),		//	44 RA10	VREF+/CVREF+/AERXD3/PMA6/RA10
	_BV( 0 ),		//	45 RF0	C1RX/ETXD1/PMD11/RF0
	_BV( 1 ),		//	46 RF1	C1TX/ETXD0/RMD10/RF1
	_BV( 6 ),		//	47 RD6	ETXEN/PMD14/CN15/RD6
	_BV( 8 ),		//	48 RD8	RTCC/EMDIO/AEMDIO/IC1/RD8
	_BV( 11 ),		//	49 RD11	EMDC/AEMDC/IC4/PMCS1/PMA14/RD11
	_BV( 7 ),		//	50 RG7	ECRX/SDA2/SDI2A/U2ARX/PMA4/CN9/RG7
	_BV( 8 ),		//	51 RG8
	_BV( 6 ),		//	52 RG6	ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	_BV( 9 ),		//	53 RG9	ERXCLK/AERXCLK/EREFCLK/AEREFCLK/SS2A/U2BRX/U2ACTS/PMA2/CN11/RG9

	//*	the analog ports start with 54
	_BV( 0 ),		//	54	RB0	PGED1/AN0/CN2/RB0
	_BV( 1 ),		//	55	RB1	PGEC1/AN1/CN3/RB1
	_BV( 2 ),		//	56	RB2	AN2/C2IN-/CN4/RB2
	_BV( 3 ),		//	57	RB3	AN3/C2IN+/CN5/RB3
	_BV( 4 ),		//	58	RB4	AN4/C1IN-/CN6/RB4
	_BV( 5 ),		//	59	RB5	AN5/C1IN+/VBUSON/CN7/RB5
	_BV( 6 ),		//	60	RB6	PGEC2/AN6/OCFA/RB6
	_BV( 7 ),		//	61	RB7	PGED2/AN7/RB7
	_BV( 8 ),		//	62	RB8	AN8/C1OUT/RB8
	_BV( 9 ),		//	63	RB9	AN9/C2OUT/RB9
	_BV( 10 ),		//	64	RB10	AN10/CVREFOUT/PMA13/RB10
	_BV( 11 ),		//	65	RB11	AN11/EREXERR/AETXERR/PMA12/RB11
	_BV( 12 ),		//	66	RB12	AN13/ERXD1/AECOL/PMA10/RB13
	_BV( 13 ),		//	67	RB13	AN12/ERXD0/AECRS/PMA11/RB12
	_BV( 14 ),		//	68	RB14	AN14/ERXD2/AETXD3/PMALH/PMA1/RB14
	_BV( 15 ),		//	69	RB15	AN15/ERXD3/AETXD2/OCFB/PMALL/PMA0/CN12/RB15
	//*	Pic32 EXTRAS start here (with #70)

	//*	Pic32 EXTRAS start here (with #70)
	_BV( 0 ),		//	70 RA0	TMS/RA0
	_BV( 1 ),		//	71 RA1	TCK/RA1
	_BV( 4 ),		//	72 RA4	TDI/RA4
	_BV( 5 ),		//	73 RA5	TDO/RA5
	_BV( 9 ),		//	74 RD9	SS1/IC2/RD9
	_BV( 13 ),		//	75 RC13	SOSCI/CN1/RC13
	_BV( 13 ),		//	76 RD13	ETXD3/PMD13/CN19/RD13
	_BV( 7 ),		//	77 RD7	ETXCLK/PMD15/CN16/RD7
	_BV( 1 ),		//	78 RG1	C2TX/ETXERR/PMD9/RG1
	_BV( 0 ),		//	79 RG0	C2RX/PMD8/RG0
	_BV( 6 ),		//	80 RA6	TRCLK/RA6
	_BV( 7 ),		//	81 RA7	TRD3/RA7
	_BV( 14 ),		//	82 RG14	TRD2/RG14
	_BV( 12 ),		//	83 RG12	TRD1/RG12
	_BV( 13 ),		//	84 RG13	TRD0/RG13
	_BV( 9 ),		//	85 RA9	VREF-/CVREF0/AERXD2/PMA7/RA9
	_BV( 1 ),		//	86 RC1	T2CK/RC1
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t digital_pin_to_timer_PGM[] = {
	NOT_ON_TIMER,		//	0 RF2	SDA1A/SDI1A/U1ARX/RF2
	NOT_ON_TIMER,		//	1 RF8	SCL1A/SDO1A/U1ATX/RF8
	NOT_ON_TIMER,		//	2 RE8	AERXD0/INT1/RE8
	_TIMER_OC1,			//	3 RD0	SDO1/OC1/INT0/RD0
	_TIMER_TCK1,		//	4 RC14	SOSCO/T1CK/CN0/RC14
	_TIMER_OC2,			//	5 RD1	OC2/RD1
	_TIMER_OC3,			//	6 RD2	OC3/RD2
	NOT_ON_TIMER,		//	7 RE9	AERXD1/INT2/RE9
	_TIMER_IC5,			//	8 RD12	ETXD2/IC5/PMD12/RD12
	_TIMER_OC4,			//	9 RD3	OC4/RD3
	_TIMER_OC5,			//	10 RD4	OC5/PMWR/CN13/RD4
	_TIMER_TCK5,		//	11 RC4	T5CK/SDI1/RC4
	NOT_ON_TIMER,		//	12 RA2	SCL2/RA2
	NOT_ON_TIMER,		//	13 RA3	SDA2/RA3
	NOT_ON_TIMER,		//	14 RF13	AC1TX/SCK3A/U3BTX/U3ARTS/RF13
	NOT_ON_TIMER,		//	15 RF12	AC1RX/SS3A/U3BRX/U3ACTS/RF12
	NOT_ON_TIMER,		//	16 RF5	SCL3A/SDO3A/U3ATX/PMA8/CN18/RF5
	NOT_ON_TIMER,		//	17 RF4	SDA3A/SDI3A/U3ARX/PMA9/CN17/RF4
	NOT_ON_TIMER,		//	18 RD15	AETXD1/SCK1A/U1BTX/U1ARTS/CN21/RD15
	NOT_ON_TIMER,		//	19 RD14	AETXD0/SS1A/U1BRX/U1ACTS/CN20/RD14
	NOT_ON_TIMER,		//	20 RA15	AETXEN/SDA1/INT4/RA15
	NOT_ON_TIMER,		//	21 RA14	AETXCLK/SCL1/INT3/RA14
	_TIMER_TCK3,		//	22 RC2	T3CK/AC2TX/RC2
	_TIMER_TCK4,		//	23 RC3	T4CK/AC2RX/RC3
	NOT_ON_TIMER,		//	24 VBUS
	NOT_ON_TIMER,		//	25 RF3	USBID/RF3
	NOT_ON_TIMER,		//	26 RG3	D-/RG3
	NOT_ON_TIMER,		//	27 RG2	D+/RG2
	NOT_ON_TIMER,		//	28 RG15
	NOT_ON_TIMER,		//	29 RG7	ECRS/SDA2A/SDI2A/U2ARX/PMA4/CN9/RG7
	NOT_ON_TIMER,		//	30 RE7	PMD7/RE7
	NOT_ON_TIMER,		//	31 RE6	PMD6/RE6
	NOT_ON_TIMER,		//	32 RE5	PMD5/RE5
	NOT_ON_TIMER,		//	33 RE4	PMD4/RE4
	NOT_ON_TIMER,		//	34 RE3	PMD3/RE3
	NOT_ON_TIMER,		//	35 RE2	PMD2/RE2
	NOT_ON_TIMER,		//	36 RE1	PMD1/RE1
	NOT_ON_TIMER,		//	37 RE0	PMD0/RE0
	_TIMER_IC3,			//	38 RD10	SCK1/IC3/PMCS2/PMA15/RD10
	NOT_ON_TIMER,		//	39 RD5	PMRD/CN14/RD5
	NOT_ON_TIMER,		//	40 RB11	AN11/EREXERR/AETXERR/PMA12/RB11
	NOT_ON_TIMER,		//	41 RB13	AN13/ERXD1/AECOL/PMA10/RB13
	NOT_ON_TIMER,		//	42 RB12	AN12/ERXD0/AECRS/PMA11/RB12
	NOT_ON_TIMER,		//	43 RG8	ERXDV/AERXDV/ECRSDV/AECRSDV/SCL2A/SDO2A/U2ATX/PMA3/CN10/RG8
	NOT_ON_TIMER,		//	44 RA10	VREF+/CVREF+/AERXD3/PMA6/RA10
	NOT_ON_TIMER,		//	45 RF0	C1RX/ETXD1/PMD11/RF0
	NOT_ON_TIMER,		//	46 RF1	C1TX/ETXD0/RMD10/RF1
	NOT_ON_TIMER,		//	47 RD6	ETXEN/PMD14/CN15/RD6
	_TIMER_IC1,			//	48 RD8	PTCC/EMDIO/AEMDIO/IC1/RD8
	_TIMER_IC4,			//	49 RD11	EMDC/AEMDC/IC4/PMCS1/PMA14/RD11
	NOT_ON_TIMER,		//	50 RG7	ECRX/SDA2/SDI2A/U2ARX/PMA4/CN9/RG7
	NOT_ON_TIMER,		//	51 RG8
	NOT_ON_TIMER,		//	52 RG6	ECOL/SCK2A/U2BTX/U2ARTS/PMA5/CN8/RG6
	NOT_ON_TIMER,		//	53 RG9	ERXCLK/AERXCLK/EREFCLK/AEREFCLK/SS2A/U2BRX/U2ACTS/PMA2/CN11/RG9
	//*	the analog ports start with 54
	NOT_ON_TIMER,		//	54	RB0	PGED1/AN0/CN2/RB0
	NOT_ON_TIMER,		//	55	RB1	PGEC1/AN1/CN3/RB1
	NOT_ON_TIMER,		//	56	RB2	AN2/C2IN-/CN4/RB2
	NOT_ON_TIMER,		//	57	RB3	AN3/C2IN+/CN5/RB3
	NOT_ON_TIMER,		//	58	RB4	AN4/C1IN-/CN6/RB4
	NOT_ON_TIMER,		//	59	RB5	AN5/C1IN+/VBUSON/CN7/RB5
	NOT_ON_TIMER,		//	60	RB6	PGEC2/AN6/OCFA/RB6
	NOT_ON_TIMER,		//	61	RB7	PGED2/AN7/RB7
	NOT_ON_TIMER,		//	62	RB8	AN8/C1OUT/RB8
	NOT_ON_TIMER,		//	63	RB9	AN9/C2OUT/RB9
	NOT_ON_TIMER,		//	64	RB10	AN10/CVREFOUT/PMA13/RB10
	NOT_ON_TIMER,		//	65	RB11	AN11/EREXERR/AETXERR/PMA12/RB11
	NOT_ON_TIMER,		//	66	RB12	AN13/ERXD1/AECOL/PMA10/RB13
	NOT_ON_TIMER,		//	67	RB13	AN12/ERXD0/AECRS/PMA11/RB12
	NOT_ON_TIMER,		//	68	RB14	AN14/ERXD2/AETXD3/PMALH/PMA1/RB14
	NOT_ON_TIMER,		//	69	RB15	AN15/ERXD3/AETXD2/OCFB/PMALL/PMA0/CN12/RB15

	//*	Pic32 EXTRAS start here (with #70)
	NOT_ON_TIMER,		//	70 RA0	TMS/RA0
	NOT_ON_TIMER,		//	71 RA1	TCK/RA1
	NOT_ON_TIMER,		//	72 RA4	TDI/RA4
	NOT_ON_TIMER,		//	73 RA5	TDO/RA5
	_TIMER_IC2,			//	74 RD9	SS1/IC2/RD9
	NOT_ON_TIMER,		//	75 RC13	SOSCI/CN1/RC13
	NOT_ON_TIMER,		//	76 RD13	ETXD3/PMD13/CN19/RD13
	NOT_ON_TIMER,		//	77 RD7	ETXCLK/PMD15/CN16/RD7
	NOT_ON_TIMER,		//	78 RG1	C2TX/ETXERR/PMD9/RG1
	NOT_ON_TIMER,		//	79 RG0	C2RX/PMD8/RG0
	NOT_ON_TIMER,		//	80 RA6	TRCLK/RA6
	NOT_ON_TIMER,		//	81 RA7	TRD3/RA7
	NOT_ON_TIMER,		//	82 RG14	TRD2/RG14
	NOT_ON_TIMER,		//	83 RG12	TRD1/RG12
	NOT_ON_TIMER,		//	84 RG13	TRD0/RG13
	NOT_ON_TIMER,		//	85 RA9	VREF-/CVREF0/AERXD2/PMA7/RA9
	NOT_ON_TIMER,		//	86 RC1	T2CK/RC1
};

/* ------------------------------------------------------------ */
/*		Include Files for Board Customization Functions			*/
/* ------------------------------------------------------------ */

#if	(OPT_BOARD_INIT != 0)
#include <plib.h>
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

	//*	Turn Secondary oscillator off
	//*	this is only needed on the mega board because the mega uses secondary
	// ocsilator pins as general I/O
	
	unsigned int dma_status;
	unsigned int int_status;
	
		mSYSTEMUnlock(int_status, dma_status);

		OSCCONCLR	=	_OSCCON_SOSCEN_MASK;


		mSYSTEMLock(int_status, dma_status);
	
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
