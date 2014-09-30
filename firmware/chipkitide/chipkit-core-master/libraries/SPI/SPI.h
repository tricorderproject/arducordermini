/************************************************************************/
/*                                                                      */
/*  SPI.h	--	Interface Declarations for SPI.cpp                      */
/*                                                                      */
/************************************************************************/
/*  Author: Oliver Jones                                                */
/*  Copyright (c) 2011, Digilent. All rights reserved.                  */
/*                                                                      */
/*	Based on original work Copyright (c) 2010 by Cristian Maglie        */
/************************************************************************/
/*  File Description:													*/
/*                                                                      */
/*  This file contains declarations need to use the chipKIT standard    */
/*  SPI library in SPI.CPP.                                             */
/*                                                                      */
/************************************************************************/
/*  Revision History:													*/
/*                                                                      */
/*  08/20/2011(GeneApperson): revised to fix build problems introduced  */
/*      by the initial port of the original Arduino library. Changed    */
/*       all use of the types BYTE and WORD to uint8_t and uint16_t.    */
/*	10/28/2011(GeneApperson): revised for new board variant scheme, and	*/
/*		fixed bug in clock divider values so that they produce the same	*/
/*		SPI clock frequency on PIC32 as they do on AVR.					*/
/*	05/27/2013(ClaudiaGoga): added PPS support for PIC32MX1 and PIC32MX2*/
/*                                                                      */
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


#if !defined(_SPI_H_INCLUDED)
#define _SPI_H_INCLUDED

#define __LANGUAGE_C__

#include <stdio.h>
#include <WProgram.h>

#include <p32_defs.h>

/*	SPIxCON
*/
#define _SPICON_ON		15
#define _SPICON_SMP		9
#define	_SPICON_CKE		8
#define _SPICON_CKP		6
#define _SPICON_MSTEN	5

/*	SPIxSTAT
*/
#define	_SPISTAT_SPIROV	6
#define	_SPISTAT_SPITBE	3
#define _SPISTAT_SPIRBF	0

/********************************/
/* The following values produce the same SPI clock rate that is
** obtained on a 16Mhz AVR assuming that the PIC32 peripheral
** bus clock is operating at 80Mhz
*/
#define SPI_CLOCK_DIV2		4		// 8 Mhz
#define SPI_CLOCK_DIV4		9		// 4 Mhz
#define SPI_CLOCK_DIV8		19		// 2 Mhz
#define SPI_CLOCK_DIV16		39		// 1 Mhz
#define SPI_CLOCK_DIV32		79		// 500 Khz
#define SPI_CLOCK_DIV64		159		// 250 Khz
#define SPI_CLOCK_DIV128	319		// 125 Khz

/* The following produce an equivlalent operating mode as these
** symbols specify on the AVR part in Arduino
*/
#define SPI_MODE0 0x100		// CKP = 0 CKE = 1
#define SPI_MODE1 0x00		// CKP = 0 CKE = 0
#define SPI_MODE2 0x140		// CKP = 1 CKE = 1 
#define SPI_MODE3 0x40		// CKP = 1 CKE = 0

class SPIClass {
private:
	static p32_spi *	spi;
	static p32_regset *	iec;
	static p32_regset *	ifs;
	static int			irq;
	static int			vec;

// Code for PPS support
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	static uint8_t			pinMISO;		//digital pin number for MISO
	static uint8_t			pinMOSI;		//digital pin number for MOSI
	static ppsFunctionType	ppsMISO;		//PPS select for SPI MISO
	static ppsFunctionType	ppsMOSI;		//PPS select for SPI MOSI
#endif
	
public:
// Code for PPS support
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	SPIClass(p32_spi * spiP, int irgP, int vecP, int pinMI, int pinMO, ppsFunctionType ppsMI, ppsFunctionType ppsMO);
#else
	SPIClass(p32_spi * spiP, int irqP, int vecP);
#endif

  inline static uint8_t transfer(uint8_t _data);

  // SPI Configuration methods

  inline static void attachInterrupt();
  inline static void detachInterrupt(); // Default

  static void begin();					// Default
  static void end();

  static void setBitOrder(uint8_t);
  static void setDataMode(uint16_t);
  static void setClockDivider(uint16_t);
};

extern SPIClass SPI;

/* SPIClass inline functions definitions
*/
uint8_t SPIClass::transfer(uint8_t _data)
{
	while ((spi->sxStat.reg & (1 << _SPISTAT_SPITBE)) == 0 );
	spi->sxBuf.reg = _data;

	while ((spi->sxStat.reg & (1 << _SPISTAT_SPIRBF)) == 0 );
	return spi->sxBuf.reg;
}

void SPIClass::attachInterrupt()
{
	/* Enable transmit and receive interrupts
	*/
	iec->set = ((1 << ((irq+1) % 32)) | (1 << ((irq+2) % 32)));
}

void SPIClass::detachInterrupt()
{
	/* Disable transmit and receive interrupts
	*/
	iec->clr = ((1 << ((irq+1) % 32)) | (1 << ((irq+2) % 32)));
}

#endif
