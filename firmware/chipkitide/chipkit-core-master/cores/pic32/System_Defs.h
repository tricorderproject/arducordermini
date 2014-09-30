/************************************************************************/
/*																		*/
/*	System_Defs.h -- System Configuration Declarations					*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the definition of symbols used for general build	*/
/* configuration of the system.											*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/29/2011(GeneApperson): Created									*/
/*	12/20/2011(GeneApperson): Added task manager declarations			*/
/*	07/26/2012(GeneApperson): Added PPS support for PIC32MX1xx/MX2xx	*/
/*		devices															*/
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

#if !defined(SYSTEM_DEFS_H)
#define SYSTEM_DEFS_H

#include "System_Config.h"
#include "cpudefs.h"

/* ------------------------------------------------------------ */
/*					EEPROM Emulation Declarations				*/
/* ------------------------------------------------------------ */

#define	_EEPROM_PAGE_SIZE	1024
#define	_EEPROM_PAGE_COUNT	1

/* ------------------------------------------------------------ */
/*					General Interrupt Declarations				*/
/* ------------------------------------------------------------ */

#if defined(__PIC32MX1XX__)
	#define	NUM_INT_VECTOR	44
	#define	NUM_INT_REQUEST	64
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

#if defined(__PIC32MX2XX__)
	#define	NUM_INT_VECTOR	44
	#define	NUM_INT_REQUEST	64
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

#if defined(__PIC32MX3XX__)
	#define	NUM_INT_VECTOR	45
	#define	NUM_INT_REQUEST	57
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

#if defined(__PIC32MX4XX__)
	#define	NUM_INT_VECTOR	46
	#define	NUM_INT_REQUEST	58
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

#if defined(__PIC32MX5XX__)
	#define	NUM_INT_VECTOR	52
	#define	NUM_INT_REQUEST	76
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

#if defined(__PIC32MX6XX__)
	#define	NUM_INT_VECTOR	52
	#define	NUM_INT_REQUEST	76
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

#if defined(__PIC32MX7XX__)
	#define	NUM_INT_VECTOR	52
	#define	NUM_INT_REQUEST	76
	#define NUM_EXTERNAL_INTERRUPTS	5
#endif

/* Symbols for referring to the external interrupts
*/
#define	EXT_INT0	0
#define	EXT_INT1	1
#define	EXT_INT2	2
#define	EXT_INT3	3
#define	EXT_INT4	4

/* ------------------------------------------------------------ */
/*					Interrupt Priority Declarations				*/
/* ------------------------------------------------------------ */
/* The following symbols are defined for each interrupt vector.
**	_IPL_XXX_ISR		- interrupt priority for ISR
**	_IPL_XXX_IPC		- priority to be programmed into the IPC register
**	_SPI_XXX_IPC		- sub-priority for the IPC register
**
** The IPL for the ISR and the IPC registers must agree.
*/

/* Core Timer
*/
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
#define	_CT_IPL_ISR		IPL7SOFT
#define	_CT_IPL_IPC		7
#define	_CT_SPL_IPC		0
#else
#define	_CT_IPL_ISR		IPL7SRS
#define	_CT_IPL_IPC		7
#define	_CT_SPL_IPC		0
#endif

/* Core Software Interrupts
*/
#define	_CS0_IPL_ISR	ipl2
#define	_CS0_IPL_IPC	2
#define	_CS0_SPL_IPC	0

#define	_CS1_IPL_ISR	ipl2
#define	_CS1_IPL_IPC	2
#define	_CS1_SPL_IPC	0

/* External Interrupts.
*/
#define	_INT0_IPL_ISR	ipl4
#define	_INT0_IPL_IPC	4
#define	_INT0_SPL_IPC	0

#define	_INT1_IPL_ISR	ipl4
#define	_INT1_IPL_IPC	4
#define	_INT1_SPL_IPC	0

#define	_INT2_IPL_ISR	ipl4
#define	_INT2_IPL_IPC	4
#define	_INT2_SPL_IPC	0

#define	_INT3_IPL_ISR	ipl4
#define	_INT3_IPL_IPC	4
#define	_INT3_SPL_IPC	0

#define	_INT4_IPL_ISR	ipl4
#define	_INT4_IPL_IPC	4
#define	_INT4_SPL_IPC	0

/* Timer Interrupts
*/
#define	_T1_IPL_ISR	ipl3
#define	_T1_IPL_IPC	3
#define	_T1_SPL_IPC	0

#define	_T2_IPL_ISR	ipl2
#define	_T2_IPL_IPC	2
#define	_T2_SPL_IPC	0

#define	_T3_IPL_ISR	ipl4
#define	_T3_IPL_IPC	4
#define	_T3_SPL_IPC	0

#define	_T4_IPL_ISR	ipl4
#define	_T4_IPL_IPC	4
#define	_T4_SPL_IPC	0

#define	_T5_IPL_ISR	ipl4
#define	_T5_IPL_IPC	4
#define	_T5_SPL_IPC	0

/* Input Capture Interrupts
*/
#define	_IC1_IPL_ISR	ipl2
#define	_IC1_IPL_IPC	2
#define	_IC1_SPL_IPC	0

#define	_IC2_IPL_ISR	ipl2
#define	_IC2_IPL_IPC	2
#define	_IC2_SPL_IPC	0

#define	_IC3_IPL_ISR	ipl2
#define	_IC3_IPL_IPC	2
#define	_IC3_SPL_IPC	0

#define	_IC4_IPL_ISR	ipl2
#define	_IC4_IPL_IPC	2
#define	_IC4_SPL_IPC	0

#define	_IC5_IPL_ISR	ipl2
#define	_IC5_IPL_IPC	2
#define	_IC5_SPL_IPC	0

/* Input Capture Error Interrupts
*/
#define	_IC1E_IPL_ISR	ipl2
#define	_IC1E_IPL_IPC	2
#define	_IC1E_SPL_IPC	0

#define	_IC2E_IPL_ISR	ipl2
#define	_IC2E_IPL_IPC	2
#define	_IC2E_SPL_IPC	0

#define	_IC3E_IPL_ISR	ipl2
#define	_IC3E_IPL_IPC	2
#define	_IC3E_SPL_IPC	0

#define	_IC4E_IPL_ISR	ipl2
#define	_IC4E_IPL_IPC	2
#define	_IC4E_SPL_IPC	0

#define	_IC5E_IPL_ISR	ipl2
#define	_IC5E_IPL_IPC	2
#define	_IC5E_SPL_IPC	0

/* Output Compare Interrupts
*/
#define	_OC1_IPL_ISR	ipl2
#define	_OC1_IPL_IPC	2
#define	_OC1_SPL_IPC	0

#define	_OC2_IPL_ISR	ipl2
#define	_OC2_IPL_IPC	2
#define	_OC2_SPL_IPC	0

#define	_OC3_IPL_ISR	ipl2
#define	_OC3_IPL_IPC	2
#define	_OC3_SPL_IPC	0

#define	_OC4_IPL_ISR	ipl2
#define	_OC4_IPL_IPC	2
#define	_OC4_SPL_IPC	0

#define	_OC5_IPL_ISR	ipl2
#define	_OC5_IPL_IPC	2
#define	_OC5_SPL_IPC	0

/* Priority level defintions for shared interrupt vectors.
** Some serial controllers implement multiple serial interfaces.
** These are given different names depending on whether they are
** being accessed as UART, SPI, or I2C. However, they all are
** the same serial controller and therefore use the same interrupt
** vector. The priority symbols are set for the primary UART name
** for the interface, and the others are set using the primary UART
** symbols.
*/

/* UARTS
*/
#define	_UART1_IPL_ISR	ipl2	//interrupt priority for ISR
#define	_UART1_IPL_IPC	2		//interrupt priority for IPC register
#define	_UART1_SPL_IPC	0		//interrupt subpriority for IPC register

#define	_UART2_IPL_ISR	ipl2	//interrupt priority for ISR
#define	_UART2_IPL_IPC	2		//interrupt priority for IPC register
#define	_UART2_SPL_IPC	0		//interrupt subpriority for IPC register

#define	_UART3_IPL_ISR	ipl2	//interrupt priority for ISR
#define	_UART3_IPL_IPC	2		//interrupt priority for IPC register
#define	_UART3_SPL_IPC	0		//interrupt subpriority for IPC register

#define	_UART4_IPL_ISR	ipl2	//interrupt priority for ISR
#define	_UART4_IPL_IPC	2		//interrupt priority for IPC register
#define	_UART4_SPL_IPC	0		//interrupt subpriority for IPC register

#define	_UART5_IPL_ISR	ipl2	//interrupt priority for ISR
#define	_UART5_IPL_IPC	2		//interrupt priority for IPC register
#define	_UART5_SPL_IPC	0		//interrupt subpriority for IPC register

#define	_UART6_IPL_ISR	ipl2	//interrupt priority for ISR
#define	_UART6_IPL_IPC	2		//interrupt priority for IPC register
#define	_UART6_SPL_IPC	0		//interrupt subpriority for IPC register

/* SPI Controllers
*/
#define	_SPI1_IPL_ISR	ipl3	//interrupt priority for the ISR
#define	_SPI1_IPL_IPC	3		//interrupt priority for the IPC register
#define	_SPI1_SPL_IPC	0		//interrupt subpriority for the IPC register

#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__) || defined(__PIC32MX3XX__) || defined(__PIC32MX4XX__)
#define	_SPI2_IPL_ISR	ipl3	//interrupt priority for the ISR
#define	_SPI2_IPL_IPC	3		//interrupt priority for the IPC register
#define	_SPI2_SPL_IPC	0		//interrupt subpriority for the IPC register
#endif

#if defined(__PIC32MX5XX__) || defined(__PIC32MX6XX__) || defined(__PIC32MX7XX__)
#define	_SPI2_IPL_ISR	_UART3_IPL_ISR	//shared with UART3
#define	_SPI2_IPL_IPC	_UART3_IPL_IPC
#define	_SPI2_SPL_IPC	_UART3_SPL_IPC

#define	_SPI3_IPL_ISR	_UART1_IPL_ISR	//shared with UART1
#define	_SPI3_IPL_IPC	_UART1_IPL_IPC		
#define	_SPI3_SPL_IPC	_UART1_SPL_IPC

#define	_SPI4_IPL_ISR	_UART2_IPL_ISR	//shared with UART2
#define	_SPI4_IPL_IPC	_UART2_IPL_IPC
#define	_SPI4_SPL_IPC	_UART2_SPL_IPC
#endif

/* I2C Controllers
*/
#define	_I2C1_IPL_ISR	ipl3	//interrupt priority for ISR
#define	_I2C1_IPL_IPC	3		//interrupt priority for IPC register
#define	_I2C1_SPL_IPC	0		//interrupt subpriority for IPC register

#define	_I2C2_IPL_ISR	ipl3	//interrupt priority for ISR
#define	_I2C2_IPL_IPC	3		//interrupt priority for IPC register
#define	_I2C2_SPL_IPC	0		//interrupt subpriority for IPC register

#if defined(__PIC32MX5XX__) || defined(__PIC32MX6XX__) || defined(__PIC32MX7XX__)
#define	_I2C3_IPL_ISR	_UART1_IPL_ISR	//shared with UART1
#define	_I2C3_IPL_IPC	_UART1_IPL_IPC
#define	_I2C3_SPL_IPC	_UART1_SPL_IPC

#define	_I2C4_IPL_ISR	_UART3_IPL_ISR	//shared with UART3
#define	_I2C4_IPL_IPC	_UART3_IPL_IPC
#define	_I2C4_SPL_IPC	_UART3_SPL_IPC

#define	_I2C5_IPL_ISR	_UART2_IPL_ISR	//shared with UART2
#define	_I2C5_IPL_IPC	_UART2_IPL_IPC
#define	_I2C5_SPL_IPC	_UART2_SPL_IPC
#endif

/* Input Change Interrupt
*/
#define	_CN_IPL_ISR		ipl1
#define	_CN_IPL_IPC		1
#define	_CN_SPL_IPC		0

/* Analog to Digital Converter Interrupt
*/
#define	_ADC_IPL_ISR	ipl2
#define	_ADC_IPL_IPC	2
#define	_ADC_SPL_IPC	0

/* Parallel Master Port Interrupt
*/
#define	_PMP_IPL_ISR	ipl2
#define	_PMP_IPL_IPC	2
#define	_PMP_SPL_IPC	0

/* Parallel Master Port Error Interrupt
*/
#define	_PMPE_IPL_ISR	ipl2
#define	_PMPE_IPL_IPC	2
#define	_PMPE_SPL_IPC	0

/* Analog Comparator Interrupts
*/
#define	_CMP1_IPL_ISR	ipl2
#define	_CMP1_IPL_IPC	2
#define	_CMP1_SPL_IPC	0

#define	_CMP2_IPL_ISR	ipl2
#define	_CMP2_IPL_IPC	2
#define	_CMP2_SPL_IPC	0

/* Fail-Safe Clock Monitor (FSCM) Interrupt
*/
#define	_FSCM_IPL_ISR	ipl2
#define	_FSCM_IPL_IPC	2
#define	_FSCM_SPL_IPC	0

/* Real Time Clock/Calendar Interrupt
*/
#define	_RTCC_IPL_ISR	ipl2
#define	_RTCC_IPL_IPC	2
#define	_RTCC_SPL_IPC	0

/* DMA Interrupts
*/
#define	_DMA0_IPL_ISR	ipl2
#define	_DMA0_IPL_IPC	2
#define	_DMA0_SPL_IPC	0

#define	_DMA1_IPL_ISR	ipl2
#define	_DMA1_IPL_IPC	2
#define	_DMA1_SPL_IPC	0

#define	_DMA2_IPL_ISR	ipl2
#define	_DMA2_IPL_IPC	2
#define	_DMA2_SPL_IPC	0

#define	_DMA3_IPL_ISR	ipl2
#define	_DMA3_IPL_IPC	2
#define	_DMA3_SPL_IPC	0

#define	_DMA4_IPL_ISR	ipl2
#define	_DMA4_IPL_IPC	2
#define	_DMA4_SPL_IPC	0

#define	_DMA5_IPL_ISR	ipl2
#define	_DMA5_IPL_IPC	2
#define	_DMA5_SPL_IPC	0

#define	_DMA6_IPL_ISR	ipl2
#define	_DMA6_IPL_IPC	2
#define	_DMA6_SPL_IPC	0

#define	_DMA7_IPL_ISR	ipl2
#define	_DMA7_IPL_IPC	2
#define	_DMA7_SPL_IPC	0

/* Flash Control Event Interrupt
*/
#define	_FCE_IPL_ISR	ipl2
#define	_FCE_IPL_IPC	2
#define	_FCE_SPL_IPC	0

/* USB Interrupt
*/
#define	_USB_IPL_ISR	ipl2
#define	_USB_IPL_IPC	2
#define	_USB_SPL_IPC	0

/* CAN Interrupts
*/
#define	_CAN1_IPL_ISR	ipl2
#define	_CAN1_IPL_IPC	2
#define	_CAN1_SPL_IPC	0

#define	_CAN2_IPL_ISR	ipl2
#define	_CAN2_IPL_IPC	2
#define	_CAN2_SPL_IPC	0

/* Ethernet Interrupt
*/
#define	_ETH_IPL_ISR	ipl2
#define	_ETH_IPL_IPC	2
#define	_ETH_SPL_IPC	0

/* ------------------------------------------------------------ */

#endif	// SYSTEM_DEFS_H

/************************************************************************/
