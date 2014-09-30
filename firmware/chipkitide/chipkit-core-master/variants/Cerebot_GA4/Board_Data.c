/************************************************************************/
/*																		*/
/*	Board_Data.c -- Board Customization Data for Digilent Cerebot GA4	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent Cerebot	GA4	*/
/* board.																*/
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
	_IOPORT_PB,		//	0  RB12		AN12/PMD0/RB12
	_IOPORT_PB,		//	1  RB11		PGEC2/RPB11/PMD1/RB11
	_IOPORT_PB,		//	2  RB10		PGED2/RPB10/CTED11/PMD2/RB10
	_IOPORT_PB,		//	3  RB9		RPB9/SDA1/CTED4/PMD3/RB9
	_IOPORT_PB,		//	4  RB8		RPB8/SCL1/CTED10/PMD4/RB8
	_IOPORT_PB,		//	5  RB7		RPB&/CTED3/PMD5/INT0/RB7
	_IOPORT_PB,		//	6  RB6		PGEC3/RPB6/PMD6/RB6
	_IOPORT_PB,		//	7  RB5		PGED3/PRB5/PMD7/RB5
	
	//Connector JB
	_IOPORT_PC,		//	8  RC2		AN8/RPC2/PMA2/RC2
	_IOPORT_PC,		//	9  RC5		RPC5/PMA3/RC5
	_IOPORT_PC,		//	10 RC4		RPC4/PMA4/RC4
	_IOPORT_PC,		//	11 RC8		RPC8/PMA5/RC8
	_IOPORT_PC,		//	12 RC7		RPC7/PMA0/RC7
	_IOPORT_PB,		//	13 RB13		AN11/RPB13/CTPLS/PMRD/RB13	
	_IOPORT_PB,		//	14 RB14		CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_IOPORT_PC,		//	15 RC6		RPC6/PMA1/RC6
	
	//Connector JC
	_IOPORT_PB,		//	16 RB4		SOSCI/RPB4/RB4
	_IOPORT_PC,		//	17 RB15		AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_IOPORT_PC, 	//	18 RC3		RPC3/RC3
	_IOPORT_PC,		//	19 RC9		RPC9/CTED7/PMA6/RC9
	_IOPORT_PA,		//	20 RA7		PGEC/TCK/CTED8/PMA7/RA7
	_IOPORT_PA,		//	21 RA8		TDO/RPA8/PMA8/RA8
	_IOPORT_PA,		//	22 RA9		TDI/RPA9/PMA9/RA9
	_IOPORT_PA,		//	23 RA10		PGED/TMS/PMA10/RA10
	
	//Connector JD
	_IOPORT_PA,		//	24 RA0		VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_IOPORT_PA,		//	25 RA1		VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_IOPORT_PC,		//	26 RC0		AN6/RPC0/RC0
	_IOPORT_PC,		//	27 RC1		AN7/RPC1/RC1
	
	//I2C connector J2
	_IOPORT_PB,		//	28 RB2		AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_IOPORT_PB,		//	29 RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3

	//User input jumper JP5 (treated like a switch)
	_IOPORT_PA		//	30 RA4		SOSCO/T1CK/CN0/RA4
	
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t digital_pin_to_bit_mask_PGM[] = {
	//Connector JA
	_BV( 12 ) ,		//	0  RB12		AN12/PMD0/RB12
	_BV( 11 ) ,		//	1  RB11		PGEC2/RPB11/PMD1/RB11
	_BV( 10 ) ,		//	2  RB10		PGED2/RPB10/CTED11/PMD2/RB10
	_BV( 9 ) ,		//	3  RB9		RPB9/SDA1/CTED4/PMD3/RB9
	_BV( 8 ) ,		//	4  RB8		RPB8/SCL1/CTED10/PMD4/RB8
	_BV( 7 ) ,		//	5  RB7		RPB&/CTED3/PMD5/INT0/RB7
	_BV( 6 ) ,		//	6  RB6		PGEC3/RPB6/PMD6/RB6
	_BV( 5 ) ,		//	7  RB5		PGED3/PRB5/PMD7/RB5
	
	//Connector JB
	_BV( 2 ) ,		//	8  RC2		AN8/RPC2/PMA2/RC2
	_BV( 5 ) ,		//	9  RC5		RPC5/PMA3/RC5
	_BV( 4 ) ,		//	10 RC4		RPC4/PMA4/RC4
	_BV( 8 ) ,		//	11 RC8		RPC8/PMA5/RC8
	_BV( 7 ) ,		//	12 RC7		RPC7/PMA0/RC7
	_BV( 13 ) ,		//	13 RB13		AN11/RPB13/CTPLS/PMRD/RB13	
	_BV( 14 ) ,		//	14 RB14		CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_BV( 6 ) ,		//	15 RC6		RPC6/PMA1/RC6
	
	//Connector JC
	_BV( 4 ) ,		//	16 RB4		SOSCI/RPB4/RB4
	_BV( 15 ) ,		//	17 RB15		AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_BV( 3 ) , 		//	18 RC3		RPC3/RC3
	_BV( 9 ),		//	19 RC9		RPC9/CTED7/PMA6/RC9
	_BV( 7 ) ,		//	20 RA7		PGEC/TCK/CTED8/PMA7/RA7
	_BV( 8 ) ,		//	21 RA8		TDO/RPA8/PMA8/RA8
	_BV( 9 ) ,		//	22 RA9		TDI/RPA9/PMA9/RA9
	_BV( 10 ) ,		//	23 RA10		PGED/TMS/PMA10/RA10
	
	//Connector JD
	_BV( 0 ) ,		//	24 RA0		VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_BV( 1 ) ,		//	25 RA1		VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_BV( 0 ) ,		//	26 RC0		AN6/RPC0/RC0
	_BV( 1 ) ,		//	27 RC1		AN7/RPC1/RC1
	
	//I2C Connector J2
	_BV( 2 ) ,		//	28 RB2		AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_BV( 3 ) ,		//	29 RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	
	//User input jumper JP5 (treated like a switch)
	_BV( 4 ) ,		//	30 RA4		SOSCO/T1CK/CN0/RA4
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t digital_pin_to_timer_PGM[] = {
	// Connector JA
	NOT_ON_TIMER,		//	0  RB12		AN12/PMD0/RB12	
	NOT_ON_TIMER,		//	1  RB11		PGEC2/RPB11/PMD1/RB11	
	NOT_ON_TIMER,		//	2  RB10		PGED2/RPB10/CTED11/PMD2/RB10	
	NOT_ON_TIMER,		//	3  RB9		RPB9/SDA1/CTED4/PMD3/RB9	
	NOT_ON_TIMER,		//	4  RB8		RPB8/SCL1/CTED10/PMD4/RB8	
	NOT_ON_TIMER,		//	5  RB7		RPB&/CTED3/PMD5/INT0/RB7	
	NOT_ON_TIMER,		//	6  RB6		PGEC3/RPB6/PMD6/RB6	
	NOT_ON_TIMER,		//	7  RB5		PGED3/PRB5/PMD7/RB5	
	
	// Connector JB
	NOT_ON_TIMER,		//	8  RC2		AN8/RPC2/PMA2/RC2	
	_TIMER_OC1,			//	9  RC5		RPC5/PMA3/RC5	
	NOT_ON_TIMER,		//	10 RC4		RPC4/PMA4/RC4	
	NOT_ON_TIMER,		//	11 RC8		RPC8/PMA5/RC8	
	NOT_ON_TIMER,		//	12 RC7		RPC7/PMA0/RC7	
	_TIMER_OC4,			//	13 RB13		AN11/RPB13/CTPLS/PMRD/RB13		
	NOT_ON_TIMER,		//	14 RB14		CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14	
	NOT_ON_TIMER,		//	15 RC6		RPC6/PMA1/RC6	
	
	// Connector JC
	NOT_ON_TIMER,		//	16 RB4		SOSCI/RPB4/RB4	
	NOT_ON_TIMER,		//	17 RB15		AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15	
	NOT_ON_TIMER, 		//	18 RC3		RPC3/RC3	
	_TIMER_OC3,			//	19 RC9		RPC9/CTED7/PMA6/RC9	
	NOT_ON_TIMER,		//	20 RA7		PGEC/TCK/CTED8/PMA7/RA7	
	NOT_ON_TIMER,		//	21 RA8		TDO/RPA8/PMA8/RA8	
	NOT_ON_TIMER,		//	22 RA9		TDI/RPA9/PMA9/RA9	
	NOT_ON_TIMER,		//	23 RA10		PGED/TMS/PMA10/RA10	
	
	// Connector JD
	NOT_ON_TIMER,		//	24 RA0		VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0	
	_TIMER_OC2,			//	25 RA1		VREF-/CVREF-/AN1/RPA1/CTED2/RA1	
	NOT_ON_TIMER,		//	26 RC0		AN6/RPC0/RC0	
	_TIMER_OC5,			//	27 RC1		AN7/RPC1/RC1	

	// I2C Connector J2
	NOT_ON_TIMER,		//	28 RB2		AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2	
	NOT_ON_TIMER,		//	29 RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3	

	//User input jumper JP5 (treated like a switch)
	NOT_ON_TIMER		//	30 RA4		SOSCO/T1CK/CN0/RA4
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** PPS register. This register is used to select the peripheral output
** connected to the pin. The register is set to 0 to disconnedt the
** pin from any peripheral so it can be used as GPIO.
** For PIC32MX1xx/2xx series devices, the PPS output select registers
** are arranged as a contiguous series of 32 bit registers. This table
** treats these registers as an array of DWORDs an stores the index
** to the register.
*/
const uint8_t digital_pin_to_pps_out_PGM[] = {
	NOT_PPS_PIN,			//	0	RB12	AN12/PMD0/RB12
	_PPS_OUT(_PPS_RPB11R),	//	1	RB11	PGEC2/RPB11/PMD1/RB11
	_PPS_OUT(_PPS_RPB10R),	//	2	RB10	PGED2/RPB10/CTED11/PMD2/RB10
	_PPS_OUT(_PPS_RPB9R),	//	3	RB9		RPB9/SDA1/CTED4/PMD3/RB9
	_PPS_OUT(_PPS_RPB8R),	//	4	RB8		RPB8/SCL1/CTED10/PMD4/RB8
	_PPS_OUT(_PPS_RPB7R),	//	5	RB7		RPB7/CTED3/PMD5/INT0/RB7
	_PPS_OUT(_PPS_RPB6R),	//	6	RB6		PGEC3/RPB6/PMD6/RB6
	_PPS_OUT(_PPS_RPB5R),	//	7	RB5		PGED3/PRB5/PMD7/RB5
	
	// Connector JB
	_PPS_OUT(_PPS_RPC2R),	//	8	RC2		AN8/RPC2/PMA2/RC2
	_PPS_OUT(_PPS_RPC5R),	//	9	RC5		RPC5/PMA3/RC5
	_PPS_OUT(_PPS_RPC4R),	//	10	RC4		RPC4/PMA4/RC4
	_PPS_OUT(_PPS_RPC8R),	//	11	RC8		RPC8/PMA5/RC8
	_PPS_OUT(_PPS_RPC7R),	//	12	RC7		RPC7/PMA0/RC7
	_PPS_OUT(_PPS_RPB13R),	//	13	RB13	AN11/RPB13/CTPLS/PMRD/RB13	
	_PPS_OUT(_PPS_RPB14R),	//	14	RB14	CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_PPS_OUT(_PPS_RPC6R),	//	15	RC6		RPC6/PMA1/RC6
	
	// Connector JC
	_PPS_OUT(_PPS_RPB4R),	//	16	RB4		SOSCI/RPB4/RB4
	_PPS_OUT(_PPS_RPB15R),	//	17	RB15	AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_PPS_OUT(_PPS_RPC3R), 	//	18	RC3		RPC3/RC3
	_PPS_OUT(_PPS_RPC9R),	//	19	RC9		RPC9/CTED7/PMA6/RC9
	NOT_PPS_PIN,			//	20	RA7		PGEC/TCK/CTED8/PMA7/RA7
	_PPS_OUT(_PPS_RPA8R),	//	21	RA8		TDO/RPA8/PMA8/RA8
	_PPS_OUT(_PPS_RPA9R),	//	22	RA9		TDI/RPA9/PMA9/RA9
	NOT_PPS_PIN,			//	23 RA10		PGED/TMS/PMA10/RA10
	
	// Connector JD
	_PPS_OUT(_PPS_RPA0R),	//	24	RA0		VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_PPS_OUT(_PPS_RPA1R),	//	25	RA1		VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_PPS_OUT(_PPS_RPC0R),	//	26	RC0		AN6/RPC0/RC0
	_PPS_OUT(_PPS_RPC1R),	//	27	RC1		AN7/RPC1/RC1

	// I2C Connector J2
	_PPS_OUT(_PPS_RPB2R),	//	28	RB2		AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_PPS_OUT(_PPS_RPB3R),	//	29	RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3	

	//User input jumper JP5 (treated like a switch)
	_PPS_OUT(_PPS_RPA4R)	//	30 RA4		SOSCO/T1CK/CN0/RA4
};

/* ------------------------------------------------------------ */
/* This table maps from the digital pin number to the value to be
** loaded into a PPS input select register to select that pin.
** It also maps from digital pin number to input/output pin set to 
** which the pin belongs. The set mask is in the high four bits,
** the select value is in the low four bits.
** Note: if the PIC32 device has more than four pin sets, or more than
** 16 pin mapping choices per input function, then this table will have
** to be redefined as a table of uint16_t values and the macros used to
** access the table redefined as well.
*/
const uint8_t digital_pin_to_pps_in_PGM[] = {
	NOT_PPS_PIN,			//	0	RB12	AN12/PMD0/RB12
	_PPS_IN(_PPS_RPB11),	//	1	RB11	PGEC2/RPB11/PMD1/RB11
	_PPS_IN(_PPS_RPB10),	//	2	RB10	PGED2/RPB10/CTED11/PMD2/RB10
	_PPS_IN(_PPS_RPB9),		//	3	RB9		RPB9/SDA1/CTED4/PMD3/RB9
	_PPS_IN(_PPS_RPB8),		//	4	RB8		RPB8/SCL1/CTED10/PMD4/RB8
	_PPS_IN(_PPS_RPB7),		//	5	RB7		RPB7/CTED3/PMD5/INT0/RB7
	_PPS_IN(_PPS_RPB6),		//	6	RB6		PGEC3/RPB6/PMD6/RB6
	_PPS_IN(_PPS_RPB5),		//	7	RB5		PGED3/PRB5/PMD7/RB5
	
	// Connector JB
	_PPS_IN(_PPS_RPC2),		//	8	RC2		AN8/RPC2/PMA2/RC2
	_PPS_IN(_PPS_RPC5),		//	9	RC5		RPC5/PMA3/RC5
	_PPS_IN(_PPS_RPC4),		//	10	RC4		RPC4/PMA4/RC4
	_PPS_IN(_PPS_RPC8),		//	11	RC8		RPC8/PMA5/RC8
	_PPS_IN(_PPS_RPC7),		//	12	RC7		RPC7/PMA0/RC7
	_PPS_IN(_PPS_RPB13),	//	13	RB13	AN11/RPB13/CTPLS/PMRD/RB13	
	_PPS_IN(_PPS_RPB14),	//	14	RB14	CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_PPS_IN(_PPS_RPC6),		//	15	RC6		RPC6/PMA1/RC6
	
	// Connector JC
	_PPS_IN(_PPS_RPB4),		//	16	RB4		SOSCI/RPB4/RB4
	_PPS_IN(_PPS_RPB15),	//	17	RB15	AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_PPS_IN(_PPS_RPC3), 	//	18	RC3		RPC3/RC3
	_PPS_IN(_PPS_RPC9),		//	19	RC9		RPC9/CTED7/PMA6/RC9
	NOT_PPS_PIN,			//	20	RA7		PGEC/TCK/CTED8/PMA7/RA7
	_PPS_IN(_PPS_RPA8),		//	21	RA8		TDO/RPA8/PMA8/RA8
	_PPS_IN(_PPS_RPA9),		//	22	RA9		TDI/RPA9/PMA9/RA9
	NOT_PPS_PIN,			//	23 RA10		PGED/TMS/PMA10/RA10
	
	// Connector JD
	_PPS_IN(_PPS_RPA0),		//	24	RA0		VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_PPS_IN(_PPS_RPA1),		//	25	RA1		VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_PPS_IN(_PPS_RPC0),		//	26	RC0		AN6/RPC0/RC0
	_PPS_IN(_PPS_RPC1),		//	27	RC1		AN7/RPC1/RC1

	// I2C Connector J2
	_PPS_IN(_PPS_RPB2),		//	28	RB2		AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_PPS_IN(_PPS_RPB3),		//	29	RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3	

	//User input jumper JP5 (treated like a switch)
	_PPS_IN(_PPS_RPA4)	//	30 RA4		SOSCO/T1CK/CN0/RA4
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
const uint8_t digital_pin_to_analog_PGM[] = {
	// Connector JA
	NOT_ANALOG_PIN,		//	0  RB12		AN12/PMD0/RB12
	NOT_ANALOG_PIN,		//	1  RB11		PGEC2/RPB11/PMD1/RB11
	NOT_ANALOG_PIN,		//	2  RB10		PGED2/RPB10/CTED11/PMD2/RB10
	NOT_ANALOG_PIN,		//	3  RB9		RPB9/SDA1/CTED4/PMD3/RB9
	NOT_ANALOG_PIN,		//	4  RB8		RPB8/SCL1/CTED10/PMD4/RB8
	NOT_ANALOG_PIN,		//	5  RB7		RPB7/CTED3/PMD5/INT0/RB7
	NOT_ANALOG_PIN,		//	6  RB6		PGEC3/RPB6/PMD6/RB6
	NOT_ANALOG_PIN,		//	7  RB5		PGED3/PRB5/PMD7/RB5
	
	// Connector JB
	NOT_ANALOG_PIN,		//	8  RC2		AN8/RPC2/PMA2/RC2
	NOT_ANALOG_PIN,		//	9  RC5		RPC5/PMA3/RC5
	NOT_ANALOG_PIN,		//	10 RC4		RPC4/PMA4/RC4
	NOT_ANALOG_PIN,		//	11 RC8		RPC8/PMA5/RC8
	NOT_ANALOG_PIN,		//	12 RC7		RPC7/PMA0/RC7
	NOT_ANALOG_PIN,		//	13 RB13		AN11/RPB13/CTPLS/PMRD/RB13	
	NOT_ANALOG_PIN,		//	14 RB14		CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	NOT_ANALOG_PIN,		//	15 RC6		RPC6/PMA1/RC6
	
	// Connector JC
	NOT_ANALOG_PIN,		//	16 RB4		SOSCI/RPB4/RB4
	NOT_ANALOG_PIN,		//	17 RB15		AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	NOT_ANALOG_PIN, 	//	18 RC3		RPC3/RC3
	NOT_ANALOG_PIN,		//	19 RC9		RPC9/CTED7/PMA6/RC9
	NOT_ANALOG_PIN,		//	20 RA7		PGEC/TCK/CTED8/PMA7/RA7
	NOT_ANALOG_PIN,		//	21 RA8		TDO/RPA8/PMA8/RA8
	NOT_ANALOG_PIN,		//	22 RA9		TDI/RPA9/PMA9/RA9
	NOT_ANALOG_PIN,		//	23 RA10		PGED/TMS/PMA10/RA10
	
	// Connector JD
	_BOARD_AN0,			//	24 RA0		VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_BOARD_AN1,			//	25 RA1		VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_BOARD_AN2,			//	26 RC0		AN6/RPC0/RC0
	_BOARD_AN3,			//	27 RC1		AN7/RPC1/RC1

	// I2C Connector J2
	NOT_ANALOG_PIN,		//	28 RB2		AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	NOT_ANALOG_PIN,		//	29 RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	
	//User input jumper JP5 (treated like a switch)
	NOT_ANALOG_PIN		//	30 RA4		SOSCO/T1CK/CN0/RA4
};

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
*/
const uint8_t analog_pin_to_channel_PGM[] = {
			//*	chipKIT Pin		PIC32 Analog channel
	0,		//*	A0						AN0
	1,		//*	A1						AN1
	6,		//*	A2						AN6
	7,		//*	A3						AN7
};

/* ------------------------------------------------------------ */
/* This table maps from an output compare number as stored in the
** digital_pin_to_timer_PGM table to the digital pin number of the
** pin that OC is connected to. This table is only required for
** devices that support peripheral pin select (PPS), i.e. PIC32MX1xx/2xx
** devices.
*/
const uint8_t output_compare_to_digital_pin_PGM[] = {
	NOT_PPS_PIN,		// not used
	9,					// OC1, JB-02
	25,					// OC2, JD-02
	19,					// OC3, JC-04
	13,					// OC4, JB-08
	27					// OC5, JD-04
};

/* ------------------------------------------------------------ */
/* This table maps from an external interrupt number to the digital
** pin for that interrupt.
*/
const uint8_t external_int_to_digital_pin_PGM[] = {
	NOT_PPS_PIN,			// INT0 is not mappable
	10,					// INT1, JB-03
	15,					// INT2, JB-10
	22,					// INT3, JC-09
	12					// INT4, JB-07
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

	ANSELA = 0;
	ANSELB = 0;
	ANSELC = 0;

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
