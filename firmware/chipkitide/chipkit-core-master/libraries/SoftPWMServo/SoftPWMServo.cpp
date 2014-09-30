/*
 SoftPWMServo.cpp - Interrupt driven PSM and Servo library for MPIDE
 Copyright (c) 2011 Brian Schmalz of SchmalzHaus.  All right reserved.
 
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
 
/* 
 Plase see the README.TXT file for more detail on how the internals of the
 library work.
*/

/*
  Change List:
  09/05/2011 <GeneApperson>:
    * Fixed a compile error introduced when the include of plib.h was
      removed from HardwareSerial.h (included by WProgram.h). Added
      include of plib.h here.
  01/12/2011 <BrianSchmalz>:
    * Re-wrote ISR and helper functions to utilize the new core timer
      attach() and detach() functions that Keith put into wiring.c
  02/07/2013 <GeneApperson>:
	* Removed dependency on Microchip plib library.
*/

/* Note: plib.h must be included before WProgram.h. There is a fundamental
** incompatibility between GenericTypedefs.h (included by plib.h) and Print.h
** (included by WProgram.h) on the declaration of the symbol BYTE.
*/

#define OPT_BOARD_INTERNAL
#include <WProgram.h>
#include <wiring.h>
#include <inttypes.h>
#include "SoftPWMServo.h"
#include "wiring_private.h"

/************ local defines **************************************************/
#define EXTRA_ISR_ENTRY_CYCLES              (48)
#define EXTRA_ISR_EXIT_CYCLES               (50)

/************ local prototypes ***********************************************/
uint32_t HandlePWMServo(uint32_t count);     // Can't be static because we pass it in to attach()
static void CopyBuffers(void);
void Add(uint32_t Channel);
void Remove(uint32_t Channel);

/************ external prototypes ********************************************/

/************ local variables ************************************************/

// These are read by the ISR, and written
// by the mainline code
typedef struct ChanStruct ChanType;
// This structure is the main method for the library to track information for
//  each pin.
struct ChanStruct
{
    int32_t             NextEdgeTime;           // Time in 40MHz units before next edge (i.e. this pin's falling edge)
    volatile uint32_t   *SetPort;               // Pointer to port register (SET) for this pin
    volatile uint32_t   *ClearPort;             // Pointer to port register (CLEAR) for this pin
    uint32_t            Port;                   // Port number for this pin
    uint32_t            Bit;                    // Bit of Port that this pin is on
    uint32_t            PWMValue;               // Length of high time for this pin, in 40MHz units
    uint32_t            IsServo;                // True if this channel is being used as a servo rather than PWM
    ChanType *          NextChanP;              // Pointer to next channel in the list (next edge)
};

static ChanType Chan[2][SOFTPWMSERVO_MAX_PINS]; // Main structure for SoftPWM. Second index is Arduino Pin number, first is buffer (inactive/active)
static ChanType * FirstChanP[2] = {NULL, NULL}; // Stores pointer to first channel
static bool InactiveBufferReady;                // Set true when inactive buffer has new data for ISR and should become active
static uint32_t FrameTime = SOFTPWMSERVO_DEFAULT_FRAME_TIME; // In 40MHz ticks, time of PWM 'cycle' or frame - when do all edges go high
static uint32_t ServoFrames = SOFTPWMSERVO_DEFAULT_SERVO_FRAMES; // Number of FrameTimes between rising edges of servo pulses

// These are only touched inside the ISR
static bool RisingEdge;                         // True if we are about to set all active channels high
static uint32_t CurrentTime;                    // Number of 40MHz ticks into the frame we are right now
static uint32_t ActiveBuffer;                   // Current buffer index (0 or 1), used to index Chan and FirstChanP, for double buffering
static ChanType * ISRFirstChanP = NULL;         // Stores ISR copy of pointer to first channel
static uint32_t ServoFrameCounter;              // When zero, set all servo channels high, then reset to ServoFrames and count frames down

// These are not touched by the ISR in any way
static uint32_t InactiveBuffer;                 // Non used buffer (0 or 1), used to index SoftPWMChan and FirstChanP, for double buffering
static bool Initalized;                         // Set true once we've installed our ISR handler

/****************** Public Functions ******************************/

// Inialize all static variables to default state
// Insert SoftPWM ISR into Core Timer ISR
int32_t SoftPWMServoInit(void)
{
    uint32_t i, j;

    // Inialize all of our static arrays
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < SOFTPWMSERVO_MAX_PINS; i++)
        {
            Chan[j][i].NextEdgeTime = 0;
            Chan[j][i].SetPort = NULL;
            Chan[j][i].ClearPort = NULL;
            Chan[j][i].Port = 0;
            Chan[j][i].Bit = 0;
            Chan[j][i].PWMValue = 0;
            Chan[j][i].IsServo = false;
            Chan[j][i].NextChanP = NULL;
        }
        FirstChanP[j] = NULL;
    }

    RisingEdge = true;
    CurrentTime = 0;
    InactiveBuffer = 1;
    ActiveBuffer = 0;
    ISRFirstChanP = NULL;
    InactiveBufferReady = false;
    FrameTime = SOFTPWMSERVO_DEFAULT_FRAME_TIME;        // Start out with default 2ms frame time
    ServoFrames = SOFTPWMSERVO_DEFAULT_SERVO_FRAMES;    // Start out with default of 10 frames (20ms)
    
    // Insert our ISR handler, if it's not already there
    if (attachCoreTimerService(HandlePWMServo))
    {
        Initalized = true;
        return SOFTPWMSERVO_OK;
    }
    else
    {
        Initalized = false;
        return SOFTPWMSERVO_ERROR;
    }
}

// Remove SoftPWM ISR from main Core Timer ISR
int32_t SoftPWMServoUnload(void)
{
    // Remove our ISR handler, and replace with what was there
    detachCoreTimerService(HandlePWMServo);
    Initalized = false;
    
    return SOFTPWMSERVO_OK;
}

// Enable SoftPWM functionaliy on a particular pin number
int32_t SoftPWMServoPinEnable(uint32_t Pin, bool PinType)
{
    // If user has not already enabled this pin for SoftPWM, then initalize it
    if (Chan[InactiveBuffer][Pin].SetPort == NULL)
    {
        // Set up this pin's 
        pinMode(Pin, OUTPUT);                                      // set servo pin to output
        digitalWrite(Pin, LOW);                                    // Always start out low
        Chan[InactiveBuffer][Pin].NextEdgeTime = 0;                // Computed on the fly in the ISR
        Chan[InactiveBuffer][Pin].Port = digitalPinToPort(Pin);    // Set up our bit and port so we don't have to
        Chan[InactiveBuffer][Pin].Bit = digitalPinToBitMask(Pin);  //  do it inside the ISR.
        Chan[InactiveBuffer][Pin].SetPort = portOutputRegister(Chan[InactiveBuffer][Pin].Port) + 2; // +2 is PORTxSET
        Chan[InactiveBuffer][Pin].ClearPort = portOutputRegister(Chan[InactiveBuffer][Pin].Port) + 1; // +1 is PORTxCLR
        Chan[InactiveBuffer][Pin].PWMValue = 0;                    // Start out with zero PWM time (always off)
        Chan[InactiveBuffer][Pin].IsServo = PinType;               // Set the type for this pin (servo vs PWM)
        Chan[InactiveBuffer][Pin].NextChanP = NULL;                // Add() will set this
        // Now also do the same thing in the other buffer
        Chan[ActiveBuffer][Pin].NextEdgeTime = 0;                  
        Chan[ActiveBuffer][Pin].Port = digitalPinToPort(Pin);    
        Chan[ActiveBuffer][Pin].Bit = digitalPinToBitMask(Pin);  
        Chan[ActiveBuffer][Pin].SetPort = portOutputRegister(Chan[InactiveBuffer][Pin].Port) + 2;
        Chan[ActiveBuffer][Pin].ClearPort = portOutputRegister(Chan[InactiveBuffer][Pin].Port) + 1;
        Chan[ActiveBuffer][Pin].PWMValue = 0;                    
        Chan[InactiveBuffer][Pin].IsServo = PinType;
        Chan[ActiveBuffer][Pin].NextChanP = NULL;                
    }
    
    return SOFTPWMSERVO_OK;
}


// Disable the SoftPWM functionality on a particular pin number
int32_t SoftPWMServoPinDisable(uint32_t Pin)
{
    int32_t intr;
    intr = disableInterrupts();
    CopyBuffers();
    
    // Pull this one out of the linked list of active channels
    Remove(Pin);

    // Mark it as unused
    Chan[InactiveBuffer][Pin].SetPort = NULL;
    Chan[InactiveBuffer][Pin].ClearPort = NULL;
    restoreInterrupts(intr);    

    return SOFTPWMSERVO_OK;
}

// Set a new PWM value for a given pin
// Primarily this consists of updating the PWMValue and then 
// re-sorting the list of active pins by removing and then adding
// the pin to the linked list.
int32_t SoftPWMServoRawWrite(uint32_t Pin, uint32_t Value, bool PinType)
{
    int i;
    int32_t intr;

    // Insert our ISR handler, if it's not already there
    if (!Initalized)
    {
        SoftPWMServoInit();
    }

    // Limit check the inputs
    if (Value > FrameTime)
    {
        Value = FrameTime;
    }
    if (Pin > SOFTPWMSERVO_MAX_PINS)
    {
        return SOFTPWMSERVO_ERROR;
    }
    
    // And if this pin already has this PWM Value, then don't do anything.
    if (Value == Chan[ActiveBuffer][Pin].PWMValue)
    {
        return SOFTPWMSERVO_OK;
    }

    // The easy way to prevent the ISR from doing a buffer swap while
    // we're in the middle of this is to disable interrupts during 
    // the time that we're mucking with the list.
    // TODO: Switch to using 3 buffers - one 'active' that the ISR
    // is currently using, one 'primed' that the mainline code doesn't
    // touch but has updates and is ready to be swapped before the
    // next rising edge, and then 'inactive' which is the one we modify
    // with here. Maybe we wouldn't need to disable interrupts then.
    intr = disableInterrupts();

    // If needed, copy the values from the previously active buffer
    // into the inactive buffer before we begin work on it.
    CopyBuffers();
 
    // Always make sure this pin's enabled
    SoftPWMServoPinEnable(Pin, PinType);

    // Update the PWM value for this pin
    Chan[InactiveBuffer][Pin].PWMValue = Value;
    Chan[InactiveBuffer][Pin].IsServo = PinType;
    
    // Remove it from the list
    Remove(Pin);
    
    // And add it back in the list, in the right place (in time)
    Add(Pin);    

    restoreInterrupts(intr);  

    return SOFTPWMSERVO_OK;
}

// return the current PWM value
// Return SOFTPWM_ERROR if pin not enabled
int32_t SoftPWMServoRawRead(uint32_t Pin) 
{
    if (Chan[InactiveBuffer][Pin].SetPort == NULL)
    {
        return SOFTPWMSERVO_ERROR;
    }
    else
    {
        return Chan[ActiveBuffer][Pin].PWMValue;
    }
}

// Value is a float, in us. and represents the on-time for this servo pin
// Pin is the pin number being changed
int32_t SoftPWMServoServoWrite(uint32_t Pin, float Value)
{
    SoftPWMServoRawWrite(Pin, usToTicks(Value), SOFTPWMSERVO_SERVO);
    
    return SOFTPWMSERVO_OK;
}

// Convert from 8-bit percentage to absolute 40MHz tick units
int32_t SoftPWMServoPWMWrite(uint32_t Pin, uint8_t Value)
{
    SoftPWMServoRawWrite(Pin, (((uint32_t)Value * FrameTime)/255), SOFTPWMSERVO_PWM);

    return SOFTPWMSERVO_OK;
}

// Read the current time, for this Pin, in us (as a float)
float SoftPWMServoServoRead(uint32_t Pin)
{
    return (ticksToUs(SoftPWMServoRawRead(Pin)));
}

// Return an 8-bit percentage based on PWMValue
int8_t SoftPWMServoPWMRead(uint32_t Pin)
{
    return ((SoftPWMServoRawRead(Pin) * 255)/FrameTime);
}

// Set the PWM frame time, in units of 40MHz CoreTimer ticks, to NewTime
// Takes effect at the beginning of the next frame
int32_t SoftPWMServoSetFrameTime(uint32_t NewTime)
{
    FrameTime = NewTime;

    return SOFTPWMSERVO_OK;
}

// Set the number of PWM frames between servo pulses.
// Takes effect the next time servos are pulsed.
int32_t SoftPWMServoSetServoFrames(uint32_t NewFrameCount)
{
    ServoFrames = NewFrameCount;

    return SOFTPWMSERVO_OK;
}

/********************  private functions *************************************/
// Primary worker function for SoftPWM
// Is called from within CoreTimer interrupt from wiring.c
// Schedules next CoreTimer interrupt based upon what needs to happen next 
// - another falling edge, or all rising edges, or 1ms CoreTimer interrupt.
uint32_t HandlePWMServo(uint32_t CurrentCount)
{
    uint32_t NextTime = 0;                  // The number of CoreTimer counts into the future when our next edge should occur
    uint32_t OldPeriod;                     // The CoreTimer value that caused the ISR to fire
    static ChanType * CurChanP = NULL;      // Pointer to the current channel we're operating on
    bool DoItAgain = false;                 // True if we don't have time to leave the ISR and come back in
    uint32_t NextTimeAcc = CurrentCount;    // Records the sum of NextTime values while we stay in the do-while loop

    
    // This do-while loop keeps us inside this function as long as there are
    // edges to process. Only once we have enough time to leave and get back
    // in for the next edge do we break out of the while loop.
    do 
    {
        // If it's time to do the rising edge of all enabled channels-
        if (RisingEdge)
        {
            // Start at the first channel
            CurChanP = ISRFirstChanP;
            
            // Check to see if we have zero channels actually loaded with data
            if (CurChanP != NULL)
            {
                // For each channel that's active, set its pin high
                while (CurChanP != NULL)
                {
                    // But only if it is not at %0
                    if (CurChanP->PWMValue != 0)
                    {
                        // Make an exception for servos - only set them
                        // high when ServoFrameCounter is zero.
                        if (
                            (CurChanP->IsServo && !ServoFrameCounter)
                            ||
                            (!CurChanP->IsServo)
                        )
                        {
                            *(CurChanP->SetPort) |= CurChanP->Bit;
                        }
                    }
                    // Advance to next channel to check it
                    CurChanP = CurChanP->NextChanP;
                }
                // Now start back at the beginning again, for the setting pins low part
                CurChanP = ISRFirstChanP;
                // And load up the time for the next (first) edge (falling edge of first channel)
                NextTime = CurChanP->PWMValue;
                CurChanP->NextEdgeTime = NextTime;
                // And mark this time as the beginning of the PWM cycle
                CurrentTime = 0;
                // We don't want to do this again until next time
                RisingEdge = false;
            }
            else
            {
                // We have no channels actually turned on (enabled or otherwise)
                // So just load the NextTime with the duraction of the whole PWM cycle and do this
                // all over again.
                NextTime = FrameTime;
                // Don't set SoftPWMRisingEdge to FALSE - leave it TRUE so we just keep doing this

                // If it's time to swap buffers, then do that here
                if (InactiveBufferReady)
                {
                    if (ActiveBuffer)
                    {
                        ActiveBuffer = 0;
                        InactiveBuffer = 1;
                    }
                    else
                    {
                        ActiveBuffer = 1;
                        InactiveBuffer = 0;
                    }
                    // And have ISR use FirstChanP from new active buffer
                    ISRFirstChanP = FirstChanP[ActiveBuffer];
                    // Tell mainline code we've swapped
                    InactiveBufferReady = false;
                }
            }

            // Count this frame, for the serov pins
            ServoFrameCounter++;
            // If we're reached our ServoFrames, limit, then set to zero to mark that
            // the next frame will have all servos do their rising edges.
            if (ServoFrameCounter == ServoFrames)
            {
                ServoFrameCounter = 0;
            }
        }
        else
        {
            // Now we have a falling edge. So we need to set some channel's pin low here.

            // Always set the next bit low, if the channel is not at 100%
            // But if it's a servo, always set it low.
            if (CurChanP->PWMValue < FrameTime || CurChanP->IsServo)
            {
                *(CurChanP->ClearPort) |= CurChanP->Bit;
            }

            // Record how much time has passed (where are we in the frame)
            CurrentTime += CurChanP->NextEdgeTime;
            
            // Check for more channels that have this same time - but only if we
            // haven't hit the end of the list yet. (Channels with same edges
            // will have PWMValues that are the same.)
            while (
                (CurChanP->NextChanP != NULL)
                &&
                (CurChanP->PWMValue == CurChanP->NextChanP->PWMValue)
            ) 
            {
                // Now start working on the next channel in the linked list
                CurChanP = CurChanP->NextChanP;

                // Only touch the output if it's not at 100% or if it is a servo
                // pin (they always go low).
                if (CurChanP->PWMValue < FrameTime || CurChanP->IsServo)
                {
                    // Set this bit low
                    *(CurChanP->ClearPort) |= CurChanP->Bit;
                }
            }
            
            // Have we run out of active channels?
            if (CurChanP->NextChanP == NULL)
            {
                // Yup, so set the next interrupt should happen at the beginning of the next frame
                NextTime = FrameTime - CurrentTime;
                
                // And make all of our channels go high then
                RisingEdge = true;
                
                // If it's time to swap buffers, then do that here
                if (InactiveBufferReady)
                {
                    if (ActiveBuffer)
                    {
                        ActiveBuffer = 0;
                        InactiveBuffer = 1;
                    }
                    else
                    {
                        ActiveBuffer = 1;
                        InactiveBuffer = 0;
                    }
                    // And have ISR use FirstChanP from new active buffer
                    ISRFirstChanP = FirstChanP[ActiveBuffer];
                    // Tell mainline code we've swapped
                    InactiveBufferReady = false;
                }
            }
            else
            {
                // Now start working on the next channel in the linked list
                CurChanP = CurChanP->NextChanP;

                // Time to compute the NextEdgeTime for the next channel
                // But only if we're not at the end.
                if (CurChanP != NULL)
                {
                    // Compute the next channel's NextEdgeTime based upon our current time and it's PWMValue
                    CurChanP->NextEdgeTime = CurChanP->PWMValue - CurrentTime;
                }

                // Just load up the time of the next falling edge
                NextTime = CurChanP->NextEdgeTime;
            }
        }       

        // Each time through the main do-while loop, keep adding in the times between
        // edges (that would have caused CoreTimer fires if we had left the ISR). Then,
        // when there is finally time to leave the ISR and come back in to get to the
        // next edge, schedule the next edge to be the sum of all of those NextTimes.
        NextTimeAcc += NextTime;

        // Determine if we have enough time to leave the ISR, return to the mainline 
        // code, and have the CoreTimer ISR fire again to get to our next edge time.
        // If not, then just stay in the do-while loop (by setting DoItAgain) and 
        // don't leave, and just pretend that we let the CoreTimer fire.
        // There's a fudge factor added in to where we think we are in time so that
        // we can copmensate for the number of CoreTimer counts it takes to leave
        // the ISR.
        //
        // Change from v1.0 to v1.1: we now do this calculation by first subtracting
        // off the OldPeriod from our current CoreTimer value. This subtraction will
        // eleminate problems where adding NextTimeAcc rolls OldPeriod over, or where
        // the CoreTimer has rolled over from OldPeriod.
        if (NextTimeAcc  < (readCoreTimer() + EXTRA_ISR_EXIT_CYCLES))
        {
            DoItAgain = true;

            // We need to wait until the time when we _would_ have actually let the
            // CoreTimer fire has come and gone. We also put a fuge factor in here to
            // simulate the number of cycles necessary to get into the ISR and to the 
            // point where the top of the do-while loop starts executing.
            while(readCoreTimer() < (NextTimeAcc + EXTRA_ISR_ENTRY_CYCLES))
            {
            }
        }
        else
        {
            DoItAgain = false;
        }
    }
    // We will continue to stay in this loop (which encompases almost the entire function)
    // until our next edge (PWM or 1ms) is far enough in the future that we can spend the
    // cycles leaving the ISR and coming back in again.
    while (DoItAgain);
    

    // Return 0 so we don't run the 1ms 'stuff' in the main Core Timer ISR, or 1
    // so that we do (this is set only once, to a 1, if we have the 1ms tick
    // fire off. Since we don't clear RetVal during this ISR, any time we enter
    // the ISR and have the 1ms tick happen, we will be telling the wiring.c code
    // to run the 1ms code.)
    return(NextTimeAcc);
}

// Remove a channel from the linked list of channels
void Remove(uint32_t Channel)
{
    ChanType * ChanP = FirstChanP[InactiveBuffer];
    ChanType * LastChanP = FirstChanP[InactiveBuffer];
    
    // Walk through the linked list, looking for our target
    while (ChanP != NULL)
    {
        // Is this elemnt the one we're looking for?
        if (ChanP == &Chan[InactiveBuffer][Channel])
        {
            // Yup. So let's remove it from the linked list then
            // Are we on the first channel?
            if (ChanP == FirstChanP[InactiveBuffer])
            {
                // Yes, so change the first channel pointer instead
                FirstChanP[InactiveBuffer] = ChanP->NextChanP;
            }
            else
            {
                // Nope, we're in the list. So change this element's previous pointer
                LastChanP->NextChanP = ChanP->NextChanP;
            }
            // And always zero this elment's next pointer out
            ChanP->NextChanP = NULL;
            
            // And we're done so bail
            break;
        }
        // Advance our pointers by one element in the list
        LastChanP = ChanP;
        ChanP = ChanP->NextChanP;
    }
}

// Add a channel into the linked list, based upon PWMValue (i.e. in order)
void Add(uint32_t Channel)
{
    ChanType * ChanP = FirstChanP[InactiveBuffer];
    ChanType * LastChanP = FirstChanP[InactiveBuffer];

    // As a speical case, if there are no elements in the list, then just add this one to the front
    if (ChanP == NULL)
    {
        // Yes, so put us first in line
        FirstChanP[InactiveBuffer] = &Chan[InactiveBuffer][Channel];
        Chan[InactiveBuffer][Channel].NextChanP = NULL;
        return;
    }
    
    // Walk through the linked list, looking for a PWMValue that's bigger than ours
    while (ChanP != NULL)
    {
        // Is this element's PWMValue greater than ours?
        if (ChanP->PWMValue > Chan[InactiveBuffer][Channel].PWMValue) 
        {
            // Yup. So let's add ourselves right here in the list
            // Are we on the first channel?
            if (ChanP == FirstChanP[InactiveBuffer])
            {
                // Yes, so put us first in line
                Chan[InactiveBuffer][Channel].NextChanP = ChanP;
                FirstChanP[InactiveBuffer] = &Chan[InactiveBuffer][Channel];
            }
            else
            {
                // Nope, we're in the list. So change this element's previous pointer
                Chan[InactiveBuffer][Channel].NextChanP = ChanP;
                LastChanP->NextChanP = &Chan[InactiveBuffer][Channel];
            }
            
            // And we're done so bail
            return;
        }
        // Advance our pointers by one element in the list
        LastChanP = ChanP;
        ChanP = ChanP->NextChanP;
    }
    // Did we blow by the end of the list without finding any greater than ours?
    LastChanP->NextChanP = &Chan[InactiveBuffer][Channel];
    Chan[InactiveBuffer][Channel].NextChanP = NULL;
}

// If the ISR has just swapped buffers, then we need to copy the ActiveBuffer's
// contents into the inactive buffer's contents so that we start modifying 
// data that matches what is currently 'live'. InactiveBufferReady will be false if
// this is the first call to Write after an ISR swap.
static void CopyBuffers(void)
{
    uint32_t i;
    
    if (!InactiveBufferReady)
    {
        // TODO: Replace with memcpy?
        for (i = 0; i < SOFTPWMSERVO_MAX_PINS; i++)
        {
            Chan[InactiveBuffer][i] = Chan[ActiveBuffer][i];
            // Now comes the hard part. Because we have pointers in this array, we can't 
            // just use the copy we have (to inactive) as is. We need to go fix it up so 
            // that all of the pointers are internally consistant and point only to 
            // channels in InactiveBuffer.
            // TODO: There MUST be a better way to do this without resorting to indexes 
            //  rather than pointers.
            if (Chan[ActiveBuffer][i].NextChanP != NULL)
            {
                Chan[InactiveBuffer][i].NextChanP = 
                    (ChanType *)(
                        (uint32_t)&Chan[InactiveBuffer] 
                        +
                        ((uint32_t)Chan[ActiveBuffer][i].NextChanP - (uint32_t)&Chan[ActiveBuffer])
                    );
            }
        }
        if (FirstChanP[ActiveBuffer] != NULL)
        {
            FirstChanP[InactiveBuffer] = 
                (ChanType *)(
                    (uint32_t)&Chan[InactiveBuffer] 
                    +
                    ((uint32_t)FirstChanP[ActiveBuffer] - (uint32_t)&Chan[ActiveBuffer])
                );
        }
        else
        {
            FirstChanP[InactiveBuffer] = NULL;
        }
    }
    InactiveBufferReady = true;
}
