/************************************************************************/
/*																		*/
/*	SoftSPI.h -- Declarations for chipKIT Software SPI Library			*/
/*																		*/
/************************************************************************/
/*	Author: 	Gene Apperson											*/
/*	Copyright (c) 2011, Digilent Inc, All rights reserved				*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This header file contains interface declarations for use of the		*/
/* chipKIT Software SPI library. This library provides support for any	*/
/* number of bit-banged software SPI ports.								*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/21/2011(Gene Apperson): Created									*/
/*																		*/
/************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/************************************************************************/

#if !defined(_SOFTSPI_H_)
#define _SOFTSPI_H_

#include <WProgram.h>
#include <p32_defs.h>

/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations					*/
/* ------------------------------------------------------------ */

/* Sybmols for the SPI modes
*/
#define	SSPI_MODE0		0
#define	SSPI_MODE1		1
#define	SSPI_MODE2		2
#define	SSPI_MODE3		3

/* Symbols for shift direction
*/
#define	SSPI_SHIFT_LEFT		0
#define	SSPI_SHIFT_RIGHT	1

/* Default SPI clock speed
*/
#define SSPI_SPEED_DEFAULT	500000

/* ------------------------------------------------------------ */
/*					General Type Declarations					*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*					Object Class Declarations					*/
/* ------------------------------------------------------------ */

class SoftSPI {
private:
	uint8_t			pinSS;
	uint8_t			pinMOSI;
	uint8_t			pinMISO;
	uint8_t			pinSCK;
	p32_ioport *	iopSS;
	p32_ioport *	iopMOSI;
	p32_ioport *	iopMISO;
	p32_ioport *	iopSCK;
	uint32_t		bitSS;
	uint32_t		bitMOSI;
	uint32_t		bitMISO;
	uint32_t		bitSCK;

	uint32_t	cntClk;
	uint32_t	cntDly;
	uint8_t		modCur;

protected:

public:
				SoftSPI();

/* Initialization and setup functions.
*/
int			begin(uint8_t pinSSt, uint8_t pinMOSIt, uint8_t pinMISOt, uint8_t pinSCKt);
void		end();
void		setSpeed(uint32_t spd);
void		setMode(int mod);
void		setDirection(int dir);
void		setDelay(int dly);

/* Data transfer functions
*/
void		setSelect(uint8_t sel) { digitalWrite(pinSS, sel); };
uint8_t		transfer(uint8_t bVal);
void		transfer(uint16_t cbReq, uint8_t * pbSnd, uint8_t * pbRcv);
void		transfer(uint16_t cbReq, uint8_t * pbSnd);
void		transfer(uint16_t cbReq, uint8_t bPad, uint8_t * pbRcv);

};

/* ------------------------------------------------------------ */
/*					Variable Declarations						*/
/* ------------------------------------------------------------ */



/* ------------------------------------------------------------ */
/*					Procedure Declarations						*/
/* ------------------------------------------------------------ */



/* ------------------------------------------------------------ */

#endif	// _SOFTSPI_H_

/************************************************************************/
