/************************************************************************/
/*																		*/
/*	Board_Defs.h --	CmodCK1 Board Customization Declarations			*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with a CmodCK1 board using a	*/
/* PIC32 part in a 44-pin package.										*/
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
/*  01/23/2013(KeithV): Modified for CK1 board                          */
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

#define	_BOARD_NAME_	"chipKIT Cmod"

/* Define the peripherals available on the board.
*/
#define	NUM_DIGITAL_PINS	39
#define	NUM_ANALOG_PINS		13
#define NUM_OC_PINS			5
#define	NUM_IC_PINS			5
#define	NUM_TCK_PINS		5
#define	NUM_INT_PINS		5

#define	NUM_SERIAL_PORTS	2       // see comment on serial Port 2 below
#define	NUM_SPI_PORTS		2
#define	NUM_I2C_PORTS		1       

#define NUM_DSPI_PORTS		2
#define NUM_DTWI_PORTS		1       

/* Define I/O devices on the board.
*/
#define	NUM_LED				2
#define NUM_BTN				0
#define	NUM_SWT				0
#define NUM_SERVO			0

/* ------------------------------------------------------------ */
/*						LED Declarations						*/
/* ------------------------------------------------------------ */

/* Define the pin numbers for the LEDs
*/
#define	PIN_LED1	14      // 14  RA10 PGED(4)/TMS/PMA10/RA10
#define	PIN_LED2	12      // 12  RB12 AN12/PMD0/RB12

/* ------------------------------------------------------------ */
/*					Button Declarations							*/
/* ------------------------------------------------------------ */

/* One button (PRG) for this board
*/
///#define	PIN_BTN1	1
/* Also define the virutal program button for soft reset */
#define USE_VIRTUAL_PROGRAM_BUTTON      1
#define VIRTUAL_PROGRAM_BUTTON_TRIS     TRISAbits.TRISA2
#define VIRTUAL_PROGRAM_BUTTON          LATAbits.LATA2

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

#define PIN_OC1		29      // RPB4 (RPB4R = 5)
#define	PIN_OC2		38      // RPB8 (RPB8R = 5)
#define	PIN_OC3		 4      // RPB9 (RPB9R = 5)
#define	PIN_OC4		22      // RPB2 (RPB2R = 5)
#define	PIN_OC5		13      // RPB13(RPB13R = 6)

#define PIN_IC1		36      // RPB6 (IC1R = 1)
#define PIN_IC2		10      // RPB10 (IC2R = 3)
#define PIN_IC3		31      // RPA9 (IC3R = 7)
#define PIN_IC4		37      // RPB7 (IC4R = 4)
#define	PIN_IC5		25      // RPC1 (RPC1R = 6)

#define	PIN_TCK1	30      // RA4
#define	PIN_TCK2	18      // RPA0 (T1CKR = 0)
#define	PIN_TCK3	27      // RPA8 (T1CKR = 5)
#define	PIN_TCK4	32      // RPC3 (T1CKR = 7)
#define	PIN_TCK5	26      // RPC2 (T1CKR = 6)

/* ------------------------------------------------------------ */
/*					Interrupt Pin Declarations					*/
/* ------------------------------------------------------------ */

#define	PIN_INT0	37      // RB7 RB7 fixed not a pps pin
#define	PIN_INT1	33      // RPC4 J2-07, RC4 used for UART2 INT (INT1R = 7)
#define PIN_INT2	13      // RPB13 (INT2R = 3)
#define	PIN_INT3	7       // RPC8 J1-07, RC8 used for SPI1 INT (INT3R = 6)
#define	PIN_INT4	37      // RPB7 (INT4R = 4)

/* ------------------------------------------------------------ */
/*					SPI Pin Declarations						*/
/* ------------------------------------------------------------ */
/* These symbols are defined for compatibility with the original
** SPI library and the original pins_arduino.h. 
*/
const static uint8_t SS   = 24;		// CS1  RC0     SS1R = 6, RPC0R = 3     24  RC0  AN6/RPC0/RC0  
const static uint8_t MISO =	35;		// SDI1 RB5     SDI1R = 1               35  RB5  PGED3/RPB5/PMD7/RB5
const static uint8_t MOSI = 25;		// SDO1 RC1     RPC1R = 3               25  RC1  AN7/RPC1/RC1    
const static uint8_t SCK  = 16;		// SCK1 RB14    RPB14R = 0              16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14

/* The Digilent DSPI library uses these ports.
*/
#define	PIN_DSPI0_SS	24          // 24  RC0  AN6/RPC0/RC0          
#define	PIN_DSPI1_SS	33          // 33  RC4  RPC4/PMA4/RC4

/* ------------------------------------------------------------ */
/*					Analog Pins									*/
/* ------------------------------------------------------------ */
/* Define symbols for accessing the analog pins. This table is  
** used to map an analog pin number to the corresponding digital
** pin number.
*/
#define	A0		18  // RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
#define	A1		19  // RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
#define A2		20  // RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
#define A3		21  // RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
#define A4		22  // RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
#define A5		23  // RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
#define A6		24  // RC0  AN6/RPC0/RC0
#define A7		25  // RC1  AN7/RPC1/RC1
#define A8		26  // RC2  AN8/RPC2/PMA2/RC2
#define A9		17  // RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
#define A10		16  // RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
#define A11		13  // RB13 AN11/RPB13/CTPLS/PMRD/RB13
#define A12     12  // RB12 AN12/PMD0/RB12

/* ------------------------------------------------------------ */
/*					Change Notice Pins							*/
/* ------------------------------------------------------------ */
/* These define the pin numbers for the various change notice
** pins.
*/

//#define	PIN_CN0	     0  //  0
//#define	PIN_CN1	     1  //  1
//#define	PIN_CN2	     2  //  2
//#define	PIN_CN3	     3  //  3
#define	PIN_CN4      4  //  4  RB9  RPB9/SDA1/CTED4/PMD3/RB9
#define	PIN_CN5      5  //  5  RC6  RPC6/PMA1/RC6
#define	PIN_CN6      6  //  6  RC7  RPC7/PMA0/RC7
#define	PIN_CN7      7  //  7  RC8  RPC8/PMA5/RC8
#define	PIN_CN8      8  //  8  RC9  RPC9/CTED7/PMA6/RC9
//#define	PIN_CN9	     9  //  9
#define	PIN_CN10    10  // 10  RB10 PGED2/RPB10/CTED11/PMD2/RB10
#define	PIN_CN11    11  // 11  RB11 PGEC2/RPB11/PMD1/RB11
#define	PIN_CN12    12  // 12  RB12 AN12/PMD0/RB12
#define	PIN_CN13    13  // 13  RB13 AN11/RPB13/CTPLS/PMRD/RB13
#define	PIN_CN14    14  // 14  RA10 PGED(4)/TMS/PMA10/RA10
#define	PIN_CN15    15  // 15  RA7  PGEC(4)/TCK/CTED8/PMA7/RA7
#define	PIN_CN16    16  // 16  RB14 CVREF/AN10/C3INB/RPB14/SCK1/CTED5/PMWR/RB14
#define	PIN_CN17    17  // 17  RB15 AN9/C3INA/RPB15/SCK2/CTED6/PMCS1/RB15
#define	PIN_CN18    18  // 18  RA0  VREF+/CVREF+/AN0/C3INC/RPA0/CTED1/RA0
#define	PIN_CN19    19  // 19  RA1  VREF-/CVREF-/AN1/RPA1/CTED2/RA1
#define	PIN_CN20    20  // 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
#define	PIN_CN21    21  // 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1
#define	PIN_CN22    22  // 22  RB2  AN4/C1INB/C2IND/RPB2/SDA2/CTED13/RB2
#define	PIN_CN23    23  // 23  RB3  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3
#define	PIN_CN24    24  // 24  RC0  AN6/RPC0/RC0
#define	PIN_CN25    25  // 25  RC1  AN7/RPC1/RC1
#define	PIN_CN26    26  // 26  RC2  AN8/RPC2/PMA2/RC2
#define	PIN_CN27    27  // 27  RA8  TDO/RPA8/PMA8/RA8
//#define	PIN_CN28    28  // 28
#define	PIN_CN29    29  // 29  RB4  SOSCI/RPB4/RB4
#define	PIN_CN30    30  // 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4  
#define	PIN_CN31    31  // 31  RA9  TDI/RPA9/PMA9/RA9
#define	PIN_CN32    32  // 32  RC3  RPC3/RC3
#define	PIN_CN33    33  // 33  RC4  RPC4/PMA4/RC4
#define	PIN_CN34    34  // 34  RC5  RPC5/PMA3/RC5
#define	PIN_CN35    35  // 35  RB5  PGED3/RPB5/PMD7/RB5
#define	PIN_CN36    36  // 36  RB6  PGEC3/RPB6/PMD6/RB6
#define	PIN_CN37    37  // 37  RB7  RPB7/CTED3/PMD5/INT0/RB7
#define	PIN_CN38    38  // 38  RB8  RPB8/SCL1/CTED10/PMD4/RB8

/* ------------------------------------------------------------ */
/*					Pin Mapping Macros							*/
/* ------------------------------------------------------------ */
/* Macros used to access the port and pin mapping tables.
** These are mostly generic, but some of them may be board specific.
** These perform slightly better as macros compared to inline functions
*/
#undef digitalPinToAnalog
#define	digitalPinToAnalog(P) ( digital_pin_to_analog_PGM[P] )

#undef analogInPinToChannel
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
extern const uint8_t	digital_pin_to_pps_out_PGM[];
extern const uint8_t	digital_pin_to_pps_in_PGM[];
extern const uint8_t 	digital_pin_to_analog_PGM[];
extern const uint8_t	analog_pin_to_channel_PGM[];

extern const uint8_t	output_compare_to_digital_pin_PGM[];
extern const uint8_t	external_int_to_digital_pin_PGM[];

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

/* Serial port 0 uses UART1 – for the serial monitor
*/
#define       _SER0_BASE           _UART1_BASE_ADDRESS
#define       _SER0_IRQ            _UART1_ERR_IRQ
#define       _SER0_VECTOR         _UART_1_VECTOR
#define       _SER0_IPL_ISR        _UART1_IPL_ISR
#define       _SER0_IPL            _UART1_IPL_IPC
#define       _SER0_SPL            _UART1_SPL_IPC
#define       _SER0_TX_OUT         PPS_OUT_U1TX     // FTDI RxD (RPB3R = 0x1) RPB3 <- U1TX    
#define       _SER0_TX_PIN         23               // 23  AN5/C1INA/C2INC/RTCC/RPB3/SCL2/RB3      
#define       _SER0_RX_IN          PPS_IN_U1RX      // FTDI TxD (U1RXR = 0x5) RPC6 -> U1RX  
#define       _SER0_RX_PIN         5                //  5  RC6  RPC6/PMA1/RC6  


/* Serial port 1 uses UART2
*/
#define       _SER1_BASE           _UART2_BASE_ADDRESS
#define       _SER1_IRQ            _UART2_ERR_IRQ
#define       _SER1_VECTOR         _UART_2_VECTOR
#define       _SER1_IPL_ISR        _UART2_IPL_ISR
#define       _SER1_IPL            _UART2_IPL_IPC
#define       _SER1_SPL            _UART2_SPL_IPC
#define       _SER1_TX_OUT         PPS_OUT_U2TX     // J2-2 (RPB0R = 0x2) RPB0 <- U2TX
#define       _SER1_TX_PIN         20               // 20  RB0  PGED1/AN2/C1IND/C2INB/C3IND/RPB0/RB0
#define       _SER1_RX_IN          PPS_IN_U2RX      // J2-3 (U2RXR = 0x2) RPB1 -> U2RX
#define       _SER1_RX_PIN         21               // 21  RB1  PGEC1/AN3/C1INC/C2INA/RPB1/CTED12/RB1


/* Serial port 2 uses UART1
** There really are not 3 UARTS, this just remaps UART1
** away from the FTDI Serial Monitor Serial0 FTDI chip and applies UART1 to the lower pins of J1.
** You can not use Serial0 and Serial2 concurrently.
*/
/*  Currently Harware Serial will not allow an MX1/2 to have 3 UARTS
#define       _SER2_BASE           _UART1_BASE_ADDRESS
#define       _SER2_IRQ            _UART1_ERR_IRQ
#define       _SER2_VECTOR         _UART_1_VECTOR
#define       _SER2_IPL_ISR        _UART1_IPL_ISR
#define       _SER2_IPL            _UART1_IPL_IPC
#define       _SER2_SPL            _UART1_SPL_IPC
#define       _SER2_TX_OUT         PPS_OUT_U1TX         // J1-8 (RPC7R = 0x1) RPC7 <- U1TX    
#define       _SER2_TX_PIN         6                    //  6  RC7  RPC7/PMA0/RC7                   
#define       _SER2_RX_IN          PPS_IN_U1RX          // J1-9 (U1RXR = 0x2) RPA4 -> U1RX 
#define       _SER2_RX_PIN         30                   // 30  RA4  SOSCO/RPA4/T1CK/CTED9/RA4    
*/
/* ------------------------------------------------------------ */
/*					SPI Port Declarations						*/
/* ------------------------------------------------------------ */

/* The default SPI port uses SPI1.
*/
#define	_SPI_BASE		_SPI1_BASE_ADDRESS
#define _SPI_ERR_IRQ	_SPI1_ERR_IRQ
#define	_SPI_RX_IRQ		_SPI1_RX_IRQ
#define	_SPI_TX_IRQ		_SPI1_TX_IRQ
#define	_SPI_VECTOR		_SPI_1_VECTOR
#define	_SPI_IPL_ISR	_SPI1_IPL_ISR
#define	_SPI_IPL		_SPI1_IPL_IPC
#define	_SPI_SPL		_SPI1_SPL_IPC

/* SPI pin declarations
*/
#define _SPI_MISO_IN	PPS_IN_SDI1
#define	_SPI_MISO_PIN	MISO
#define _SPI_MOSI_OUT	PPS_OUT_SDO1
#define	_SPI_MOSI_PIN	MOSI


/* Full SPI1 on J1
*/
#define	_DSPI0_BASE			_SPI1_BASE_ADDRESS
#define	_DSPI0_ERR_IRQ		_SPI1_ERR_IRQ
#define	_DSPI0_RX_IRQ		_SPI1_RX_IRQ
#define	_DSPI0_TX_IRQ		_SPI1_TX_IRQ
#define	_DSPI0_VECTOR		_SPI_1_VECTOR
#define	_DSPI0_IPL_ISR		_SPI1_IPL_ISR
#define	_DSPI0_IPL			_SPI1_IPL_IPC
#define	_DSPI0_SPL			_SPI1_SPL_IPC

#define _DSPI0_MISO_IN		PPS_IN_SDI1
#define _DSPI0_MISO_PIN		35				// SDI1 RB5     SDI1R = 1               35  RB5  PGED3/RPB5/PMD7/RB5
#define _DSPI0_MOSI_OUT		PPS_OUT_SDO1
#define _DSPI0_MOSI_PIN		25				// SDO1 RC1     RPC1R = 3               25  RC1  AN7/RPC1/RC1  

/* non-expanded SPI2 on the lower pins of J2
*/
#define	_DSPI1_BASE			_SPI2_BASE_ADDRESS
#define	_DSPI1_ERR_IRQ		_SPI2_ERR_IRQ
#define	_DSPI1_RX_IRQ		_SPI2_RX_IRQ
#define	_DSPI1_TX_IRQ		_SPI2_TX_IRQ
#define	_DSPI1_VECTOR		_SPI_2_VECTOR
#define	_DSPI1_IPL_ISR		_SPI2_IPL_ISR
#define	_DSPI1_IPL			_SPI2_IPL_IPC
#define	_DSPI1_SPL			_SPI2_SPL_IPC

#define _DSPI1_MISO_IN		PPS_IN_SDI2
#define _DSPI1_MISO_PIN		32				// RC3  SDI2    SDI2R = 7
#define _DSPI1_MOSI_OUT		PPS_OUT_SDO2
#define _DSPI1_MOSI_PIN		36				// RB6  SDO2    RPB6R = 4

/* ------------------------------------------------------------ */
/*					I2C Port Declarations						*/
/* ------------------------------------------------------------ */

/* The standard I2C1 port uses I2C1 (SCL1/SDA1). 
** RB8/RB9 pins 38/4
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
**		DTWI0 is on RB8/RB9 pins 38/4 
*/
#define	_DTWI0_BASE		_I2C1_BASE_ADDRESS
#define	_DTWI0_BUS_IRQ	_I2C1_BUS_IRQ
#define	_DTWI0_SLV_IRQ	_I2C1_SLAVE_IRQ
#define	_DTWI0_MST_IRQ	_I2C1_MASTER_IRQ
#define	_DTWI0_VECTOR	_I2C_1_VECTOR
#define	_DTWI0_IPL_ISR	_I2C1_IPL_ISR
#define	_DTWI0_IPL		_I2C1_IPL_IPC
#define	_DTWI0_SPL		_I2C1_SPL_IPC

/* ------------------------------------------------------------ */
/*					A/D Converter Declarations					*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */

#endif	// OPT_BOARD_INTERNAL

/* ------------------------------------------------------------ */

#endif	// BOARD_DEFS_H

/************************************************************************/
