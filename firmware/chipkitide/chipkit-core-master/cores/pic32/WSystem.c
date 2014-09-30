/************************************************************************/
/*																		*/
/*	WSystem.c -- Low Level System Management Functions					*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2012, Digilent. All rights reserved						*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*	This module contains functions for low level system control and		*/
/*	management of the processor. This includes things like interrupt	*/
/*	management and processor configuration.								*/
/*																		*/
/************************************************************************/
//*	This module is free software; you can redistribute it and/or
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
/*  Revision History:													*/
/*																		*/
/*	08/23/2012(GeneApperson): Created									*/
/*	06/18/2013(Keith Vogel): Finished the interrupt vector handler									*/
/*																		*/
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include	<p32xxxx.h>

#define	OPT_SYSTEM_INTERNAL
#include	<System_Defs.h>
#include	<p32_defs.h>

#include	"wiring.h"


/* ------------------------------------------------------------ */
/*				Local Type Definitions							*/
/* ------------------------------------------------------------ */

/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */

//************************************************************************
//* Interrupt vector dispatch table
//* This table contains pointers to the dynamically installed interrupt service routines.
//* The interrupt vectors in program flash memory have been populated with dispatch
//* functions that indirect to the ISR specified by this table.
extern const uint32_t _GEN_EXCPT_ADDR;
void (*volatile _isr_primary_install[NUM_INT_VECTOR]) (void) = {[0 ... NUM_INT_VECTOR-1] = (isrFunc) &_GEN_EXCPT_ADDR}; /* Initialize all 64*/

/* ------------------------------------------------------------ */
/*				Local Variables									*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Forward Declarations							*/
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*				Public Interface Functions						*/
/* ------------------------------------------------------------ */
/*			Interrupt Vector Management Functions				*/
/* ------------------------------------------------------------ */

/***	initIntVector
**
**	Parameters:
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initializes the RAM IntVector table to
**		all of the compiler generated interrupt vectors
**		This will provide backwards compatibility should
**		someone not set their interrupt vector by calling
**		setIntVector; but by not setting the IntVector
**      your vector may be maked by a conflicting peripheral
*/
void initIntVector(void)
{
    const IMAGE_HEADER_INFO * pImageHeader = getImageHeaderInfoStructure();
    int i = 0;
    void * pvOrgIntVec = pImageHeader->pOrgVector0;

    for(i=0; i<NUM_INT_VECTOR; i++)
    {
        // If a compiler installed interrupt handler exits, pre-load it
        // and don't fool with the priority
        if(*((uint32_t *) pvOrgIntVec) != 0xFFFFFFFF)
        {
            _isr_primary_install[i] = (isrFunc) pvOrgIntVec;
        }

        pvOrgIntVec += pImageHeader->cbVectorSpacing;
    }

    return;
}

/***	setIntVector
**
**	Parameters:
**		vec		- interrupt vector number
**		func	- interrupt service routine to install
**
**	Return Value:
**		Returns pointer to previous interrupt service routine for the vector
**              This may return the compiler installed routine if the compiler set one.
**              It will return the address of the general exception handler if no previous ISR was set.
**              It will return 0/NULL if the vector requested is out of range of the processor
**
**	Errors:
**		None as this is used in begin() methods that have no error returns.
**
**	Description:
**		Dynamically install an interrupt service routine for the specified
**		interrupt vector; This will blast over exiting ones without an error
**      because many Arduino begin methods return no errors and just expect this to
**      work. However, this may overwrite a previeously installed ISR.
**
**      This does not change the priority level of the interrupt routine
*/
isrFunc setIntVector(int vec, isrFunc func)
{
    const IMAGE_HEADER_INFO * pImageHeader = getImageHeaderInfoStructure();
    isrFunc t = 0;

    if (vec < NUM_INT_VECTOR)
    {
        t = _isr_primary_install[vec];
        _isr_primary_install[vec] = func;       
    }

    return t;
}

/* ------------------------------------------------------------ */
/***	getIntVector
**
**	Parameters:
**		vec		- interrupt vector number
**
**	Return Value:
**              The current ISR function
**
**	Errors:
**              NULL if vector is out of range
**
**	Description:
**          Returns the currently assigned ISR function without
**          changeing anything.
**
*/
isrFunc getIntVector(int vec)
{

    if (vec < NUM_INT_VECTOR)
    {
        return _isr_primary_install[vec];
    }
    else
    {
        return 0;
    }
}

/* ------------------------------------------------------------ */
/***	clearIntVector
**
**	Parameters:
**		vec		- interrupt vector number
**
**	Return Value:
**      Returns the currently set ISR before clearing it
**
**	Errors:
**		Returns NULL if the vector number specified is out of range
**
**	Description:
**		Sets the priority to 0 thus disabling the ISR, and sets the 
**      pointer to the general exception handler.
*/
isrFunc clearIntVector(int vec)
{
    const IMAGE_HEADER_INFO * pImageHeader = getImageHeaderInfoStructure();
    void * pvOrgIntVec = pImageHeader->pOrgVector0 + (vec * pImageHeader->cbVectorSpacing);
    isrFunc rISR = 0;

    if (vec < NUM_INT_VECTOR)
    {
        rISR = _isr_primary_install[vec];
        setIntPriority(vec, 0, 0);                                  // this will disable the interrupt
        _isr_primary_install[vec] = (isrFunc) &_GEN_EXCPT_ADDR;
    }
    return(rISR);
}

/* ------------------------------------------------------------ */
/*				Interrupt Management Functions					*/
/* ------------------------------------------------------------ */
/***	enableInterrupts
**
**	Parameters:
**		none
**
**	Return Value:
**		Previous state of the global interrupt enable flag
**
**	Errors:
**		none
**
**	Description:
**		This function sets the global interrupt enable flag,
**		enabling all interrupts.
*/

uint32_t __attribute__((nomips16))  enableInterrupts(void)
{
    uint32_t status = 0;

    asm volatile("ei    %0" : "=r"(status));

    return status;
}

/* ------------------------------------------------------------ */
/***	disableInterrutps
**
**	Parameters:
**		none
**
**	Return Value:
**		Previous state fo the global interrupt enable flag
**
**	Errors:
**		none
**
**	Description:
**		This function clears the global interrupt enable flag,
**		disabling all interrupts.
*/

uint32_t __attribute__((nomips16)) disableInterrupts(void)
{
    uint32_t status = 0;

    asm volatile("di    %0" : "=r"(status));

    return status;
}

/* ------------------------------------------------------------ */
/***	restoreInterrupts
**
**	Parameters:
**		st		- Previous state of global interrupt enable flag
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function restores the state of the global interrupt
**		enable flag to a previous state. The value passed in for
**		st should be a value previously returned by either
**		enableInterrupts() or disableInterrupts().
*/

void __attribute__((nomips16))  restoreInterrupts(uint32_t st)
{
    if (st & 0x00000001)
	{
        asm volatile("ei");
	}
    else
	{
        asm volatile("di");
	}
}

/* ------------------------------------------------------------ */
/***	getIntFlag
**
**	Parameters:
**		irq		- Interrupt request number
**
**	Return Value:
**		Returns the state of the request interrupt flag.
**
**	Errors:
**		none
**
**	Description:
**		Return the state of the interrupt request flag for the
**		specified interrupt. The return value will be 0 if the
**		flag is not set, and non-zero if the flag is set.
*/

uint32_t getIntFlag(int irq)
{
	p32_regset *	ifs;

	ifs = ((p32_regset *)&IFS0) + (irq / 32);
	return (ifs->reg & (1 << (irq % 32))) != 0;
}


/* ------------------------------------------------------------ */
/***	clearIntFlag
**
**	Parameters:
**		irq		- Interrupt request number
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Clear the interrupt request flag for the specified interrupt.
*/

void clearIntFlag(int irq)
{
	p32_regset *	ifs;

	ifs = ((p32_regset *)&IFS0) + (irq / 32);
	ifs->clr = 1 << (irq % 32);
}

/* ------------------------------------------------------------ */
/***	setIntEnable
**
**	Parameters:
**		irq		- Interrupt request number
**
**	Return Value:
**		Returns the previous state of the specified interrupt enable flag
**
**	Errors:
**		none
**
**	Description:
**		Set the interrupt enable flag for the specified interrupt
**		request. This will enable whatever peripheral interrupt is
**		associated with the specified interrupt request.
*/

uint32_t setIntEnable(int irq)
{
	p32_regset *	iec;
	uint32_t		st;

	iec = ((p32_regset *)&IEC0) + (irq / 32);
	st = iec->reg;
	iec->set = 1 << (irq % 32);
	return st;
}

/* ------------------------------------------------------------ */
/***	clearIntEnable
**
**	Parameters:
**		irq		- interrupt request number
**
**	Return Value:
**		Returns the previous state of the specified interrupt enable flag
**
**	Errors:
**		none
**
**	Description:
**		Disable the interrupt for the specified interrupt request
*/

uint32_t clearIntEnable(int irq)
{
	p32_regset *	iec;
	uint32_t		st;

	iec = ((p32_regset *)&IEC0) + (irq / 32);
	st = iec->reg;
	iec->clr = 1 << (irq % 32);
	return st;
}

/* ------------------------------------------------------------ */
/***	restoreIntEnable
**
**	Parameters:
**		irq			- interrupt request number
**		st			- previous enable state to restore
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function restores the interrupt enable flag to a
**		previous state. The value specified in the st parameter
**		should be a value previously returned by setIntEnable()
**		or clearIntEnable()
*/

void restoreIntEnable(int irq, uint32_t st)
{
	p32_regset *	iec;
	uint32_t		bit;

	iec = ((p32_regset *)&IEC0) + (irq / 32);
	bit = (1 << (irq % 32));
	if ((st & bit) != 0)
	{
		iec->set = bit;
	}
	else
	{
		iec->clr = bit;
	}
}

/* ------------------------------------------------------------ */
/***	setIntPriority
**
**	Parameters:
**		vec			- interrupt vector number
**		ipl			- interrupt priority level to set
**		spl			- interrupt sub-priority level to set
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function sets interrupt priority and sub-priority levels
**		for the specified interrupt vector.
*/

void setIntPriority(int vec, int ipl, int spl)
{
	p32_regset *	ipc;
	int				bn;

	/* Compute the address of the interrupt priority control register used
	** by this interrupt vector
	*/
	ipc = ((p32_regset *)&IPC0) + (vec / 4);

	/* Compute the number of bit positions to shift to get to the
	** correct position for the priority bits for this vector.
	*/
	bn = 8 * (vec % 4);

	/* Set the interrupt privilege level and sub-privilege level
	*/
	ipc->clr = (0x1F << bn);
	ipc->set = ((ipl << 2) + spl) << bn;
}

/* ------------------------------------------------------------ */
/***	getIntPriority
**
**	Parameters:
**		vec			- interrupt vector number
**		pipl		- pointer to variable to receive priority
**		pspl		- pointer to variable to receive sub-priority
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		This function sets interrupt priority and sub-priority levels
**		for the specified interrupt vector.
*/

void getIntPriority(int vec, int * pipl, int * pspl)
{
	p32_regset *	ipc;
	int				bn;

	/* Compute the address of the interrupt priority control register used
	** by this interrupt vector
	*/
	ipc = ((p32_regset *)&IPC0) + (vec / 4);

	/* Compute the number of bit positions to shift to get to the
	** correct position for the priority bits for this vector.
	*/
	bn = 8 * (vec % 4);

	/* Set the interrupt privilege level and sub-privilege level
	*/
	*pipl = (ipc->reg >> (bn+2)) & 0x07;
	*pspl = (ipc->reg >> bn) & 0x03;

}

/* ------------------------------------------------------------ */
/*			Misc Processor Support Functions					*/
/* ------------------------------------------------------------ */
/***	getPeripheralClock()
**
**	Parameters:
**		none
**
**	Return Value:
**		Returns the current peripheral bus clock frequency
**
**	Errors:
**		none
**
**	Description:
**		Get the peripheral bus clock frequency
*/

uint32_t getPeripheralClock()
{
	uint32_t	clkPb;

    clkPb = F_CPU;
    clkPb >>= OSCCONbits.PBDIV;

    return clkPb;

}

/* ------------------------------------------------------------ */
/***	readCoreTimer
**
**	Parameters:
**		none
**
**	Return Value:
**		Returns core timer count value
**
**	Errors:
**		none
**
**	Description:
**		Returns the current value of the core timer.
*/

uint32_t __attribute__((nomips16)) readCoreTimer(void)
{
    uint32_t tmr;

    // Get the value of the core timer count register.
    asm volatile("mfc0   %0, $9" : "=r"(tmr));

    return tmr;
}

/* ------------------------------------------------------------ */
/***	writeCoreTimer
**
**	Parameters:
**		tmr		- value to write to core timer counter
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Writes the specified value to the core timer count register.
*/

void __attribute__((nomips16)) writeCoreTimer(uint32_t tmr)
{
    // Write the value to the core timer count register
    asm volatile("mtc0   %0, $9": "+r"(tmr));

}

/* ------------------------------------------------------------ */
/*			Private System Configuration Functions				*/
/* ------------------------------------------------------------ */
/***	configSystem
**
**	Parameters:
**		clk		- processor master clock frequency
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Configure the processor. This disables data ram wait states,
**		sets the number of flash wait states and enables predictive
**		prefetch for both cached and non-cached memory segments.
*/

void __attribute__ ((nomips16)) _configSystem(uint32_t clk)
{
	uint32_t	stInt;
#ifdef _PCACHE
	uint32_t	stCache;
    uint32_t	wait;
	register unsigned long tmp;
#endif

	stInt = disableInterrupts();

	/* Disable wait states in data ram.
	*/
	BMXCONCLR = (1 << _BMXCON_BMXWSDRM_POSITION);

#ifdef _PCACHE

	stCache = CHECON;

	/* Configure predictive prefetch caching for both cached and
	** non-cached memory regions.
	*/
    stCache |= (3 << _CHECON_PREFEN_POSITION);

	/* Turn on caching for KSEG0
	*/
	asm("mfc0 %0,$16,0" :  "=r"(tmp));
	tmp = (tmp & ~7) | 3;
	asm("mtc0 %0,$16,0" :: "r" (tmp));

	/* Configure the number of wait states in the program flash
	*/
    wait = 0;

    while(clk > FLASH_SPEED_HZ)
    {
        wait += 1;
        clk -= FLASH_SPEED_HZ;
    }

    stCache &= ~_CHECON_PFMWS_MASK;
	stCache |= (wait << _CHECON_PFMWS_POSITION);

	CHECON = stCache;

#endif


	restoreInterrupts(stInt);
}

/* ------------------------------------------------------------ */
/***	_enableMultiVectorInterrupts
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
**		Configure the system for vectored interrupts and turn
**		interrupts on.
*/

void __attribute__ ((nomips16)) _enableMultiVectorInterrupts()
{
    unsigned int val;

    /* Set the CP0 bit so that interrupt exceptions use the
	** special interrupt vector and not the general exception vector.
	*/
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

	/* Turn on multi-vectored interrupts.
	*/
    INTCONSET = _INTCON_MVEC_MASK;

    /* Enable interrupts.
	*/
    enableInterrupts();

}

/* ------------------------------------------------------------ */
/***	_initCoreTimer
**
**	Parameters:
**		prd		- Core timer interrupt period
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Clear the core timer counter and initialize the compare
**		period register.
*/

void __attribute__((nomips16)) _initCoreTimer(uint32_t prd)
{
	/* Clear the core timer counter
	*/
    asm volatile("mtc0   $0,$9");

    /* Store the requested value in the compare register
	*/
    asm volatile("mtc0   %0,$11" : "+r"(prd));
}

/* ------------------------------------------------------------ */
/***	_softwareReset
**
**	Parameters:
**		none
**
**	Return Value:
**		Does not return
**
**	Errors:
**		none
**
**	Description:
**		This function performs a software reset of the processor. This
**		requires the following steps: Unlock the processor; Set the SWRST
**		bit in the RSWRT register; Read the RSWRT register.
**
**	Note:
**		Something like the while(1) needs to be performed after the read
**		to ensure that no other instructions are executed before the
**		actual reset occurs.
*/

 void __attribute__((noreturn)) _softwareReset(void)
{
	volatile int * p = &RSWRST;

	// Unlock the system
	disableInterrupts();
	SYSKEY = 0;
	SYSKEY = 0xAA996655;
	SYSKEY = 0x556699AA;

	// Perform the software reset
	RSWRSTSET=_RSWRST_SWRST_MASK;
	*p;

	// Wait for the rest to take place
	while(1);

}

/* ------------------------------------------------------------ */
/***	ProcName
**
**	Parameters:
**
**	Return Value:
**
**	Errors:
**
**	Description:
**
*/

/* ------------------------------------------------------------ */

/************************************************************************/

