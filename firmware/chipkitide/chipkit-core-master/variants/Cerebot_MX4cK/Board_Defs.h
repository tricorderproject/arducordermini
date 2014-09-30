/************************************************************************/
/*																		*/
/*	Board_Defs.h --	Board Customization for Digilent Cerebot MX4cK		*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent Cerebot		*/
/* MX4cK board.															*/
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

#define	_BOARD_NAME_	"Cerebot MX4cK"

/* Define the Microcontroller peripherals available on the board.
*/
#define	NUM_DIGITAL_PINS	74
#define	NUM_ANALOG_PINS		14
#define	NUM_OC_PINS			5
#define	NUM_IC_PINS			5
#define	NUM_TCK_PINS		4
#define	NUM_INT_PINS		5

#define	NUM_SERIAL_PORTS	2
#define	NUM_SPI_PORTS		1
#define	NUM_I2C_PORTS		1

#define	NUM_DSPI_PORTS		2
#define NUM_DTWI_PORTS		2

/* Define I/O devices on the board.
*/
#define	NUM_LED				4
#define NUM_BTN				2
#define	NUM_SWT				0
#define NUM_SERVO			8

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
#define	PIN_LED1	64
#define	PIN_LED2	65
#define	PIN_LED3	66
#define	PIN_LED4	67

/* ------------------------------------------------------------ */
/*					Button Declarations							*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the Buttons
*/
#define	PIN_BTN1	42	
#define	PIN_BTN2	43

/* ------------------------------------------------------------ */
/*					Switch Declarations							*/
/* ------------------------------------------------------------ */

/* No switches on this board.
*/

/* ------------------------------------------------------------ */
/*					Servo Pin Declarations						*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the servo connectors
*/
#define	PIN_SERVO1	16
#define	PIN_SERVO2	17
#define	PIN_SERVO3	18
#define	PIN_SERVO4	19
#define	PIN_SERVO5	20
#define	PIN_SERVO6	21
#define	PIN_SERVO7	22
#define	PIN_SERVO8	23

/* ------------------------------------------------------------ */
/*					Timer Pin Declarations						*/
/* ------------------------------------------------------------ */

#define PIN_OC1		53
#define	PIN_OC2		25
#define	PIN_OC3		29
#define	PIN_OC4		37
#define	PIN_OC5		14

#define PIN_IC1		54
#define PIN_IC2		26
#define PIN_IC3		30
#define PIN_IC4		38
#define	PIN_IC5		70

//#define	PIN_TCK1	not connected
#define	PIN_TCK2	27
#define	PIN_TCK3	31
#define	PIN_TCK4	39
#define	PIN_TCK5	71

/* ------------------------------------------------------------ */
/*					Interrupt Pin Declarations					*/
/* ------------------------------------------------------------ */

#define	PIN_INT0	53
#define	PIN_INT1	52
#define PIN_INT2	36
#define	PIN_INT3	40
#define	PIN_INT4	41

/* ------------------------------------------------------------ */
/*					SPI Pin Declarations						*/
/* ------------------------------------------------------------ */
/* These symbols are defined for compatibility with the original
** SPI library and the original pins_arduino.h
*/
const static uint8_t SS   = 8;		// PIC32 SS2
const static uint8_t MOSI = 9;		// PIC32 SDO2
const static uint8_t MISO = 10;		// PIC32 SDI2
const static uint8_t SCK  = 11;		// PIC32 SCK2

/* The Digilent DSPI library uses these ports.
**		DSPI0	connector JB
**		DSPI1	connector J1
*/
#define	PIN_DSPI0_SS	8
#define	PIN_DSPI1_SS	26

/* ------------------------------------------------------------ */
/*					Analog Pins									*/
/* ------------------------------------------------------------ */
/* Define symbols for accessing the analog pins. This table is
** used to map an analog pin number to the corresponding digital
** pin number.
*/
#define	A0		56
#define	A1		57
#define A2		58
#define A3		59
#define A4		60
#define A5		61
#define A6		62
#define A7		63
#define A8		64
#define A9		65
#define A10		66
#define A11		67
#define A12		12
#define	A13		15

/* ------------------------------------------------------------ */
/*					Change Notice Pins							*/
/* ------------------------------------------------------------ */
/* These define the pin numbers for the various change notice
** pins.
*/
//#define	PIN_CN0		//not connected	
//#define	PIN_CN1		//not connected
#define	PIN_CN2		56
#define	PIN_CN3		57
#define	PIN_CN4		58
#define	PIN_CN5		59
#define	PIN_CN6		60
#define	PIN_CN7		61
#define	PIN_CN8		11
#define	PIN_CN9		10
#define	PIN_CN10	9
#define	PIN_CN11	8
#define	PIN_CN12	12
#define	PIN_CN13	14
#define	PIN_CN14	13
#define	PIN_CN15	28
#define	PIN_CN16	24
#define	PIN_CN17	50
#define	PIN_CN18	49
#define	PIN_CN19	55
#define	PIN_CN20	32
#define	PIN_CN21	35

/* ------------------------------------------------------------ */
/*					Pin Mapping Macros							*/
/* ------------------------------------------------------------ */
/* This section contains the definitions for pin mapping macros that
/* are being redefined for this board variant.
*/

#undef digitalPinToAnalog
#define	digitalPinToAnalog(P) ( ((P) < NUM_ANALOG_PINS) ? (P) : digital_pin_to_analog_PGM[P] )

#undef analotInPinToChannel
#define analogInPinToChannel(P) ( analog_pin_to_channel_PGM[P]  )

/* ------------------------------------------------------------ */
/*					Data Definitions							*/
/* ------------------------------------------------------------ */

/* The following declare externals to access the pin mapping
** tables. These tables are defined in Board_Data.c.
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

/* Serial port 0 uses UART1
*/
#define	_SER0_BASE		_UART1_BASE_ADDRESS
#define	_SER0_IRQ		_UART1_ERR_IRQ
#define	_SER0_VECTOR	_UART_1_VECTOR
#define	_SER0_IPL_ISR	_UART1_IPL_ISR
#define	_SER0_IPL		_UART1_IPL_IPC
#define	_SER0_SPL		_UART1_SPL_IPC

/* Serial port 1 uses UART2
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

/* The standard SPI port uses SPI2. Connector JB
*/
#define	_SPI_BASE		_SPI2_BASE_ADDRESS
#define _SPI_ERR_IRQ	_SPI2_ERR_IRQ
#define	_SPI_RX_IRQ		_SPI2_RX_IRQ
#define	_SPI_TX_IRQ		_SPI2_TX_IRQ
#define	_SPI_VECTOR		_SPI_2_VECTOR
#define	_SPI_IPL_ISR	_SPI2_IPL_ISR
#define	_SPI_IPL		_SPI2_IPL_IPC
#define	_SPI_SPL		_SPI2_SPL_IPC

/* The Digilent DSPI library uses these ports.
**		DSPI0	connector JB
**		DSPI1	connector J1
*/
#define	_DSPI0_BASE			_SPI2_BASE_ADDRESS
#define	_DSPI0_ERR_IRQ		_SPI2_ERR_IRQ
#define	_DSPI0_RX_IRQ		_SPI2_RX_IRQ
#define	_DSPI0_TX_IRQ		_SPI2_TX_IRQ
#define	_DSPI0_VECTOR		_SPI_2_VECTOR
#define	_DSPI0_IPL_ISR		_SPI2_IPL_ISR
#define	_DSPI0_IPL			_SPI2_IPL_IPC
#define	_DSPI0_SPL			_SPI2_SPL_IPC

#define	_DSPI1_BASE			_SPI1_BASE_ADDRESS
#define	_DSPI1_ERR_IRQ		_SPI1_ERR_IRQ
#define	_DSPI1_RX_IRQ		_SPI1_RX_IRQ
#define	_DSPI1_TX_IRQ		_SPI1_TX_IRQ
#define	_DSPI1_VECTOR		_SPI_1_VECTOR
#define	_DSPI1_IPL_ISR		_SPI1_IPL_ISR
#define	_DSPI1_IPL			_SPI1_IPL_IPC
#define	_DSPI1_SPL			_SPI1_SPL_IPC

/* ------------------------------------------------------------ */
/*					I2C Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard I2C port uses I2C2 on connector J6. This I2C
** bus has fixed pull-ups and contains the EEPROM and DAC.
*/
#define	_TWI_BASE		_I2C2_BASE_ADDRESS
#define	_TWI_BUS_IRQ	_I2C2_BUS_IRQ
#define	_TWI_SLV_IRQ	_I2C2_SLAVE_IRQ
#define	_TWI_MST_IRQ	_I2C2_MASTER_IRQ
#define	_TWI_VECTOR		_I2C_2_VECTOR
#define	_TWI_IPL_ISR	_I2C2_IPL_ISR
#define _TWI_IPL		_I2C2_IPL_IPC
#define	_TWI_SPL		_I2C2_SPL_IPC

/* Declarations for Digilent DTWI library.
**		DTWI0 is on I2C1, connector J2
**		DTWI1 is on I2C2, connector J6.
**
** DTWI1 has the I2C EEPROM and DAC.
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

/* ------------------------------------------------------------ */
/*					A/D Converter Declarations					*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */

#endif	//OPT_BOARD_INTERNAL

/* ------------------------------------------------------------ */

#endif	// BOARD_DEFS_H

/************************************************************************/
