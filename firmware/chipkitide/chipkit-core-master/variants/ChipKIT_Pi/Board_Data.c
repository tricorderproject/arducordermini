/************************************************************************/
/*																		*/
/*	Board_Data.c --	ChipKit PI Customization Data Declarations		    */
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
/*  03/26/2013(KeithV): Modified for DP32 board                         */
/*  06/14/2013(BrianS): Modified for ChipKIT Pi board                   */
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
    // Pins 0 through 18
    _IOPORT_PA, //  0   RA4  	SOSCO/RPA4/T1CK/CTED9/PMA1/RA4
    _IOPORT_PB, //  1   RB4     SOSCI/RPB4/RB4
    _IOPORT_PB, //  2   RB5     TMS/RPB5/USBID/RB5
    _IOPORT_PB, //  3   RB13    AN11/RPB13/CTPLS/PMRD/RB13 
	_IOPORT_PB, //  4   RB1    	PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1
	_IOPORT_PB, //  5   RB0    	PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0
	_IOPORT_PA, //  6   RA2    	OSC1/CLKI/RPA2/RA2
	_IOPORT_PA, //  7   RA3    	OSC2/CLKO/RPA3/PMA0/RA3
	_IOPORT_PB, //  8   RB10	PGED2/RPB10/D+/CTED11/RB10
    _IOPORT_PB, //  9   RB11    PGEC2/RPB11/D-/RB11 
	_IOPORT_PB, // 10   RB7     TDI/RPB7/CTED3/PMD5/INT0/RB7
	_IOPORT_PA, // 11   RA1     PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1
	_IOPORT_PB, // 12   RB8     TCK/RPB8/SCL1/CTED10/PMD4/RB8
	_IOPORT_PB, // 13   RB14    CVREF/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 
	_IOPORT_PA, // 14   RA0    	PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0
	_IOPORT_PB, // 15   RB15    AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_IOPORT_PB, // 16   RB2    	AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2
	_IOPORT_PB, // 17   RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3
	_IOPORT_PB,	// 18	RB9		TDO/RPB9/SDA1/CTED4/PMD3/RB9
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t	digital_pin_to_bit_mask_PGM[] = {
    // Pins 0 through 18
    _BV( 4 ) ,   //  0   RA4  	SOSCO/RPA4/T1CK/CTED9/PMA1/RA4
    _BV( 4 ) ,   //  1   RB4    SOSCI/RPB4/RB4
    _BV( 5 ) ,   //  2   RB5    TMS/RPB5/USBID/RB5
    _BV( 13 ) ,  //  3   RB13   AN11/RPB13/CTPLS/PMRD/RB13 
	_BV( 1 ) ,	 //  4   RB1    PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1
	_BV( 0 ) ,	 //  5   RB0    PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0
	_BV( 2 ),	 //  6   RA2    OSC1/CLKI/RPA2/RA2
	_BV( 3 ),	 //  7   RA3    OSC2/CLKO/RPA3/PMA0/RA3
	_BV( 10 ) ,	 //  8   RB10	PGED2/RPB10/D+/CTED11/RB10
    _BV( 11 ) ,  //  9   RB11   PGEC2/RPB11/D-/RB11 
	_BV( 7 ) ,	 // 10   RB7    TDI/RPB7/CTED3/PMD5/INT0/RB7
	_BV( 1 ) ,	 // 11   RA1    PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1
	_BV( 8 ),	 // 12   RB8    TCK/RPB8/SCL1/CTED10/PMD4/RB8
	_BV( 14 ),	 // 13   RB14   CVREF/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 
	_BV( 0 ) ,	 // 14   RA0    PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0
	_BV( 15 ) ,	 // 15   RB15   AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_BV( 2 ) ,	 // 16   RB2    AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2
	_BV( 3 ) ,	 // 17   RB3	AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3
	_BV( 9 ) ,	 // 18	 RB9	TDO/RPB9/SDA1/CTED4/PMD3/RB9
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint8_t	digital_pin_to_timer_PGM[] = {
    // Pins 0 through 18
    NOT_ON_TIMER,                           //  0   J4-1    RA4  	SOSCO/RPA4/T1CK/CTED9/PMA1/RA4
    NOT_ON_TIMER,                           //  1   J4-2    RB4    	SOSCI/RPB4/RB4
    _TIMER_OC2  | _TIMER_IC3,               //  2   J4-3    RB5    	TMS/RPB5/USBID/RB5
    _TIMER_OC3  | _TIMER_TCK5,              //  3   J4-4    RB13   	AN11/RPB13/CTPLS/PMRD/RB13 
	NOT_ON_TIMER,	                        //  4   J4-5    RB1    	PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1
	NOT_ON_TIMER,	                        //  5   J4-6    RB0    	PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0
	_TIMER_OC5  | _TIMER_TCK4 | _TIMER_IC1, //  6   J4-7    RA2    	OSC1/CLKI/RPA2/RA2
	NOT_ON_TIMER,	                        //  7   J4-8    RA3    	OSC2/CLKO/RPA3/PMA0/RA3
	_TIMER_OC1,	                            //  8   J4-9    RB10	PGED2/RPB10/D+/CTED11/RB10
    NOT_ON_TIMER,                           //  9   J3-1    RB11   	PGEC2/RPB11/D-/RB11 
	NOT_ON_TIMER,	                        // 10   J3-2    RB7    	TDI/RPB7/CTED3/PMD5/INT0/RB7
	_TIMER_IC2,	                            // 11   J3-3    RA1    	PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1
	_TIMER_TCK3,	                        // 12   J3-4    RB8    	TCK/RPB8/SCL1/CTED10/PMD4/RB8
	_TIMER_OC4  | _TIMER_IC5,	            // 13   J3-5    RB14   	CVREF/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 
	_TIMER_TCK2 | _TIMER_IC4,	            // 14   J3-6    RA0    	PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0
	NOT_ON_TIMER,	                        // 15   J3-7    RB15   	AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	NOT_ON_TIMER,	                        // 16   J3-8    RB2    	AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2
	NOT_ON_TIMER,                           // 17   J3-9    RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3
	_TIMER_TCK1,	                        // 18   J3-10   RB9		TDO/RPB9/SDA1/CTED4/PMD3/RB9
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** PPS register. This register is used to select the peripheral output
** connected to the pin. The register is set to 0 to disconnect the
** pin from any peripheral so it can be used as GPIO.
** For PIC32MX1xx/2xx series devices, the PPS output select registers
** are arranged as a contiguous series of 32 bit registers. This table
** treats these registers as an array of DWORDs an stores the index
** to the register.
*/
const uint8_t digital_pin_to_pps_out_PGM[] = {
    // Pins 0 through 18
    _PPS_OUT(_PPS_RPA4R),   //  0   J4-1    RA4  	SOSCO/RPA4/T1CK/CTED9/PMA1/RA4
    _PPS_OUT(_PPS_RPB4R),   //  1   J4-2    RB4    	SOSCI/RPB4/RB4
    _PPS_OUT(_PPS_RPB5R),   //  2   J4-3    RB5    	TMS/RPB5/USBID/RB5
    _PPS_OUT(_PPS_RPB13R),  //  3   J4-4    RB13   	AN11/RPB13/CTPLS/PMRD/RB13 
	_PPS_OUT(_PPS_RPB1R),	//  4   J4-5    RB1    	PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1
	_PPS_OUT(_PPS_RPB0R),	//  5   J4-6    RB0    	PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0
	_PPS_OUT(_PPS_RPA2R),	//  6   J4-7    RA2    	OSC1/CLKI/RPA2/RA2
	_PPS_OUT(_PPS_RPA3R),	//  7   J4-8    RA3    	OSC2/CLKO/RPA3/PMA0/RA3
	_PPS_OUT(_PPS_RPB10R),	//  8   J4-9    RB10	PGED2/RPB10/D+/CTED11/RB10
    _PPS_OUT(_PPS_RPB11R),  //  9   J3-1    RB11   	PGEC2/RPB11/D-/RB11 
	_PPS_OUT(_PPS_RPB7R),	// 10   J3-2    RB7    	TDI/RPB7/CTED3/PMD5/INT0/RB7
	_PPS_OUT(_PPS_RPA1R),	// 11   J3-3    RA1    	PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1
	_PPS_OUT(_PPS_RPB8R),   // 12   J3-4    RB8    	TCK/RPB8/SCL1/CTED10/PMD4/RB8
	_PPS_OUT(_PPS_RPB14R),	// 13   J3-5    RB14   	CVREF/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 
	_PPS_OUT(_PPS_RPA0R),   // 14   J3-6    RA0    	PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0
	_PPS_OUT(_PPS_RPB15R),  // 15   J3-7    RB15   	AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_PPS_OUT(_PPS_RPB2R),	// 16   J3-8    RB2    	AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2
	_PPS_OUT(_PPS_RPB3R),	// 17   J3-9    RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3
	_PPS_OUT(_PPS_RPB9R),	// 18   J3-10   RB9		TDO/RPB9/SDA1/CTED4/PMD3/RB9
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
    // Pins 0 through 18
    _PPS_IN(_PPS_RPA4),   	//  0   J4-1    RA4  	SOSCO/RPA4/T1CK/CTED9/PMA1/RA4
    _PPS_IN(_PPS_RPB4),   	//  1   J4-2    RB4    	SOSCI/RPB4/RB4
    _PPS_IN(_PPS_RPB5),   	//  2   J4-3    RB5    	TMS/RPB5/USBID/RB5
    _PPS_IN(_PPS_RPB13),  	//  3   J4-4    RB13   	AN11/RPB13/CTPLS/PMRD/RB13 
	_PPS_IN(_PPS_RPB1),		//  4   J4-5    RB1    	PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1
	_PPS_IN(_PPS_RPB0),		//  5   J4-6    RB0    	PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0
	_PPS_IN(_PPS_RPA2),		//  6   J4-7    RA2    	OSC1/CLKI/RPA2/RA2
	_PPS_IN(_PPS_RPA3),		//  7   J4-8    RA3    	OSC2/CLKO/RPA3/PMA0/RA3
	_PPS_IN(_PPS_RPB10),	//  8   J4-9    RB10	PGED2/RPB10/D+/CTED11/RB10
    _PPS_IN(_PPS_RPB11),  	//  9   J3-1    RB11   	PGEC2/RPB11/D-/RB11 
	_PPS_IN(_PPS_RPB7),		// 10   J3-2    RB7    	TDI/RPB7/CTED3/PMD5/INT0/RB7
	_PPS_IN(_PPS_RPA1),		// 11   J3-3    RA1    	PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1
	_PPS_IN(_PPS_RPB8),   	// 12   J3-4    RB8    	TCK/RPB8/SCL1/CTED10/PMD4/RB8
	_PPS_IN(_PPS_RPB14),	// 13   J3-5    RB14   	CVREF/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 
	_PPS_IN(_PPS_RPA0),   	// 14   J3-6    RA0    	PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0
	_PPS_IN(_PPS_RPB15),  	// 15   J3-7    RB15   	AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_PPS_IN(_PPS_RPB2),		// 16   J3-8    RB2    	AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2
	_PPS_IN(_PPS_RPB3),		// 17   J3-9    RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3
	_PPS_IN(_PPS_RPB9),		// 18   J3-10   RB9		TDO/RPB9/SDA1/CTED4/PMD3/RB9
};

/* ------------------------------------------------------------ */
/* This table maps from a digital pin number to the corresponding
** analog pin number.
*/
//#if defined(_NOT_USED_)
const uint8_t digital_pin_to_analog_PGM[] = {
    // Pins 0 through 38
    NOT_ANALOG_PIN, //  0   J4-1    RA4  	SOSCO/RPA4/T1CK/CTED9/PMA1/RA4
    NOT_ANALOG_PIN, //  1   J4-2    RB4    	SOSCI/RPB4/RB4
    NOT_ANALOG_PIN, //  2   J4-3    RB5    	TMS/RPB5/USBID/RB5
    NOT_ANALOG_PIN, //  3   J4-4    RB13   	AN11/RPB13/CTPLS/PMRD/RB13 
	NOT_ANALOG_PIN, //  4   J4-5    RB1    	PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/PMD1/RB1
	NOT_ANALOG_PIN,	//  5   J4-6    RB0    	PGED1/AN2/C1IND/C2INB/C3IND/RPB0/PMD0/RB0
	NOT_ANALOG_PIN,	//  6   J4-7    RA2    	OSC1/CLKI/RPA2/RA2
	NOT_ANALOG_PIN, //  7   J4-8    RA3    	OSC2/CLKO/RPA3/PMA0/RA3
	NOT_ANALOG_PIN,	//  8   J4-9    RB10	PGED2/RPB10/D+/CTED11/RB10
    NOT_ANALOG_PIN, //  9   J3-1    RB11   	PGEC2/RPB11/D-/RB11 
	NOT_ANALOG_PIN,	// 10   J3-2    RB7    	TDI/RPB7/CTED3/PMD5/INT0/RB7
	NOT_ANALOG_PIN, // 11   J3-3    RA1    	PGEC3/VREF-/CVREF-/AN1/RPA1/CTED2/PMD6/RA1
	NOT_ANALOG_PIN,	// 12   J3-4    RB8    	TCK/RPB8/SCL1/CTED10/PMD4/RB8
	NOT_ANALOG_PIN,	// 13   J3-5    RB14   	CVREF/AN10/C3INB/RPB14/VBUSON/SCK1/CTED5/RB14 
	_BOARD_AN0,	    // 14   J3-6    RA0    	PGED3/VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/PMD7/RA0
	_BOARD_AN9,		// 15   J3-7    RB15   	AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
	_BOARD_AN4,		// 16   J3-8    RB2    	AN4/C1INB/C2IND/RPB2/SDA2/CTED13/PMD2/RB2
	_BOARD_AN5,		// 17   J3-9    RB3		AN5/C1INA/C2INC/RTCC/RPB3/SCL2/PMWR/RB3
	NOT_ANALOG_PIN,	// 18   J3-10   RB9		TDO/RPB9/SDA1/CTED4/PMD3/RB9
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
	0,		//*	A0				0
	1,		//*	Not used
	2,		//* Not used
	3,		//* Not used
	4,		//* A4				4
	5,		//* A5				5
	6,		//* Not used
	7,		//* Not used
	8,		//* Not used
	9,		//* A1				9
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
	PIN_OC1,	        // A0, B3, B4, B15, B7  ; B15   RPB15R  = 5  	
	PIN_OC2,	        // A1, B5, B1, B11, B8  ; B8    RPB8R   = 5
	PIN_OC3,	        // A3, B14, B0, B10, B9 ; B9    RPB9R   = 5
	PIN_OC4,	        // A2, B6, A4, B13, B2  ; B2    RPB2R   = 5
	PIN_OC5,	        // A2, B6, A4, B13, B2	; B13   RPB13R  = 6
};

/* ------------------------------------------------------------ */
/* This table maps from an external interrupt number to the digital
** pin for that interrupt.
*/

const uint8_t external_int_to_digital_pin_PGM[] = {
	NOT_PPS_PIN,		// INT0 is not mappable;    RB7
	PIN_INT1,			// A3, B14, B0, B10, B9;    B9  INT1R = RPB9 = 4
	PIN_INT2,			// A2, B6, A4, B13, B2;     B2  INT2R = RPB2 = 4
	PIN_INT3,			// A1, B5, B1, B11, B8;     B8  INT3R = RPB8 = 4
	PIN_INT4			// A0, B3, B4, B15, B7;     B4  INT4R = RPB4 = 2
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

	//	Turn Secondary oscillator off as GPIO is needed
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
