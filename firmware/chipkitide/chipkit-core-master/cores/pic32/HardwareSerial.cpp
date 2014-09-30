//************************************************************************
//*	HardwareSerial.cpp
//*	
//*	Arduino core files for PIC32
//*		Copyright (c) 2010, 2011 by Mark Sproul
//*	
//*	
//************************************************************************
//*	this code is based on code Copyright (c) 2005-2006 David A. Mellis
//*	
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.//*	See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA  02111-1307  USA
//*	
//*	
//************************************************************************
//*		Important Note
//*			On AVR, uarts start at 0, on Pic, they start at 1
//*			So Serial is uart 1
//*			So Serial1 is really uart 2
//*			etc
//*
//************************************************************************
//*	USB support
//*		If USB is enabled, the first serial port (Serial.xxx) is redirected to USB
//*		Serial0.xxx then takes over for the 1st uart in case the programmer needs to use it as well
//************************************************************************
//*	this code is best viewed with tabs set to 4 spaces
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 12,	2010	<MLS> Got MPLAB X working on MacOSX 1.6 for the first time
//*	Oct 12,	2010	<MLS> Discovered pic32-gcc does not support c++
//*	Oct 13,	2010	<MLS> borrowing code from "uart_interrupt.c" example from microchip
//*	Dec 13,	2010	<MLS> Interrupt must be AFTER the read
//*	Jan 22,	2011	<MLS> Working on testing serial1 -> 3
//*	Feb  6,	2011	<MLS> Uart2 working pin Pic32 starterKit (32MX360F512L)
//*	Feb  6,	2011	<MLS> Uart1B, Uart3A, Uart3B working pin Digilent MEGA (32MX795F512L)
//*	Apr 10,	2011	<MLS> Added defs for UNO board
//*	Apr 13,	2011	<MLS> Support for UART4 is NOT finished
//*	May 25, 2011	<MLS> Added support for Uart2 on UNO32
//*	Jun 17,	2011	<MLS> Added Serial4 and Serial5 for MEGA32, ISRs not finished
//*	Jun 24,	2011	<MLS> Adding USB support, code from Rich Testardi (http://www.cpustick.com/downloads.htm)
//*	Jul  3,	2011	<MLS> Fixed bug in baud rate calculation (http://www.chipkit.org/forum/viewtopic.php?f=7&t=213&p=948#p948)
//*	Sep  1,	2011	<MLS> Issue #111, #ifdefs around <plib.h>, it was being included twice
//*	Nov  1,	2011	<MLS> Issue #140, HardwareSerial not derived from Stream 
//*	Nov  1,	2011	<MLS> Also fixed some other compatibilty issues
//* Nov 12, 2012	<GeneApperson> Rewrite for board variant support
//* Sep  8, 2012    <BrianSchmalz> Fix dropping bytes on USB RX bug
//*	Jul 26, 2012	<GeneApperson> Added PPS support for PIC32MX1xx/MX2xx devices 
//* Nov 23, 2012    <BrianSchmalz> Auto-detect when to use BRGH = 1 (high baud rates)
//*	Feb  6, 2013	<GeneApperson> Removed dependencies on the Microchip plib library
//************************************************************************
#if !defined(__LANGUAGE_C__)
#define __LANGUAGE_C__
#endif

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <p32xxxx.h>
#include <sys/attribs.h>

#include "wiring.h"
#include "wiring_private.h"

#define OPT_SYSTEM_INTERNAL
#define	OPT_BOARD_INTERNAL
#include "pins_arduino.h"

#include "HardwareSerial.h"

#if defined(_USE_USB_FOR_SERIAL_)
//	#define	_DEBUG_USB_VIA_SERIAL0_
#endif

extern "C"
{
void __attribute__((interrupt(),nomips16)) IntSer0Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer1Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer2Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer3Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer4Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer5Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer6Handler(void);
void __attribute__((interrupt(),nomips16)) IntSer7Handler(void);
}

/* ------------------------------------------------------------ */
/*			General Declarations								*/
/* ------------------------------------------------------------ */
// Baud rate above which we use high baud divisor (BRGH = 1)
#define LOW_HIGH_BAUD_SPLIT     200000

/* ------------------------------------------------------------ */
/*			HardwareSerial Object Class Implementation			*/
/* ------------------------------------------------------------ */
/***	HardwareSerial::HardwareSerial
**
**	Parameters:
**		uartP		- pointer to base register for UART
**		irqP		- base IRQ number for the UART
**		vecP		- interrupt vector number used by this UART
**		iplP		- interrupt priority level for the interrupt
**		splP		- interrupt sub-priority level
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Object constructor. Initialize member variables, and
**		any global variables used by the object.
*/

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
HardwareSerial::HardwareSerial(p32_uart * uartT, int irqT, int vecT, int iplT, int splT, isrFunc isrHandler, int pinT, int pinR, ppsFunctionType ppsT, ppsFunctionType ppsR)
#else
HardwareSerial::HardwareSerial(p32_uart * uartT, int irqT, int vecT, int iplT, int splT, isrFunc isrHandler)
#endif
{
	uart = uartT;
	irq  = irqT;
	vec  = vecT;
	irq  = (uint8_t)irqT;
	vec  = (uint8_t)vecT;
	ipl  = (uint8_t)iplT;
	spl  = (uint8_t)splT;
    isr  = isrHandler;

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	pinTx = (uint8_t)pinT;
	pinRx = (uint8_t)pinR;
	ppsTx = ppsT;
	ppsRx = ppsR;
#endif

	/* The interrupt flag and enable control register addresses and
	** the bit numbers for the flag bits can be computed from the
	** IRQ number for the UART. The irq parameter specifies the IRQ
	** for the ERR interrupt. The RX interrupt IRQ is ERR+1 and the
	** TX interrupt IRQ is ERR+2; There are 32 IRQ bits in each IFS
	** and IEC register. For each IFS register, there is a SET, CLR,
	** and INV register, so the distance (in dwords) from IFS0 to IFS1
	** is 4.
	** The interrupt priorty control register address and the priority bits
	** can be computed from the vector number. Each IPC register contains the
	** the priority bits for four vectors. Each byte of an IPC registger contains
	** the priority and sub-priority bits arranged such that  bits 0-1 are
	** the sub-priority, bits 2-4 the priority, and bits 5-7 unused.
	*/
	ifs = ((p32_regset *)&IFS0) + (irq / 32);	//interrupt flag register set
	iec = ((p32_regset *)&IEC0) + (irq / 32);	//interrupt enable control reg set

	bit_err = 1 << (irq % 32);		//error interrupt flag/enable bit
	bit_rx  = 1 << ((irq+1) % 32);	//rx interrupt flag/enable bit
	bit_tx  = 1 << ((irq+2) % 32);	//tx interrupt flag/enable bit
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::begin
**
**	Parameters:
**		baudRate		- baud rate to use on port
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the UART for use, setting the baud rate to the
**		requested value, data size of 8-bits, and no parity.
*/

void HardwareSerial::begin(unsigned long baudRate)
{
	p32_regset *	ipc;	//interrupt priority control register set
	int				irq_shift;

	/* Initialize the receive buffer.
	*/
	purge();

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	/* Map the UART TX to the appropriate pin.
	*/
    mapPps(pinTx, ppsTx);

	/* Map the UART RX to the appropriate pin.
	*/
    mapPps(pinRx, ppsRx);
#endif

    setIntVector(vec, isr);

	/* Set the interrupt privilege level and sub-privilege level
	*/
	setIntPriority(vec, ipl, spl);

	/* Clear the interrupt flags, and set the interrupt enables for the
	** interrupts used by this UART.
	*/
	ifs->clr = bit_rx + bit_tx + bit_err;	//clear all interrupt flags

	iec->clr = bit_rx + bit_tx + bit_err;	//disable all interrupts
	iec->set = bit_rx;						//enable rx interrupts

	/* Initialize the UART itself.
	**	http://www.chipkit.org/forum/viewtopic.php?f=7&t=213&p=948#p948
    ** Use high baud rate divisor for bauds over LOW_HIGH_BAUD_SPLIT
    */
	uart->uxSta.reg = 0;
    if (baudRate < LOW_HIGH_BAUD_SPLIT)
    {
        uart->uxBrg.reg    = ((__PIC32_pbClk / 16 / baudRate) - 1);      // calculate actual BAUD generate value.
        uart->uxMode.reg = (1 << _UARTMODE_ON);                          // enable UART module
    }
    else
    {
        uart->uxBrg.reg    = ((__PIC32_pbClk / 4 / baudRate) - 1);       // calculate actual BAUD generate value.
        uart->uxMode.reg = (1 << _UARTMODE_ON) | (1 << _UARTMODE_BRGH);  // enable UART module
    }
    uart->uxSta.reg  = (1 << _UARTSTA_UTXEN) + (1 << _UARTSTA_URXEN);    // enable transmitter and receiver
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::end
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
**		Disable the UART and UART interrupts.
*/

void HardwareSerial::end()
{
	p32_regset *	iec;	//interrupt enable control register set

	/* Disable all UART interrupts.
	*/
	iec = ((p32_regset *)&IEC0) + (irq / 32);	//interrupt enable control reg set
	iec->clr = bit_err + bit_rx + bit_tx;
	
	/* Disable the UART so that the pins can be used as general purpose I/O
	*/
	uart->uxMode.reg =	0;

    clearIntVector(vec);
}

/* ------------------------------------------------------------ */
/***	HardwareSerial.available
**
**	Parameters:
**		none
**
**	Return Value:
**		Returns the number of characters available in the receive buffer
**
**	Errors:
**		none
**
**	Description:
**		Return the number of characters currently available in the
**		receive buffer.
*/

int HardwareSerial::available(void)
{
	return (RX_BUFFER_SIZE + rx_buffer.head - rx_buffer.tail) % RX_BUFFER_SIZE;
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::peek
**
**	Parameters:
**		none
**
**	Return Value:
**		returns the next character from the receive buffer
**
**	Errors:
**		returns -1 if no characters in buffer
**
**	Description:
**		This returns the next character in the receive buffer without
**		removing it from the buffer, or -1 if no characters are in the buffer.
*/

int HardwareSerial::peek()
{
	if (rx_buffer.head == rx_buffer.tail)
	{
		return -1;
	}
	else
	{
		return rx_buffer.buffer[rx_buffer.tail];
	}
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::read
**
**	Parameters:
**		none
**
**	Return Value:
**		next character from the receive buffer
**
**	Errors:
**		returns -1 if no characters in buffer
**
**	Description:
**		Return the next character from the receive buffer and remove
**		it from the buffer, or -1 if no characters are available in
**		the buffer.
*/

int HardwareSerial::read(void)
{
	unsigned char theChar;

	// if the head isn't ahead of the tail, we don't have any characters
	if (rx_buffer.head == rx_buffer.tail)
	{
		return -1;
	}
	else
	{
		theChar			= rx_buffer.buffer[rx_buffer.tail];
		rx_buffer.tail	= (rx_buffer.tail + 1) % RX_BUFFER_SIZE;
		return (theChar);
	}
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::flush
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
**		Empty the send buffer by waiting for the
**		fifo to empty and the transmitter to become idle
*/
void HardwareSerial::flush()
{
	while ((uart->uxSta.reg & (1 << _UARTSTA_TMRT)) == 0)	//check the TRMT bit
	{
		//* wait for the transmitter to be clear
	}
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::purge
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
**		Empty the receive buffer by discarding any characters in
**		the buffer.
*/

void HardwareSerial::purge()
{
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// were full, not empty.
	rx_buffer.head = rx_buffer.tail;
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::write
**
**	Parameters:
**		theChar		- the character to transmit
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Wait until the transmitter is idle, and then transmit the
**		specified character.
*/

void HardwareSerial::write(uint8_t theChar)
{

	while ((uart->uxSta.reg & (1 << _UARTSTA_UTXBF)) != 0)	//check the UTXBF bit
  {
		//* wait for the transmitter buffer to have room
	}

	uart->uxTx.reg = theChar;
}

/* ------------------------------------------------------------ */
/***	HardwareSerial::doSerialInt
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
**		for the UART being used by this object. It's purpose is
**		to process receive interrupts and place the received
**		characters into the receive buffer.
*/

void HardwareSerial::doSerialInt(void)
{
	int		bufIndex;
	uint8_t	ch;

	/* If it's a receive interrupt, get the character and store
	** it in the receive buffer.
	*/
	if ((ifs->reg & bit_rx) != 0)
	{
		ch = uart->uxRx.reg;
		bufIndex	= (rx_buffer.head + 1) % RX_BUFFER_SIZE;
	
		/* If we should be storing the received character into the location
		** just before the tail (meaning that the head would advance to the
		** current location of the tail), we're about to overflow the buffer
		** and so we don't write the character or advance the head.
		*/
		if (bufIndex != rx_buffer.tail)
		{
			rx_buffer.buffer[rx_buffer.head] = ch;
			rx_buffer.head = bufIndex;
		}

		/* Clear the interrupt flag.
		*/
		ifs->clr = bit_rx;
	}

	/* If it's a transmit interrupt, ignore it, as we don't current
	** have interrupt driven i/o on the transmit side.
	*/
	if ((ifs->reg & bit_tx) != 0)
	{
		/* Clear the interrupt flag.
		*/
		ifs->clr = bit_tx;
	}

}

/* ------------------------------------------------------------ */
/*				USBSerial Object Class Implementation			*/
/* ------------------------------------------------------------ */


//*******************************************************************************************

#pragma mark -
#pragma mark -----------------USB support

#if defined(_USB) && defined(_USE_USB_FOR_SERIAL_)

#include	"HardwareSerial_cdcacm.h"
#include	"HardwareSerial_usb.h"

ring_buffer rx_bufferUSB = { { 0 }, 0, 0 };

#define     USBSerialBufferFree()     (((RX_BUFFER_SIZE - 1) + rx_bufferUSB.tail - rx_bufferUSB.head) % RX_BUFFER_SIZE)

//*******************************************************************************************
// Return TRUE if we could take the character, return FALSE if there wasn't room
inline boolean store_char(unsigned char theChar, ring_buffer *rx_buffer)
{
int	bufIndex;

    // Compute the place where we want to store this byte - one beyond the head
	bufIndex	= (rx_buffer->head + 1) % RX_BUFFER_SIZE;

    // If the place where we are about to store the character is the tail, then
    // we would overflow the buffer if we put our character there. This is because
    // if head = tail, the buffer is empty. If head = tail-1, then the buffer
    // is full. So only write into the buffer if we are not writing at the tail.
	if (bufIndex != rx_buffer->tail)
	{
		rx_buffer->buffer[rx_buffer->head]	=	theChar;
		rx_buffer->head	=	bufIndex;
        return(true);
	}
    else
    {
        return(false);
	}
}

//****************************************************************
void	USBresetRoutine(void)
{
	
}

//****************************************************************
// Need to return FALSE if we need USB to hold off for awhile
boolean	USBstoreDataRoutine(const byte *buffer, int length)
{
    unsigned int	i;

    // Put each byte into the serial recieve buffer
    for (i=0; i<length; i++)
	{
        store_char(buffer[i], &rx_bufferUSB);
	}
    // If there isn't going to be enough space for a whole nother buffer, then return
    // false so USB will NAK and we won't get any more data.
    if (USBSerialBufferFree() < USB_SERIAL_MIN_BUFFER_FREE)
    {
        return(false);
    }
    else
    {
        return(true);
    }
}


//*******************************************************************************************
USBSerial::USBSerial(ring_buffer	*rx_buffer)
{
	_rx_buffer			=	rx_buffer;
	_rx_buffer->head	=	0;
	_rx_buffer->tail	=	0;
}

USBSerial::operator int() {
    return gConnected ? 1 : 0;
}

#ifdef _DEBUG_USB_VIA_SERIAL0_
	#define	DebugViaSerial0(x)	Serial0.println(x)
#else
	#define	DebugViaSerial0(x)
#endif


//*******************************************************************************************
void USBSerial::begin(unsigned long baudRate)
{
	DebugViaSerial0("USBSerial::begin");

	DebugViaSerial0("calling usb_initialize");
	usb_initialize();
	DebugViaSerial0("returned from usb_initialize");

	cdcacm_register(USBresetRoutine, USBstoreDataRoutine);
	DebugViaSerial0("returned from cdcacm_register");

	// Must enable glocal interrupts - in this case, we are using multi-vector mode
	//INTEnableSystemMultiVectoredInt();
	DebugViaSerial0("INTEnableSystemMultiVectoredInt");

}


//*******************************************************************************************
void USBSerial::end()
{
}

//*******************************************************************************************
int USBSerial::available(void)
{
	return (RX_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % RX_BUFFER_SIZE;
}

//*******************************************************************************************
int USBSerial::peek()
{
	if (_rx_buffer->head == _rx_buffer->tail)
	{
		return -1;
	}
	else
	{
		return _rx_buffer->buffer[_rx_buffer->tail];
	}
}

//*******************************************************************************************
int USBSerial::read(void)
{
	unsigned char theChar;

	// If the head = tail, then the buffer is empty, so nothing to read
	if (_rx_buffer->head == _rx_buffer->tail)
	{
		return -1;
	}
	else
	{
		theChar				=	_rx_buffer->buffer[_rx_buffer->tail];
		_rx_buffer->tail	=	(_rx_buffer->tail + 1) % RX_BUFFER_SIZE;
        
        // If we just made enough room for the next packet to fit into our buffer,
        // start the packets flowing from the PC again
        if (USBSerialBufferFree() >= USB_SERIAL_MIN_BUFFER_FREE)
        {
            cdcacm_command_ack();
        }
        
		return (theChar);
	}
}

//*******************************************************************************************
void USBSerial::flush()
{
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// don't reverse this or there may be problems if the RX interrupt
	// occurs after reading the value of rx_buffer_head but before writing
	// the value to rx_buffer_tail; the previous value of rx_buffer_head
	// may be written to rx_buffer_tail, making it appear as if the buffer
	// were full, not empty.
	_rx_buffer->head	=	_rx_buffer->tail;
}

//*******************************************************************************************
void USBSerial::write(uint8_t theChar)
{
unsigned char	usbBuf[4];

	usbBuf[0]	=	theChar;
	
	cdcacm_print(usbBuf, 1);
}

//*	testing showed 63 gave better speed results than 64

#define	kMaxUSBxmitPkt	63
//*******************************************************************************************
void USBSerial::write(const uint8_t *buffer, size_t size)
{

	if (size < kMaxUSBxmitPkt)
	{
		//*	it will fit in one transmit packet
		cdcacm_print(buffer, size);
	}
	else
	{
	//*	we can only transmit a maxium of 64 bytes at a time, break it up into 64 byte packets
	unsigned char	usbBuffer[kMaxUSBxmitPkt + 2];
	unsigned short	ii;
	size_t 			packetSize;
	
		packetSize	=	0;
		for (ii=0; ii<size; ii++)
		{
			usbBuffer[packetSize++]	=	buffer[ii];
			if (packetSize >= kMaxUSBxmitPkt)
			{
				cdcacm_print(usbBuffer, packetSize);
				packetSize	=	0;
			}
		}
		if (packetSize > 0)
		{
			cdcacm_print(usbBuffer, packetSize);
		}
	}
}

//*******************************************************************************************
void USBSerial::write(const char *str)
{
size_t size;

	size	=	strlen(str);
	write((const uint8_t *)str, size);
}


#endif		//	defined(_USB)



/* ------------------------------------------------------------ */
/*			UART Interrupt Service Routines						*/
/* ------------------------------------------------------------ */

//*	we need the extern C so that the interrupt handler names don't
//* get mangled by C++

extern "C" {

/* ------------------------------------------------------------ */
/***	IntSer0Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 0.
*/
#if defined(_SER0_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer0Handler(void)
{
#if defined(_USB) && defined(_USE_USB_FOR_SERIAL_)
	Serial0.doSerialInt();
#else
	Serial.doSerialInt();
#endif
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer1Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 1.
*/
#if defined(_SER1_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer1Handler(void)
{
	Serial1.doSerialInt();
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer2Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 2.
*/
#if defined(_SER2_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer2Handler(void)
{
	Serial2.doSerialInt();
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer3Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 3.
*/
#if defined(_SER3_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer3Handler(void)
{
	Serial3.doSerialInt();
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer4Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 4.
*/
#if defined(_SER4_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer4Handler(void)
{
	Serial4.doSerialInt();
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer5Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 5.
*/
#if defined(_SER5_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer5Handler(void)
{
	Serial5.doSerialInt();
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer6Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 6.
*/
#if defined(_SER6_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer6Handler(void)
{
	Serial6.doSerialInt();
}
#endif

/* ------------------------------------------------------------ */
/***	IntSer7Handler
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
**		Interrupt service routine for the UART being used by
**		serial port 7.
*/
#if defined(_SER7_VECTOR)

void __attribute__((interrupt(), nomips16)) IntSer7Handler(void)
{
	Serial7.doSerialInt();
}
#endif

};	// extern C

/* ------------------------------------------------------------ */
/*			Serial Port Object Instances						*/
/* ------------------------------------------------------------ */

#if defined(_USB) && defined(_USE_USB_FOR_SERIAL_)
/* If we're using USB for serial, the USB serial port gets
** instantiated as Serial and hardware serial port 0 gets
** instantiated as Serial0.
*/
USBSerial		Serial(&rx_bufferUSB);
#if defined(_SER0_BASE)
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
HardwareSerial Serial0((p32_uart *)_SER0_BASE, _SER0_IRQ, _SER0_VECTOR, _SER0_IPL, _SER0_SPL, IntSer0Handler, _SER0_TX_PIN, _SER0_RX_PIN, _SER0_TX_OUT, _SER0_RX_IN);
#else
HardwareSerial Serial0((p32_uart *)_SER0_BASE, _SER0_IRQ, _SER0_VECTOR, _SER0_IPL, _SER0_SPL, IntSer0Handler);
#endif
#endif

#else
/* If we're not using USB for serial, then hardware serial port 0
** gets instantiated as Serial.
** NOTE: PIC32MX1xx/2xx devices only have 2 UARTS, so we're not defining more variant
** object instances for those devices.
*/
#if defined(_SER0_BASE)
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
HardwareSerial Serial((p32_uart *)_SER0_BASE, _SER0_IRQ, _SER0_VECTOR, _SER0_IPL, _SER0_SPL, IntSer0Handler, _SER0_TX_PIN, _SER0_RX_PIN, _SER0_TX_OUT, _SER0_RX_IN);
#else
HardwareSerial Serial((p32_uart *)_SER0_BASE, _SER0_IRQ, _SER0_VECTOR, _SER0_IPL, _SER0_SPL, IntSer0Handler);
#endif
#endif

#endif	//defined(_USB) && defined(_USE_USB_FOR_SERIAL_)

#if defined(_SER1_BASE)
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
HardwareSerial Serial1((p32_uart *)_SER1_BASE, _SER1_IRQ, _SER1_VECTOR, _SER1_IPL, _SER1_SPL, IntSer1Handler, _SER1_TX_PIN, _SER1_RX_PIN, _SER1_TX_OUT, _SER1_RX_IN);
#else
HardwareSerial Serial1((p32_uart *)_SER1_BASE, _SER1_IRQ, _SER1_VECTOR, _SER1_IPL, _SER1_SPL, IntSer1Handler);
#endif
#endif

#if defined(_SER2_BASE)
HardwareSerial Serial2((p32_uart *)_SER2_BASE, _SER2_IRQ, _SER2_VECTOR, _SER2_IPL, _SER2_SPL, IntSer2Handler);
#endif

#if defined(_SER3_BASE)
HardwareSerial Serial3((p32_uart *)_SER3_BASE, _SER3_IRQ, _SER3_VECTOR, _SER3_IPL, _SER3_SPL, IntSer3Handler);
#endif

#if defined(_SER4_BASE)
HardwareSerial Serial4((p32_uart *)_SER4_BASE, _SER4_IRQ, _SER4_VECTOR, _SER4_IPL, _SER4_SPL, IntSer4Handler);
#endif

#if defined(_SER5_BASE)
HardwareSerial Serial5((p32_uart *)_SER5_BASE, _SER5_IRQ, _SER5_VECTOR, _SER5_IPL, _SER5_SPL, IntSer5Handler);
#endif

#if defined(_SER6_BASE)
HardwareSerial Serial6((p32_uart *)_SER6_BASE, _SER6_IRQ, _SER6_VECTOR, _SER6_IPL, _SER6_SPL, IntSer6Handler);
#endif

#if defined(_SER7_BASE)
HardwareSerial Serial7((p32_uart *)_SER7_BASE, _SER7_IRQ, _SER7_VECTOR, _SER7_IPL, _SER7_SPL, IntSer7Handler);
#endif

/* ------------------------------------------------------------ */

/************************************************************************/
