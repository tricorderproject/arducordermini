/************************************************************************/
/*                                                                      */
/*  PmodJSTKDspi  --  Illustrate Use of DSPI Library with PmodJSTK      */
/*                                                                      */
/************************************************************************/
/*  Author: Gene Apperson                                               */
/*  Copyright 2011, Digilent Inc, All rights reserved.                  */
/************************************************************************/
/*
  This program is free software; you can redistribute it and/or
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
/************************************************************************/
/*  Module Description:                                                 */
/*                                                                      */
/* This example illustrates using the Digilent DSPI library to          */
/* communicate with a PmodJSTK from a Cerebot MX4cK.                    */
/*                                                                      */
/* This demo blinks LED3 and LED4 on boards that have four LEDs, and at */
/* the same time, blinks the two LEDs on the PmodJSTK. It reads the     */
/* state of the two buttons on the PmodJSTK, and turns LED1 and LED2 on */
/* and off based on the button state. The X and Y joystick position is  */
/* read and placed into global variables, but not used by the demo      */
/* itself.                                                              */
/*                                                                      */
/************************************************************************/
/*  Revision History:                                                   */
/*                                                                      */
/*  10/27/2011(GeneApperson): Created                                   */
/*                                                                      */
/************************************************************************/


/* ------------------------------------------------------------ */
/*                Include File Definitions                      */
/* ------------------------------------------------------------ */

/* Pull in the DSPI library
*/
#include <DSPI.h>

/* ------------------------------------------------------------ */
/*                Local Type Definitions                        */
/* ------------------------------------------------------------ */

#define	cntBlinkInit	50000

/* ------------------------------------------------------------ */
/*                Global Variables                              */
/* ------------------------------------------------------------ */

int      cntBtnBlink;
uint8_t  fbLedPmod;
uint8_t  fbBtnPmod;
int      xcoPmod;
int      ycoPmod;
int      fLed3;
int      fLed4;

/* Unlike many chipKIT/Arduino libraries, the DSPI library doesn't
** automatically instantiate any interface objects. It is necessary
** to declare an instance of one of the interface objects in the
** sketch. This creates an object to talk to SPI port 0. Similarly,
** declaring a variable of type DSPI1, DSPI2, DSPI3, etc. will create
** an object to talk to DSPI port 1, 2, or 3.
*/
DSPI0    spi;

/* ------------------------------------------------------------ */
/*                Local Variables                               */
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*                Forward Declarations                          */
/* ------------------------------------------------------------ */


/* ------------------------------------------------------------ */
/*                Procedure Definitions                         */
/* ------------------------------------------------------------ */
/***  setup
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Initialize the system.
*/

void
setup() {

    DeviceInit();
    AppInit();
    
}

/* ------------------------------------------------------------ */
/***  loop
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Main application loop.
*/

void
loop() {
    
  AppTask();
  
}

/* ------------------------------------------------------------ */
/***  DeviceInit
**
**  Parameters:
**    none
**
**  Return Value:
**  none
**
**  Errors:
**  none
**
**  Description:
**    Perform basic board/device level initialization.
*/

void
DeviceInit()
{

  /* Set the LED pins to be outputs. Some boards support more
  ** than two LEDs. On those boards, also blink the additional
  ** LEDs.
  */
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  
  #if defined(PIN_LED3)
  pinMode(PIN_LED3, OUTPUT);
  #endif
  
  #if defined(PIN_LED4)
  pinMode(PIN_LED4, OUTPUT);
  #endif

  /* Initialize the SPI port.
  ** Setting the SPI clock speed to 250khz will satisfy the 
  ** PmodJSTK requirement of having at least 6us of delay between
  ** bytes sent.
  */
  spi.begin();
  spi.setSpeed(250000);
  
}

/* ------------------------------------------------------------ */
/***	AppInit
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Perform application level initialization. Call the various
**    init functions to initalize the application subsystems.
*/

void
AppInit()
  {

  /* Init program state variables.
  */
  cntBtnBlink = cntBlinkInit;
  fbLedPmod = 0x01;
  fbBtnPmod = 0;
  xcoPmod = 0;
  ycoPmod = 0;

  /* Start with LED3 on and LED4 off
  */
  fLed3 = HIGH;
  fLed4 = LOW;

}

/* ------------------------------------------------------------ */
/***	AppTask
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Perform main application functions. This is called once
**    each time through the main program loop.
*/

void
AppTask()
  {
  unsigned int	dwBtn;

  /* Check the state of button 1 and set LED 1 accordingly
  */
  dwBtn = fbBtnPmod & 0x01;
  if (dwBtn == 0) {
    digitalWrite(PIN_LED1, LOW);
  }
  else {
    digitalWrite(PIN_LED1, HIGH);
  }

  /* Check the state of button 2 and set LED 2 accordingly
  */
  dwBtn = fbBtnPmod & 0x02;
  if (dwBtn == 0) {
    digitalWrite(PIN_LED2, LOW);
  }
  else {
    digitalWrite(PIN_LED2, HIGH);
  }

  /* Check if it is time to blink LED3 & LED4 and update
  ** the joystick.
  */
  cntBtnBlink -= 1;
  if (cntBtnBlink == 0) {
    
  #if defined(PIN_LED3)
    digitalWrite(PIN_LED3, fLed3);
    fLed3 = (fLed3 == HIGH) ? LOW : HIGH;
  #endif
  
  #if defined(PIN_LED4)
    digitalWrite(PIN_LED4, fLed4);
    fLed4 = (fLed4 == HIGH) ? LOW : HIGH;
  #endif

    /* Toggle the setting for the LEDs on the joystick.
    */
    fbLedPmod ^= 0x03;
    
    /* Update the joystick.
    */
    ReadJoystick(fbLedPmod, &fbBtnPmod, &xcoPmod, &ycoPmod);

    cntBtnBlink = cntBlinkInit;
  }
}

/* ------------------------------------------------------------ */
/***  ReadJoystick
**
**  Parameters:
**    fbLed	- LED state to set
**    pfbBtn	- variable to receive button state
**    pxco	- pointer to var to receive x coordinate
**    pyco	- pointer to var to receive y coordinate
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Read the current position of the joystick and buttons.
*/
void
ReadJoystick(uint8_t fbLed, uint8_t * pfbBtn, int * pxco, int * pyco)
  {
  uint8_t    rgbSnd[5];
  uint8_t    rgbRcv[5];
  int	     ib;

  /* Initialize the transmit buffer.
  */
  for (ib = 0; ib < 5; ib++) {
    rgbSnd[ib] = 0x50 + ib;
  }
  rgbSnd[0] = fbLedPmod + 0x80;  //first byte sent sets the LEDs
  
  /* Bring SS low to begin the transaction.
  */
  spi.setSelect(LOW);

  /* Wait 10us for Pmod to become ready
  */
  Delay10us();

  /* Send the data to the Pmod and get the response.
  */
  spi.transfer(5, rgbSnd, rgbRcv);
  
  /* Bring SS high to end the transaction.
  */
  spi.setSelect(HIGH);

  /* Set up the return values.
  */
  *pfbBtn = rgbRcv[4] >> 1;
  *pxco = (uint16_t)((rgbRcv[1] << 8) + rgbRcv[0]);
  *pyco = (uint16_t)((rgbRcv[3] << 8) + rgbRcv[2]);

}

/* ------------------------------------------------------------ */
/***  Delay10us
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Delay loop for ~10uS
*/

void
Delay10us()
  {
  volatile int		cnt;

  for (cnt = 0; cnt < 100; cnt++) {
  }

}

/* ------------------------------------------------------------ */

/************************************************************************/


