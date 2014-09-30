/************************************************************************/
/*																		*/
/*	Board_Defs.h --	Board Customization for Digilent chipKIT Uno32		*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent chipKIT		*/
/* Uno32 board.															*/
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

#define	_BOARD_NAME_	"chipKIT WF32"

/* Define the Microcontroller peripherals available on the board.
*/
#define	NUM_DIGITAL_PINS	74
#define	NUM_ANALOG_PINS		12
#define NUM_OC_PINS			5
#define	NUM_IC_PINS			5
#define	NUM_TCK_PINS		4
#define	NUM_INT_PINS		5

#define	NUM_SERIAL_PORTS	3   // 1 & 3,4
#define	NUM_SPI_PORTS		4   // 4 is dedicated to MRF
#define	NUM_I2C_PORTS		3   //2,3,4; 1,5 out because of MRF

#define NUM_DSPI_PORTS		4
#define	NUM_DTWI_PORTS		3

/* Define I/O devices on the board.
*/
#define	NUM_LED				4
#define NUM_BTN				2
#define	NUM_SWT				0
#define NUM_SERVO			0

/* Define the number of pins including extended i/o pins.
** These are pins that are not native to the microcontroller, such
** as implemented via an i/o expander or external A/D or D/A.
** This board doesn't have any.
*/
#define	NUM_DIGITAL_PINS_EXTENDED	NUM_DIGITAL_PINS
#define	NUM_ANALOG_PINS_EXTENDED	NUM_ANALOG_PINS

/* ------------------------------------------------------------ */
/*					Virtual Program Button						*/
/* ------------------------------------------------------------ */
#define USE_VIRTUAL_PROGRAM_BUTTON      1
#define VIRTUAL_PROGRAM_BUTTON_TRIS     TRISCbits.TRISC12
#define VIRTUAL_PROGRAM_BUTTON          LATCbits.LATC12

/* ------------------------------------------------------------ */
/*						LED Declarations						*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the LEDs.
*/
#define	PIN_LED1	13
#define	PIN_LED2	43
#define	PIN_LED3	48
#define	PIN_LED4	47

/* ------------------------------------------------------------ */
/*					Button Declarations							*/
/* ------------------------------------------------------------ */

/* Define buttons on this board.
*/
#define	PIN_BTN1	65	
#define	PIN_BTN2	66

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

#define PIN_OC1		3
#define	PIN_OC2		5
#define	PIN_OC3		6
#define	PIN_OC4		9
#define	PIN_OC5		10

#define PIN_IC1		70      // shared with 2
#define PIN_IC2		71      // shared with 7
#define PIN_IC3		72      // shared with 8
#define PIN_IC4		35
#define	PIN_IC5		73      // shared with 10

//#define	PIN_TCK1	not connected
#define	PIN_TCK2	67      // shard with 34
#define	PIN_TCK3	68      // shard with 35
#define	PIN_TCK4	69      // shard with 36
#define	PIN_TCK5	38

/* ------------------------------------------------------------ */
/*					Interrupt Pin Declarations					*/
/* ------------------------------------------------------------ */

#define	PIN_INT0	3   // uno32 is on 38
#define	PIN_INT1	2
#define PIN_INT2	7
#define	PIN_INT3	8
#define	PIN_INT4	57  // used by MRF and is not on uno32 pin 35.

/* ------------------------------------------------------------ */
/*					SPI Pin Declarations						*/
/* ------------------------------------------------------------ */
/* These symbols are defined for compatibility with the original
** SPI library and the original pins_arduino.h
*/
const static uint8_t SS   = 44;		// for SPI master operation, shared with pin 10
const static uint8_t MOSI = 11;		// PIC32 SDO2
const static uint8_t MISO = 12;		// PIC32 SDI2
const static uint8_t SCK  = 13;		// PIC32 SCK2

/* The Digilent DSPI library uses these ports.
*/
#define	PIN_DSPI0_SS	44      // SS2; Shared on pin 10
#define	PIN_DSPI1_SS	71      // SS1; Shared on pin 7
#define	PIN_DSPI2_SS	39      // SS3
#define	PIN_DSPI3_SS	54      // SS4; Dedicated to the MRF

/* ------------------------------------------------------------ */
/*					Analog Pins									*/
/* ------------------------------------------------------------ */
/* Define symbols for accessing the analog pins. This table is
** used to map an analog pin number to the corresponding digital
** pin number.
*/
#define	A0		14      // AN2
#define	A1		15      // AN4
#define A2		16      // AN8
#define A3		17      // AN0
#define A4		18      // AN10
#define A5		19      // AN11
#define A6		20      // AN3
#define A7		21      // AN5
#define A8		22      // AN9
#define A9		23      // AN1
#define A10		24      // AN14
#define A11		25      // AN15

/* ------------------------------------------------------------ */
/*					Change Notice Pins							*/
/* ------------------------------------------------------------ */
/* These define the pin numbers for the various change notice
** pins.
*/
//#define	PIN_CN0		//not conected
//#define	PIN_CN1		//not conected
#define	PIN_CN2		17      // Uno32 on 42
#define	PIN_CN3		23      // Uno32 on 41
#define	PIN_CN4		14
#define	PIN_CN5		20
#define	PIN_CN6		15
#define	PIN_CN7		21
#define	PIN_CN8		13
#define	PIN_CN9		12
#define	PIN_CN10	11
#define	PIN_CN11	44
#define	PIN_CN12	25
#define	PIN_CN13	10
#define	PIN_CN14	34      // Uno32 on 14
#define	PIN_CN15	36
#define	PIN_CN16	37
#define	PIN_CN17	55      // 39; needed to be moved for the MRF
#define	PIN_CN18	56      // 40; needed to be moved for the MRF

/* ------------------------------------------------------------ */
/*					Pin Mapping Macros							*/
/* ------------------------------------------------------------ */
/* This section contains the definitions for pin mapping macros that
/* are being redefined for this board variant.
*/

#undef digitalPinToAnalog
#define	digitalPinToAnalog(P) ( (P) < 12 ? (P) : ((P) >= 14) && ((P) < 26) ? (P)-14 : NOT_ANALOG_PIN )

#undef analogInPinToChannel
#define analogInPinToChannel(P) ( analog_pin_to_channel_PGM[P]  )

/* ------------------------------------------------------------ */
/*					Data Declarations							*/
/* ------------------------------------------------------------ */

/* The following declare externals to access the pin mapping
** tables. These tables are defined in Board_Data.c.
*/

#if !defined(OPT_BOARD_DATA)

extern const uint32_t	port_to_tris_PGM[];
extern const uint8_t	digital_pin_to_port_PGM[];
extern const uint16_t	digital_pin_to_bit_mask_PGM[];
extern const uint16_t	digital_pin_to_timer_PGM[];
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

/* Serial port 1 uses UART4; this goes to pins 39&40
*/
#define	_SER1_BASE		_UART4_BASE_ADDRESS
#define	_SER1_IRQ		_UART4_ERR_IRQ
#define	_SER1_VECTOR	_UART_4_VECTOR
#define	_SER1_IPL_ISR	_UART4_IPL_ISR
#define	_SER1_IPL		_UART4_IPL_IPC
#define	_SER1_SPL		_UART4_SPL_IPC

/* Serial port 2 uses UART3
*/
#define	_SER2_BASE		_UART3_BASE_ADDRESS
#define	_SER2_IRQ		_UART3_ERR_IRQ
#define	_SER2_VECTOR	_UART_3_VECTOR
#define	_SER2_IPL_ISR	_UART3_IPL_ISR
#define	_SER2_IPL		_UART3_IPL_IPC
#define	_SER2_SPL		_UART3_SPL_IPC

/* ------------------------------------------------------------ */
/*					SPI Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard SPI port uses SPI2.
*/
#define	_SPI_BASE		_SPI2_BASE_ADDRESS
#define _SPI_ERR_IRQ	_SPI2_ERR_IRQ
#define	_SPI_RX_IRQ		_SPI2_RX_IRQ
#define	_SPI_TX_IRQ		_SPI2_TX_IRQ
#define	_SPI_VECTOR		_SPI_2_VECTOR
#define _SPI_IPL_ISR	_SPI2_IPL_ISR
#define	_SPI_IPL		_SPI2_IPL_IPC
#define	_SPI_SPL		_SPI2_SPL_IPC

/* The Digilent DSPI library uses these ports.
*/
#define	_DSPI0_BASE			_SPI2_BASE_ADDRESS
#define	_DSPI0_ERR_IRQ		_SPI2_ERR_IRQ
#define	_DSPI0_RX_IRQ		_SPI2_RX_IRQ
#define	_DSPI0_TX_IRQ		_SPI2_TX_IRQ
#define	_DSPI0_VECTOR		_SPI_2_VECTOR
#define _DSPI0_IPL_ISR		_SPI2_IPL_ISR
#define	_DSPI0_IPL			_SPI2_IPL_IPC
#define	_DSPI0_SPL			_SPI2_SPL_IPC

#define	_DSPI1_BASE			_SPI1_BASE_ADDRESS
#define	_DSPI1_ERR_IRQ		_SPI1_ERR_IRQ
#define	_DSPI1_RX_IRQ		_SPI1_RX_IRQ
#define	_DSPI1_TX_IRQ		_SPI1_TX_IRQ
#define	_DSPI1_VECTOR		_SPI_1_VECTOR
#define _DSPI1_IPL_ISR		_SPI1_IPL_ISR
#define	_DSPI1_IPL			_SPI1_IPL_IPC
#define	_DSPI1_SPL			_SPI1_SPL_IPC

#define	_DSPI2_BASE			_SPI3_BASE_ADDRESS
#define	_DSPI2_ERR_IRQ		_SPI3_ERR_IRQ
#define	_DSPI2_RX_IRQ		_SPI3_RX_IRQ
#define	_DSPI2_TX_IRQ		_SPI3_TX_IRQ
#define	_DSPI2_VECTOR		_SPI_3_VECTOR
#define _DSPI2_IPL_ISR		_SPI3_IPL_ISR
#define	_DSPI2_IPL			_SPI3_IPL_IPC
#define	_DSPI2_SPL			_SPI3_SPL_IPC

// this is the MRF24
#define	_DSPI3_BASE			_SPI4_BASE_ADDRESS
#define	_DSPI3_ERR_IRQ		_SPI4_ERR_IRQ
#define	_DSPI3_RX_IRQ		_SPI4_RX_IRQ
#define	_DSPI3_TX_IRQ		_SPI4_TX_IRQ
#define	_DSPI3_VECTOR		_SPI_4_VECTOR
#define _DSPI3_IPL_ISR		_SPI4_IPL_ISR
#define	_DSPI3_IPL			_SPI4_IPL_IPC
#define	_DSPI3_SPL			_SPI4_SPL_IPC

/* ------------------------------------------------------------ */
/*					I2C Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard I2C port uses I2C1 (SCL1/SDA1). These come to pins
** A4/A5 pins 18/19 on the analog connector. It is necessary to have jumpers
** JP6/JP8 set appropriately (RG2/RG3 position) to access the I2C
** signals.  
*/
#define	_TWI_BASE		_I2C2_BASE_ADDRESS
#define	_TWI_BUS_IRQ	_I2C2_BUS_IRQ
#define	_TWI_SLV_IRQ	_I2C2_SLAVE_IRQ
#define	_TWI_MST_IRQ	_I2C2_MASTER_IRQ
#define	_TWI_VECTOR		_I2C_2_VECTOR
#define _TWI_IPL_ISR	_I2C2_IPL_ISR
#define _TWI_IPL		_I2C2_IPL_IPC
#define	_TWI_SPL		_I2C2_SPL_IPC

/* Declarations for Digilent DTWI library.
**		DTWI0 is SDA2/SCL2 on A4/A5 pins 18/19 (see above comment).
**		DTWI1 is SDA3/SCL3 on on digital pins 0 & 1.
**		DTWI1 is SDA4/SCL4 on on digital pins 12 & 11.
*/
#define	_DTWI0_BASE		_I2C2_BASE_ADDRESS
#define	_DTWI0_BUS_IRQ	_I2C2_BUS_IRQ
#define	_DTWI0_SLV_IRQ	_I2C2_SLAVE_IRQ
#define	_DTWI0_MST_IRQ	_I2C2_MASTER_IRQ
#define	_DTWI0_VECTOR	_I2C_2_VECTOR
#define	_DTWI0_IPL_ISR	_I2C2_IPL_ISR
#define	_DTWI0_IPL		_I2C2_IPL_IPC
#define	_DTWI0_SPL		_I2C2_SPL_IPC

#define	_DTWI1_BASE		_I2C3_BASE_ADDRESS
#define	_DTWI1_BUS_IRQ	_I2C3_BUS_IRQ
#define	_DTWI1_SLV_IRQ	_I2C3_SLAVE_IRQ
#define	_DTWI1_MST_IRQ	_I2C3_MASTER_IRQ
#define	_DTWI1_VECTOR	_I2C_3_VECTOR
#define	_DTWI1_IPL_ISR	_I2C3_IPL_ISR
#define	_DTWI1_IPL		_I2C3_IPL_IPC
#define	_DTWI1_SPL		_I2C3_SPL_IPC

#define	_DTWI2_BASE		_I2C4_BASE_ADDRESS
#define	_DTWI2_BUS_IRQ	_I2C4_BUS_IRQ
#define	_DTWI2_SLV_IRQ	_I2C4_SLAVE_IRQ
#define	_DTWI2_MST_IRQ	_I2C4_MASTER_IRQ
#define	_DTWI2_VECTOR	_I2C_4_VECTOR
#define	_DTWI2_IPL_ISR	_I2C4_IPL_ISR
#define	_DTWI2_IPL		_I2C4_IPL_IPC
#define	_DTWI2_SPL		_I2C4_SPL_IPC

/* ------------------------------------------------------------ */
/*					A/D Converter Declarations					*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */

#endif	// OPT_BOARD_INTERNAL

/* ------------------------------------------------------------ */

#endif	// BOARD_DEFS_H

/************************************************************************/
