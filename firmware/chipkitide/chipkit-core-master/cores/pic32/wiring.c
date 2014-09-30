//************************************************************************
//*	wiring.c
//*	
//*	Arduino core files for PIC32
//*		Copyright (c) 2010, 2011 by Mark Sproul
//*	
//*	
//************************************************************************
//*	this code is based on code Copyright (c) 2005-2006 David A. Mellis
//*	
//*	This library is free software; you can redistribute it and/or
//*	modify it under the terms of the GNU Lesser General Public
//*	License as published by the Free Software Foundation; either
//*	version 2.1 of the License, or (at your option) any later version.
//*	
//*	This library is distributed in the hope that it will be useful,
//*	but WITHOUT ANY WARRANTY; without even the implied warranty of
//*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.//*	See the GNU
//*	Lesser General Public License for more details.
//*	
//*	You should have received a copy of the GNU Lesser General
//*	Public License along with this library; if not, write to the
//*	Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//*	Boston, MA	02111-1307	USA
//*	
//*	
//************************************************************************
//*	Edit History
//************************************************************************
//*	Oct 15,	2010	<MLS> Master interrupts working to generate millis()
//*	May 18,	2011	<MLS> merged in Brian Schmalz work on microseconds timer
//*	May 20,	2011	<MLS> For mega board, disabling secondary oscillator
//*	Aug 17,	2011	<MLS> Issue #84 disable the uart on init so that the pins can be used as general purpose I/O
//*	Aug  1,	2011	<BPS> added softpwm
//* Sept 12, 2011	<GeneApperson> Fixed bug in core timer interrupt service routine
//*						when some interrupts had been missed due to interrupts disabled
//* Nov 12, 2011	<GeneApperson> revised for board variant support
//* Nov 19, 2011    <BPS> Added WestfW's code from ChipKit forum - fixes
//*                 lost millisecond and microsecond times during rollover
//*	Dec 11,	2011	<MLS> Issue #151 added INTEnableInterrupts and INTDisableInterrupts
//* Dec 12, 2011	<GeneApperson> added call to _scheduleTask in delay()
//* Jan  9, 2012    <KeithV> Added CoreTimer Services to the CoreTimerHandler and fixed bugs where CT would be missed.
//                  Also fixed write_comp() inline assembler
//                  Also added countdown debug mask to stop the core timer when debugging.
//* Jun  1, 2012    <BPS> Added SoftReset() for software bootload
//	Feb  6, 2013	<GeneApperson> Removed dependencies on the Microchip plib library
//************************************************************************

#include <p32xxxx.h>
#include <sys/attribs.h>

#define	OPT_SYSTEM_INTERNAL
#define OPT_BOARD_INTERNAL	//pull in internal symbol definitons
#include "pins_arduino.h"
#include "p32_defs.h"

#include "wiring_private.h"

#undef _ENABLE_PIC_RTC_

//************************************************************************
//*	This sets the MPIDE version number in the image header as defined in the linker script
extern const uint32_t __attribute__((section(".mpide_version"))) _verMPIDE_Stub = MPIDEVER;    // assigns the build number in the header section in the image

// core timer ISR
void __attribute__((interrupt(),nomips16)) CoreTimerHandler(void);

//************************************************************************
//*	globals
//************************************************************************

unsigned int	__PIC32_pbClk;

// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

// Number of CoreTimer ticks per microsecond, for micros() function
#define CORETIMER_TICKS_PER_MICROSECOND		(F_CPU / 2 / 1000000UL)


//*	the "g" prefix means global variable
// Stores the current millisecond count (from power on)
volatile unsigned long gTimer0_millis	=	0;

// Variable used to track the microsecond count (from power on)
volatile unsigned long gCore_timer_last_val		=	0;
volatile unsigned long gCore_timer_micros		=	0;
volatile unsigned long gMicros_overflows		=	0;
volatile unsigned long gCore_timer_first_val	=	0;
volatile unsigned long gMicros_calculating		=	0;

// SoftPWM library update function pointer
uint32_t (*gSoftPWMServoUpdate)(void) = NULL;

// PPS lock variable
uint8_t ppsGlobalLock = false;

//************************************************************************
unsigned long millis()
{
	return(gTimer0_millis);
}

//************************************************************************
// Read the CoreTimer register, which counts up at a rate of 40MHz
// (CPU clock/2). Each microsecond will be 40 of these counts.
// We keep track of the total number of microseconds since the PIC
// was powered on, as an int. Which means that this value will
// overflow every 71.58 minutes. We have to keep track of the CoreTimer
// overflows. The first value of CoreTimer after an overflow is recorded,
// and all micros() calls after that (until the next overflow) are 
// referenced from that value. This insures accuracy and that micros()
// lines up perfectly with millis().
//************************************************************************
unsigned long micros()
{
	uint32_t	st;
	unsigned int cur_timer_val	=	0;
	unsigned int micros_delta	=	0;

	unsigned int result;
	
	st = disableInterrupts();
	result = gTimer0_millis * 1000;
	cur_timer_val = ReadCoreTimer();
	cur_timer_val -= gCore_timer_last_val;
	cur_timer_val += CORETIMER_TICKS_PER_MICROSECOND/2;  // rounding
	cur_timer_val /= CORETIMER_TICKS_PER_MICROSECOND;  // convert to microseconds
	restoreInterrupts(st);
	return (result + cur_timer_val);

}

//************************************************************************
// Delay for a given number of milliseconds.
void delay(unsigned long ms)
{
unsigned long	startMillis;

	startMillis	=	gTimer0_millis;
	while ((gTimer0_millis - startMillis) < ms)
	{
		_scheduleTask();
	}
}

//************************************************************************
//*	Delay for the given number of microseconds. Will fail on micros()
//*	rollover every 71 minutes
void delayMicroseconds(unsigned int us)
{
unsigned long	startMicros	=	micros();

	while ((micros() - startMicros) < us)
	{
		//*	do nothing
	}
}


//************************************************************************
void init()
{

#if defined(DEAD)
#ifdef _ENABLE_PIC_RTC_
	// Configure the device for maximum performance but do not change the PBDIV
	// Given the options, this function will change the flash wait states, RAM
	// wait state and enable prefetch cache but will not change the PBDIV.
	// The PBDIV value is already set via the pragma FPBDIV option above..
	__PIC32_pbClk	=	SYSTEMConfig(F_CPU, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
#else
	__PIC32_pbClk	=	SYSTEMConfigPerformance(F_CPU);
#endif
#endif

	// Configure the processor for the proper number of wait states and caching.
	_configSystem(F_CPU);

	// Enable multi-vector interrupts
	_enableMultiVectorInterrupts();

	// Initialize the core timer for use to maintain the system timer tick.
	_initCoreTimer(CORE_TICK_RATE);

    initIntVector();

	setIntPriority(_CORE_TIMER_VECTOR, _CT_IPL_IPC, _CT_SPL_IPC);
	setIntVector(_CORE_TIMER_VECTOR, CoreTimerHandler);
	setIntEnable(_CORE_TIMER_IRQ);

	// Save the peripheral bus frequency for later use.
	__PIC32_pbClk = getPeripheralClock();

   // allow for debugging, this will stop the core timer when the debugger takes control
    _CP0_BIC_DEBUG(_CP0_DEBUG_COUNTDM_MASK); 

#if defined(DEAD)
#ifdef _ENABLE_PIC_RTC_
	RtccInit();									// init the RTCC
//	while(RtccGetClkStat() != RTCC_CLK_ON);		// wait for the SOSC to be actually running and RTCC to have its clock source
												// could wait here at most 32ms

	// time is MSb: hour, min, sec, rsvd. date is MSb: year, mon, mday, wday.
	RtccOpen(0x10073000, 0x11010901, 0);
	RtccSetTimeDate(0x10073000, 0x10101701);
	// please note that the rsvd field has to be 0 in the time field!
#endif
#endif

	delay(50);

	//*	as per Al.Rodriguez@microchip.com, Jan 7, 2011
	//*	Disable the JTAG interface.
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)
	CFGCONbits.JTAGEN = 0;
	//CFGCONbits.TDOEN = 0;
	//OSCCONbits.SOSCEN = 0;
#else
	DDPCONbits.JTAGEN	=	0;
#endif


#if (OPT_BOARD_INIT != 0)
void	_board_init(void);
	_board_init();
#endif

	//* Initialize the periodic task manager
	_initTaskManager();

	//*	Issue #84
	//*	disable the uart so that the pins can be used as general purpose I/O
#if defined(_SER0_BASE)
	p32_uart *	uart;
	uart = (p32_uart *)_SER0_BASE;
	uart->uxMode.clr = (1 << _UARTMODE_ON);
#endif
}

//************************************************************************
//*		PPS - Peripheral Pin Select - Functions
//*
/* Currently, PPS is only available in PIC32MX1xx/PIC32MX2xx devices.
*/
#if defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

// Locks all PPS functions so that calls to mapPpsInput() or mapPpsOutput() always fail.
// You would use this function if you set up all of your PPS settings at the beginning
// of your sketch, and then wanted to prevent any changes while running the rest of the
// sketch. Can be unlocked with unlockPps().
void lockPps()
{
    ppsGlobalLock = true;
}

// Once the PPS system has been locked with logkPps(), this function will unlock it.
// Use this function before making any changes with mapPpsInput() or mapPpsOutput()
// functions.
void unlockPps()
{
    ppsGlobalLock = false;
}

// Use this function to connect up a input or output function (peripheral) with a 
// digitial pin.
// <pin> : Digital pin to connect
// <func> : Input or output name from ppsFunctionType enum (see p32_defs.h)
// Note that this function will fail if the pps system is locked, or if
// <pin> can't be mapped to <func>. There are only certain pins (up to 8)
// that can be mapped ro each <func>.
boolean mapPps(uint8_t pin, ppsFunctionType func)
{
	p32_ppsin *		pps;

    // if the pps system is locked, then don't do anything
    if (ppsGlobalLock)
    {
        return false;
    }
    
    if (!isPpsPin(pin))
    {
        return false;
    }

    // Check for valid PPS pin number and valid function number (input or output)
	if (
        !isPpsPin(pin) 
        || 
        ((ppsInputFromFunc(func) > NUM_PPS_IN) && ppsFuncIsInput(func))
        ||
        ((ppsOutputFromFunc(func) > NUM_PPS_OUT) && ppsFuncIsOutput(func))
    )
	{
		return false;
	}

	/* Check if the requested peripheral input can be mapped to
	** the requested pin.
	*/
	if ((ppsSetFromPin(pin) & ppsSetFromFunc(func)) == 0)
	{
		return false;
	}

    if (ppsFuncIsInput(func))
    {
	/* An input is mapped from the pin to the peripheral input
	** function by storing the select value into the register associated
	** with the peripheral function.
	*/
	pps = ppsInputRegister(func);
	*pps = ppsInputSelect(pin);
	}
    else
	{

	/* An output is mapped by storing the select value for the output function
	** being mapped into the mapping register associated with the pin.
	*/
	pps = ppsOutputRegister(pin);
	*pps = ppsOutputSelect(func);
   }
	return true;
	
}

#endif	// defined(__PIC32MX1XX__) || defined(__PIC32MX2XX__)

//************************************************************************
//*	Deal with the 'virtual' program button and SoftReset(). This allows
//* a sketch to cause the board to reboot, and either force entry into
//* the bootloader, or not.
//* Will return FALSE if ENTER_BOOTLOADER_ON_BOOT is not suppored.
//* On return of FALSE, no registers or latches will have been disturbed.
//* RUN_SKETCH_ON_BOOT is always supported.
//************************************************************************

unsigned int executeSoftReset(uint32_t options)
{
    const IMAGE_HEADER_INFO * pImageHeader = getImageHeaderInfoStructure();

    // We will use the LAT bit of the program button (if the board has one)
    // as the 'virutal' program button. The bootloader will read this bit
    // upon boot (only after a software reset) to see if it should go into
    // bootload mode or just run the sketch.

 #if  (USE_VIRTUAL_PROGRAM_BUTTON == 1)

    // Set/clear the LAT bit
    if (options == ENTER_BOOTLOADER_ON_BOOT)
    {
        // lets see if the bootloader has the capability to do this.
        // if we can not support this, make sure we have NOT fooled with any TRIS or Program buttons, do not disturb things
        // because we will not be resetting.
        if( ((pImageHeader->bootloaderCapabilities & blCapNotProvided) == blCapNotProvided)  ||  
            ((pImageHeader->bootloaderCapabilities & blCapVirtualProgramButton) != blCapVirtualProgramButton) )
        {   
            return(false);
        }
      
        VIRTUAL_PROGRAM_BUTTON_TRIS = 1;    // Set virtual program button to be an input (should be already)
        VIRTUAL_PROGRAM_BUTTON = 1;         // Set to stay in the bootloader
    }
    else
    {
        // Set virtual program button to be an input (should be already)
        VIRTUAL_PROGRAM_BUTTON_TRIS = 1;    // Set virtual program button to be an input (should be already)
        VIRTUAL_PROGRAM_BUTTON = 0;         // Set to jump to application
    }

#else       // No virtual program button
    // if we don't have virtual program buttons, we can't stay in the bootloader
    if (options == ENTER_BOOTLOADER_ON_BOOT)
    {
        return(false);
    }
#endif  // end virtual program button
 
    // At this point either we have a virtual program buttons and we can support ENTER_BOOTLOADER_ON_BOOT
    // or we just want to soft reset. A RUN_SKETCH_ON_BOOT soft reset requires no special funcitonality in the bootloader.
    // so we can always do a RUN_SKETCH_ON_BOOT.

    // Always clear the EXTR bit to make sure we don't read the real program 
    // button on boot
    RCONbits.EXTR = 0;
    
    // Now perform the software reset
    _softwareReset();

    return(true);       // never will be executed.
}

//************************************************************************
//*	CoreTimerHandler Services (KeithV)
//************************************************************************

uint32_t millisecondCoreTimerService(uint32_t curTime);

/*
    uint32_t CoreTimerService(uint32_t count)

    A CoreTimer Service is a callback routine that will get called when the core timer value equals the last value returned by your service; 
    also known as your requested compare time. When registering a CoreTimerService callback routine, the routine will be called on the next regularly 
    scheduled event currently waiting the CoreTimerHandler. From system start, there is a millisecond CoreTimerService running, so in most cases once you 
    register your callback serivce it should be called within 1 ms of attaching (registering). In some cases if interrupts are diaabled it may be as 
    long as 50 ms before your first call is made. Passed in to your Service is the current value of the CoreTimer count register, this is a rolling count 
    that rolls once every 2^32 / 40000000 ~ 107seconds. The return value from your service should be the next value of count that you want to be notified; 
    logically like setting the compare register; however, CoreTimerHandler is managing several services and will notify you when your value has been hit. 
    You will totally screw up CoreTimerHandler if you set the compare register directly. Here are the rules for writing a CoreTimerService callback routine.

    The rules:

    1.	You do NOT set “compare”!
    2.  Do not do anything that could cause CoreTimerHandler to be called recursively. For example, do not enable interrupts as the CT flag is still set
        and will immeditely cause the system to call CoreTimerHandler.
    3.	The value of the count register is passed to you, however this could be several ticks old. Usually this is not a problem. It is allowed 
        for you to read the count register directly, however you must return a compare value that is greater in time (so it can be a uint32 wrapped value) 
        than the count value passed to you. 
    4.	You will NOT be called before your compare value has been hit; however you may be called late should interrupts get disabled.
    5.	Unfortunately, because of things like the EEProm writes, you can be called late and you must “catch-up” however best you can and return 
        the next requested “compare” time on your next call.
    6.	There are limits to how far in the future you can set your next "compare" time. Right now this is limited to 90 seconds. If you need a longer delay you
        should be using something other than a CoreTimer Services to do this. You probably should really limit your next "compare" time to less than few seconds.
    7.	Your next requested “compare” time MUST be equal to or after (in time) the “current” time as passed in to you. You may add up to 90 seconds to the 
        current time, even if this causes uint32 wrap; but do not subtract from the current time and return that. There is a region known to CoreTimerHandler 
        that is before the current time, but that uint32 "value" is after the current time + 90 seconds.
     8.	CoreTimerHandler will keep looping until count is less than whatever the next compare is “after” CT was cleared to insure that CT is not missed. 
        It is possible that you could be called a second time before exiting the CoreTimerHandler ISR if you request a new compare time that is very close to 
        the current time.
    9.	After attaching, your service will be called on the next schedule call to CoreTimerHandler. Since there is always a ms service that gets triggered, 
        this will typically mean your first call to your Service will be within 1 ms of attaching, unless interrupts are disabled and you are delayed; 
        it could then be as much as 50ms.
    10. Understand, your callback is being called while executing inside the CoreTimerHandler ISR. Your code should be as fast as possible. If too much
        time is taken, the ISR may never exit and no sketch will ever run!
*/
//************************************************************************
#define read_count(dest) __asm__ __volatile__("mfc0 %0,$9" : "=r" (dest))
#define read_comp(dest) __asm__ __volatile__("mfc0 %0,$11" : "=r" (dest))
#define write_comp(src) __asm__ __volatile__("mtc0 %0,$11" : : "r" (src))

#define mCTSetIntFlag() (IFS0SET = _IFS0_CTIF_MASK)
#define mCTClearIntFlag() (IFS0CLR = _IFS0_CTIF_MASK)

typedef  uint32_t (*CoreTimerService)(uint32_t);

typedef struct
{
    volatile uint32_t            nextInt;
    CoreTimerService			serivce;
} CoreTimerInfo;

// make sure our ms timer is always in the list; so we initialize it into the list
// the rest of the slots are open for CoreTimer callback attachments.
CoreTimerInfo gCoreTimerInfo[] = {{0, millisecondCoreTimerService}, {0, NULL}, {0, NULL}};
#define MaxNbrOfCoreTimerServices   (sizeof(gCoreTimerInfo) / sizeof(CoreTimerInfo))

// This is a base value used to put our conditional logic into the linear range of an uint32, it also
// is used as the initial trigger time so that newly attached serices are called on the next call to CoreTimerHandler.
static volatile uint32_t gLastBaseCount = 0;

/***	unsigned int attachCoreTimerService(uint32_t (* service)(uint32_t))
**
**	Synopsis:   
**      Attaches a CoreTimer service to the CoreTimerHandler so that you can get direct
**      notifiaitons when the core timer hits specific values.
**
**	Parameters:
**      service - A function pointer to the callback routine to be called; with function signature of "uint32_t service(uint32_t count);" See rules above.
**
**	Return Values:
**      true if there is room in the sevice list to add your callback routine, false if all stots are taken
**
**	Errors:
**      returns false if all slots in the list are currently in use.
**
**  Notes:
**
**      This allows you to register a callback routine that will be called when the core timer clock == to the
**      compare value you requested as the return parameter from your callback serivce. 
**
**      The first call to your callback will usually be within 1 ms of attaching, but if interrupts are disabled may be 
**      significantly long, even as much as 50 ms or so.
**
*/
unsigned int attachCoreTimerService(uint32_t (* service)(uint32_t))
{
    int i;

    // make sure we are not already registered
    for(i = 0; i<MaxNbrOfCoreTimerServices; i++)
    {
        // found it, do nothing
        if(gCoreTimerInfo[i].serivce == service)
        {
            return(true);
        }
    }

    // we are not register, find an open slot
    // look for a open slot
    for(i = 0; i<MaxNbrOfCoreTimerServices; i++)
    {
        // found one, add the service
        if(gCoreTimerInfo[i].serivce == NULL)
        {
			 uint32_t lastBaseCount;

			// this has a very specific order...
			// first we initialize the nextInt time to something
			// that is in the begining part or our linear time range
			lastBaseCount = gLastBaseCount;
			gCoreTimerInfo[i].nextInt = lastBaseCount;

			// it is possible that the core timer handler was called here, and that
			// would put gLastBaseCount more like 100+ sec in the future, rather than than
			// at the bottom or our linear time. But since the serice is still NULL, our serivce was
			// not called and we missed it. But assign the service pointer and we will have to check to see
			// if we missed it.
			gCoreTimerInfo[i].serivce = service;

			// at this point our serice is ready to be called by the core timer handler and
			// there are 3 conditions at this point...
			//
			//	1. the isr was called right before we assigned the serice pointer and we missed it, and gCoreTimerInfo[i].nextInt is really far in the future; and we will miss more
			//	2. the isr was called right after we assigned the service pointer, the serices has already been processed and nextInt has our next interrupt time in it
			//		and we don't want to screw with that.
			//	3. the most likely case, the isr was not called yet.

			// we know if the serivce was run already:
			//  1. lastBaseCount != gLastBaseCount, as gLastBaseCount was just updated by the isr
			//	2. lastBaseCount != gCoreTimerInfo[i].nextInt, as the serivce was run and the nextInt was set to something less than 90s in the future  by the service
			//		which won't be the old base time as that is much closer to 107s in the future (outside of our allowable future time range for the serivce).

			// we know if nothing has happened
			//  1. lastBaseCount == gLastBaseCount, as gLastBaseCount was not updated by the isr
			//	2. lastBaseCount == gCoreTimerInfo[i].nextInt, as the serivce was not run and nothing changed nextInt

			// the case of concern is case 1 where we missed it; and we want to make sure we run it quickly
			// if we missed it we know:
			//  1. lastBaseCount != gLastBaseCount, as gLastBaseCount was just updated by the isr
			//	2. lastBaseCount == gCoreTimerInfo[i].nextInt, as the serivce was not run (missed) and nothing changed nextInt

			// we also know that the isr can be run at any time and we can keep missing it even while we are trying to fix it.
			// so go into a loop checking for the "we missed it" case until we don't miss it.
			while(lastBaseCount != gLastBaseCount  &&  lastBaseCount == gCoreTimerInfo[i].nextInt)
			{
				lastBaseCount = gLastBaseCount;
				gCoreTimerInfo[i].nextInt = lastBaseCount;
			}

			// at this point we know either the serice has been run, or nothing has happened at all
			// we know we didn't miss it because of the while loop.
			// now just trigger the isr for good measure. If we have run it already, nothing bad will
			// happen except the isr will run with nothing to do
			// otherwise it will trigger the serice immediately.
			mCTSetIntFlag();
            return(true);
        }
    }
    return(false);
}

/***	unsigned int detachCoreTimerService(uint32_t (* service)(uint32_t))
**
**	Synopsis:   
**      Removes your service from the CoreTimerHandler callback list.
**
**	Parameters:
**      service - A function pointer to the service to remove, this is the same function pointer that was used when adding the service
**
**	Return Values:
**      true if the service was found and removed. False if the service pointer was not found; then nothing was removed from the list.
**
**	Errors:
**      returns false if the function pointer was not found.
**
**  Notes:
*/
unsigned int detachCoreTimerService(uint32_t (* service)(uint32_t))
{
    int i;

    // look for this serivce in the list
    for(i = 0; i<MaxNbrOfCoreTimerServices; i++)
    {
        // found it
        if(gCoreTimerInfo[i].serivce == service)
        {
            // remove it from the slot
            gCoreTimerInfo[i].serivce = NULL;
            return(true);
        }
    }
    return(false);
}

/***	unsigned int callCoreTimerServiceNow(uint32_t (* service)(uint32_t))
**
**	Synopsis:
**      Will update your next isr time to the next regularly scheduled isr time
**
**	Parameters:
**      service - A function pointer to the service to update the next isr time, this is the same function pointer that was used when adding the service
**
**	Return Values:
**      true if the service was found and updated. False if the service pointer was not found; then nothing was updated.
**
**	Errors:
**      returns false if the function pointer was not found.
**
**  Notes:
*/
unsigned int callCoreTimerServiceNow(uint32_t (* service)(uint32_t))
{
    int i;

    // look for this serivce in the list
    for(i = 0; i<MaxNbrOfCoreTimerServices; i++)
    {
        // found it
        if(gCoreTimerInfo[i].serivce == service)
        {
			 uint32_t lastBaseCount;

			 // this is a very specific sequence of events as the isr can occur at anytime here
			 // to understand it look in the attach code for the sequence
			 do
			 {
				lastBaseCount = gLastBaseCount;
				gCoreTimerInfo[i].nextInt = lastBaseCount;
			 } while(lastBaseCount != gLastBaseCount  &&  lastBaseCount == gCoreTimerInfo[i].nextInt);

			mCTSetIntFlag();
            return(true);
        }
    }
    return(false);
}

/***	uint32_t millisecondCoreTimerService(uint32_t curTime)
**
**	Synopsis:   
**      This is the millisecond CoreTimer Service that keeps track of milliseconds for such functions as millis().
**
**	Parameters:
**      curTime - the current time as presented by CoreTimerHandler. This is basically the value of the count register when the ISR is called.
**
**	Return Values:
**      The value of count when I want this routine to be called again. It is logically like setting the compare register.
**
**	Errors:
**      Can not have any.
**
**  Notes:
**      This Service is critical to the operation of the system and should never be removed from the CoreTimerHandler list.
**
*/
uint32_t millisecondCoreTimerService(uint32_t curTime)
{
    static nextInt = 0;
    uint32_t relWait = 0;
    uint32_t relTime = curTime - nextInt;
    uint32_t millisLocal = gTimer0_millis;  // defeat volatility

    // catch-up up to current time; we may have fallen behind due to interrupts being diabled.
    while(relWait <= relTime)
    {
        millisLocal++;                      // add a ms to our time
        relWait += CORE_TICK_RATE;          // add a ms to our next ISR time
     }

    // set when we want to be called again
    nextInt += relWait;                     // calculate the absolute interrupt time we want.

    // we want to sync gCore_timer_last_val with the last millisecond "count" value
    // curTime may not be exactly on a millisecond boundary, but we know where that is
    // we know nextInt is our next millisecond boundary, so less 1 CORE_TICK_RATE will be our last one
    // gCore_timer_last_val = curTime;         // This is the original bogus code
    gCore_timer_last_val =  nextInt - CORE_TICK_RATE;

    // update the global millisecond counter.
    gTimer0_millis = millisLocal;           // Total number of ms

    return(nextInt);
}

/***	void __ISR(_CORE_TIMER_VECTOR, _CT_IPL_ISR) CoreTimerHandler(void)
**
**	Synopsis:   
**      The CoreTimerHandler ISR. This manages timer events off of the core timer counter using the 
**      count and compare system register and the CT interrupt.
**
**	Parameters:
**      none, but has the effect of know that count >= compare.
**
**	Return Values:
**      none, but compare is set for the next interrupt to take place
**
**	Errors:
**      none
**
**  Notes:
**      This ISR will walk the list of all attached CoreTimer Services and will call all serivces where count has exceeded 
**      each service's logical compare values. And then the next and soonest logical compare value is searched for and set as
**      the real compare value to be interrupted to notify the Serivces when count hits that value.
**
*/
void __attribute__((interrupt(),nomips16)) CoreTimerHandler(void)
{
    uint32_t curTime;
    uint32_t compare;
    uint32_t nextBase;

    uint32_t relNextInt;
    uint32_t relCurTime;
    uint32_t relInt;

    int i;

    // we know that count >= compare, otherwise we would not have been interrupted
    // we also know that count and compare >= gLastBaseCount as this was our last count value.

    // get our current time; this will establish our next base
    read_count(curTime); 
    relCurTime = curTime - gLastBaseCount;
    nextBase = curTime;

    do
    {
        // make sure we find the lowest int to set
        relNextInt = 0xFFFFFFFF;

        // check to see who all we need to call
        for(i=0; i<MaxNbrOfCoreTimerServices; i++)
        {
            // if the serivce exists
            if(gCoreTimerInfo[i].serivce != NULL)
            {
                // if their time has come up
                relInt = gCoreTimerInfo[i].nextInt - gLastBaseCount;
                if(relInt <= relCurTime)
                {
                    // call their routine to get their next interrupt time
                    gCoreTimerInfo[i].nextInt = gCoreTimerInfo[i].serivce(curTime);

                    // recalculate the relative time of thier next int
                    // so we can see if this is the next int we need to set
                    relInt = gCoreTimerInfo[i].nextInt - gLastBaseCount;
                }

                // see if this is the next interrupt we want to set
                // we are looking for the closest/lowest int to set.
                if(relInt < relNextInt)
                {
                    relNextInt = relInt;
                }
            }
        }
      
        // at this point we have checked all of the serivces and found the next interrupt time (compare value) to set. 
        // The millisecondCoreTimerService is alway active and will always have a compare time no more than 1 ms away. However
        // other service may cause the compare value to be set for an earlier time; but we always know there will be a compare time
        // to set, so we know that relNextInt has a value other than 0xFFFFFFFF in it.

        // Go ahead and set the compare register to the next interrupt we want.
        // we need to apply our base to convert from relative values to an absolute time.
        compare = relNextInt + gLastBaseCount;
        write_comp(compare); 

        // clear the CT flag
        mCTClearIntFlag();

        // read the count after the CT flag has been set so we can make sure count has not passed compare
        // during our processing of this int
        read_count(curTime); 

        // get the relative time so we can operate in the linear portion of our uint32.
        relCurTime = curTime - gLastBaseCount;

        // if the current time has passed our interrupt time, then we basically hit the interrupt again
        // so we probabaly missed the CT flag being set and we need to reprocess this interrupt and find the next one to set.
    } while(relNextInt <= relCurTime);
 
    // otherwise the next interrupt time (compare time) is after the current time and CT will catch it when count == compare.
    // we can safely exit the ISR.

    // but first we must set our new base so the next time we come into this routine we
    // have a valid lower base to shift our times to for comparisons.
    gLastBaseCount = nextBase;
}

