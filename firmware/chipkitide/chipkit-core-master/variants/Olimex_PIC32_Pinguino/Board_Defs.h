/************************************************************************/
/*  																	*/
/*	Board_Defs.h --	Default Board Customization Declarations			*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with a generic board using a	*/
/* PIC32 part in a 64-pin package.										*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	10/07/2011(GeneA): Created											*/
/*	11/28/2011(GeneA): Moved data definitions and configuration			*/
/*		functions to Board_Data.c										*/
/*	11/29/2011(GeneA): Moved int priority definitions to System_Defs.h	*/
/*  03/11/2012(BrianS): Modified for Fubarino board                     */
/*  20/05/2013(): Modified for Olimex Pinguino32 board					*/
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

#if !defined(BOARD_DEFS_H)
#define BOARD_DEFS_H

#include <inttypes.h>

/* ------------------------------------------------------------ */
/*				Public Board Declarations						*/
/* ------------------------------------------------------------ */
/* The following define symbols that can be used in a sketch to
** refer to periperhals on the board generically.
*/

#define	_BOARD_NAME_	"PIC32_Pinguino"

/* Define the peripherals available on the board.
*/
#define	NUM_DIGITAL_PINS	36
#define	NUM_ANALOG_PINS		8
#define NUM_OC_PINS		4
#define	NUM_IC_PINS		4
#define	NUM_TCK_PINS		0
#define	NUM_INT_PINS		5

#define	NUM_SERIAL_PORTS	2
#define	NUM_SPI_PORTS		1
#define	NUM_I2C_PORTS		1

#define NUM_DSPI_PORTS		1
#define NUM_DTWI_PORTS		0

/* Define I/O devices on the board.
*/
#define	NUM_LED			2
#define NUM_BTN			1
#define	NUM_SWT			0
#define NUM_SERVO		0

/* ------------------------------------------------------------ */
/*						LED Declarations						*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the LEDs
*/
#define	PIN_LED1	13
#define	PIN_LED2	14

/* ------------------------------------------------------------ */
/*					Button Declarations							*/
/* ------------------------------------------------------------ */

/* One button (PRG) for this board
*/
#define	PIN_BTN1	17  // has pull up

/* Also define the virtual program button for soft reset */
#define USE_VIRTUAL_PROGRAM_BUTTON      1
#define VIRTUAL_PROGRAM_BUTTON_TRIS     TRISDbits.TRISD0
#define VIRTUAL_PROGRAM_BUTTON          LATDbits.LATD0

/* ------------------------------------------------------------ */
/*					Switch Declarations							*/
/* ------------------------------------------------------------ */

/* No switches on this board.
*/

/* ------------------------------------------------------------ */
/*					Servo Pin Declarations						*/
/* ------------------------------------------------------------ */

/* No servo connectors on this board.
*/

/* ------------------------------------------------------------ */
/*					Timer Pin Declarations						*/
/* ------------------------------------------------------------ */

//#define 	PIN_OC1		not connected
#define	PIN_OC2		14
#define	PIN_OC3		0
#define	PIN_OC4		1
#define	PIN_OC5		2

#define PIN_IC1		6
#define PIN_IC2		15
#define PIN_IC3		16
#define PIN_IC4		7
//#define	PIN_IC5		11

//#define	PIN_TCK1	not connected
//#define	PIN_TCK2	not available on the chip
//#define	PIN_TCK3	not available on the chip
//#define	PIN_TCK4	not available on the chip
//#define	PIN_TCK5	not available on the chip

/* ------------------------------------------------------------ */
/*					Interrupt Pin Declarations					*/
/* ------------------------------------------------------------ */

#define	PIN_INT0	17
#define	PIN_INT1	6
#define	PIN_INT2	15
#define	PIN_INT3	16
#define	PIN_INT4	7

/* ------------------------------------------------------------ */
/*					SPI Pin Declarations						*/
/* ------------------------------------------------------------ */
/* These symbols are defined for compatibility with the original
** SPI library and the original pins_arduino.h. SPI2 is used for
** the default SPI port as it's pin numbers stay constant on all
** devices.
*/
/// TODO: For Fubarino, do we need these?
const static uint8_t SS   = 105;		// PIC32 SS2
const static uint8_t MOSI =	104;		// PIC32 SDO2
const static uint8_t MISO = 103;		// PIC32 SDI2
const static uint8_t SCK  = 102;		// PIC32 SCK2

/* The Digilent DSPI library uses these ports.
*/
/// TODO: For Fubarino, do we need these?
#define	PIN_DSPI0_SS	105

/* ------------------------------------------------------------ */
/*					Analog Pins									*/
/* ------------------------------------------------------------ */
/* Define symbols for accessing the analog pins. This table is
** used to map an analog pin number to the corresponding digital
** pin number.
*/
#define	A0	28
#define	A1	29
#define A2	30
#define A3	31
#define A4	32
#define A5	33
#define A6	34
#define A7	35

/* ------------------------------------------------------------ */
/*					Change Notice Pins							*/
/* ------------------------------------------------------------ */
/* These define the pin numbers for the various change notice
** pins.
*/
//#define	PIN_CN0
//#define	PIN_CN1
//#define	PIN_CN2
#define	PIN_CN3		28
#define	PIN_CN4		29
#define	PIN_CN5		30
#define	PIN_CN6		31
//#define	PIN_CN7		28
#define	PIN_CN8		13
#define	PIN_CN9		12
#define	PIN_CN10	11
#define	PIN_CN11	10
#define	PIN_CN12	9
#define	PIN_CN13	2
#define	PIN_CN14	3
#define	PIN_CN15	4
#define	PIN_CN16	5
//#define	PIN_CN17	28
//#define	PIN_CN18	29

/* ------------------------------------------------------------ */
/*					Pin Mapping Macros							*/
/* ------------------------------------------------------------ */
/* Macros used to access the port and pin mapping tables.
** These are mostly generic, but some of them may be board specific.
** These perform slightly better as macros compared to inline functions
*/
#define digitalPinToPort(P) ( digital_pin_to_port_PGM[P]  )
#define digitalPinToBitMask(P) ( digital_pin_to_bit_mask_PGM[P]  )
#define digitalPinToTimerOC(P)  ( (digital_pin_to_timer_PGM[P] & _MSK_TIMER_OC)  )
#define digitalPinToTimerIC(P)  ( (digital_pin_to_timer_PGM[P] & _MSK_TIMER_IC)  )
#define digitalPinToTimerTCK(P) ( (digital_pin_to_timer_PGM[P] & _MSK_TIMER_TCK) )
#define	digitalPinToTimer(P)	digitalPinToTimerOC(P)
#define portRegisters(P) ( port_to_tris_PGM[P] )
#define portModeRegister(P) ( (volatile uint32_t *)port_to_tris_PGM[P] )
#define portInputRegister(P) ( (volatile uint32_t *)(port_to_tris_PGM[P] + 0x0010) )
#define portOutputRegister(P) ( (volatile uint32_t *)(port_to_tris_PGM[P] + 0x0020) )

// This definition can be used for the default mapping.
//#define	digitalPinToAnalog(P) ( (((P) > 15) && ((P) < 32)) ? (P)-16 : NOT_ANALOG_PIN )
// This definition can be used for the non-default case where there
// is a mapping table to go from digital pin to analog pin
#define	digitalPinToAnalog(P) ( digital_pin_to_analog_PGM[P] )

// This definition can be used for the default one-to-one mapping
//#define analogInPinToChannel(P) ( P )
// This definition is used when there isn't a one-to-one mapping
// This uses a table to do the mapping.
#define analogInPinToChannel(P) ( analog_pin_to_channel_PGM[P]  )

/* ------------------------------------------------------------ */
/*					Data Definitions							*/
/* ------------------------------------------------------------ */

/* The following declare externals to access the pin mapping
** tables.
*/

#if !defined(OPT_BOARD_DATA)

extern const uint32_t	port_to_tris_PGM[];
extern const uint8_t	digital_pin_to_port_PGM[];
extern const uint16_t	digital_pin_to_bit_mask_PGM[];
extern const uint16_t	digital_pin_to_timer_PGM[];

//#if defined(_NOT_USED_)
extern const uint8_t 	digital_pin_to_analog_PGM[];
//#endif

//#if defined(_NOT_USED_)
extern const uint8_t	analog_pin_to_channel_PGM[];
//#endif

#endif

/* ------------------------------------------------------------ */
/*				Internal Declarations							*/
/* ------------------------------------------------------------ */
/* The following declarations are used to map peripherals for	*/
/* the core and libraries and to provide configuration options	*/
/* for the core. They are not normally needed by a user sketch.	*/
/* ------------------------------------------------------------ */

#if defined(OPT_BOARD_INTERNAL)

/* ------------------------------------------------------------ */
/*				Core Configuration Declarations					*/
/* ------------------------------------------------------------ */
/*																*/
/* These are conditional compilation switches that control the	*/
/* board core configuration functions. These functions provide	*/
/* hooks that can call from some of the core functions into		*/
/* functions defined below that can be used to extend or		*/
/* replace the default behavior of the core function. To use	*/
/* this, enter the appropriate code into the appropriate		*/
/* function skeleton below and then set the appropriate switch	*/
/* value to 1. This will cause the configuration function to be	*/
/* compiled into the build and will cause the code to call the	*/
/* hook function to be compiled into the core function.			*/
/*																*/
/* ------------------------------------------------------------ */

#define	OPT_BOARD_INIT			1	//board needs special init code
#define	OPT_BOARD_DIGITAL_IO	0	//board does not extend digital i/o functions
#define	OPT_BOARD_ANALOG_READ	0	//board does not extend analogRead
#define	OPT_BOARD_ANALOG_WRITE	0	//board does not extend analogWrite

/* ------------------------------------------------------------ */
/*					Serial Port Declarations					*/
/* ------------------------------------------------------------ */

/* Serial port 0 uses UART1
*/
#define	_SER0_BASE		_UART1_BASE_ADDRESS
#define	_SER0_IRQ		_UART1_ERR_IRQ
#define	_SER0_VECTOR	_UART_1_VECTOR
#define	_SER0_IPL_ISR	_UART1_IPL_ISR
#define	_SER0_IPL		_UART1_IPL_IPC
#define	_SER0_SPL		_UART1_SPL_IPC
//#define>_SER0_RX_PIN    8$
//#define>_SER0_TX_PIN    9$



/* Serial port 1 uses UART2
*/
#define	_SER1_BASE		_UART2_BASE_ADDRESS
#define	_SER1_IRQ		_UART2_ERR_IRQ
#define	_SER1_VECTOR	_UART_2_VECTOR
#define	_SER1_IPL_ISR	_UART2_IPL_ISR
#define	_SER1_IPL		_UART2_IPL_IPC
#define	_SER1_SPL		_UART2_SPL_IPC
//#define>_SER0_RX_PIN    28$
//#define>_SER0_TX_PIN    29$



/* ------------------------------------------------------------ */
/*					SPI Port Declarations						*/
/* ------------------------------------------------------------ */

/* The default SPI port uses SPI2. The pins for SPI2 stay the
** same on all PIC32 devices. The pins for SPI1 move around,
** and the ports beyond SPI2 aren't defined on some parts.
*/
#define	_SPI_BASE		_SPI2_BASE_ADDRESS
#define _SPI_ERR_IRQ	_SPI2_ERR_IRQ
#define	_SPI_RX_IRQ		_SPI2_RX_IRQ
#define	_SPI_TX_IRQ		_SPI2_TX_IRQ
#define	_SPI_VECTOR		_SPI_2_VECTOR
#define	_SPI_IPL_ISR	_SPI2_IPL_ISR
#define	_SPI_IPL		_SPI2_IPL_IPC
#define	_SPI_SPL		_SPI2_SPL_IPC

/* The Digilent DSPI library uses the same port.
*/
#define	_DSPI0_BASE			_SPI2_BASE_ADDRESS
#define	_DSPI0_ERR_IRQ		_SPI2_ERR_IRQ
#define	_DSPI0_RX_IRQ		_SPI2_RX_IRQ
#define	_DSPI0_TX_IRQ		_SPI2_TX_IRQ
#define	_DSPI0_VECTOR		_SPI_2_VECTOR
#define	_DSPI0_IPL_ISR		_SPI2_IPL_ISR
#define	_DSPI0_IPL			_SPI2_IPL_IPC
#define	_DSPI0_SPL			_SPI2_SPL_IPC

/* ------------------------------------------------------------ */
/*					I2C Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard I2C port uses I2C1 (SCL1/SDA1). These come to pins
** A4/A5 on the analog connector. It is necessary to have jumpers
** JP6/JP8 set appropriately (RG2/RG3 position) to access the I2C
** signals.
*/
#define	_TWI_BASE		_I2C1_BASE_ADDRESS
#define	_TWI_BUS_IRQ	_I2C1_BUS_IRQ
#define	_TWI_SLV_IRQ	_I2C1_SLAVE_IRQ
#define	_TWI_MST_IRQ	_I2C1_MASTER_IRQ
#define	_TWI_VECTOR		_I2C_1_VECTOR
#define	_TWI_IPL_ISR	_I2C1_IPL_ISR
#define _TWI_IPL		_I2C1_IPL_IPC
#define	_TWI_SPL		_I2C1_SPL_IPC

/* Declarations for Digilent DTWI library.
**		DTWI0 is on A4/A5 (see above comment).
**		DTWI1 is on digital pins 38 & 39.
*/
#define	_DTWI0_BASE		_I2C1_BASE_ADDRESS
#define	_DTWI0_BUS_IRQ	_I2C1_BUS_IRQ
#define	_DTWI0_SLV_IRQ	_I2C1_SLAVE_IRQ
#define	_DTWI0_MST_IRQ	_I2C1_MASTER_IRQ
#define	_DTWI0_VECTOR	_I2C_1_VECTOR
#define	_DTWI0_IPL		_I2C1_IPL_IPC
#define	_DTWI0_SPL		_I2C1_SPL_IPC

#define	_DTWI1_BASE		_I2C2_BASE_ADDRESS
#define	_DTWI1_BUS_IRQ	_I2C2_BUS_IRQ
#define	_DTWI1_SLV_IRQ	_I2C2_SLAVE_IRQ
#define	_DTWI1_MST_IRQ	_I2C2_MASTER_IRQ
#define	_DTWI1_VECTOR	_I2C_2_VECTOR
#define	_DTWI1_IPL		_I2C2_IPL_IPC
#define	_DTWI1_SPL		_I2C2_SPL_IPC

/* ------------------------------------------------------------ */
/*					A/D Converter Declarations					*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */

#endif	// OPT_BOARD_INTERNAL

/* ------------------------------------------------------------ */

#endif	// BOARD_DEFS_H

/************************************************************************/
