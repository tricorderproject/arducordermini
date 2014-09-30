/************************************************************************/
/*																		*/
/*	Board_Data.c --	Cmod Customization Data Declarations		        */
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with a CmodCK1 board using a	*/
/* PIC32 part in a 44-pin package.										*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/28/2011(GeneA): Created by splitting data out of Board_Defs.h	*/
/*  01/23/2013(KeithV): Modified for CK1 board                          */
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
    // Pins 0 through 38
    NOT_A_PIN,  //  0
    NOT_A_PIN,  //  1
    NOT_A_PIN,  //  2
    NOT_A_PIN,  //  3
    _IOPORT_PB, //  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
	_IOPORT_PC, //  5  RC6  RPC6/PMA1/RC6
	_IOPORT_PC, //  6  RC7  RPC7/PMA0/RC7
	_IOPORT_PC, //  7  RC8  RPC8/PMA5/RC8
	_IOPORT_PC, //  8  RC9  RPC9/CTED7/PMA6/RC9
    NOT_A_PIN,  //  9
	_IOPORT_PB, // 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
	_IOPORT_PB, // 11  RB11 PGEC2/RPB11/PMD1/RB11
	_IOPORT_PB, // 12  RB12 AN12/PMD0/RB12
	_IOPORT_PB, // 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
	_IOPORT_PA, // 14  RA10 PGED(4)/TMS/PMA10/RA10
	_IOPORT_PA, // 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
	_IOPORT_PB, // 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_IOPORT_PB, // 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_IOPORT_PA, // 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_IOPORT_PA, // 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_IOPORT_PB, // 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
	_IOPORT_PB, // 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
	_IOPORT_PB, // 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_IOPORT_PB, // 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
    _IOPORT_PC, // 24  RC0  AN6/RPC0/RC0
	_IOPORT_PC, // 25  RC1  AN7/RPC1/RC1
	_IOPORT_PC, // 26  RC2  AN8/RPC2/PMA2/RC2
	_IOPORT_PA, // 27  RA8  TDO/RPA8/PMA8/RA8
    NOT_A_PIN,  // 28
	_IOPORT_PB, // 29  RB4  SOSCI/RPB4/RB4
	_IOPORT_PA, // 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
	_IOPORT_PA, // 31  RA9  TDI/RPA9/PMA9/RA9
	_IOPORT_PC, // 32  RC3  RPC3/RC3
	_IOPORT_PC, // 33  RC4  RPC4/PMA4/RC4
	_IOPORT_PC, // 34  RC5  RPC5/PMA3/RC5
	_IOPORT_PB, // 35  RB5  PGED3/RPB5/PMD7/RB5
	_IOPORT_PB, // 36  RB6  PGEC3/RPB6/PMD6/RB6
	_IOPORT_PB, // 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
	_IOPORT_PB, // 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {
    // Pins 0 through 38
    NOT_A_PIN,   //  0
    NOT_A_PIN,   //  1
    NOT_A_PIN,   //  2
    NOT_A_PIN,   //  3
	_BV( 9 ) ,	 //  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
	_BV( 6 ) ,	 //  5  RC6  RPC6/PMA1/RC6
	_BV( 7 ),	 //  6  RC7  RPC7/PMA0/RC7
	_BV( 8 ),	 //  7  RC8  RPC8/PMA5/RC8
	_BV( 9 ) ,	 //  8  RC9  RPC9/CTED7/PMA6/RC9
    NOT_A_PIN,   //  9
	_BV( 10 ) ,	 // 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
	_BV( 11 ) ,	 // 11  RB11 PGEC2/RPB11/PMD1/RB11
	_BV( 12 ),	 // 12  RB12 AN12/PMD0/RB12
	_BV( 13 ),	 // 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
	_BV( 10 ) ,	 // 14  RA10 PGED(4)/TMS/PMA10/RA10
	_BV( 7 ) ,	 // 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
	_BV( 14 ) ,	 // 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_BV( 15 ) ,	 // 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_BV( 0 ) ,	 // 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_BV( 1 ) ,	 // 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_BV( 0 ) ,	 // 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
	_BV( 1 ) ,	 // 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
	_BV( 2 ) ,	 // 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_BV( 3 ) ,	 // 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	_BV( 0 ) ,	 // 24  RC0  AN6/RPC0/RC0
	_BV( 1 ) ,	 // 25  RC1  AN7/RPC1/RC1
	_BV( 2 ) ,	 // 26  RC2  AN8/RPC2/PMA2/RC2
	_BV( 8 ) ,	 // 27  RA8  TDO/RPA8/PMA8/RA8
    NOT_A_PIN,   // 28
	_BV( 4 ) ,	 // 29  RB4  SOSCI/RPB4/RB4
	_BV( 4 ) ,	 // 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
	_BV( 9 ) ,	 // 31  RA9  TDI/RPA9/PMA9/RA9
	_BV( 3 ) ,	 // 32  RC3  RPC3/RC3
	_BV( 4 ) ,	 // 33  RC4  RPC4/PMA4/RC4
	_BV( 5 ) ,	 // 34  RC5  RPC5/PMA3/RC5
	_BV( 5 ) ,	 // 35  RB5  PGED3/RPB5/PMD7/RB5
	_BV( 6 ) ,	 // 36  RB6  PGEC3/RPB6/PMD6/RB6
	_BV( 7 ) ,	 // 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
	_BV( 8 ) ,	 // 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t	digital_pin_to_timer_PGM[] = {
    // Pins 0 through 38
    NOT_A_PIN,      //  0
    NOT_A_PIN,      //  1
    NOT_A_PIN,      //  2
    NOT_A_PIN,      //  3
	_TIMER_OC3,	    //  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
	NOT_ON_TIMER,	//  5  RC6  RPC6/PMA1/RC6
	NOT_ON_TIMER,	//  6  RC7  RPC7/PMA0/RC7
	NOT_ON_TIMER,	//  7  RC8  RPC8/PMA5/RC8
	NOT_ON_TIMER,	//  8  RC9  RPC9/CTED7/PMA6/RC9
    NOT_A_PIN,      //  9
	_TIMER_IC2,	    // 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
	NOT_ON_TIMER,	// 11  RB11 PGEC2/RPB11/PMD1/RB11
	NOT_ON_TIMER,	// 12  RB12 AN12/PMD0/RB12
	_TIMER_OC5,	    // 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
	NOT_ON_TIMER,	// 14  RA10 PGED(4)/TMS/PMA10/RA10
	NOT_ON_TIMER,	// 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
	NOT_ON_TIMER,	// 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	NOT_ON_TIMER,   // 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_TIMER_TCK2,	// 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	NOT_ON_TIMER,	// 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	NOT_ON_TIMER,	// 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
	NOT_ON_TIMER,	// 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
	_TIMER_OC4,	    // 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	NOT_ON_TIMER,	// 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	NOT_ON_TIMER,	// 24  RC0  AN6/RPC0/RC0
	_TIMER_IC5,	    // 25  RC1  AN7/RPC1/RC1
	_TIMER_TCK5,	// 26  RC2  AN8/RPC2/PMA2/RC2
	_TIMER_TCK3,	// 27  RA8  TDO/RPA8/PMA8/RA8
    NOT_A_PIN,      // 28
	_TIMER_OC1 ,	// 29  RB4  SOSCI/RPB4/RB4
	_TIMER_TCK1,	// 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
	_TIMER_IC3,	    // 31  RA9  TDI/RPA9/PMA9/RA9
	_TIMER_TCK4,	// 32  RC3  RPC3/RC3
	NOT_ON_TIMER,	// 33  RC4  RPC4/PMA4/RC4
	NOT_ON_TIMER,	// 34  RC5  RPC5/PMA3/RC5
	NOT_ON_TIMER,	// 35  RB5  PGED3/RPB5/PMD7/RB5
    _TIMER_IC1,	    // 36  RB6  PGEC3/RPB6/PMD6/RB6
	_TIMER_IC4,	    // 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
	_TIMER_OC2,	    // 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8
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
    // Pins 0 through 38
    NOT_A_PIN,              //  0
    NOT_A_PIN,              //  1
    NOT_A_PIN,              //  2
    NOT_A_PIN,              //  3
	_PPS_OUT(_PPS_RPB9R),	//  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
	_PPS_OUT(_PPS_RPC6R),	//  5  RC6  RPC6/PMA1/RC6
	_PPS_OUT(_PPS_RPC7R),	//  6  RC7  RPC7/PMA0/RC7
	_PPS_OUT(_PPS_RPC8R),	//  7  RC8  RPC8/PMA5/RC8
	_PPS_OUT(_PPS_RPC9R),	//  8  RC9  RPC9/CTED7/PMA6/RC9
    NOT_A_PIN,              //  9
	_PPS_OUT(_PPS_RPB10R),	// 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
	_PPS_OUT(_PPS_RPB11R),	// 11  RB11 PGEC2/RPB11/PMD1/RB11
	NOT_PPS_PIN,	        // 12  RB12 AN12/PMD0/RB12
	_PPS_OUT(_PPS_RPB13R),	// 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
	NOT_PPS_PIN,	        // 14  RA10 PGED(4)/TMS/PMA10/RA10
	NOT_PPS_PIN,	        // 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
	_PPS_OUT(_PPS_RPB14R),	// 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_PPS_OUT(_PPS_RPB15R),	// 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_PPS_OUT(_PPS_RPA0R),	// 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_PPS_OUT(_PPS_RPA1R),	// 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_PPS_OUT(_PPS_RPB0R),	// 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
	_PPS_OUT(_PPS_RPB1R),	// 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
	_PPS_OUT(_PPS_RPB2R),	// 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_PPS_OUT(_PPS_RPB3R),	// 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	_PPS_OUT(_PPS_RPC0R),	// 24  RC0  AN6/RPC0/RC0
	_PPS_OUT(_PPS_RPC1R), 	// 25  RC1  AN7/RPC1/RC1
	_PPS_OUT(_PPS_RPC2R),	// 26  RC2  AN8/RPC2/PMA2/RC2
	_PPS_OUT(_PPS_RPA8R),	// 27  RA8  TDO/RPA8/PMA8/RA8
    NOT_A_PIN,              // 28
	_PPS_OUT(_PPS_RPB4R),	// 29  RB4  SOSCI/RPB4/RB4
	_PPS_OUT(_PPS_RPA4R),	// 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
	_PPS_OUT(_PPS_RPA9R),	// 31  RA9  TDI/RPA9/PMA9/RA9
	_PPS_OUT(_PPS_RPC3R),	// 32  RC3  RPC3/RC3
	_PPS_OUT(_PPS_RPC4R),	// 33  RC4  RPC4/PMA4/RC4
	_PPS_OUT(_PPS_RPC5R),	// 34  RC5  RPC5/PMA3/RC5
	_PPS_OUT(_PPS_RPB5R),	// 35  RB5  PGED3/RPB5/PMD7/RB5
	_PPS_OUT(_PPS_RPB6R),	// 36  RB6  PGEC3/RPB6/PMD6/RB6
	_PPS_OUT(_PPS_RPB7R),	// 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
	_PPS_OUT(_PPS_RPB8R),	// 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8
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
    // Pins 0 through 38
    NOT_A_PIN,              //  0
    NOT_A_PIN,              //  1
    NOT_A_PIN,              //  2
    NOT_A_PIN,              //  3
	_PPS_IN(_PPS_RPB9),	    //  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
	_PPS_IN(_PPS_RPC6),	    //  5  RC6  RPC6/PMA1/RC6
	_PPS_IN(_PPS_RPC7),	    //  6  RC7  RPC7/PMA0/RC7
	_PPS_IN(_PPS_RPC8),	    //  7  RC8  RPC8/PMA5/RC8
	_PPS_IN(_PPS_RPC9),	    //  8  RC9  RPC9/CTED7/PMA6/RC9
    NOT_A_PIN,              //  9
	_PPS_IN(_PPS_RPB10),	// 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
	_PPS_IN(_PPS_RPB11),	// 11  RB11 PGEC2/RPB11/PMD1/RB11
	NOT_PPS_PIN,	        // 12  RB12 AN12/PMD0/RB12
	_PPS_IN(_PPS_RPB13),	// 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
	NOT_PPS_PIN,	        // 14  RA10 PGED(4)/TMS/PMA10/RA10
	NOT_PPS_PIN,	        // 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
	_PPS_IN(_PPS_RPB14),	// 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_PPS_IN(_PPS_RPB15),	// 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_PPS_IN(_PPS_RPA0),	    // 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_PPS_IN(_PPS_RPA1),	    // 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_PPS_IN(_PPS_RPB0),	    // 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
	_PPS_IN(_PPS_RPB1),	    // 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
	_PPS_IN(_PPS_RPB2),	    // 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_PPS_IN(_PPS_RPB3),	    // 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	_PPS_IN(_PPS_RPC0),	    // 24  RC0  AN6/RPC0/RC0
	_PPS_IN(_PPS_RPC1), 	// 25  RC1  AN7/RPC1/RC1
	_PPS_IN(_PPS_RPC2),	    // 26  RC2  AN8/RPC2/PMA2/RC2
	_PPS_IN(_PPS_RPA8),	    // 27  RA8  TDO/RPA8/PMA8/RA8
    NOT_A_PIN,              // 28
	_PPS_IN(_PPS_RPB4),	    // 29  RB4  SOSCI/RPB4/RB4
	_PPS_IN(_PPS_RPA4),	    // 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
	_PPS_IN(_PPS_RPA9),	    // 31  RA9  TDI/RPA9/PMA9/RA9
	_PPS_IN(_PPS_RPC3),	    // 32  RC3  RPC3/RC3
	_PPS_IN(_PPS_RPC4),	    // 33  RC4  RPC4/PMA4/RC4
	_PPS_IN(_PPS_RPC5),	    // 34  RC5  RPC5/PMA3/RC5
	_PPS_IN(_PPS_RPB5),	    // 35  RB5  PGED3/RPB5/PMD7/RB5
	_PPS_IN(_PPS_RPB6),	    // 36  RB6  PGEC3/RPB6/PMD6/RB6
	_PPS_IN(_PPS_RPB7),	    // 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
	_PPS_IN(_PPS_RPB8),	    // 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
//#if defined(_NOT_USED_)
const uint8_t digital_pin_to_analog_PGM[] = {
    // Pins 0 through 38
    NOT_A_PIN,          //  0
    NOT_A_PIN,          //  1
    NOT_A_PIN,          //  2
    NOT_A_PIN,          //  3
	NOT_ANALOG_PIN,     //  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
	NOT_ANALOG_PIN,	    //  5  RC6  RPC6/PMA1/RC6
	NOT_ANALOG_PIN,	    //  6  RC7  RPC7/PMA0/RC7
	NOT_ANALOG_PIN,     //  7  RC8  RPC8/PMA5/RC8
	NOT_ANALOG_PIN,	    //  8  RC9  RPC9/CTED7/PMA6/RC9
    NOT_A_PIN,          //  9
	NOT_ANALOG_PIN,	    // 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
	NOT_ANALOG_PIN,	    // 11  RB11 PGEC2/RPB11/PMD1/RB11
	_BOARD_AN12,	    // 12  RB12 AN12/PMD0/RB12
	_BOARD_AN11,	    // 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
	NOT_ANALOG_PIN,	    // 14  RA10 PGED(4)/TMS/PMA10/RA10
	NOT_ANALOG_PIN,	    // 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
	_BOARD_AN10,	    // 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
	_BOARD_AN9,	        // 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_BOARD_AN0,	        // 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
	_BOARD_AN1,	        // 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
	_BOARD_AN2,	        // 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
	_BOARD_AN3,	        // 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
	_BOARD_AN4,	        // 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
	_BOARD_AN5,	        // 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
	_BOARD_AN6,	        // 24  RC0  AN6/RPC0/RC0
	_BOARD_AN7,	        // 25  RC1  AN7/RPC1/RC1
	_BOARD_AN8,	        // 26  RC2  AN8/RPC2/PMA2/RC2
	NOT_ANALOG_PIN,	    // 27  RA8  TDO/RPA8/PMA8/RA8
    NOT_A_PIN,          // 28
	NOT_ANALOG_PIN,	    // 29  RB4  SOSCI/RPB4/RB4
	NOT_ANALOG_PIN,	    // 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
	NOT_ANALOG_PIN,	    // 31  RA9  TDI/RPA9/PMA9/RA9
	NOT_ANALOG_PIN,	    // 32  RC3  RPC3/RC3
	NOT_ANALOG_PIN,	    // 33  RC4  RPC4/PMA4/RC4
	NOT_ANALOG_PIN,	    // 34  RC5  RPC5/PMA3/RC5
	NOT_ANALOG_PIN,	    // 35  RB5  PGED3/RPB5/PMD7/RB5
	NOT_ANALOG_PIN,	    // 36  RB6  PGEC3/RPB6/PMD6/RB6
	NOT_ANALOG_PIN,     // 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
	NOT_ANALOG_PIN,     // 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8
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
};
//#endif

/* ------------------------------------------------------------ */
/* This table maps from an output compare number as stored in the
** digital_pin_to_timer_PGM table to the digital pin number of the
** pin that OC is connected to. This table is only required for
** devices that support peripheral pin select (PPS), i.e. PIC32MX1xx/2xx
** devices.
*/

const uint8_t output_compare_to_digital_pin_PGM[] = {
	PIN_OC1,	// RPB4 (RPB4R = 5)	
	PIN_OC2,	// RPB8 (RPB8R = 5)
	PIN_OC3,	// RPB9 (RPB9R = 5)
	PIN_OC4,	// RPB2 (RPB2R = 5)
	PIN_OC5,	// RPB13(RPB13R = 6)	
};

/* ------------------------------------------------------------ */
/* This table maps from an external interrupt number to the digital
** pin for that interrupt.
*/

const uint8_t external_int_to_digital_pin_PGM[] = {
	NOT_PPS_PIN,		// INT0 is not mappable; RB7
	PIN_INT1,			// RPC4 J2-07, RC4 used for UART2 INT (INT1R = 7)
	PIN_INT2,			// RPB13 (INT2R = 3)
	PIN_INT3,			// RPC8 J1-07, RC8 used for SPI1 INT (INT3R = 6)
	PIN_INT4			// RPB7 (INT4R = 4)
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
