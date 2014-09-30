/************************************************************************/
/*																		*/
/*	DSPI.h	--	Declarations for Digilent chipKIT SPI Library			*/
/*																		*/
/************************************************************************/
/*	Author:		Gene Apperson											*/
/*	Copyright (c) 2011, Digilent Inc. All rights reserved.				*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This header file contains interface declarations for use of the		*/
/* Digilent chipKIT SPI library.										*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	10/28/2011(GeneApperson): Created									*/
/*	05/27/2013(ClaudiaGoga): added PPS support for PIC32MX1 and PIC32MX2*/
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

#if !defined(_DSPI_H_)
#define	_DSPI_H_

#include	<WProgram.h>

#include	<p32xxxx.h>
#include	<p32_defs.h>

/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations					*/
/* ------------------------------------------------------------ */

#define	DSPI_MODE0	((0 << _SPICON_CKP)|(1 << _SPICON_CKE))		// CKP = 0 CKE = 1
#define	DSPI_MODE1	((0 << _SPICON_CKP)|(0 << _SPICON_CKE))		// CKP = 0 CKE = 0
#define	DSPI_MODE2	((1 << _SPICON_CKP)|(1 << _SPICON_CKE))		// CKP = 1 CKE = 1
#define	DSPI_MODE3	((1 << _SPICON_CKP)|(0 << _SPICON_CKE))		// CKP = 1 CKE = 0

#define DSPI_8BIT	8
#define DSPI_16BIT	16
#define DSPI_32BIT	32

#define	_DSPI_SPD_DEFAULT	1000000L

/* ------------------------------------------------------------ */
/*					Variable Declarations						*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*					Function Declarations						*/
/* ------------------------------------------------------------ */

/* Forward declarations for the interrupt service routines.
** These functions need to be declared so that they can be declared
** as friends of the DSPI class, so that they can call the private
** method doDspiInterrupt
*/
extern "C" {
	void __attribute__((nomips16)) IntDspi0Handler(void);
	void __attribute__((nomips16)) IntDspi1Handler(void);
	void __attribute__((nomips16)) IntDspi2Handler(void);
	void __attribute__((nomips16)) IntDspi3Handler(void);
};

/* ------------------------------------------------------------ */
/*					Object Class Declarations					*/
/* ------------------------------------------------------------ */

class DSPI {

	friend		void __attribute__((nomips16)) IntDspi0Handler(void);
	friend		void __attribute__((nomips16)) IntDspi1Handler(void);
	friend		void __attribute__((nomips16)) IntDspi2Handler(void);
	friend		void __attribute__((nomips16)) IntDspi3Handler(void);

private:
	p32_regset *		pregIfs;	//pointer to interrupt flag register
	p32_regset *		pregIec;	//pointer to interrupt enable control register
	uint32_t			bitErr;		//overrun error interrupt flag bit
	uint32_t			bitRx;		//receive interrupt flag bit
	uint32_t			bitTx;		//transmit interrupt flag bit
	volatile uint8_t *	pbSndCur;	//current point in transmit buffer
	volatile uint8_t *	pbRcvCur;	//current point in receive buffer
	volatile uint16_t	cbCur;		//count of bytes left to transfer
	uint8_t				bPad;		//pad byte for some transfers
	uint8_t				fRov;		//receive overflow error flag

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	uint8_t				pinMISO;		//digital pin number for MISO
	uint8_t				pinMOSI;		//digital pin number for MOSI
	ppsFunctionType		ppsMISO;		//PPS select for SPI MISO
	ppsFunctionType		ppsMOSI;		//PPS select for SPI MOSI
#endif	

	void	doDspiInterrupt();

protected:
	p32_spi *			pspi;		//pointer to the SPI object
    isrFunc             isr;        // the ISR function to use
	uint8_t				vec;		//interrupt vector number
	uint8_t				ipl;		//interrupt priority and sub-priority
	uint8_t				pinSS;		//digital pin number for slave select pin

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
			DSPI (int pinMI, int pinMO, ppsFunctionType ppsMI, ppsFunctionType ppsMO);
#else
			DSPI();
#endif

	void	init(uint8_t irqErr, uint8_t irqRx, uint8_t irqTx, isrFunc isrHandler);

public:

/* Initialization and setup functions.
*/
void		begin();
void		begin(uint8_t pin);
void		end();
void		setSpeed(uint32_t spd);
void		setMode(uint16_t  mod);
void		setPinSelect(uint8_t pin);
void		setTransferSize(uint8_t txsize);

/* Data transfer functions.
*/
void		setSelect(uint8_t sel) { digitalWrite(pinSS, sel); };
uint32_t	transfer(uint32_t bVal);
void		transfer(uint16_t cbReq, uint8_t * pbSnd, uint8_t * pbRcv);
void		transfer(uint16_t cbReq, uint8_t * pbSnd);
void		transfer(uint16_t cbReq, uint8_t bPad, uint8_t * pbRcv);

/* Interrupt control and interrupt driven I/O functions
*/
void		enableInterruptTransfer();
void		disableInterruptTransfer();
void		intTransfer(uint16_t cbReq, uint8_t * pbSnd, uint8_t * pbRcv);
void		intTransfer(uint16_t cbReq, uint8_t * pbSnd);
void		intTransfer(uint16_t cbReq, uint8_t bPadT, uint8_t * pbRcv);
void		cancelIntTransfer();
uint16_t	transCount() { return cbCur; };
int			isOverflow() { return fRov; };
void		clearOverflow() { fRov = 0; };
};

/* Object class for DSPI port 0
*/
#if (NUM_DSPI_PORTS > 0)
class DSPI0 : public DSPI {
public:
			DSPI0();
void		enableInterruptTransfer();
void		disableInterruptTransfer();
};
#endif

/* Object class for DSPI port 1
*/
#if (NUM_DSPI_PORTS > 1)
class DSPI1 : public DSPI {
public:
			DSPI1();
void		enableInterruptTransfer();
void		disableInterruptTransfer();
};
#endif

/* Object class for DSPI port 2
*/
#if (NUM_DSPI_PORTS > 2)
class DSPI2 : public DSPI {
public:
			DSPI2();
void		enableInterruptTransfer();
void		disableInterruptTransfer();
};
#endif

/* Object class for DSPI port 3
*/
#if (NUM_DSPI_PORTS > 3)
class DSPI3 : public DSPI {
public:
			DSPI3();
void		enableInterruptTransfer();
void		disableInterruptTransfer();
};
#endif

/* ------------------------------------------------------------ */

#endif	// _DSPI_H_

/************************************************************************/
