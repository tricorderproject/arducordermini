//************************************************************************
//*	Pins_arduinohc
//*
//*	Arduino core files for PIC32
//*		Copyright (c) 2010, 2011 by Mark Sproul
//*	
//*	
//************************************************************************
//*	this code is based on code Copyright (c) 2005-2006 David A. Mellis
//*	
//*	pins_arduino.h - Pin definition functions for Arduino
//*	Part of Arduino - http://www.arduino.cc/
//*	
//*	
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
//************************************************************************
//*	Edit History
//************************************************************************
//*	May  5,	2011	<MLS> added analog_pin_to_channel_PGM
//* Nov 12, 2011	<GeneApperson> Rewrite for board variant support
//* Nov 28, 2011	<GeneApperson> split board data out into Board_Data.c
//*	Jul 26, 2012	<GeneApperson> Added PPS support for PIC32MX1xx/MX2xx devices
//************************************************************************

#define OPT_BOARD_INTERNAL
#define OPT_BOARD_DATA
#include <p32xxxx.h>
#include "pins_arduino.h"
#include "p32_defs.h"

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
//* General data tables to support PPS pin mapping on PIC32MX1xx/2xx devices.
//*
#if defined(OPT_BOARD_DATA)
/* This table is used to map from an output compare number to the
** value to load into the output pin PPS select register to map
** the output compare to the pin.
*/
const uint8_t output_compare_to_pps_sel_PGM[] = {
	0,					// not used
	PPS_OUT_OC1,
	PPS_OUT_OC2,
	PPS_OUT_OC3,
	PPS_OUT_OC4,
	PPS_OUT_OC5
};

/* This table is used to map from an external interrupt number to the
** PPS input selection function used to map the input to a pin. The
** digital_pin_to_pps_in_PGM[] table in the board variant data file
** contains the select value to load to map the input to the board
** default pin for the input function.
*/
const uint8_t ext_int_to_pps_sel_PGM[] = {
	NOT_PPS_PIN,			// INT0 is not mappable
	PPS_IN_INT1,
	PPS_IN_INT2,
	PPS_IN_INT3,
	PPS_IN_INT4
};

#endif	// OPT_BOARD_DATA
#endif	// __PIC32MX1XX__ || __PIC32MX2XX__

//* Table and function definitions for the board variant.
#include "Board_Data.c"

//************************************************************************
