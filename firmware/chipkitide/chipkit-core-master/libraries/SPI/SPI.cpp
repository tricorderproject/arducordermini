/************************************************************************/
/*                                                                      */
/*	SPI.cpp	--	Top Level Module for chipKIT standard SPI Library		*/
/*                                                                      */
/************************************************************************/
/*  Author: Oliver Jones                                                */
/*  Copyright (c) 2011, Digilent. All rights reserved.                  */
/*                                                                      */
/*	Based on original work Copyright (c) 2010 by Cristian Maglie        */
/************************************************************************/
/*  File Description:													*/
/*                                                                      */
/*	This is the top level module for the standard SPI Library for the	*/
/*	chipKIT system. This library is based on, and is functionally		*/
/*	similar to the original Arduino standard SPI library.				*/
/*                                                                      */
//************************************************************************
//*	Revision History:													*/
//************************************************************************
//*	Aug 20,	2011	<GeneApperson> revised to fix build problems introduced
//*					by the initial port of the original Arduino library. Changed
//*					all use of the types BYTE and WORD to uint8_t and uint16_t.
//*	Oct 28, 2011	<GeneApperson> revised for new board variant scheme
//*	May 27, 2013	<(ClaudiaGoga>: added PPS support for PIC32MX1 and PIC32MX2
//************************************************************************
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
//*	You should have received a copy of the GNU Lesser General Public
//*	License along with this library; if not, write to the Free Software
//*	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//*	
//************************************************************************


#define __LANGUAGE_C__

#define	OPT_BOARD_INTERNAL

#include "SPI.h"

extern p32_spi *	SPIClass::spi;
extern p32_regset *	SPIClass::iec;
extern p32_regset * SPIClass::ifs;
extern int			SPIClass::irq;
extern int			SPIClass::vec;

// Code for PPS support
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	extern uint8_t		SPIClass::pinMISO;	
	extern uint8_t		SPIClass::pinMOSI;		
	extern ppsFunctionType	SPIClass::ppsMISO;		
	extern ppsFunctionType	SPIClass::ppsMOSI;	
#endif

// Code for PPS support
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	SPIClass SPI((p32_spi *) _SPI_BASE, _SPI_ERR_IRQ, _SPI_VECTOR, _SPI_MISO_PIN, _SPI_MOSI_PIN, _SPI_MISO_IN, _SPI_MOSI_OUT);
#else
	SPIClass SPI((p32_spi *) _SPI_BASE, _SPI_ERR_IRQ, _SPI_VECTOR);
#endif

//************************************************************************

// Code for PPS support
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
SPIClass::SPIClass(p32_spi * spiP, int irqP, int vecP, int pinMI, int pinMO, ppsFunctionType ppsMI, ppsFunctionType ppsMO)
#else
SPIClass::SPIClass(p32_spi * spiP, int irqP, int vecP)
#endif
{
	/* Save the pointer to the SPI port and the base IRQ number.
	*/
	spi = spiP;
	irq = irqP;
	vec = vecP;

	// Code for PPS support
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	pinMISO = (uint8_t)pinMI;
	pinMOSI = (uint8_t)pinMO;
	ppsMISO = ppsMI;
	ppsMOSI = ppsMO;
#endif
		
}

//************************************************************************
//* This routine initializes the SPI controller for use. This follows
//* the recommended init sequence in Section 23. Serial Peripheral
//* interface in the PIC32 Family Reference Manual.

void SPIClass::begin() 
{
	uint8_t			tmp;
	p32_regset *	ipc;		//interrupt priority register
	int				ipl_shift;

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	/* Map the SPI MISO to the appropriate pin.
	*/
    mapPps(pinMISO, ppsMISO);

	/* Map the SPI MOSI to the appropriate pin.
	*/
    mapPps(pinMOSI, ppsMOSI);

#endif


	/* Initialize the pins. The pin directions for SDO, SDI and SCK
	** are set automatically when the SPI controller is enabled. The
	** SS pin isn't explicitly used by the SPI controller when in
	** master mode, so we need to initialize it ourselves.
	*/
	pinMode(SS, OUTPUT);
	digitalWrite(SS, HIGH);

	/* The IRQ stored by the constructor is for the SPI controller ERR interrupt.
	** That plus the following two are the IRQs for the SPI interrupts.
	** Disable all SPI interrupts.
	*/
	iec = ((p32_regset *)&IEC0) + (irq / 32);	//interrupt enable control reg
	iec->clr = 0x07 << (irq % 32);

	/* Disable and reset the SPI controller.
	*/
	spi->sxCon.reg = 0;

	/* Clear the receive buffer.
	*/
	tmp = spi->sxBuf.reg;

	/* Clear any pending interrupt flags.
	*/
	ifs = ((p32_regset *)&IFS0) + (irq / 32);	//interrupt flag register
	ifs->clr = 0x07 << (irq % 32);

	/* Compute the bit position for the interrupt priority and
	** sub-priority control bits and then set the priority and sub-priority.
	*/
	ipc = ((p32_regset *)&IPC0) + (vec / 4);	//interrupt priority control reg
	ipl_shift = 8 * (vec % 4);
	ipc->clr = (0x1F << ipl_shift);
	ipc->set = ((_SPI_IPL << 2) + _SPI_SPL) << ipl_shift;

	/* Set the clock frequency. An Arduino board with a 16Mhz clock defaults
	** the SPI clock speed to SPI_CLOCK_DIV4, resulting in a 4Mhz SPI clock.
	*/
	spi->sxBrg.reg = SPI_CLOCK_DIV4;

	/* Clear the receive overflow bit.
	*/
	spi->sxStat.clr = (1 << _SPISTAT_SPIROV);

	/* Enable the SPI controller.
	** Warning: if the SS pin ever becomes a LOW INPUT then SPI 
	** automatically switches to Slave, so the data direction of 
	** the SS pin MUST be kept as OUTPUT.
	*/
	spi->sxCon.set = (1 << _SPICON_MSTEN) + SPI_MODE0;
	spi->sxCon.set = (1 << _SPICON_ON);

}

//************************************************************************
void SPIClass::end()
{
	spi->sxCon.clr = (1 << _SPICON_ON);
}

//************************************************************************
void SPIClass::setBitOrder(uint8_t bitOrder)
{
	//PIC32 does not support selectable shift direction.
	// they always shift left (MSB first)
}

//************************************************************************
void SPIClass::setDataMode(uint16_t mode)
{
	spi->sxCon.clr = (1 << _SPICON_ON);
	spi->sxCon.clr = 0x0140;	// force both mode bits to 0
	spi->sxCon.set = mode;		// set the requested mode
	spi->sxCon.set = (1 << _SPICON_ON);
}

//************************************************************************
void SPIClass::setClockDivider(uint16_t rate)
{
	spi->sxCon.clr = (1 << _SPICON_ON);
	spi->sxBrg.reg = rate & 0x1FF;
	spi->sxCon.set = (1 << _SPICON_ON);
}