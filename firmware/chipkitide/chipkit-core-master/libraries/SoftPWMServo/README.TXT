README.TXT - for SoftPWMServo library
Released August 2011 by Brian Schmalz http://www.schmalzhaus.com
Written for all PIC32 based boards

This document describes the overall intent of the SoftPWMServo library, as well
as the technical details that you may want to know in order to understand some 
of the aspects of using the library in your application.

See SoftPWMServo.h for information on version differences of his library.

Overview:

The SoftPWMServo library was written primarily to allow existing Arduino sketches
to be more easily ported to the ChipKIT boards. Since the PIC32 does not have as 
many available PWM outputs or RC Servo outputs, this library implements in software
what would normally be done almost entirely in hardware. It allows for every single
pin on a PIC32 based boards to be used (simultaneously) for PWM output or RC Servo
output. Since it is a software based library, it does come with some negatives 
compared with a purely hardware implementation (like the existing analogWrite()).
This document will describe how the library works and how the output will differ
from real hardware based PWM or Servo output.

Usage:

The quick and dirty of this library is that any call to analogWrite() can be replaced
with a call to SoftPWMServoPWMWrite(), and you will get the advantage of being able 
to use any pin for the output.

There are three Write() calls in this library: SoftPWMServoPWMWrite(), 
SoftPWMServoServoWrite() and SoftPWMServoRawWrite(). The first to implicitly set the
pin to be either a PWM or Servo output, while the third one gives the user complete
control over the pin by allowing the pulse width to be specified in 40MHz CoreTimer
ticks.

Please see the example files for some quick example usages.

Definitions:

First, it is useful to define some terminology used in the library code and comments.

    Frame Time : This is the number of 40MHz CoreTimer ticks between rising edges
        of the PWM pins. It is the unit of time that all other parts of the library
        are based on. This unit is called the frame.
    
    1ms Tick : Because the library shares the CoreTimer with the normal code in 
        the core library that needs to execute code every 1ms, the library must
        not only manage scheduling the CoreTimer ISR to fire when it needs to
        set a pin high or low, it must also have the ISR fire exactly every 1ms.
        This is the 1ms Tick. The 1ms Tick happens asynchronously with all of the
        rising and falling edges in the library.
        
    Servo Frames : RC Servo pulses are generated exactly like normal PWM pulses,
        except that there are a certain number of frames that are skipped (i.e.
        the pin is not set high for those frames) so that the RC servo does not
        receive pulses too quickly. 
        
    Chanel or Pin Linked List : Internal to the library, there is a simple 
        linked list that contains information about each pin that is currently
        supposed to generate a pulse. This linked list is sorted so that the
        library just has to look at the next element in the list to know what
        pin is supposed to have a falling edge next.

Architecture:

The fundamental concept that the library operates on is that at the beginning of
each frame, all pins that are 'active' (or generating pulses) are set high. Then,
the CoreTimer is scheduled to fire at each of the pin's falling edges. When that
time comes, each pin's output is set low at the proper time. Then, at the beginning
of the next frame, all active pins are set high again.

The SoftPWMServo library hooks into the CoreTimer interrupt. On all PIC32 based
boards, there is a 1ms interrupt running from the CoreTimer that allows for
millisecond timing in the system. The CoreTimer runs at 40Mhz, and is a free
running counter in the PIC32 core. You can schedule when the next CoreTimer 
interrupt will happen by using the UpdateCoreTimer() call, which adds a value
to the last value in the CoreTimer compare register. When the CoreTimer and
the compare register match, the interrupt occurs.

The HandlePWMServo() routine does all of the hard work. It is called every
time the CoreTimer ISR fires, from within wiring.c. It handles setting 
pins high or low, (if that's what needs to be done) and calculating when the
next edge (rising edge, falling edge, or 1ms tick) needs to occur, and then
scheduling the CoreTimer to fire at that point in time. It also handles
noticing when there is new timing data (because the user changed a pin's PWM
time, or added or removed a pin from the linked list) and switching between
the two buffers of data. (This prevents any glitches in the PWM output.) 

When the user calls one of the Write() calls, the library will make sure that the
CoreTimer interrupt is properly hooked with a call to the HandlePWMServo()
function. It will then make sure that the requested pin is enabled, and if 
it has not been enabled before, it will set the pin to be a digital output
and set it low. It will then remove the pin from the linked listed (if it was
there already) and then insert it back into the linked list in the proper place
(this is how the linked list is always sorted according to falling edge time).

There are several other important functions contained in the HandlePWMServo()
call. One is the scheduling of the 1ms Tick. If the HandlePWMServo() call 
returns a non-zero value, then the Core Timer ISR function in wiring.c will
execute the 1ms Tick code. If it returns a zero value, then this code will not
be run. This is how the HandlePWMServo() function schedules both PWM edges and
1ms Tick calls. 

Also, the HandlePWMServo() function attempts to minimize the amount of time 
between edges that need to occur close in time. It takes around 40 CPU cycles
to leave the function and return to mainline code, and about 40 CPU cycles from
the time the CoreTimer fires to when HandlePWMServo can begin processing edges.
So if the total time between when the function is about to exit, and when the 
next edge is supposed to occur, is less than this amount of time, it will not
exit, but rather loops back around and processes the next edge. This continues
until there is enough time before the next edge to actually leave and come
back in.

Timing:

The timing analysis of this library can be a bit complex, because it is not a
fixed thing. Rather, the exact time that the pins are set high or low depends
on a large number of factors, including when the 1ms Tick happens to fall, how
many pins are currently active, when the previous edge occurred, and how many
pins have edges that fall within about 100 CPU cycles of one another before
the edge in question.

However, some generalities can be stated:

    * Each falling edge (if just one edge happens at a time) requires about 250ns 
      of CPU time. Thus 41 edges all falling at once take up about 10.3us.

    * The above time does not include the time needed to get into the ISR and out
      again. This adds about 1.8uS to the total, no matter how many pins fire
      at once.      
      
So for a single pin of PWM, about 4us of CPU time (out of a 2ms Frame Time) is needed.
This works out to about 0.2% CPU overhead.

If all 85 pins are active and are generating PWM pulses, about 24us will be needed
to generate the rising edges, and then (if all of the falling edges are more than
2us apart) 85 * 2us = 170us will be required (in total) for all of the falling 
edges. This means that, at full tilt, about 10% of the CPU will be used for this
library. Not bad!

Jitter is a very large concern with a software PWM library like this. Any time
interrupts are disabled in the system, jitter will be added to the pulse edges.
Also, the asynchronous 1ms Tick firing will cause some jitter. Jitter also is 
generated as users change PWM durations as the library is running - as the pins' 
edges move around in time, they may delay other pins' edges slightly because the
CPU can't set or clear two pins zero seconds apart.

That being said, in a system where there is no other code that disables interrupts,
jitter on each edge should be less than about 50ns. The more pins that are used,
the higher this number can go. Also, since interrupts are disabled during the 
Write() calls, calling these Write() functions very rapidly will increase the jitter
value.

Double Buffering:

To provide glitchless PWM and RC servo operation, there are two buffers for pulse
width data. One (active buffer) is the buffer that the ISR actually operates on, 
and uses to set pins high and low. The other (inactive buffer) is the buffer that 
the user's code modifies (with calls to Write()). Any time a modification is made 
to the inactive buffer, the ISR will swap buffers at the next rising edge (beginning
of the frame) and use the updated buffer. This means that user code can modify
the PWM pulse width values at any time (even very rapidly) and no glitches will 
occur in the PWM output.

