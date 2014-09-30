//************************************************************************
//*	p32_defs.h
//*
//*	chipKIT core files for PIC32
//*		Copyright (c) 2011 by Digilent Inc.
//*	
//************************************************************************
//*		Author: Gene Apperson
//*		Copyright (c) 2011, Digilent Inc, All rights reserved
//************************************************************************
//*
//* This file contains hardware dependent symbol and data type declarations
//* for the PIC32 microcontroller.
//*
//************************************************************************
//*	This file is part of the core system for the chipKIT version
//* of the Arduino code base. It defines various generic symbols
//* describing the Microchip PIC32 devices.
//*	
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
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 2, 2011	<Gene Apperson> created
//*	Jul 26, 2012 <GeneApperson> Added PPS support for PIC32MX1xx/MX2xx devices
//* Feb  6, 2013 <GeneApperson> Added bit definitions for several peripherals
//************************************************************************


#if !defined(_P32_DEFS_H)
#define _P32_DEFS_H

#include "cpudefs.h"
#include <inttypes.h>

/* ------------------------------------------------------------ */
/*				Misc. Declarations								*/
/* ------------------------------------------------------------ */

#define	FLASH_SPEED_HZ          30000000

/* ------------------------------------------------------------ */
/*				Register Declarations							*/
/* ------------------------------------------------------------ */

/* This structure describes the register layout of the primary
** register, set, clear, and invert registers associated with
** most special function registers.
*/
typedef struct {
	volatile uint32_t	reg;
	volatile uint32_t	clr;
	volatile uint32_t	set;
	volatile uint32_t	inv;
} p32_regset;

/* This structure describes the register layout for a buffer
** register that does't have the associated set, clear, and invert
** registers.
*/
typedef struct {
	volatile uint32_t	reg;
	volatile uint32_t	rsv1;
	volatile uint32_t	rsv2;
	volatile uint32_t	rsv3;
} p32_regbuf;

/* This structure describes the register layout of an I/O port.
*/
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
typedef struct {
	volatile p32_regset ansel;
	volatile p32_regset	tris;
	volatile p32_regset	port;
	volatile p32_regset	lat;
	volatile p32_regset	odc;
	volatile p32_regset cnpu;
	volatile p32_regset cnpd;
	volatile p32_regset cncon;
	volatile p32_regset cnen;
	volatile p32_regset cnstat;
} p32_ioport;
#else
typedef struct {
	volatile p32_regset	tris;
	volatile p32_regset	port;
	volatile p32_regset	lat;
	volatile p32_regset	odc;
} p32_ioport;
#endif

/* This structure defines the registers for a PIC32 UART.
*/
typedef struct {
	volatile p32_regset	uxMode;
	volatile p32_regset	uxSta;
	volatile p32_regbuf	uxTx;
	volatile p32_regbuf	uxRx;
	volatile p32_regset	uxBrg;
} p32_uart;

/* UxMODE - Define bits in UART mode port
*/
#define	_UARTMODE_ON	15
#define _UARTMODE_BRGH  3

/* UxSTA - Define bits in UART status/control register
*/
#define	_UARTSTA_URXEN	12
#define	_UARTSTA_UTXEN	10
#define _UARTSTA_UTXBF  9
#define	_UARTSTA_TMRT	8

/* Structure for the registers of a PIC32 SPI controller
*/
typedef struct {
	volatile p32_regset sxCon;
	volatile p32_regset sxStat;
	volatile p32_regbuf sxBuf;
	volatile p32_regset sxBrg;
} p32_spi;

/*	SPIxCON - Define bits in the SPI control port
*/
#define _SPICON_ON		15
#define _SPICON_MODE32		11
#define _SPICON_MODE16		10
#define _SPICON_SMP		9
#define	_SPICON_CKE		8
#define _SPICON_CKP		6
#define _SPICON_MSTEN	5

/*	SPIxSTAT - Define symbols in the SPI status port
*/
#define	_SPISTAT_SPIROV	6
#define	_SPISTAT_SPITBE	3
#define _SPISTAT_SPIRBF	0

/* This structure defines the registers for a PIC32 I2C port.
*/
typedef struct {
	volatile p32_regset	ixCon;
	volatile p32_regset ixStat;
	volatile p32_regset ixAdd;
	volatile p32_regset ixMsk;
	volatile p32_regset ixBrg;
	volatile p32_regset ixTrn;
	volatile p32_regbuf ixRcv;
} p32_i2c;

/* I2CxCON - Define symbols for the I2C control port bits
*/
#define	_I2CCON_ON		15
#define	_I2CCON_SIDL	13
#define	_I2CCON_SCLREL	12
#define _I2CCON_STRICT	11
#define	_I2CCON_A10M	10
#define	_I2CCON_DISSLW	9
#define	_I2CCON_SMEN	8
#define	_I2CCON_GCEN	7
#define	_I2CCON_STREN	6
#define	_I2CCON_ACKDT	5
#define	_I2CCON_ACKEN	4
#define	_I2CCON_RCEN	3
#define	_I2CCON_PEN		2
#define	_I2CCON_RSEN	1
#define	_I2CCON_SEN		0

/* I2CSTAT - Define symbols for the I2C status port bits
*/
#define	_I2CSTAT_ACKSTAT	15
#define	_I2CSTAT_TRSTAT		14
#define	_I2CSTAT_BCL		10
#define	_I2CSTAT_GCSTAT		9
#define	_I2CSTAT_ADD10		8
#define	_I2CSTAT_IWCOL		7
#define	_I2CSTAT_I2COV		6
#define	_I2CSTAT_DA			5
#define	_I2CSTAT_P			4
#define	_I2CSTAT_S			3
#define	_I2CSTAT_RW			2
#define	_I2CSTAT_RBF		1
#define	_I2CSTAT_TBF		0

/* This structure defines the registers for a PIC32 Timer.
*/
typedef struct {
	volatile p32_regset tmxCon;
	volatile p32_regset tmxTmr;
	volatile p32_regset tmxPr;
} p32_timer;

/* Define bits in the timer control register.
** Type A timers (timer1) have different control bits
** than Type B timers (timer2 - timer5)
*/
// Type A timer - Timer1
#define _BN_TACON_ON		15
#define	_BN_TACON_FRZ		14
#define	_BN_TACON_SIDL		13
#define	_BN_TACON_TWDIS		12
#define	_BN_TACON_TWIP		11
#define	_BN_TACON_TGATE		7
#define _BN_TACON_TCKPS		4
#define	_BN_TACON_TSYNC		2
#define _BN_TACON_TCS		1

#define TACON_ON			(1 << _BN_TACON_ON)
#define TACON_OFF			(0)
#define	TACON_FRZ_ON		(1 << _BN_TACON_FRZ)
#define	TACON_FRZ_OFF		(0)
#define	TACON_IDLE_STOP		(1 << _BN_TACON_SIDL)
#define	TACON_IDLE_RUN		(0)
#define	TACON_TWDIS_ON		(1 << _BN_TACON_TWDIS)
#define	TACON_TWDIS_OFF		(0)
#define	TACON_TWIP			(1 << _BN_TACON_TWIP)
#define	TACON_TGATE_ON		(1 << _BN_TACON_TGATE)
#define	TACON_TGATE_OFF		(0)
#define	TACON_TSYNC_ON		(1 << _BN_TACON_TSYNC)
#define	TACON_TSYNC_OFF		(0)

#define TACON_SRC_INT		(0 << _BN_TACON_TCS)
#define TACON_SRC_EXT		(1 << _BN_TACON_TCS)

#define	TACON_PS_MASK		(3 << _BN_TACON_TCKPS)
#define	TACON_PS_1			(0 << _BN_TACON_TCKPS)
#define TACON_PS_8			(1 << _BN_TACON_TCKPS)
#define	TACON_PS_64			(2 << _BN_TACON_TCKPS)
#define	TACON_PS_256		(3 << _BN_TACON_TCKPS)

// Type B timer - Timer2-Timer5
#define	_BN_TBCON_ON		15
#define	_BN_TBCON_FRZ		14
#define	_BN_TBCON_SIDL		13
#define	_BN_TBCON_TGATE		7
#define	_BN_TBCON_TCKPS		4
#define	_BN_TBCON_T32		3
#define	_BN_TBCON_TCS		1

#define	TBCON_ON			(1 << _BN_TBCON_ON)
#define	TBCON_OFF			(0)
#define	TBCON_FRZ_ON		(1 << _BN_TBCON_FRZ)
#define	TBCON_FRZ_OFF		(0)
#define	TBCON_IDLE_STOP		(1 << _BN_TBCON_SIDL)
#define	TBCON_IDLE_RUN		(0)
#define	TBCON_TGATE_ON		(1 << _BN_TBCON_TGATE)
#define	TBCON_TGATE_OFF		(0)

#define TBCON_PS_MASK		(7 << _BN_TBCON_TCKPS)
#define	TBCON_PS_1			(0 << _BN_TBCON_TCKPS)
#define	TBCON_PS_2			(1 << _BN_TBCON_TCKPS)
#define TBCON_PS_4			(2 << _BN_TBCON_TCKPS)
#define TBCON_PS_8			(3 << _BN_TBCON_TCKPS)
#define TBCON_PS_16			(4 << _BN_TBCON_TCKPS)
#define	TBCON_PS_32			(5 << _BN_TBCON_TCKPS)
#define TBCON_PS_64			(6 << _BN_TBCON_TCKPS)
#define TBCON_PS_256		(7 << _BN_TBCON_TCKPS)

#define	TBCON_MODE32		(1 << _BN_TBCON_T32)
#define	TBCON_MODE16		(0)
#define TBCON_SRC_EXT		(1 << _BN_TBCON_TCS)
#define TBCON_SRC_INT		(0)

/* This structure defines the registers for a PIC32 Input Capture.
*/
typedef struct {
	volatile p32_regset icxCon;
	volatile p32_regbuf icxBuf;
} p32_ic;

/* Define bits in the incput capture control register
*/
#define	_BN_ICCON_ON		15
#define	_BN_ICCON_FRZ		14
#define	_BN_ICCON_SIDL		13
#define	_BN_ICCON_FEDGE		9
#define	_BN_ICCON_C32		8
#define	_BN_ICCON_ICTMR		7
#define	_BN_ICCON_ICI		5
#define	_BN_ICCON_ICOV		4
#define	_BN_ICCON_ICBNE		3
#define	_BN_ICCON_ICM		0

#define	ICCON_ON			(1 << _BN_ICCON_ON)
#define	ICCON_OFF			(0)
#define	ICCON_FRZ_ON		(1 << _BN_ICCON_FRZ)
#define	ICCON_FRZ_OFF		(0)
#define	ICCON_IDLE_STOP		(1 << _BN_ICCON_SIDL)
#define	ICCON_IDLE_RUN		(0)
#define	ICCON_FEDGE_RISING	(1 << _BN_ICCON_FEDGE)
#define	ICCON_FEDGE_FALLING	(0)
#define	ICCON_WIDTH_32		(1 << _BN_ICCON_C32)
#define	ICCON_WIDTH_16		(0)
#define	ICCON_SOURCE_TIMER2	(1 << _BN_ICCON_ICTMR)
#define	ICCON_SOURCE_TIMER3	(0)
#define	ICCON_INT_FOURTH_EVENT	(3 << _BN_ICCON_ICI)
#define	ICCON_INT_THIRD_EVENT	(2 << _BN_ICCON_ICI)
#define	ICCON_INT_SECOND_EVENT	(1 << _BN_ICCON_ICI)
#define	ICCON_INT_EVERY_EVENT	(0 << _BN_ICCON_ICI)
#define	ICCON_OVERFLOW		(1 << _BN_ICCON_ICOV)
#define	ICCON_ICBNE			(1 << _BN_ICCON_ICBNE)
#define	ICCON_ICM_INTERRUPT		(7 << _BN_ICCON_ICM)
#define	ICCON_ICM_EVERY_EDGE	(6 << _BN_ICCON_ICM)
#define	ICCON_ICM_RISING_16		(5 << _BN_ICCON_ICM)
#define	ICCON_ICM_RISING_4		(4 << _BN_ICCON_ICM)
#define	ICCON_ICM_RISING_EDGE	(3 << _BN_ICCON_ICM)
#define	ICCON_ICM_FALLING_EDGE	(2 << _BN_ICCON_ICM)
#define	ICCON_ICM_EDGE_DETECT	(1 << _BN_ICCON_ICM)
#define	ICCON_ICM_DISABLE		(0 << _BN_ICCON_ICM)

/* This structure defines the registers for a PIC32 Output Compare.
*/
typedef struct {
	volatile p32_regset ocxCon;
	volatile p32_regset ocxR;
	volatile p32_regset ocxRs;
} p32_oc;

/* Define bits in the output compare control register
*/
#define _BN_OCCON_ON		15
#define	_BN_OCCON_SIDL		13
#define _BN_OCCON_OC32		5
#define	_BN_OCCON_OCFLT		4
#define _BN_OCCON_OCTSEL	3
#define	_BN_OCCON_OCM		0

#define OCCON_ON			(1 << _BN_OCCON_ON)
#define OCCON_OFF			(0)
#define	OCCON_IDLE_STOP		(1 << _BN_OCCON_SIDL)
#define	OCCON_IDLE_RUN		(0)
#define OCCON_MODE32		(1 << _BN_OCCON_OC32)
#define OCCON_MODE16		(0)
#define	OCCON_OCFLT			(1 << _BN_OCCON_OCFLT)
#define	OCCON_SRC_TIMER3	(1 << _BN_OCCON_OCTSEL)
#define	OCCON_SRC_TIMER2	(0)

#define OCCON_PWM_FAULT_ENABLE		(7 << _BN_OCCON_OCM)
#define	OCCON_PWM_FAULT_DISABLE		(6 << _BN_OCCON_OCM)
#define	OCCON_PULSE_CONTINUOUS		(5 << _BN_OCCON_OCM)
#define	OCCON_PULSE_SINGLE			(4 << _BN_OCCON_OCM)
#define	OCCON_PULSE_TOGGLE			(3 << _BN_OCCON_OCM)
#define	OCCON_FALLING_EDGE			(2 << _BN_OCCON_OCM)
#define	OCCON_RISING_EDGE			(1 << _BN_OCCON_OCM)
#define OCCON_MODE_OFF				(0 << _BN_OCCON_OCM)

/* This structure defines the registers for a PIC32 A/D converter
*/
typedef struct {
	volatile p32_regset adxCon1;
	volatile p32_regset adxCon2;
	volatile p32_regset adxCon3;
	volatile p32_regset adxChs;
	volatile p32_regset adxPcfg;
	volatile p32_regset adxCssl;
	volatile p32_regbuf	adxBuf0;
	volatile p32_regbuf	adxBuf1;
	volatile p32_regbuf	adxBuf2;
	volatile p32_regbuf	adxBuf3;
	volatile p32_regbuf	adxBuf4;
	volatile p32_regbuf	adxBuf5;
	volatile p32_regbuf	adxBuf6;
	volatile p32_regbuf	adxBuf7;
	volatile p32_regbuf	adxBuf8;
	volatile p32_regbuf	adxBuf9;
	volatile p32_regbuf	adxBufA;
	volatile p32_regbuf	adxBufB;
	volatile p32_regbuf	adxBufC;
	volatile p32_regbuf	adxBufD;
	volatile p32_regbuf	adxBufE;
	volatile p32_regbuf	adxBufF;
} p32_adc;

/* This structure defines the change notice/pull-up enable registers.
*/
typedef struct {
	volatile p32_regset cnCon;
	volatile p32_regset cnEn;
	volatile p32_regset cnPue;
} p32_cn;

/* This structure defines the registers for the PIC32 parallel master port.
*/
typedef struct {
	volatile p32_regset pmpCon;
	volatile p32_regset pmpMode;
	volatile p32_regset pmpAddr;
	volatile p32_regset	pmpDout;
	volatile p32_regset pmpDin;
	volatile p32_regset	pmpAen;
	volatile p32_regset pmpStat;
} p32_pmp;


/* ------------------------------------------------------------ */
/*			Peripheral Pin Select Output Declarations			*/
/* ------------------------------------------------------------ */

/* Currently, PPS is only supported in PIC32MX1xx/PIC32MX2xx devices.
*/
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

/* The PPS pins and peripheral functions are divided up into four sets.
** In some cases, the sets are disjoint, and in other cases there is
** overlap between the sets. These symbols are used to associate a pin
** or input/ouput function with the sets of which it is a member.
** The set values associated with the input/output functions and the
** input/output pins are used for error checking in the mapping functions.
*/
#define	_PPS_SET_A	0x0100
#define _PPS_SET_B	0x0200
#define	_PPS_SET_C	0x0400
#define	_PPS_SET_D	0x0800

/* Data type for PPS output select register.
*/
typedef uint32_t p32_ppsout;

#define _PPS_INPUT_BIT  (1 << 15)
#define	PPS_OUT_MASK	0x000F
#define	PPS_IN_MASK		0x00FF
#define	NUM_PPS_IN		44          // This must be set to the highest PPS_IN_xxx value
#define NUM_PPS_OUT     7           // This must be set to the highest PPS_OUT_xxx value

/* This enum specifies all of the possible input and output peripherals you can
** pass into the mapPps() function's <func> parameter. All of the inputs
** have their _PPS_INPUT_BIT set, while the outputs don't. (Thats how the
** mapPps() function can tell the difference.)
*/

typedef enum {
/* The following symbols define the output functions that are mappable with
** PPS. These give the select values used to map a peripheral function to a PPS
** output pin combined with their set membership. The PPS output select values
** are divided into four sets. Some peripheral functions are duplicated in more
** than one set. In this case they have the same select value in each set.
*/
    PPS_OUT_GPIO	= (0 + (_PPS_SET_A|_PPS_SET_B|_PPS_SET_C|_PPS_SET_D)),

    PPS_OUT_U1TX	= (1 + _PPS_SET_A),
    PPS_OUT_U2RTS	= (2 + _PPS_SET_A),
    PPS_OUT_SS1		= (3 + _PPS_SET_A),
    PPS_OUT_OC1		= (5 + _PPS_SET_A),
    PPS_OUT_C2OUT	= (7 + _PPS_SET_A),

    PPS_OUT_SDO1	= (3 + (_PPS_SET_B | _PPS_SET_C)),
    PPS_OUT_SDO2	= (4 + (_PPS_SET_B | _PPS_SET_C)),
    PPS_OUT_OC2		= (5 + _PPS_SET_B),

    PPS_OUT_OC4		= (5 + _PPS_SET_C),
    PPS_OUT_OC5		= (6 + _PPS_SET_C),
    PPS_OUT_REFCLKO	= (7 + _PPS_SET_C),

    PPS_OUT_U1RTS	= (1 + _PPS_SET_D),
    PPS_OUT_U2TX	= (2 + _PPS_SET_D),
    PPS_OUT_SS2		= (4 + _PPS_SET_D),
    PPS_OUT_OC3		= (5 + _PPS_SET_D),
    PPS_OUT_C1OUT	= (7 + _PPS_SET_D),

/* The following symbols define the input functions that are mappable
** using PPS. These are used as an index to the input selection mapping
** register for that peripheral function. In the current (as of 07/12/2012)
** PIC32MX1xx/2xx devices, this is a direct mapping. If future devices add 
** new input functions, or change the order of the input select registers,
** this mapping will have to be changed to be done through a table.
*/

    PPS_IN_INT1		= (0  + _PPS_SET_D + _PPS_INPUT_BIT),
    PPS_IN_INT2		= (1  + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_INT3		= (2  + _PPS_SET_B + _PPS_INPUT_BIT),
    PPS_IN_INT4		= (3  + _PPS_SET_A + _PPS_INPUT_BIT),
    PPS_IN_T2CK		= (5  + _PPS_SET_A + _PPS_INPUT_BIT),
    PPS_IN_T3CK		= (6  + _PPS_SET_B + _PPS_INPUT_BIT),
    PPS_IN_T4CK		= (7  + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_T5CK		= (8  + _PPS_SET_D + _PPS_INPUT_BIT),
    PPS_IN_IC1		= (9  + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_IC2		= (10 + _PPS_SET_D + _PPS_INPUT_BIT),
    PPS_IN_IC3		= (11 + _PPS_SET_B + _PPS_INPUT_BIT),
    PPS_IN_IC4		= (12 + _PPS_SET_A + _PPS_INPUT_BIT),
    PPS_IN_IC5		= (13 + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_OCFA		= (17 + _PPS_SET_D + _PPS_INPUT_BIT),
    PPS_IN_OCFB		= (18 + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_U1RX		= (19 + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_U1CTS	= (20 + _PPS_SET_B + _PPS_INPUT_BIT),
    PPS_IN_U2RX		= (21 + _PPS_SET_B + _PPS_INPUT_BIT),
    PPS_IN_U2CTS	= (22 + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_SDI1		= (32 + _PPS_SET_B + _PPS_INPUT_BIT),
    PPS_IN_SS1		= (33 + _PPS_SET_A + _PPS_INPUT_BIT),
    PPS_IN_SDI2		= (35 + _PPS_SET_C + _PPS_INPUT_BIT),
    PPS_IN_SS2		= (36 + _PPS_SET_D + _PPS_INPUT_BIT),
    PPS_IN_REFCLKI	= (45 + _PPS_SET_A + _PPS_INPUT_BIT),

} ppsFunctionType;


/* Data type for PPS input select register.
*/
typedef uint32_t p32_ppsin;


/* These symbols define the values to load into a PPS input select register
** to assign the actual input pin. The PIC32 architecture divides these values 
** into four disjoint sets. Set membership is defined as part of the value to
** allow error checking when the pins are being mapped.
*/
#define	_PPS_RPA0		(0 + _PPS_SET_A)
#define	_PPS_RPB3		(1 + _PPS_SET_A)
#define	_PPS_RPB4		(2 + _PPS_SET_A)
#define	_PPS_RPB15		(3 + _PPS_SET_A)
#define	_PPS_RPB7		(4 + _PPS_SET_A)
#define	_PPS_RPC7		(5 + _PPS_SET_A)
#define	_PPS_RPC0		(6 + _PPS_SET_A)
#define	_PPS_RPC5		(7 + _PPS_SET_A)

#define	_PPS_RPA1		(0 + _PPS_SET_B)
#define	_PPS_RPB5		(1 + _PPS_SET_B)
#define	_PPS_RPB1		(2 + _PPS_SET_B)
#define	_PPS_RPB11		(3 + _PPS_SET_B)
#define	_PPS_RPB8		(4 + _PPS_SET_B)
#define	_PPS_RPA8		(5 + _PPS_SET_B)
#define	_PPS_RPC8		(6 + _PPS_SET_B)
#define	_PPS_RPA9		(7 + _PPS_SET_B)

#define	_PPS_RPA2		(0 + _PPS_SET_C)
#define	_PPS_RPB6		(1 + _PPS_SET_C)
#define	_PPS_RPA4		(2 + _PPS_SET_C)
#define	_PPS_RPB13		(3 + _PPS_SET_C)
#define	_PPS_RPB2		(4 + _PPS_SET_C)
#define	_PPS_RPC6		(5 + _PPS_SET_C)
#define	_PPS_RPC1		(6 + _PPS_SET_C)
#define	_PPS_RPC3		(7 + _PPS_SET_C)

#define	_PPS_RPA3		(0 + _PPS_SET_D)
#define	_PPS_RPB14		(1 + _PPS_SET_D)
#define	_PPS_RPB0		(2 + _PPS_SET_D)
#define	_PPS_RPB10		(3 + _PPS_SET_D)
#define	_PPS_RPB9		(4 + _PPS_SET_D)
#define	_PPS_RPC9		(5 + _PPS_SET_D)
#define	_PPS_RPC2		(6 + _PPS_SET_D)
#define	_PPS_RPC4		(7 + _PPS_SET_D)

/* These symbols define the indices of the output pin mapping
** registers.
*/
#define	_PPS_RPA0R		0
#define	_PPS_RPA1R		1
#define	_PPS_RPA2R		2
#define	_PPS_RPA3R		3
#define	_PPS_RPA4R		4
#define _PPS_RPA8R		8
#define	_PPS_RPA9R		9

#define	_PPS_RPB0R		11
#define	_PPS_RPB1R		12
#define	_PPS_RPB2R		13
#define	_PPS_RPB3R		14
#define	_PPS_RPB4R		15
#define	_PPS_RPB5R		16
#if defined(__PIC32MX1XX__)
#define	_PPS_RPB6R		17
#else
#define	_PPS_RPB6R		NOT_PPS_PIN
#endif
#define	_PPS_RPB7R		18
#define	_PPS_RPB8R		19
#define	_PPS_RPB9R		20
#define	_PPS_RPB10R		21
#define	_PPS_RPB11R		22
#define	_PPS_RPB13R		24
#define	_PPS_RPB14R		25
#define	_PPS_RPB15R		26

#define	_PPS_RPC0R		27
#define	_PPS_RPC1R		28
#define	_PPS_RPC2R		29
#define	_PPS_RPC3R		30
#define	_PPS_RPC4R		31
#define	_PPS_RPC5R		32
#define	_PPS_RPC6R		33
#define	_PPS_RPC7R		34
#define	_PPS_RPC8R		35
#define	_PPS_RPC9R		36

#endif	// defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

/* ------------------------------------------------------------ */

#endif		// P32_DEFS_H

//************************************************************************
