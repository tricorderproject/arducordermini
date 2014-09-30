/*********************************************************************
 *
 *                  Generic Exception Handler
 *
 *********************************************************************
 * FileName:        exceptions.c
 * Dependencies:
 *
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 * Author:			Darren Wenn
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32/PIC24 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32/PIC24 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 *
 ********************************************************************/

#include <p32xxxx.h>

// declared static in case exception condition would prevent
// auto variable being created
static enum {
	EXCEP_IRQ = 0,			// interrupt
	EXCEP_AdEL = 4,			// address error exception (load or ifetch)
	EXCEP_AdES,				// address error exception (store)
	EXCEP_IBE,				// bus error (ifetch)
	EXCEP_DBE,				// bus error (load/store)
	EXCEP_Sys,				// syscall
	EXCEP_Bp,				// breakpoint
	EXCEP_RI,				// reserved instruction
	EXCEP_CpU,				// coprocessor unusable
	EXCEP_Overflow,			// arithmetic overflow
	EXCEP_Trap,				// trap (possible divide by zero)
	EXCEP_IS1 = 16,			// implementation specfic 1
	EXCEP_CEU,				// CorExtend Unuseable
	EXCEP_C2E				// coprocessor 2
} _excep_code;

static unsigned int _epc_code;
static unsigned int _excep_addr;

//************************************************************************
// this function overrides the normal _weak_ generic handler
void _general_exception_handler(void)
{
	asm volatile("mfc0 %0,$13" : "=r" (_epc_code));
	asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

	_epc_code = (_excep_code & 0x0000007C) >> 2;

	while (1)
	{
		// Examine _excep_code to identify the type of exception
		// Examine _excep_addr to find the address that caused the exception
	}
}
