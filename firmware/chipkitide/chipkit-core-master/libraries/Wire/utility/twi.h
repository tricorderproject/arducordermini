/*
  twi.h - Inter-Integrated Library for Pic Arduino Boards
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.
  Revision Data: 5/20/2011(Oliver Jones)

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

#ifndef twi_h
#define twi_h

  #include <inttypes.h>
  #include <p32_defs.h>

  #ifndef CLK_PBUS
  #define CLK_PBUS 80000000
  #endif

  #ifndef TWI_FREQ
  #define TWI_FREQ 100000
  #endif

  #ifndef TWI_BUFFER_LENGTH
  #define TWI_BUFFER_LENGTH 32
  #endif

  //State define
  #define TW_IDLE				0x00
  #define TW_START				0x01
  #define TW_STOP		 		0x02
  #define TW_MT_DATA			0x03
  #define TW_MT_SLA				0x04
  #define TW_MT_DATA_NACK		0x05
  #define TW_MT_SLA_NACK		0x06
  #define TW_MR_DATA  			0x07
  #define TW_MR_SLA				0x08
  #define TW_MR_ACK_SENT		0x09
  #define TW_MR_NACK_SENT		0x0A
  #define TW_MR_SLA_NACK		0x0B
  #define TW_ARB_LOST			0x0C
 	
  #define TW_SR_SLA				0x0E
  #define TW_SR_DATA			0x0F
  #define TW_SR_STOP			0x10
  #define TW_ST_SLA				0x11
  #define TW_ST_DATA			0x12


/* ------------------------------------------------------------ */
/*					      Register Fields     					*/
/* ------------------------------------------------------------ */

/*	I2CxCON
*/
#define		bnOn			15
#define		bnFrz			14
#define		bnSidl			13
#define		bnSclrel		12
#define		bnStrict		11
#define		bnA10m			10
#define		bnDisslw		9
#define		bnSmen			8
#define		bnGcen			7
#define		bnStren			6
#define		bnAckdt			5
#define		bnAcken			4
#define		bnRcen			3
#define		bnPen			2
#define		bnRsen			1
#define		bnSen			0

/*	I2CxSTAT
*/
#define		bnAckstat		15
#define		bnTrstat		14
#define		bnBcl			10
#define		bnGcstat		9
#define		bnAdd10			8
#define		bnIwcol			7
#define		bnI2cov			6
#define		bnDa			5
#define		bnP				4
#define		bnS				3
#define		bnRw			2
#define		bnRbf			1
#define		bnTbf			0

/*	IFS0
*/
#define		bnI2c1mif		31
#define		bnI2c1sif		30
#define		bnI2c1bif		29

/*	IFS1
*/
#define		bnI2c2mif		13
#define		bnI2c2sif		12
#define		bnI2c2bif		11

/*	IEC0
*/
#define		bnI2c1mie		31
#define		bnI2c1sie		30
#define		bnI2c1bie		29

/*	IEC1
*/
#define		bnI2c2mie		13
#define		bnI2c2sie		12
#define		bnI2c2bie		11

/*	IPC6
*/
#define		bnI2c1ip2		12
#define		bnI2c1ip1		11
#define		bnI2c1ip0		10
#define		bnI2c1is1		9
#define		bnI2c1is0		8

/*	IPC8
*/
#define		bnI2c2ip2		12
#define		bnI2c2ip1		11
#define		bnI2c2ip0		10
#define		bnI2c2is1		9
#define		bnI2c2is0		8
//***************************************************************

#define bnLED4      0
#define trisLED4    TRISF
#define latLED4		LATF

  
  void twi_init(p32_i2c * ptwiT, uint8_t irqBus, uint8_t irqSlv, uint8_t irqMst, uint8_t vec);
  void twi_setAddress(uint8_t);
  uint8_t twi_readFrom(uint8_t, uint8_t*, uint8_t);
  uint8_t twi_writeTo(uint8_t, uint8_t*, uint8_t, uint8_t);
  uint8_t twi_transmit(uint8_t*, uint8_t);
  void twi_attachSlaveRxEvent( void (*)(uint8_t*, int) );
  void twi_attachSlaveTxEvent( void (*)(void) );

#endif

