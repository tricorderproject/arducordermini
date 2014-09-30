/************************************************************************/
/*																		*/
/*	Board_Defs.h --	Board Customization for Digilent Cerebot MX7cK		*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent Cerebot		*/
/* MX7cK board.															*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	10/06/2011(GeneA): Created											*/
/*	11/28/2011(GeneA): Moved data definitions and configuration			*/
/*		functions to Board_Data.c										*/
/*	11/29/2011(GeneA): Moved int priority definitions to System_Defs.h	*/
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

#define	_BOARD_NAME_	"Cerebot MX7cK"

/* Define the peripherals available on the board.
*/
#define	NUM_DIGITAL_PINS	61
#define	NUM_ANALOG_PINS		10
#define	NUM_OC_PINS			5
#define	NUM_IC_PINS			3
#define	NUM_TCK_PINS		2
#define	NUM_INT_PINS		5

#define	NUM_SERIAL_PORTS	2
#define	NUM_SPI_PORTS		1
#define	NUM_I2C_PORTS		1

#define	NUM_DSPI_PORTS		3
#define	NUM_DTWI_PORTS		4

/* Define I/O devices on the board.
*/
#define	NUM_LED				4
#define NUM_BTN				3
#define	NUM_SWT				0
#define NUM_SERVO			0

/* Define the number of extended i/o pins. These are pins
** that are not native to the microcontroller. This board
** doesn't have any.
*/
#define	NUM_DIGITAL_PINS_EXTENDED	NUM_DIGITAL_PINS
#define	NUM_ANALOG_PINS_EXTENDED	NUM_ANALOG_PINS

/* ------------------------------------------------------------ */
/*						LED Declarations						*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the LEDs
*/
#define	PIN_LED1	51
#define	PIN_LED2	52
#define	PIN_LED3	53
#define	PIN_LED4	54

/* ------------------------------------------------------------ */
/*					Button Declarations							*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the Buttons
*/
#define	PIN_BTN1	48	
#define	PIN_BTN2	49
#define PIN_BTN3	50

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

#define PIN_OC1		25
#define	PIN_OC2		28
#define	PIN_OC3		29
#define	PIN_OC4		30
#define	PIN_OC5		22

//#define PIN_IC1		not connected
#define PIN_IC2		24
#define PIN_IC3		27
//#define PIN_IC4		not connected
#define	PIN_IC5		31

//#define	PIN_TCK1	not connected
#define	PIN_TCK2	16
//#define	PIN_TCK3	not connected
//#define	PIN_TCK4	not connected
#define	PIN_TCK5	26

/* ------------------------------------------------------------ */
/*					Interrupt Pin Declarations					*/
/* ------------------------------------------------------------ */

#define	PIN_INT0	25
#define	PIN_INT1	36
#define PIN_INT2	44
#define	PIN_INT3	57
#define	PIN_INT4	58

/* ------------------------------------------------------------ */
/*					SPI Pin Declarations						*/
/* ------------------------------------------------------------ */
/* These symbols are defined for compatibility with the original
** SPI library and the original pins_arduino.h
** The default SPI port is on connector JF.
*/
const static uint8_t SS   = 40;		// PIC32 SS4
const static uint8_t MOSI = 41;		// PIC32 SDO4
const static uint8_t MISO = 42;		// PIC32 SDI4
const static uint8_t SCK  = 43;		// PIC32 SCK4

/* The Digilent DSPI library uses these ports.
**		DSPI0	connector JD
**		DSPI1	connector JE
**		DSPI2	connector JF
*/
#define	PIN_DSPI0_SS	24
#define	PIN_DSPI1_SS	32
#define	PIN_DSPI2_SS	40

/* ------------------------------------------------------------ */
/*					Analog Pins									*/
/* ------------------------------------------------------------ */
/* Define symbols for accessing the analog pins. This table is
** used to map an analog pin number to the corresponding digital
** pin number.
*/
#define	A0		0
#define	A1		1
#define A2		2
#define A3		3
#define A4		4
#define A5		5
#define A6		6
#define A7		7
#define A8		20
#define A9		23

/* ------------------------------------------------------------ */
/*					Change Notice Pins							*/
/* ------------------------------------------------------------ */
/* These define the pin numbers for the various change notice
** pins.
*/
//#define	PIN_CN0		//not connected	
//#define	PIN_CN1		//not connected	
//#define	PIN_CN2		//not connected	
//#define	PIN_CN3		//not connected	
#define	PIN_CN4		0
#define	PIN_CN5		1
#define	PIN_CN6		2
#define	PIN_CN7		59
#define	PIN_CN8		48
#define	PIN_CN9		49
//#define	PIN_CN10	//not connected	
//#define	PIN_CN11		//not connected	
#define	PIN_CN12	20
#define	PIN_CN13	22
#define	PIN_CN14	21
//#define	PIN_CN15	//not connected	
#define	PIN_CN16	19
#define	PIN_CN17	42
#define	PIN_CN18	41
#define	PIN_CN19	60
#define	PIN_CN20	32
#define	PIN_CN21	35

/* ------------------------------------------------------------ */
/*					Pin Mapping Macros							*/
/* ------------------------------------------------------------ */
/* This section contains the definitions for pin mapping macros that
/* are being redefined for this board variant.
*/

#undef digitalPinToAnalog
#define	digitalPinToAnalog(P) ( (P) < 10 ? (P) : digital_pin_to_analog_PGM[P] )

#undef analogInPinToChannel
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
extern const uint8_t 	digital_pin_to_analog_PGM[];
extern const uint8_t	analog_pin_to_channel_PGM[];

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

#define	OPT_BOARD_INIT			0	//board needs no special init code
#define	OPT_BOARD_DIGITAL_IO	0	//board does not extend digital i/o functions
#define	OPT_BOARD_ANALOG_READ	0	//board does not extend analogRead
#define	OPT_BOARD_ANALOG_WRITE	0	//board does not extend analogWrite

/* ------------------------------------------------------------ */
/*					Serial Port Declarations					*/
/* ------------------------------------------------------------ */

/* Serial port 0 uses UART1. Connector JE
*/
#define	_SER0_BASE		_UART1_BASE_ADDRESS
#define	_SER0_IRQ		_UART1_ERR_IRQ
#define	_SER0_VECTOR	_UART_1_VECTOR
#define	_SER0_IPL_ISR	_UART1_IPL_ISR
#define	_SER0_IPL		_UART1_IPL_IPC
#define	_SER0_SPL		_UART1_SPL_IPC

/* Serial port 1 uses UART2. Connector JF
*/
#define	_SER1_BASE		_UART2_BASE_ADDRESS
#define	_SER1_IRQ		_UART2_ERR_IRQ
#define	_SER1_VECTOR	_UART_2_VECTOR
#define	_SER1_IPL_ISR	_UART2_IPL_ISR
#define	_SER1_IPL		_UART2_IPL_IPC
#define	_SER1_SPL		_UART2_SPL_IPC

/* ------------------------------------------------------------ */
/*					SPI Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard library SPI port uses SPI4. Connector JF
*/
#define	_SPI_BASE		_SPI4_BASE_ADDRESS
#define _SPI_ERR_IRQ	_SPI4_ERR_IRQ
#define	_SPI_RX_IRQ		_SPI4_RX_IRQ
#define	_SPI_TX_IRQ		_SPI4_TX_IRQ
#define	_SPI_VECTOR		_SPI_4_VECTOR
#define	_SPI_IPL_ISR	_SPI4_IPL_ISR
#define	_SPI_IPL		_SPI4_IPL_IPC
#define	_SPI_SPL		_SPI4_SPL_IPC

/* The Digilent DSPI library uses these ports.
**		DSPI0	connector JD
**		DSPI1	connector JE
**		DSPI2	connector JF
*/
#define	_DSPI0_BASE			_SPI1_BASE_ADDRESS
#define	_DSPI0_ERR_IRQ		_SPI1_ERR_IRQ
#define	_DSPI0_RX_IRQ		_SPI1_RX_IRQ
#define	_DSPI0_TX_IRQ		_SPI1_TX_IRQ
#define	_DSPI0_VECTOR		_SPI_1_VECTOR
#define	_DSPI0_IPL_ISR		_SPI1_IPL_ISR
#define	_DSPI0_IPL			_SPI1_IPL_IPC
#define	_DSPI0_SPL			_SPI1_SPL_IPC

#define	_SPI3_ERR_IRQ	_SPI1A_ERR_IRQ	//this definition is missing from
										// the Microchip header file.
#define	_DSPI1_BASE			_SPI3_BASE_ADDRESS
#define	_DSPI1_ERR_IRQ		_SPI3_ERR_IRQ
#define	_DSPI1_RX_IRQ		_SPI3_RX_IRQ
#define	_DSPI1_TX_IRQ		_SPI3_TX_IRQ
#define	_DSPI1_VECTOR		_SPI_3_VECTOR
#define	_DSPI1_IPL_ISR		_SPI3_IPL_ISR
#define	_DSPI1_IPL			_SPI3_IPL_IPC
#define	_DSPI1_SPL			_SPI3_SPL_IPC

#define	_DSPI2_BASE			_SPI4_BASE_ADDRESS
#define	_DSPI2_ERR_IRQ		_SPI4_ERR_IRQ
#define	_DSPI2_RX_IRQ		_SPI4_RX_IRQ
#define	_DSPI2_TX_IRQ		_SPI4_TX_IRQ
#define	_DSPI2_VECTOR		_SPI_4_VECTOR
#define	_DSPI2_IPL_ISR		_SPI4_IPL_ISR
#define	_DSPI2_IPL			_SPI4_IPL_IPC
#define	_DSPI2_SPL			_SPI4_SPL_IPC

/* ------------------------------------------------------------ */
/*					I2C Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard I2C port uses I2C2 (SCL2/SDA2) on connector J8.
** This bus has fixed pull-ups and contains the EEPROM.
*/
#define	_TWI_BASE		_I2C2_BASE_ADDRESS
#define	_TWI_BUS_IRQ	_I2C2_BUS_IRQ
#define	_TWI_SLV_IRQ	_I2C2_SLAVE_IRQ
#define	_TWI_MST_IRQ	_I2C2_MASTER_IRQ
#define	_TWI_VECTOR		_I2C_2_VECTOR
#define	_TWI_IPL_ISR	_I2C2_IPL_ISR
#define _TWI_IPL		_I2C2_IPL_IPC
#define	_TWI_SPL		_I2C2_SPL_IPC

/* Declarations for Digilent DTWI library. DTWI0 and DTWI1 are
** connected to the 2x4 I2C daisy chain connectors. The pins for the
** other DTWI are on Pmod connectors.
**		DTWI0 is on J7, has jumperable current mirrors for pull-ups
**		DTWI1 is on J8, has fixed pullups and EEPROM
**		DTWI2 is on JE (pins 2&3), digital pins 33 (SCL) & 34 (SDA)
**		DTWI3 is on JF (pins 2&3), digital pins 41 (SCL) & 42 (SDA)
*/
#define	_DTWI0_BASE		_I2C1_BASE_ADDRESS
#define	_DTWI0_BUS_IRQ	_I2C1_BUS_IRQ
#define	_DTWI0_SLV_IRQ	_I2C1_SLAVE_IRQ
#define	_DTWI0_MST_IRQ	_I2C1_MASTER_IRQ
#define	_DTWI0_VECTOR	_I2C_1_VECTOR
#define	_DTWI0_IPL_ISR	_I2C1_IPL_ISR
#define	_DTWI0_IPL		_I2C1_IPL_IPC
#define	_DTWI0_SPL		_I2C1_SPL_IPC

#define	_DTWI1_BASE		_I2C2_BASE_ADDRESS
#define	_DTWI1_BUS_IRQ	_I2C2_BUS_IRQ
#define	_DTWI1_SLV_IRQ	_I2C2_SLAVE_IRQ
#define	_DTWI1_MST_IRQ	_I2C2_MASTER_IRQ
#define	_DTWI1_VECTOR	_I2C_2_VECTOR
#define	_DTWI1_IPL_ISR	_I2C2_IPL_ISR
#define	_DTWI1_IPL		_I2C2_IPL_IPC
#define	_DTWI1_SPL		_I2C2_SPL_IPC

#define	_DTWI2_BASE		_I2C3_BASE_ADDRESS
#define	_DTWI2_BUS_IRQ	_I2C3_BUS_IRQ
#define	_DTWI2_SLV_IRQ	_I2C3_SLAVE_IRQ
#define	_DTWI2_MST_IRQ	_I2C3_MASTER_IRQ
#define	_DTWI2_VECTOR	_I2C_3_VECTOR
#define	_DTWI2_IPL_ISR	_I2C3_IPL_ISR
#define	_DTWI2_IPL		_I2C3_IPL_IPC
#define	_DTWI2_SPL		_I2C3_SPL_IPC

#define	_DTWI3_BASE		_I2C5_BASE_ADDRESS
#define	_DTWI3_BUS_IRQ	_I2C5_BUS_IRQ
#define	_DTWI3_SLV_IRQ	_I2C5_SLAVE_IRQ
#define	_DTWI3_MST_IRQ	_I2C5_MASTER_IRQ
#define	_DTWI3_VECTOR	_I2C_5_VECTOR
#define	_DTWI3_IPL_ISR	_I2C5_IPL_ISR
#define	_DTWI3_IPL		_I2C5_IPL_IPC
#define	_DTWI3_SPL		_I2C5_SPL_IPC

/* ------------------------------------------------------------ */
/*					A/D Converter Declarations					*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */

#endif	//OPT_BOARD_INTERNAL

/* ------------------------------------------------------------ */

#endif	// BOARD_DEFS_H

/************************************************************************/
