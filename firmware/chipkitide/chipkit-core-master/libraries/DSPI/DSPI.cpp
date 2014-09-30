/************************************************************************/
/*																		*/
/*	DSPI.cpp	--	Implementation for Digilent chipKIT SPI Library		*/
/*																		*/
/************************************************************************/
/*	Author: 	Gene Apperson											*/
/*	Copyright (c) 2011, Digilent Inc, All rights reserved				*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/* This is the main program module for the Digilent SPI library for use	*/
/* with the chipKIT system. This library supports access to all of the	*/
/* SPI ports defined on the board in use.								*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	10/28/2011(Gene Apperson): Created									*/
/*	05/27/2013(Claudia Goga) : Added PPS support for PIC32MX1/2			*/
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


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#define OPT_BOARD_INTERNAL
#include	<sys/attribs.h>
#include	<DSPI.h>

/* ------------------------------------------------------------ */
/*				Forward references to int handlers              */
/* ------------------------------------------------------------ */
extern "C" void __attribute__((interrupt(),nomips16)) IntDspi0Handler(void);
extern "C" void __attribute__((interrupt(),nomips16)) IntDspi1Handler(void);
extern "C" void __attribute__((interrupt(),nomips16)) IntDspi2Handler(void);
extern "C" void __attribute__((interrupt(),nomips16)) IntDspi3Handler(void);

/* ------------------------------------------------------------ */
/*				Local Type and Constant Definitions				*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Local Variables									*/
/* ------------------------------------------------------------ */

#if defined(_DSPI0_VECTOR)
static DSPI *	pdspi0 = 0;
#endif

#if defined(_DSPI1_VECTOR)
static DSPI *	pdspi1 = 0;
#endif

#if defined(_DSPI2_VECTOR)
static DSPI *	pdspi2 = 0;
#endif

#if defined(_DSPI3_VECTOR)
static DSPI *	pdspi3 = 0;
#endif

/* ------------------------------------------------------------ */
/*				Forward Declarations							*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Procedure Definitions							*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				DSPI Object Class Implementation				*/
/* ------------------------------------------------------------ */
/*				Initialization and Setup Functions				*/
/* ------------------------------------------------------------ */
/***	DSPI::DSPI
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
**		DSPI constructor. This is private so that this object can't
**		be instantiated. Only objects from the derived classes
**		can be instantiated.
*/

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
DSPI::DSPI(int pinMI, int pinMO, ppsFunctionType ppsMI, ppsFunctionType ppsMO)
#else
DSPI::DSPI()
#endif
 {

	pspi = 0;
	cbCur = 0;

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	pinMISO = (uint8_t)pinMI;
	pinMOSI = (uint8_t)pinMO;
	ppsMISO = ppsMI;
	ppsMOSI = ppsMO;
#endif

}

/* ------------------------------------------------------------ */
/***	DSPI::init
**
**	Parameters:
**		irqErr		- IRQ for the SPI error interrupt
**		irqRx		- IRQ for the SPI receive interrupt
**		irqTx		- IRQ for the SPI transmit interrupt
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the object. This is called from the constructors
**		of the derived classes.
*/

void
DSPI::init(uint8_t irqErr, uint8_t irqRx, uint8_t irqTx, isrFunc isrHandler) {

	/* The interrupt flag and enable control register addresses and
	** the bit numbers for the flag bits can be computed from the
	** IRQ numbers for the SPI port. There are 32 IRQ bits in each IFS
	** and IEC register. For each IFS register, there is a SET, CLR,
	** and INV register, so the distance (in dwords) from IFS0 to IFS1
	** is 4. This code assumes that all of the enable control and flag
	** bits for an SPI controller are in the same IEC and IFS registers.
	*/
	pregIec = ((p32_regset *)&IEC0) + (irqErr / 32);	// interrupt enable control register
	pregIfs = ((p32_regset *)&IFS0) + (irqErr / 32);	// interrupt flag register

	bitErr = 1 << (irqErr % 32);	// error interrupt flag/enable bit
	bitRx  = 1 << (irqRx % 32);		// rx interrupt flag/enable bit
	bitTx  = 1 << (irqTx % 32);		// tx interrupt flag/enable bit

    isr = isrHandler;
}

/* ------------------------------------------------------------ */
/***	DSPI::begin
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
**		Initialize the SPI port with all default values.
*/

void
DSPI::begin() {

	/* Use the default pin specified in the constructor.
	*/
	begin(pinSS);

}

/* ------------------------------------------------------------ */
/***	DSPI::begin
**
**	Parameters:
**		pinT		- pin to use for SS instead of the default.
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the SPI port with the default values. This
**		will set the clock rate to the default speed and the
**		pin for SS to the specified pin.
*/

void
DSPI::begin(uint8_t pinT) {

	p32_regset *	pregIpc;
	int				bnVec;
	uint8_t			bTmp;
	uint16_t		brg;

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	/* Map the SPI MISO to the appropriate pin.
	*/
    mapPps(pinMISO, ppsMISO);

	/* Map the SPI MOSI to the appropriate pin.
	*/
    mapPps(pinMOSI, ppsMOSI);
#endif

    // set up the interrupt handler 
    setIntVector(vec, isr);

/* Initialize the pins. The pin directions for SDO, SDI and SCK
	** are set automatically when the SPI controller is enabled. The
	** SS pin isn't explicitly used by the SPI controller when in
	** master mode, so we need to initialize it ourselves.
	*/
	setPinSelect(pinT);

	/* Disable interrupts on this SPI controller.
	*/
	pregIec->clr = bitErr + bitRx + bitTx;

	/* Disable and reset the SPI controller.
	*/
	pspi->sxCon.reg = 0;

	/* Clear the receive buffer.
	*/
	bTmp = pspi->sxBuf.reg;

	/* Clear all SPI interrupt flags.
	*/
	pregIfs->clr = bitErr + bitRx + bitTx;

	/* Compute the address of the interrupt priority control register
	** used by this SPI controller.
	*/
	pregIpc = ((p32_regset *)&IPC0) + (vec / 4);	// interrupt priority control register

	/* Compute the bit position of the interrupt priority bits for
	** this interrupt vector.
	*/
	bnVec = 8 * (vec % 4);

	/* Set the interrupt priority and sub-priority bits.
	** The interrupt priorty control register address and the priority bits
	** can be computed from the vector number. Each IPC register contains the
	** the priority bits for four vectors. Each byte of an IPC registger contains
	** the priority and sub-priority bits arranged such that  bits 0-1 are
	** the sub-priority, bits 2-4 the priority, and bits 5-7 unused.
	*/
	pregIpc->clr = (0x1F << bnVec);
	pregIpc->set = ipl << bnVec;

	/* Set the default baud rate.
	*/
	brg = (uint16_t)((F_CPU / (2 * _DSPI_SPD_DEFAULT)) - 1);
	pspi->sxBrg.reg = brg;

	/* Clear the receive overflow bit and receive overflow error flag
	*/
	pspi->sxStat.clr = (1 << _SPISTAT_SPIROV);
	fRov = 0;

	/* Enable the SPI controller.
	** Warning: if the SS pin ever becomes a LOW INPUT then SPI 
	** automatically switches to Slave, so the data direction of 
	** the SS pin MUST be kept as OUTPUT.
	*/
	pspi->sxCon.reg = 0;
	pspi->sxCon.set = (1 << _SPICON_ON) + (1 << _SPICON_MSTEN) + DSPI_MODE0;

}	

/* ------------------------------------------------------------ */
/***	DSPI::end
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
**		Return the object to the uninitialized state and disable
**		the SPI controller.
*/

void
DSPI::end() {

	pspi->sxCon.reg = 0;	
	cbCur = 0;
	clearIntVector(vec);	
}

/* ------------------------------------------------------------ */
/***	DSPI::setSpeed
**
**	Parameters:
**		spd		- clock speed to set in HZ
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This sets the SPI clock speed to the highest supported
**		frequency that doesn't exceed the requested value. It computes
**		the appropriate value to load into the SPI baud register
**		based on requested clock speed and peripheral bus frequency.
*/

void
DSPI::setSpeed(uint32_t spd) {

	uint16_t	brg;

	/* Compute the baud rate divider for this frequency.
	*/
	brg = (uint16_t)((F_CPU / (2 * spd)) - 1);

	/* That the baud rate value is in the correct range.
	*/
	if (brg == 0xFFFF) {
		/* The user tried to set a frequency that is too high to support.
		** Set it to the highest supported frequency.
		*/
		brg = 0;
	}

	if (brg > 0x1FF) {
		/* The user tried to set a frequency that is too low to support.
		** Set it to the lowest supported frequency.
		*/
		brg = 0x1FF;
	}

	/* Write the value to the SPI baud rate register. Section 23. SPI
	** of the PIC32 Family Reference Manual says to disable the SPI
	** controller before writing to the baud register
	*/
	pspi->sxCon.clr = (1 << _SPICON_ON);	// disable SPI
	pspi->sxBrg.reg = brg;
	pspi->sxCon.set = (1 << _SPICON_ON);	// enable SPI

}

/* ------------------------------------------------------------ */
/***	DSPI::setMode
**
**	Parameters:
**		mod		- requested SPI mode.
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Set the SPI controller to the requested data mode. This
**		should be one of the values:
**			DSPI_MODE0, DSPI_MODE1, DSPI_MODE2, DSPI_MODE3
*/

void
DSPI::setMode(uint16_t mod) {

	if ((mod & ~((1 << _SPICON_CKP)|(1 << _SPICON_CKE))) != 0) {
		/* This is an invalid value.
		*/
		return;
	}

	pspi->sxCon.clr = (1 << _SPICON_ON);
	pspi->sxCon.clr =((1 << _SPICON_CKP)|(1 << _SPICON_CKE));	// force both mode bits to 0

	pspi->sxCon.set = mod;		// set the requested mode
	pspi->sxCon.set = (1 << _SPICON_ON);
	
}

/* ------------------------------------------------------------ */
/***	DSPI::setPinSelect
**
**	Parameters:
**		pin		- the pin to use as the slave select
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This sets the pin used for slave select. It will make the
**		pin be an output driving high. This pin will then be use
**		by the setSelect method.
*/

void
DSPI::setPinSelect(uint8_t pin) {

	pinSS = pin;

	pinMode(pinSS, OUTPUT);
	digitalWrite(pinSS, HIGH);

}

/* ------------------------------------------------------------ */
/***	DSPI::setPinSelect
**
**	Parameters:
**		pin		- the pin to use as the slave select
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This sets the pin used for slave select. It will make the
**		pin be an output driving high. This pin will then be use
**		by the setSelect method.
*/

void
DSPI::setTransferSize(uint8_t bits) {
	switch(bits) {
		default:
			// Anything that's not recognised we'll just take as 8 bit
		case DSPI_8BIT:
			pspi->sxCon.clr = 1<<_SPICON_MODE32;
			pspi->sxCon.clr = 1<<_SPICON_MODE16;
			break;
		case DSPI_16BIT:
			pspi->sxCon.clr = 1<<_SPICON_MODE32;
			pspi->sxCon.set = 1<<_SPICON_MODE16;
			break;
		case DSPI_32BIT:
			pspi->sxCon.set = 1<<_SPICON_MODE32;
			pspi->sxCon.clr = 1<<_SPICON_MODE16;
			break;
	}
}

/* ------------------------------------------------------------ */
/*				Data Transfer Functions							*/
/* ------------------------------------------------------------ */
/***	DSPI::transfer
**
**	Parameters:
**		bVal	- byte/word to send
**
**	Return Value:
**		returns byte/word received from the slave
**
**	Errors:
**		none
**
**	Description:
**		Send the specified byte to the SPI slave device, returning
**		the byte received from the slave device.
*/

uint32_t
DSPI::transfer(uint32_t bVal) {

	while ((pspi->sxStat.reg & (1 << _SPISTAT_SPITBE)) == 0) {
	}
	pspi->sxBuf.reg = bVal;

	while ((pspi->sxStat.reg & (1 << _SPISTAT_SPIRBF)) == 0) {
	}

	return pspi->sxBuf.reg;

}

/* ------------------------------------------------------------ */
/***	DSPI::transfer
**
**	Parameters:
**		cbReq	- number of bytes to transfer
**		pbSnd	- pointer to buffer to bytes to send
**		pbRcv	- pointer to hold received bytes
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function will send the requested bytes to the SPI
**		slave device, simultaneously saving the bytes received
**		from the slave device.
*/

void
DSPI::transfer(uint16_t cbReq, uint8_t * pbSnd, uint8_t * pbRcv) {
	
	for (cbCur = cbReq; cbCur > 0; cbCur--) {
		*pbRcv++ = transfer(*pbSnd++);
	}

}

/* ------------------------------------------------------------ */
/***	DSPI::transfer
**
**	Parameters:
**		cbReq	- number of bytes to send to the slave
**		pbSnd	- buffer containing bytes to send
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function will send the requested bytes to the SPI
**		slave device, discarding the bytes received from the
**		slave.
*/

void
DSPI::transfer(uint16_t cbReq, uint8_t * pbSnd) {

	for (cbCur = cbReq; cbCur > 0; cbCur--) {
		transfer(*pbSnd++);
	}

}

/* ------------------------------------------------------------ */
/***	DSPI::transfer
**
**	Parameters:
**		cbReq	- number of bytes to receive from the slave
**		bPad	- pad byte to send to slave
**		pbRcv	- buffer to hold received bytes
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function will receive the specified number of bytes
**		from the slave. The given pad byte will be sent to the
**		slave to cause the received bytes to be sent.
*/

void
DSPI::transfer(uint16_t cbReq, uint8_t bPad, uint8_t * pbRcv) {

	for (cbCur = cbReq; cbCur > 0; cbCur--) {
		*pbRcv++ = transfer(bPad);
	}

}

/* ------------------------------------------------------------ */
/*					Interrupt Control Functions					*/
/* ------------------------------------------------------------ */
/***	enableInterruptTransfer
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
**		Sets up the interrupt controller and enables interrupts
**		for this SPI port.
*/

void
DSPI::enableInterruptTransfer() {

	 clearOverflow();			// clear the receive overflow error flag

	/* Clear the interrupt flags and then enable SPI interrupts. Don't enable the
	** transmit interrupt now. This will happen in the transfer function that 
	** begins a data transfer operation.
	*/
	pregIfs->clr = bitRx + bitTx + bitErr;		// clear all interrupt flags
	pregIec->set = bitRx + bitErr;				// enable interrupts

}

/* ------------------------------------------------------------ */
/***	disableInterruptTransfer
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
**		Turns off SPI interrupts for this SPI port.
*/

void
DSPI::disableInterruptTransfer() {

	/* Disable SPI interrupts and then clear the interrupt flags.
	*/
	pregIec->clr = bitRx + bitTx + bitErr;	// disable all interrupts
	pregIfs->clr = bitRx + bitTx + bitErr;	// clear all interrupt flags

}

/* ------------------------------------------------------------ */
/***	DSPI::cancelIntTransfer
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
**		This will cancel an interrupt driven transfer. It is still
**		the caller's responsibility to drive SS high to release
**		the slave device.
*/

void
DSPI::cancelIntTransfer() {

	uint8_t		bTmp;

	/* Clear the receive buffer.
	*/
	bTmp = pspi->sxBuf.reg;

	/* Clear the interrupt flags.
	*/
	pregIfs->clr = bitErr + bitRx + bitTx;

	/* Set the count of bytes remaining to 0.
	*/
	cbCur = 0;

}

/* ------------------------------------------------------------ */
/*					Interrupt Driven I/O Functions				*/
/* ------------------------------------------------------------ */
/***	DSPI::intTransfer
**
**	Parameters:
**		cbReq		- number of bytes to transfer
**		pbSnd		- pointer to buffer of bytes to transmit
**		pbRcv		- pointer to buffer to receive return bytes
**
**	Return Value:
**		none
**
**	Errors:
**		Overrun error handled in interrupt service routine
**
**	Description:
**		This function will set up and begin an interrupt driven
**		transfer where the received bytes are stored into a
**		receive buffer.
*/

void
DSPI::intTransfer(uint16_t cbReq, uint8_t * pbSnd, uint8_t * pbRcv) {

	/* Set up the control variables for the transfer.
	*/
	cbCur = cbReq;
	pbSndCur = pbSnd;
	pbRcvCur = pbRcv;

	/* Wait for the transmitter to be ready
	*/
	while ((pspi->sxStat.reg & (1 << _SPISTAT_SPITBE)) == 0) {
	}

	/* Send the first byte.
	*/
	pspi->sxBuf.reg = *pbSndCur++;

}

/* ------------------------------------------------------------ */
/***	DSPI::intTransfer
**
**	Parameters:
**		cbReq		- number of bytes to transfer
**		pbSnd		- pointer to buffer of bytes to transmit
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function will set up and begin an interrupt driven
**		transfer where the received bytes are discarded.
*/

void
DSPI::intTransfer(uint16_t cbReq, uint8_t * pbSnd) {

	/* Set up the control variables for the transfer.
	*/
	cbCur = cbReq;
	pbSndCur = pbSnd;
	pbRcvCur = 0;

	/* Wait for the transmitter to be ready
	*/
	while ((pspi->sxStat.reg & (1 << _SPISTAT_SPITBE)) == 0) {
	}

	/* Send the first byte.
	*/
	pspi->sxBuf.reg = *pbSndCur++;

}

/* ------------------------------------------------------------ */
/***	DSPI::intTransfer
**
**	Parameters:
**		cbReq		- number of bytes to receive
**		bPadT		- pad byte to send to the slave device
**		pbRcv		- pointer to buffer to receive returned bytes
**
**	Return Value:
**		none
**
**	Errors:
**		Overrun error handled by the interrupt service routine
**
**	Description:
**		This function will set up and begin an interrupt driven
**		transfer where there is no transmit buffer but the returned
**		bytes are stored. The given pad byte is sent to the slave
**		to cause the returned bytes to be sent by the slave.
*/

void
DSPI::intTransfer(uint16_t cbReq, uint8_t bPadT, uint8_t * pbRcv) {

	/* Set up the control variables for the transfer.
	*/
	cbCur = cbReq;
	pbSndCur = 0;
	pbRcvCur = pbRcv;
	bPad = bPadT;

	/* Wait for the transmitter to be ready
	*/
	while ((pspi->sxStat.reg & (1 << _SPISTAT_SPITBE)) == 0) {
	}

	/* Send the first byte.
	*/
	pspi->sxBuf.reg = bPad;

}

/* ------------------------------------------------------------ */
/***	DSPI::doDspiInterrupt
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
**		This function is called by the interrupt service routine
**		to handle SPI interrupts for this SPI port. It should only
**		be entered while performing an interrupt driven data
**		transfer operation.
*/

void
DSPI::doDspiInterrupt() {

	uint8_t		bTmp;
	uint32_t	regIfs;

	/* Get the interrupt flag status.
	*/
	regIfs = pregIfs->reg;

	/* Check for and handle overrun error interrupt.
	*/
	if ((regIfs & bitErr) != 0) {
		fRov = 1;				// set the receive overflow error flag;
		pspi->sxStat.clr = (1 << _SPISTAT_SPIROV);	//clear status bit
		pregIfs->clr = bitErr;
	}

	/* Check for and handle receive interrupt.
	*/
	if ((regIfs & bitRx) != 0) {

		/* Get the received character.
		*/
		bTmp = pspi->sxBuf.reg;		//read next byte from SPI controller
		cbCur -= 1;					//count this byte as received

		/* Are we storing it? pbRcvCur is 0 if we are sending only
		** and ignoring the received data.
		*/
		if (pbRcvCur != 0) {
			*pbRcvCur++ = bTmp;		//store the received byte into output buffer
		}

		/* Send the next byte to the slave. pbSndCur is 0 if we are
		** receiving only. In this case send the pad byte.
		*/
		if (cbCur > 0) {
			bTmp = (pbSndCur != 0) ? *pbSndCur++ : bPad;
			pspi->sxBuf.reg = bTmp;
		}

		pregIfs->clr = bitRx;		//clear the receive interrupt flag

	}

}

/* ------------------------------------------------------------ */
/*				DSPI0 Object Class Implementation				*/
/* ------------------------------------------------------------ */

#if defined(_DSPI0_BASE)

/***	DSPI0::DSPI0
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
**		Constructor.
*/

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
DSPI0::DSPI0() : DSPI(_DSPI0_MISO_PIN, _DSPI0_MOSI_PIN, _DSPI0_MISO_IN, _DSPI0_MOSI_OUT)
#else
DSPI0::DSPI0() 
#endif
{

	pspi = (p32_spi *) _DSPI0_BASE;
	vec = _DSPI0_VECTOR;
	ipl = ((_DSPI0_IPL & 0x07) << 2) + (_DSPI0_SPL & 0x03);
	pinSS = PIN_DSPI0_SS;

	init(_DSPI0_ERR_IRQ, _DSPI0_RX_IRQ, _DSPI0_TX_IRQ, IntDspi0Handler);
}

/* ------------------------------------------------------------ */
/***	enableInterruptTransfer
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
**		Sets up the interrupt controller and enables interrupts
**		for this SPI port.
*/

void
DSPI0::enableInterruptTransfer() {

	pdspi0 = this;
	DSPI::enableInterruptTransfer();
}

/* ------------------------------------------------------------ */
/***	disableInterruptTransfer
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
**		Turns off SPI interrupts for this SPI port.
*/

void
DSPI0::disableInterruptTransfer() {

	DSPI::disableInterruptTransfer();
	pdspi0 = 0;
}

#endif	// _DSPI0_BASE

/* ------------------------------------------------------------ */
/*				DSPI1 Object Class Implementation				*/
/* ------------------------------------------------------------ */

#if defined(_DSPI1_BASE)

/***	DSPI1::DSPI1
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
**		Constructor.
*/

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
DSPI1::DSPI1() : DSPI(_DSPI1_MISO_PIN, _DSPI1_MOSI_PIN, _DSPI1_MISO_IN, _DSPI1_MOSI_OUT)
#else
DSPI1::DSPI1()
#endif
{

	pspi = (p32_spi *) _DSPI1_BASE;
	vec = _DSPI1_VECTOR;
	ipl = ((_DSPI1_IPL & 0x07) << 2) + (_DSPI1_SPL & 0x03);
	pinSS = PIN_DSPI1_SS;

	init(_DSPI1_ERR_IRQ, _DSPI1_RX_IRQ, _DSPI1_TX_IRQ, IntDspi1Handler);
}

/* ------------------------------------------------------------ */
/***	enableInterruptTransfer
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
**		Sets up the interrupt controller and enables interrupts
**		for this SPI port.
*/

void
DSPI1::enableInterruptTransfer() {

	pdspi1 = this;
	DSPI::enableInterruptTransfer();
}

/* ------------------------------------------------------------ */
/***	disableInterruptTransfer
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
**		Turns off SPI interrupts for this SPI port.
*/

void
DSPI1::disableInterruptTransfer() {


	DSPI::disableInterruptTransfer();
	pdspi1 = 0;
}

#endif	// _DSPI1_BASE

/* ------------------------------------------------------------ */
/*				DSPI2 Object Class Implementation				*/
/* ------------------------------------------------------------ */

#if defined(_DSPI2_BASE)

/***	DSPI2::DSPI2
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
**		Constructor.
*/

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
DSPI2::DSPI2() : DSPI(_DSPI2_MISO_PIN, _DSPI2_MOSI_PIN, _DSPI2_MISO_IN, _DSPI2_MOSI_OUT)
#else
DSPI2::DSPI2()
#endif
{

	pspi = (p32_spi *) _DSPI2_BASE;
	vec = _DSPI2_VECTOR;
	ipl = ((_DSPI2_IPL & 0x07) << 2) + (_DSPI2_SPL & 0x03);
	pinSS = PIN_DSPI2_SS;

	init(_DSPI2_ERR_IRQ, _DSPI2_RX_IRQ, _DSPI2_TX_IRQ, IntDspi2Handler);
}

/* ------------------------------------------------------------ */
/***	enableInterruptTransfer
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
**		Sets up the interrupt controller and enables interrupts
**		for this SPI port.
*/

void
DSPI2::enableInterruptTransfer() {

	pdspi2 = this;
	DSPI::enableInterruptTransfer();
}

/* ------------------------------------------------------------ */
/***	disableInterruptTransfer
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
**		Turns off SPI interrupts for this SPI port.
*/

void
DSPI2::disableInterruptTransfer() {

	DSPI::disableInterruptTransfer();
	pdspi2 = 0;
}

#endif	// _DSPI2_BASE

/* ------------------------------------------------------------ */
/*				DSPI3 Object Class Implementation				*/
/* ------------------------------------------------------------ */

#if defined(_DSPI3_BASE)

/***	DSPI3::DSPI3
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
**		Constructor.
*/

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
DSPI3::DSPI3() : DSPI(_DSPI3_MISO_PIN, _DSPI3_MOSI_PIN, _DSPI3_MISO_IN, _DSPI3_MOSI_OUT)
#else
DSPI3::DSPI3()
#endif
{

	pspi = (p32_spi *) _DSPI3_BASE;
	vec = _DSPI3_VECTOR;
	ipl = ((_DSPI3_IPL & 0x07) << 2) + (_DSPI3_SPL & 0x03);
	pinSS = PIN_DSPI3_SS;

	init(_DSPI3_ERR_IRQ, _DSPI3_RX_IRQ, _DSPI3_TX_IRQ, IntDspi3Handler);
}

/* ------------------------------------------------------------ */
/***	enableInterruptTransfer
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
**		Sets up the interrupt controller and enables interrupts
**		for this SPI port.
*/

void
DSPI3::enableInterruptTransfer() {

	pdspi3 = this;
	DSPI::enableInterruptTransfer();
}

/* ------------------------------------------------------------ */
/***	disableInterruptTransfer
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
**		Turns off SPI interrupts for this SPI port.
*/

void
DSPI3::disableInterruptTransfer() {

	DSPI::disableInterruptTransfer();
	pdspi3 = 0;
}

#endif	// _DSPI3_BASE

/* ------------------------------------------------------------ */
/*			Interrupt Service Routines							*/
/* ------------------------------------------------------------ */

extern "C" {

/* ------------------------------------------------------------ */
/***	IntDspi0Handler
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
**		Interrupt service routine the SPI controller being used
**		logical SPI port DSPI0
*/
#if defined(_DSPI0_VECTOR)

void __attribute__((interrupt(), nomips16)) IntDspi0Handler(void)
{
	if (pdspi0 != 0) {
		pdspi0->doDspiInterrupt();
	}
}
#endif

/* ------------------------------------------------------------ */
/***	IntDspi1Handler
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
**		Interrupt service routine the SPI controller being used
**		logical SPI port DSPI1
*/
#if defined(_DSPI1_VECTOR)

void __attribute__((interrupt(), nomips16)) IntDspi1Handler(void)
{
	if (pdspi1 != 0) {
		pdspi1->doDspiInterrupt();
	}
}
#endif

/* ------------------------------------------------------------ */
/***	IntDspi2Handler
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
**		Interrupt service routine the SPI controller being used
**		logical SPI port DSPI2
*/
#if defined(_DSPI2_VECTOR)

void __attribute__((interrupt(), nomips16)) IntDspi2Handler(void)
{
	if (pdspi2 != 0) {
		pdspi2->doDspiInterrupt();
	}
}
#endif

/* ------------------------------------------------------------ */
/***	IntDspi3Handler
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
**		Interrupt service routine the SPI controller being used
**		logical SPI port DSPI3
*/
#if defined(_DSPI3_VECTOR)

void __attribute__((interrupt(), nomips16)) IntDspi3Handler(void)
{
	if (pdspi3 != 0) {
		pdspi3->doDspiInterrupt();
	}
}
#endif

};		// extern "C"

/* ------------------------------------------------------------ */

/************************************************************************/

