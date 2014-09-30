/************************************************************************/
/*																		*/
/*	Board_Data.c -- Board Customization Data for Digilent chipKIT WF32	*/
/*																		*/
/************************************************************************/
/*	Author: Gene Apperson												*/
/*	Copyright 2011, Digilent. All rights reserved						*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/* This file contains the board specific declartions and data structure	*/
/* to customize the chipKIT MPIDE for use with the Digilent chipKIT		*/
/* Uno32 board.															*/
/*																		*/
/* This code is based on earlier work:									*/
/*		Copyright (c) 2010, 2011 by Mark Sproul							*/
/*		Copyright (c) 2005, 2006 by David A. Mellis						*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	11/28/2011(GeneA): Created by splitting data out of Board_Defs.h	*/
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

#if !defined(BOARD_DATA_C)
#define BOARD_DATA_C

#include <inttypes.h>

/* ------------------------------------------------------------ */
/*					Data Tables									*/
/* ------------------------------------------------------------ */
/* The following declarations define data used in pin mapping.	*/
/* ------------------------------------------------------------ */

#if defined(OPT_BOARD_DATA)

/* ------------------------------------------------------------ */
/* This table is used to map from port number to the address of
** the TRIS register for the port. This is used for setting the
** pin direction.
*/
const uint32_t port_to_tris_PGM[] = {
	NOT_A_PORT,				//index value 0 is not used

#if defined(_PORTA)
	(uint32_t)&TRISA,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTB)
	(uint32_t)&TRISB,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTC)
	(uint32_t)&TRISC,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTD)
	(uint32_t)&TRISD,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTE)
	(uint32_t)&TRISE,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTF)
	(uint32_t)&TRISF,
#else
	NOT_A_PORT,
#endif

#if defined(_PORTG)
	(uint32_t)&TRISG,
#else
	NOT_A_PORT,
#endif

	NOT_A_PORT,
};

/* ------------------------------------------------------------ */
/* This table is used to map the digital pin number to the port
** containing that pin.
*/
const uint8_t digital_pin_to_port_PGM[] = {
    _IOPORT_PF,		//	0   RF02    SDA3/SDI3/U1RX/RF2
    _IOPORT_PF,		//	1   RF08    SCL3/SDO3/U1TX/RF8
    _IOPORT_PE,		//	2   RE08    AERXD0/INT1/RE8
    _IOPORT_PD,		//	3   RD00    SDO1/OC1/INT0/RD0
    _IOPORT_PF,		//	4   RF01    ETXD0/PMD10/RF1
    _IOPORT_PD,		//	5   RD01    OC2/RD1
    _IOPORT_PD,		//	6   RD02    OC3/RD2    
    _IOPORT_PE,		//	7   RE09    AERXD1/INT2/RE9   
    _IOPORT_PA,		//	8   RA14    AETXCLK/SCL1/INT3/RA14 
    _IOPORT_PD,		//	9   RD03    OC4/RD3   
    _IOPORT_PD,		//	10  RD04    OC5/PMWR/CN13/RD4  
    _IOPORT_PG,		//	11  RG08    ERXDV/AERXDV/ECRSDV/AECRSDV/SCL4/SDO2/U3TX/PMA3/CN10/RG8
    _IOPORT_PG,		//	12  RG07    ECRS/SDA4/SDI2/U3RX/PMA4/CN9/RG7
    _IOPORT_PG,		//	13  RG06    ECOL/SCK2/U6TX/U3RTS/PMA5/CN8/RG6 (SPI_SCK, User LED1)
    _IOPORT_PB,		//	14  RB02    AN2/C2IN-/CN4/RB2
    _IOPORT_PB,		//	15  RB04    AN4/C1IN-/CN6/RB4
    _IOPORT_PB,		//	16  RB08    AN8/C1OUT/RB8
    _IOPORT_PB,		//	17  RB00    PGED1/AN0/CN2/RB0
    _IOPORT_PB,		//	18  RB10    AN10/CVrefout/PMA13/RB10
    _IOPORT_PB,		//	19  RB11    AN11/ERXERR/AETXERR/PMA12/RB11   
    _IOPORT_PB,		//	20  RB03    AN3/C2IN+/CN5/RB3
    _IOPORT_PB,		//	21  RB05    AN5/C1IN+/VBUSON/CN7/RB5
    _IOPORT_PB,		//	22  RB09    AN9/C2OUT/RB9
    _IOPORT_PB,		//	23  RB01    PGEC1/AN1/CN3/RB1
    _IOPORT_PB,		//	24  RB14    AN14/ERXD2/AETXD3/PMALH/PMA1/RB14  
    _IOPORT_PB,		//	25  RB15    AN15/ERXD3/AETXD2/OCFB/PMALL/PMA0/CN12/RB15
    _IOPORT_PE,		//	26  RE00    PMD0/RE0
    _IOPORT_PE,		//	27  RE01    PMD1/RE1  
    _IOPORT_PE,		//	28  RE02    PMD2/RE2
    _IOPORT_PE,		//	29  RE03    PMD3/RE3   
    _IOPORT_PE,		//	30  RE04    PMD4/RE4  
    _IOPORT_PE,		//	31  RE05    PMD5/RE5
    _IOPORT_PE,		//	32  RE06    PMD6/RE6
    _IOPORT_PE,		//	33  RE07    PMD7/RE7 
    _IOPORT_PD,		//	34  RD05    PMRD/CN14/RD5
    _IOPORT_PD,		//	35  RD11    EMDC/AEMDC/IC4/PMCS1/PMA14/RD11
    _IOPORT_PD,		//	36  RD06    ETXEN/PMD14/CN15/RD6
    _IOPORT_PD,		//	37  RD07    ETXCLK/PMD15/CN16/RD7
    _IOPORT_PC,		//	38  RC04    T5CK/SDI1/RC4
    _IOPORT_PD,		//	39  RD14    AETXD0/SS3/U4RX/U1CTS/CN20/RD14
    _IOPORT_PD,		//	40  RD15    AETXD1/SCK3/U4TX/U1RTS/CN21/RD15
    _IOPORT_PA,		//	41  RA09    Vref-/CVref-/AERXD2/PMA7/RA9
    _IOPORT_PA,		//	42  RA10    Vref+/CVref+/AERXD3/PMA6/RA10   (Pin A; VREF+)

    // these are above the highest pin on the board
    _IOPORT_PF,		//	43  RF00    ETXD1/PMD11/RF0                 (User LED2)
    _IOPORT_PG,		//	44  RG09    ERXCLK/AERXCLK/EREFCLK/AEREFCLK/SS2/U6RX/U3CTS/PMA2/CN11/RG9 (SPI_SS (JPR to digital pin 10 position))
    _IOPORT_PA,		//	45  RA02    SCL2/RA2                        (I2C, wire (jumper to A5) shared with pin 19)                       
    _IOPORT_PA,		//	46  RA03    SDA2/RA3                        (I2C, wire (jumper to A4) shared with pin 18)
    _IOPORT_PA,		//	47  RA00    TMS/RA0                         (User LED4)
    _IOPORT_PA,		//	48  RA01    TCK/RA1                         (User LED3)

    // SD Card
    _IOPORT_PG,	    //	49  RG15    AERXERR/RG15                    (SD Card)
    _IOPORT_PG,	    //	50  RG14    TRD2/RG14                       (SD Card)
    _IOPORT_PG,	    //	51  RG12    TRD1/RG12                       (SD Card)
    _IOPORT_PG,	    //	52  RG13    TRD0/RG13                       (SD Card)

    // MRF24-G WiFi Module
    _IOPORT_PF,	    //	53  RF13    SCK4/U5TX/U2RTS/RF13            (MRF24 SPI)
    _IOPORT_PF,	    //	54  RF12    SS4/U5RX/U2CTS/RF12             (MRF24 SPI)
    _IOPORT_PF,	    //	55  RF04    SDA5/SDI4/U2RX/PMA9/CN17/RF4    (MRF24 SPI)   
    _IOPORT_PF,	    //	56  RF05    SCL5/SDO4/U2TX/PMA8/CN18/RF5    (MRF24 SPI)  
    _IOPORT_PA,	    //	57  RA15    AETXEN/SDA1/INT4/RA15           (MRF24 INT)
    _IOPORT_PG,	    //	58  RG01    ETXERR/PMD9/RG1                 (MRF24 HIBERNATE)
    _IOPORT_PG,	    //	59  RG00    PMD8/RG0                        (MRF24 RESET)

    // surplus pins
    _IOPORT_PB,	    //	60  RB12    AN12/ERXD0/AECRS/PMA11/RB12     (Power Supply Monitor)
    _IOPORT_PB,	    //	61  RB13    AN13/ERXD1/AECOL/PMA10/RB13     (5V Power Enable)4
    _IOPORT_PA,	    //	62  RA04    TDI/RA4                         (SDA pullup)
    _IOPORT_PA,	    //	63  RA05    TDO/RA5                         (SCL pullup)
    _IOPORT_PD,	    //	64  RD13    ETXD3/PMD13/CN19/RD13           (CBUS4)
    _IOPORT_PA,	    //	65  RA06    TRCLK/RA6                       (BTN1)
    _IOPORT_PA,	    //	66  RA07    TRD3/RA7                        (BTN1)

    // shared pins
    _IOPORT_PC,		//	67  RC01    T2CK/RC1                        (shared with digital pin 34)
    _IOPORT_PC,		//	68  RC02    T3CK/RC2                        (shared with digital pin 35)
    _IOPORT_PC,		//	69  RC03    T4CK/RC3                        (shared with digital pin 36)
    _IOPORT_PD,		//	70  RD08    RTCC/EMDIO/AEMDIO/IC1/RD8       (shared with digital pin 2)
    _IOPORT_PD,		//	71  RD09    SS1/IC2/RD9                     (shared with digital pin 7)
    _IOPORT_PD,		//	72  RD10    SCK1/IC3/PMCS2/PMA15/RD10       (shared with digital pin 8)
    _IOPORT_PD,		//	73  RD12    ETXD2/IC5/PMD12/RD12            (shared with digital pin 10) 
};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to a bit mask
** for the corresponding bit within the port.
*/
const uint16_t digital_pin_to_bit_mask_PGM[] = 
{
	_BV( 2 ),	    //	0   RF02    SDA3/SDI3/U1RX/RF2	
	_BV( 8 ),		//	1   RF08    SCL3/SDO3/U1TX/RF8
	_BV( 8 ),		//	2   RE08    AERXD0/INT1/RE8
	_BV( 0 ),		//	3   RD00    SDO1/OC1/INT0/RD0
	_BV( 1 ),		//	4   RF01    ETXD0/PMD10/RF1
	_BV( 1 ),		//	5   RD01    OC2/RD1
	_BV( 2 ),		//	6   RD02    OC3/RD2    
	_BV( 9 ),		//	7   RE09    AERXD1/INT2/RE9   
	_BV( 14 ),		//	8   RA14    AETXCLK/SCL1/INT3/RA14 
	_BV( 3 ),		//	9   RD03    OC4/RD3   
	_BV( 4 ),		//	10  RD04    OC5/PMWR/CN13/RD4  
	_BV( 8 ),		//	11  RG08    ERXDV/AERXDV/ECRSDV/AECRSDV/SCL4/SDO2/U3TX/PMA3/CN10/RG8
	_BV( 7 ),		//	12  RG07    ECRS/SDA4/SDI2/U3RX/PMA4/CN9/RG7
	_BV( 6 ),		//	13  RG06    ECOL/SCK2/U6TX/U3RTS/PMA5/CN8/RG6 (SPI_SCK, User LED)
	_BV( 2 ),		//	14  RB02    AN2/C2IN-/CN4/RB2
	_BV( 4 ),		//	15  RB04    AN4/C1IN-/CN6/RB4
	_BV( 8 ),		//	16  RB08    AN8/C1OUT/RB8
	_BV( 0 ),		//	17  RB00    PGED1/AN0/CN2/RB0
	_BV( 10 ),		//	18  RB10    AN10/CVrefout/PMA13/RB10
	_BV( 11 ),		//	19  RB11    AN11/ERXERR/AETXERR/PMA12/RB11   
	_BV( 3 ),		//	20  RB03    AN3/C2IN+/CN5/RB3
	_BV( 5 ),		//	21  RB05    AN5/C1IN+/VBUSON/CN7/RB5
	_BV( 9 ),		//	22  RB09    AN9/C2OUT/RB9
	_BV( 1 ),		//	23  RB01    PGEC1/AN1/CN3/RB1
	_BV( 14 ),		//	24  RB14    AN14/ERXD2/AETXD3/PMALH/PMA1/RB14  
	_BV( 15 ),		//	25  RB15    AN15/ERXD3/AETXD2/OCFB/PMALL/PMA0/CN12/RB15
	_BV( 0 ),		//	26  RE00    PMD0/RE0
	_BV( 1 ),		//	27  RE01    PMD1/RE1  
	_BV( 2 ),		//	28  RE02    PMD2/RE2
	_BV( 3 ),		//	29  RE03    PMD3/RE3   
	_BV( 4 ),		//	30  RE04    PMD4/RE4  
	_BV( 5 ),		//	31  RE05    PMD5/RE5
	_BV( 6 ),		//	32  RE06    PMD6/RE6
	_BV( 7 ),		//	33  RE07    PMD7/RE7 
	_BV( 5 ),		//	34  RD05    PMRD/CN14/RD5
	_BV( 11 ),		//	35  RD11    EMDC/AEMDC/IC4/PMCS1/PMA14/RD11
	_BV( 6 ),		//	36  RD06    ETXEN/PMD14/CN15/RD6
	_BV( 7 ),		//	37  RD07    ETXCLK/PMD15/CN16/RD7
	_BV( 4 ),		//	38  RC04    T5CK/SDI1/RC4
	_BV( 14 ),		//	39  RD14    AETXD0/SS3/U4RX/U1CTS/CN20/RD14
	_BV( 15 ),		//	40  RD15    AETXD1/SCK3/U4TX/U1RTS/CN21/RD15
	_BV( 9 ),		//	41  RA09    Vref-/CVref-/AERXD2/PMA7/RA9
	_BV( 10 ),		//	42  RA10    Vref+/CVref+/AERXD3/PMA6/RA10   (Pin A; VREF+)
	
    // these are above the highest pin on the board
    _BV( 0 ),		//	43  RF00    ETXD1/PMD11/RF0                 (User LED)
    _BV( 9 ),		//	44  RG09    ERXCLK/AERXCLK/EREFCLK/AEREFCLK/SS2/U6RX/U3CTS/PMA2/CN11/RG9 (SPI_SS (JPR to digital pin 10 position))
    _BV( 2 ),		//	45  RA02    SCL2/RA2                        (I2C, wire (jumper to A5) shared with pin 19)                       
    _BV( 3 ),		//	46  RA03    SDA2/RA3                        (I2C, wire (jumper to A4) shared with pin 18)
    _BV( 0 ),		//	47  RA00    TMS/RA0                         (User LED)
    _BV( 1 ),		//	48  RA01    TCK/RA1                         (User LED)

    // SD Card
    _BV( 15 ),		//	49  RG15    AERXERR/RG15                    (SD Card)
    _BV( 14 ),		//	50  RG14    TRD2/RG14                       (SD Card)
    _BV( 12 ),		//	51  RG12    TRD1/RG12                       (SD Card)
    _BV( 13 ),		//	52  RG13    TRD0/RG13                       (SD Card)

    // MRF24-G WiFi Module
    _BV( 13 ),		//	53  RF13    SCK4/U5TX/U2RTS/RF13            (MRF24 SPI)
    _BV( 12 ),		//	54  RF12    SS4/U5RX/U2CTS/RF12             (MRF24 SPI)
    _BV( 4 ),		//	55  RF04    SDA5/SDI4/U2RX/PMA9/CN17/RF4    (MRF24 SPI)   
    _BV( 5 ),		//	56  RF05    SCL5/SDO4/U2TX/PMA8/CN18/RF5    (MRF24 SPI)  
    _BV( 15 ),		//	57  RA15    AETXEN/SDA1/INT4/RA15           (MRF24 INT)
    _BV( 1 ),		//	58  RG01    ETXERR/PMD9/RG1                 (MRF24 HIBERNATE)
    _BV( 0 ),		//	59  RG00    PMD8/RG0                        (MRF24 RESET)

    // surplus pins
    _BV( 12 ),		//	60  RB12    AN12/ERXD0/AECRS/PMA11/RB12     (Power Supply Monitor)
    _BV( 13),		//	61  RB13    AN13/ERXD1/AECOL/PMA10/RB13     (5V Power Enable)
    _BV( 4 ),		//	62  RA04    TDI/RA4                         (SDA pullup)
    _BV( 5 ),		//	63  RA05    TDO/RA5                         (SCL pullup)
    _BV( 13 ),		//	64  RD13    ETXD3/PMD13/CN19/RD13           (CBUS4)
    _BV( 6 ),		//	65  RA06    TRCLK/RA6                       (BTN1)
    _BV( 7 ),		//	66  RA07    TRD3/RA7                        (BTN1)

    // shared pins
    _BV( 1 ),		//	67  RC01    T2CK/RC1                        (shared with digital pin 34)
    _BV( 2 ),		//	68  RC02    T3CK/RC2                        (shared with digital pin 35)
    _BV( 3 ),		//	69  RC03    T4CK/RC3                        (shared with digital pin 36)
    _BV( 8 ),		//	70  RD08    RTCC/EMDIO/AEMDIO/IC1/RD8       (shared with digital pin 2)
    _BV( 9 ),		//	71  RD09    SS1/IC2/RD9                     (shared with digital pin 7)
    _BV( 10 ),		//	72  RD10    SCK1/IC3/PMCS2/PMA15/RD10       (shared with digital pin 8)
    _BV( 12 ),		//	73  RD12    ETXD2/IC5/PMD12/RD12            (shared with digital pin 10) 

};

/* ------------------------------------------------------------ */
/* This table is used to map from digital pin number to the output
** compare number, input capture number, and timer external clock
** input associated with that pin.
*/
const uint16_t digital_pin_to_timer_PGM[] =
{
	NOT_ON_TIMER,	        //	0   RF02    SDA3/SDI3/U1RX/RF2		
	NOT_ON_TIMER,			//	1   RF08    SCL3/SDO3/U1TX/RF8
	NOT_ON_TIMER,		    //	2   RE08    AERXD0/INT1/RE8
	_TIMER_OC1,				//	3   RD00    SDO1/OC1/INT0/RD0
	NOT_ON_TIMER,			//	4   RF01    ETXD0/PMD10/RF1
	_TIMER_OC2,				//	5   RD01    OC2/RD1
	_TIMER_OC3,				//	6   RD02    OC3/RD2    
	NOT_ON_TIMER,			//	7   RE09    AERXD1/INT2/RE9   
	NOT_ON_TIMER,			//	8   RA14    AETXCLK/SCL1/INT3/RA14 
	_TIMER_OC4,				//	9   RD03    OC4/RD3   
	_TIMER_OC5,	            //	10  RD04    OC5/PMWR/CN13/RD4  
	NOT_ON_TIMER,			//	11  RG08    ERXDV/AERXDV/ECRSDV/AECRSDV/SCL4/SDO2/U3TX/PMA3/CN10/RG8
	NOT_ON_TIMER,			//	12  RG07    ECRS/SDA4/SDI2/U3RX/PMA4/CN9/RG7
	NOT_ON_TIMER,			//	13  RG06    ECOL/SCK2/U6TX/U3RTS/PMA5/CN8/RG6 (SPI_SCK, User LED)
	NOT_ON_TIMER,			//	14  RB02    AN2/C2IN-/CN4/RB2
	NOT_ON_TIMER,			//	15  RB04    AN4/C1IN-/CN6/RB4
	NOT_ON_TIMER,			//	16  RB08    AN8/C1OUT/RB8
	NOT_ON_TIMER,			//	17  RB00    PGED1/AN0/CN2/RB0
	NOT_ON_TIMER,			//	18  RB10    AN10/CVrefout/PMA13/RB10
	NOT_ON_TIMER,			//	19  RB11    AN11/ERXERR/AETXERR/PMA12/RB11   
	NOT_ON_TIMER,			//	20  RB03    AN3/C2IN+/CN5/RB3
	NOT_ON_TIMER,			//	21  RB05    AN5/C1IN+/VBUSON/CN7/RB5
	NOT_ON_TIMER,			//	22  RB09    AN9/C2OUT/RB9
	NOT_ON_TIMER,			//	23  RB01    PGEC1/AN1/CN3/RB1
	NOT_ON_TIMER,			//	24  RB14    AN14/ERXD2/AETXD3/PMALH/PMA1/RB14  
	NOT_ON_TIMER,			//	25  RB15    AN15/ERXD3/AETXD2/OCFB/PMALL/PMA0/CN12/RB15
	NOT_ON_TIMER,			//	26  RE00    PMD0/RE0
	NOT_ON_TIMER,			//	27  RE01    PMD1/RE1  
	NOT_ON_TIMER,			//	28  RE02    PMD2/RE2
	NOT_ON_TIMER,			//	29  RE03    PMD3/RE3   
	NOT_ON_TIMER,			//	30  RE04    PMD4/RE4  
	NOT_ON_TIMER,			//	31  RE05    PMD5/RE5
	NOT_ON_TIMER,			//	32  RE06    PMD6/RE6
	NOT_ON_TIMER,			//	33  RE07    PMD7/RE7 
	NOT_ON_TIMER,			//	34  RD05    PMRD/CN14/RD5
	_TIMER_IC4,				//	35  RD11    EMDC/AEMDC/IC4/PMCS1/PMA14/RD11
	NOT_ON_TIMER,			//	36  RD06    ETXEN/PMD14/CN15/RD6
	NOT_ON_TIMER,			//	37  RD07    ETXCLK/PMD15/CN16/RD7
	_TIMER_TCK5,			//	38  RC04    T5CK/SDI1/RC4
	NOT_ON_TIMER,			//	39  RD14    AETXD0/SS3/U4RX/U1CTS/CN20/RD14
	NOT_ON_TIMER,			//	40  RD15    AETXD1/SCK3/U4TX/U1RTS/CN21/RD15
	NOT_ON_TIMER,			//	41  RA09    Vref-/CVref-/AERXD2/PMA7/RA9
	NOT_ON_TIMER,			//	42  RA10    Vref+/CVref+/AERXD3/PMA6/RA10   (Pin A; VREF+)	

    // these are above the highest pin on the board
    NOT_ON_TIMER,			//	43  RF00    ETXD1/PMD11/RF0                 (User LED)
    NOT_ON_TIMER,			//	44  RG09    ERXCLK/AERXCLK/EREFCLK/AEREFCLK/SS2/U6RX/U3CTS/PMA2/CN11/RG9 (SPI_SS (JPR to digital pin 10 position))
    NOT_ON_TIMER,			//	45  RA02    SCL2/RA2                        (I2C, wire (jumper to A5) shared with pin 19)                       
    NOT_ON_TIMER,			//	46  RA03    SDA2/RA3                        (I2C, wire (jumper to A4) shared with pin 18)
    NOT_ON_TIMER,			//	47  RA00    TMS/RA0                         (User LED)
    NOT_ON_TIMER,			//	48  RA01    TCK/RA1                         (User LED)

    // SD Card
    NOT_ON_TIMER,			//	49  RG15    AERXERR/RG15                    (SD Card)
    NOT_ON_TIMER,			//	50  RG14    TRD2/RG14                       (SD Card)
    NOT_ON_TIMER,			//	51  RG12    TRD1/RG12                       (SD Card)
    NOT_ON_TIMER,			//	52  RG13    TRD0/RG13                       (SD Card)

    // MRF24-G WiFi Module
    NOT_ON_TIMER,           //	53  RF13    SCK4/U5TX/U2RTS/RF13            (MRF24 SPI)
    NOT_ON_TIMER,			//	54  RF12    SS4/U5RX/U2CTS/RF12             (MRF24 SPI)
    NOT_ON_TIMER,			//	55  RF04    SDA5/SDI4/U2RX/PMA9/CN17/RF4    (MRF24 SPI)   
    NOT_ON_TIMER,			//	56  RF05    SCL5/SDO4/U2TX/PMA8/CN18/RF5    (MRF24 SPI)  
    NOT_ON_TIMER,			//	57  RA15    AETXEN/SDA1/INT4/RA15           (MRF24 INT)
    NOT_ON_TIMER,			//	58  RG01    ETXERR/PMD9/RG1                 (MRF24 HIBERNATE)
    NOT_ON_TIMER,			//	59  RG00    PMD8/RG0                        (MRF24 RESET)

    // surplus pins
    NOT_ON_TIMER,           //	60  RB12    AN12/ERXD0/AECRS/PMA11/RB12     (Power Supply Monitor)
    NOT_ON_TIMER,			//	61  RB13    AN13/ERXD1/AECOL/PMA10/RB13     (5V Power Enable)
    NOT_ON_TIMER,			//	62  RA04    TDI/RA4                         (SDA pullup)
    NOT_ON_TIMER,			//	63  RA05    TDO/RA5                         (SCL pullup)
    NOT_ON_TIMER,			//	64  RD13    ETXD3/PMD13/CN19/RD13           (CBUS4)
    NOT_ON_TIMER,			//	65  RA06    TRCLK/RA6                       (BTN1)
    NOT_ON_TIMER,			//	66  RA07    TRD3/RA7                        (BTN1)

    // shared pins
    _TIMER_TCK2,            //	67  RC01    T2CK/RC1                        (shared with digital pin 34)
    _TIMER_TCK3,			//	68  RC02    T3CK/RC2                        (shared with digital pin 35)
    _TIMER_TCK4,			//	69  RC03    T4CK/RC3                        (shared with digital pin 36)
    _TIMER_IC1,			    //	70  RD08    RTCC/EMDIO/AEMDIO/IC1/RD8       (shared with digital pin 2)
    _TIMER_IC2,			    //	71  RD09    SS1/IC2/RD9                     (shared with digital pin 7)
    _TIMER_IC3,			    //	72  RD10    SCK1/IC3/PMCS2/PMA15/RD10       (shared with digital pin 8)
    _TIMER_IC5,			    //	73  RD12    ETXD2/IC5/PMD12/RD12            (shared with digital pin 10) 
};

/* ------------------------------------------------------------ */
/* This table is used to map from the analog pin number to the
** actual A/D converter channel used for that pin.
*/
const uint8_t analog_pin_to_channel_PGM[] =
{
			//*	chipKIT Pin		PIC32 Analog channel
	2,		//*	A0						AN2
	4,		//*	A1						AN4
	8,		//*	A2						AN8
	0,		//*	A3						AN0
	10,		//*	A4						AN10
	11,		//*	A5						AN11
	3,		//*	A6						AN3
	5,		//*	A7						AN5
	9,		//*	A8						AN9
	1,		//*	A9						AN1
	14,		//*	A10						AN14
	15,		//*	A11						AN15

};

/* ------------------------------------------------------------ */
/*				Board Customization Functions					*/
/* ------------------------------------------------------------ */
/*																*/
/* The following can be used to customize the behavior of some	*/
/* of the core API functions. These provide hooks that can be	*/
/* used to extend or replace the default behavior of the core	*/
/* functions. To use one of these functions, add the desired	*/
/* code to the function skeleton below and then set the value	*/
/* of the appropriate compile switch above to 1. This will		*/
/* cause the hook function to be compiled into the build and	*/
/* to cause the code to call the hook function to be compiled	*/
/* into the appropriate core function.							*/
/*																*/
/* ------------------------------------------------------------ */
/***	_board_init
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
**		This function is called from the core init() function.
**		This can be used to perform any board specific init
**		that needs to be done when the processor comes out of
**		reset and before the user sketch is run.
*/
#if	(OPT_BOARD_INIT != 0)

void _board_init(void) {
	
}

#endif

/* ------------------------------------------------------------ */
/***	_board_pinMode
**
**	Parameters:
**		pin		- digital pin number to configure
**		mode	- mode to which the pin should be configured
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the pinMode
**		function. It can perform any special processing needed
**		when setting the pin mode. If this function returns zero,
**		control will pass through the normal pinMode code. If
**		it returns a non-zero value the normal pinMode code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_pinMode(uint8_t pin, uint8_t mode) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_getPinMode
**
**	Parameters:
**		pin		- digital pin number
**		mode	- pointer to variable to receive mode value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the getPinMode
**		function. It can perform any special processing needed
**		when getting the pin mode. If this function returns zero,
**		control will pass through the normal getPinMode code. If
**		it returns a non-zero value the normal getPinMode code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_getPinMode(uint8_t pin, uint8_t * mode) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_digitalWrite
**
**	Parameters:
**		pin		- digital pin number
**		val		- value to write to the pin
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the digitalWrite
**		function. It can perform any special processing needed
**		in writing to the pin. If this function returns zero,
**		control will pass through the normal digitalWrite code. If
**		it returns a non-zero value the normal digitalWrite code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_digitalWrite(uint8_t pin, uint8_t val) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_digitalRead
**
**	Parameters:
**		pin		- digital pin number
**		val		- pointer to variable to receive pin value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the digitalRead
**		function. It can perform any special processing needed
**		in reading from the pin. If this function returns zero,
**		control will pass through the normal digitalRead code. If
**		it returns a non-zero value the normal digitalRead code isn't
**		executed.
*/
#if	(OPT_BOARD_DIGITAL_IO != 0)

int	_board_digitalRead(uint8_t pin, uint8_t * val) {
	
	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogRead
**
**	Parameters:
**		pin		- analog channel number
**		val		- pointer to variable to receive analog value
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogRead
**		function. It can perform any special processing needed
**		in reading from the pin. If this function returns zero,
**		control will pass through the normal analogRead code. If
**		it returns a non-zero value the normal analogRead code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_READ != 0)

int	_board_analogRead(uint8_t pin, int * val) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogReference
**
**	Parameters:
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogReference
**		function. It can perform any special processing needed
**		to set the reference voltage. If this function returns zero,
**		control will pass through the normal analogReference code. If
**		it returns a non-zero value the normal analogReference code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_READ != 0)

int	_board_analogReference(uint8_t mode) {

	return 0;

}

#endif

/* ------------------------------------------------------------ */
/***	_board_analogWrite
**
**	Parameters:
**		pin		- pin number
**		val		- analog value to write
**
**	Return Value:
**		Returns 0 if not handled, !0 if handled.
**
**	Errors:
**		none
**
**	Description:
**		This function is called at the beginning of the analogWrite
**		function. It can perform any special processing needed
**		in writing to the pin. If this function returns zero,
**		control will pass through the normal analogWrite code. If
**		it returns a non-zero value the normal analogWrite code isn't
**		executed.
*/
#if (OPT_BOARD_ANALOG_WRITE != 0)

int	_board_analogWrite(uint8_t pin, int val) {

	return 0;

}

#endif

#endif // OPT_BOARD_DATA

/* ------------------------------------------------------------ */

#endif	// BOARD_DATA_C

/************************************************************************/
