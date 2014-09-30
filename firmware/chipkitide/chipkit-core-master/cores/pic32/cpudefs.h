//************************************************************************
//*	cpudefs.h
//*	
//*	Arduino core files for PIC32
//*		Copyright (c) 2011 by Mark Sproul
//*	
//*		This file is designed to provide some of the cpu specific definitions
//*		that are available for avr chips and not for pic32 chips
//************************************************************************
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
//*	Apr 16, 2011	<MLS> started on cpudefs.h
//*	Apr 24,	2011	<MLS> copied to bootloader, important to keep them in sync
//*	Jun 16,	2011	<MLS> Added 32MX360F256L
//*	Jun 21,	2011	<MLS> Added 32MX440F512H
//* Nov 19, 2011	<GeneApperson> corrected errors in some parts, added
//*						definitions for all 1XX/2XX/3XX/4XX/5XX/6XX/7XX devices
//************************************************************************

//************************************************************************
//*	atmel chip names
#if defined(__AVR__)

	#if defined (__AVR_AT94K__)
										#define	_CPU_NAME_	"AT94k"
	#elif defined (__AVR_AT43USB320__)
										#define	_CPU_NAME_	"AT43USB320"
	#elif defined (__AVR_AT43USB355__)
										#define	_CPU_NAME_	"AT43USB355"
	#elif defined (__AVR_AT76C711__)
										#define	_CPU_NAME_	"AT76C711"
	#elif defined (__AVR_AT86RF401__)
										#define	_CPU_NAME_	"AT86RF401"
	#elif defined (__AVR_AT90PWM1__)
										#define	_CPU_NAME_	"AT90PWM1"
	#elif defined (__AVR_AT90PWM2__)
										#define	_CPU_NAME_	"AT90PWM2"
	#elif defined (__AVR_AT90PWM2B__)
										#define	_CPU_NAME_	"AT90PWM2B"
	#elif defined (__AVR_AT90PWM3__)
										#define	_CPU_NAME_	"AT90PWM3"
	#elif defined (__AVR_AT90PWM3B__)
										#define	_CPU_NAME_	"AT90PWM3B"
	#elif defined (__AVR_AT90PWM216__)
										#define	_CPU_NAME_	"AT90PWM216"
	#elif defined (__AVR_AT90PWM316__)
										#define	_CPU_NAME_	"AT90PWM316"
	#elif defined (__AVR_ATmega32C1__)
										#define	_CPU_NAME_	"ATmega32C1"
	#elif defined (__AVR_ATmega32M1__)
										#define	_CPU_NAME_	"ATmega32M1"
	#elif defined (__AVR_ATmega32U4__)
										#define	_CPU_NAME_	"ATmega32U4"
	#elif defined (__AVR_ATmega32U6__)
										#define	_CPU_NAME_	"ATmega32U6"
	#elif defined (__AVR_ATmega128__)
										#define	_CPU_NAME_	"Atmega128"
	#elif defined (__AVR_ATmega1280__)
										#define	_CPU_NAME_	"ATmega1280"
	#elif defined (__AVR_ATmega1281__)
										#define	_CPU_NAME_	"ATmega1281"
	#elif defined (__AVR_ATmega1284P__)
										#define	_CPU_NAME_	"ATmega1284"
	#elif defined (__AVR_ATmega128RFA1__)
										#define	_CPU_NAME_	"ATmega128RFA1"
	#elif defined (__AVR_ATmega2560__)
										#define	_CPU_NAME_	"ATmega2560"
	#elif defined (__AVR_ATmega2561__)
										#define	_CPU_NAME_	"ATmega2561"
	#elif defined (__AVR_AT90CAN32__)
										#define	_CPU_NAME_	"AT90CAN32"
	#elif defined (__AVR_AT90CAN64__)
										#define	_CPU_NAME_	"AT90CAN64"
	#elif defined (__AVR_AT90CAN128__)
										#define	_CPU_NAME_	"AT90CAN128"
	#elif defined (__AVR_AT90USB82__)
										#define	_CPU_NAME_	"AT90USB82"
	#elif defined (__AVR_AT90USB162__)
										#define	_CPU_NAME_	"AT90USB162"
	#elif defined (__AVR_AT90USB646__)
										#define	_CPU_NAME_	"AT90USB646"
	#elif defined (__AVR_AT90USB647__)
										#define	_CPU_NAME_	"AT90USB647"
	#elif defined (__AVR_AT90USB1286__)
										#define	_CPU_NAME_	"AT90USB1286"
	#elif defined (__AVR_AT90USB1287__)
										#define	_CPU_NAME_	"AT90USB1287"
	#elif defined (__AVR_ATmega64__)
										#define	_CPU_NAME_	"ATmega64"
	#elif defined (__AVR_ATmega640__)
										#define	_CPU_NAME_	"ATmega640"
	#elif defined (__AVR_ATmega644__)
										#define	_CPU_NAME_	"ATmega644"
	#elif defined (__AVR_ATmega644P__)
										#define	_CPU_NAME_	"ATmega644P"
	#elif defined (__AVR_ATmega645__)
										#define	_CPU_NAME_	"ATmega645"
	#elif defined (__AVR_ATmega6450__)
										#define	_CPU_NAME_	"ATmega6450"
	#elif defined (__AVR_ATmega649__)
										#define	_CPU_NAME_	"ATmega649"
	#elif defined (__AVR_ATmega6490__)
										#define	_CPU_NAME_	"ATmega6490"
	#elif defined (__AVR_ATmega103__)
										#define	_CPU_NAME_	"ATmega103"
	#elif defined (__AVR_ATmega32__)
										#define	_CPU_NAME_	"Atmega32"
	#elif defined (__AVR_ATmega323__)
										#define	_CPU_NAME_	"ATmega323"
	#elif defined (__AVR_ATmega324P__)
										#define	_CPU_NAME_	"ATmega324P"
	#elif defined (__AVR_ATmega325__)
										#define	_CPU_NAME_	"ATmega325"
	#elif defined (__AVR_ATmega325P__)
										#define	_CPU_NAME_	"ATmega325P"
	#elif defined (__AVR_ATmega3250__)
										#define	_CPU_NAME_	"ATmega3250"
	#elif defined (__AVR_ATmega3250P__)
										#define	_CPU_NAME_	"ATmega3250P"
	#elif defined (__AVR_ATmega328P__)
										#define	_CPU_NAME_	"ATmega328P"
	#elif defined (__AVR_ATmega329__)
										#define	_CPU_NAME_	"ATmega329"
	#elif defined (__AVR_ATmega329P__)
										#define	_CPU_NAME_	"ATmega329P"
	#elif defined (__AVR_ATmega3290__)
										#define	_CPU_NAME_	"ATmega3290"
	#elif defined (__AVR_ATmega3290P__)
										#define	_CPU_NAME_	"ATmega3290P"
	#elif defined (__AVR_ATmega32HVB__)
										#define	_CPU_NAME_	"ATmega32HVB"
	#elif defined (__AVR_ATmega406__)
										#define	_CPU_NAME_	"ATmega406"
	#elif defined (__AVR_ATmega16__)
										#define	_CPU_NAME_	"Atmega16"
	#elif defined (__AVR_ATmega161__)
										#define	_CPU_NAME_	"ATmega161"
	#elif defined (__AVR_ATmega162__)
										#define	_CPU_NAME_	"ATmega162"
	#elif defined (__AVR_ATmega163__)
										#define	_CPU_NAME_	"ATmega163"
	#elif defined (__AVR_ATmega164P__)
										#define	_CPU_NAME_	"ATmega164P"
	#elif defined (__AVR_ATmega165__)
										#define	_CPU_NAME_	"ATmega165"
	#elif defined (__AVR_ATmega165P__)
										#define	_CPU_NAME_	"ATmega165P"
	#elif defined (__AVR_ATmega168__)
										#define	_CPU_NAME_	"ATmega168"
	#elif defined (__AVR_ATmega168P__)
										#define	_CPU_NAME_	"ATmega168P"
	#elif defined (__AVR_ATmega169__)
										#define	_CPU_NAME_	"Atmega169"
	#elif defined (__AVR_ATmega169P__)
										#define	_CPU_NAME_	"ATmega169P"
	#elif defined (__AVR_ATmega8HVA__)
										#define	_CPU_NAME_	"ATmega8HVA"
	#elif defined (__AVR_ATmega16HVA__)
										#define	_CPU_NAME_	"ATmega16HVA"
	#elif defined (__AVR_ATmega8__)
										#define	_CPU_NAME_	"ATmega8"
	#elif defined (__AVR_ATmega48__)
										#define	_CPU_NAME_	"ATmega48"
	#elif defined (__AVR_ATmega48P__)
										#define	_CPU_NAME_	"ATmega48P"
	#elif defined (__AVR_ATmega88__)
										#define	_CPU_NAME_	"ATmega88"
	#elif defined (__AVR_ATmega88P__)
										#define	_CPU_NAME_	"ATmega88P"
	#elif defined (__AVR_ATmega8515__)
										#define	_CPU_NAME_	"ATmega8515"
	#elif defined (__AVR_ATmega8535__)
										#define	_CPU_NAME_	"ATmega8535"
	#elif defined (__AVR_AT90S8535__)
										#define	_CPU_NAME_	"AT90S8535"
	#elif defined (__AVR_AT90C8534__)
										#define	_CPU_NAME_	"AT90C8534"
	#elif defined (__AVR_AT90S8515__)
										#define	_CPU_NAME_	"AT90S8515"
	#elif defined (__AVR_AT90S4434__)
										#define	_CPU_NAME_	"AT90S4434"
	#elif defined (__AVR_AT90S4433__)
										#define	_CPU_NAME_	"AT90S4433"
	#elif defined (__AVR_AT90S4414__)
										#define	_CPU_NAME_	"AT90S4414"
	#elif defined (__AVR_ATtiny22__)
										#define	_CPU_NAME_	"ATtiny22"
	#elif defined (__AVR_ATtiny26__)
										#define	_CPU_NAME_	"ATtiny26"
	#elif defined (__AVR_AT90S2343__)
										#define	_CPU_NAME_	"AT90S2343"
	#elif defined (__AVR_AT90S2333__)
										#define	_CPU_NAME_	"AT90S2333"
	#elif defined (__AVR_AT90S2323__)
										#define	_CPU_NAME_	"AT90S2323"
	#elif defined (__AVR_AT90S2313__)
										#define	_CPU_NAME_	"AT90S2313"
	#elif defined (__AVR_ATtiny2313__)
										#define	_CPU_NAME_	"ATtiny2313"
	#elif defined (__AVR_ATtiny13__)
										#define	_CPU_NAME_	"ATtiny13"
	#elif defined (__AVR_ATtiny13A__)
										#define	_CPU_NAME_	"ATtiny13A"
	#elif defined (__AVR_ATtiny25__)
										#define	_CPU_NAME_	"ATtiny25"
	#elif defined (__AVR_ATtiny45__)
										#define	_CPU_NAME_	"ATtiny45"
	#elif defined (__AVR_ATtiny85__)
										#define	_CPU_NAME_	"ATtiny85"
	#elif defined (__AVR_ATtiny24__)
										#define	_CPU_NAME_	"ATtiny24"
	#elif defined (__AVR_ATtiny44__)
										#define	_CPU_NAME_	"ATtiny44"
	#elif defined (__AVR_ATtiny84__)
										#define	_CPU_NAME_	"ATtiny84"
	#elif defined (__AVR_ATtiny261__)
										#define	_CPU_NAME_	"ATtiny261"
	#elif defined (__AVR_ATtiny461__)
										#define	_CPU_NAME_	"ATtiny461"
	#elif defined (__AVR_ATtiny861__)
										#define	_CPU_NAME_	"ATtiny861"
	#elif defined (__AVR_ATtiny43U__)
										#define	_CPU_NAME_	"ATtiny43U"
	#elif defined (__AVR_ATtiny48__)
										#define	_CPU_NAME_	"ATtiny48"
	#elif defined (__AVR_ATtiny88__)
										#define	_CPU_NAME_	"ATtiny88"
	#elif defined (__AVR_ATtiny167__)
										#define	_CPU_NAME_	"ATtiny167"
	#elif defined (__AVR_ATmega8U2__)
										#define	_CPU_NAME_	"ATmega8U2"
	#else
		#error cpu not defined
	#endif


//??	#define	_AVR_CPU_NAME_	_CPU_NAME_

//************************************************************************
//*	Microchip pic32 chip names
#elif defined(__PIC32MX__)

	#define	E2END		0x0fff	//*	4 k of simulated EEPROM
	
	//************************************************************************
	//*	100 series

	#if defined(__32MX110F016B__)
		#define _CPU_NAME_	"32MX110F016B"
		#define	FLASHEND	(((16 - 4) * 1024L) - 1)
		#define	RAMEND		((4 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX110F016C__)
		#define _CPU_NAME_	"32MX110F016C"
		#define	FLASHEND	(((16 - 4) * 1024L) - 1)
		#define	RAMEND		((4 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX110F016D__)
		#define _CPU_NAME_	"32MX110F016D"
		#define	FLASHEND	(((16 - 4) * 1024L) - 1)
		#define	RAMEND		((4 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX120F032B__)
		#define _CPU_NAME_	"32MX120F032B"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX120F032C__)
		#define _CPU_NAME_	"32MX120F032C"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX120F032D__)
		#define _CPU_NAME_	"32MX120F032D"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX130F064B__)
		#define _CPU_NAME_	"32MX130F064B"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX130F064C__)
		#define _CPU_NAME_	"32MX130F064C"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX130F064D__)
		#define _CPU_NAME_	"32MX130F064D"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX150F128B__)
		#define _CPU_NAME_	"32MX150F128B"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX150F128C__)
		#define _CPU_NAME_	"32MX150F128C"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX1XX__

	#elif defined(__32MX150F128D__)
		#define _CPU_NAME_	"32MX150F128D"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX1XX__

	//************************************************************************
	//*	200 series

	#elif defined(__32MX210F016B__)
		#define _CPU_NAME_	"32MX210F016B"
		#define	FLASHEND	(((16 - 4) * 1024L) - 1)
		#define	RAMEND		((4 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX210F016C__)
		#define _CPU_NAME_	"32MX210F016C"
		#define	FLASHEND	(((16 - 4) * 1024L) - 1)
		#define	RAMEND		((4 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX210F016D__)
		#define _CPU_NAME_	"32MX210F016D"
		#define	FLASHEND	(((16 - 4) * 1024L) - 1)
		#define	RAMEND		((4 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX220F032B__)
		#define _CPU_NAME_	"32MX220F032B"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX220F032C__)
		#define _CPU_NAME_	"32MX220F032C"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX220F032D__)
		#define _CPU_NAME_	"32MX220F032D"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX230F064B__)
		#define _CPU_NAME_	"32MX230F064B"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX230F064C__)
		#define _CPU_NAME_	"32MX230F064C"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX230F064D__)
		#define _CPU_NAME_	"32MX230F064D"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX250F128B__)
		#define _CPU_NAME_	"32MX250F128B"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX250F128C__)
		#define _CPU_NAME_	"32MX250F128C"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX2XX__

	#elif defined(__32MX250F128D__)
		#define _CPU_NAME_	"32MX250F128D"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX2XX__

	//************************************************************************
	//*	300 series

	#elif defined(__32MX320F032H__)
		#define _CPU_NAME_	"32MX320F032H"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX320F064H__)
		#define	_CPU_NAME_	"32MX320F064H"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX320F128H__)
		#define	_CPU_NAME_	"32MX320F128H"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX340F128H__)
		#define	_CPU_NAME_	"32MX340F128H"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX340F256H__)
		#define	_CPU_NAME_	"32MX340F256H"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX340F512H__)
		#define	_CPU_NAME_	"32MX340F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX320F128L__)
		#define	_CPU_NAME_	"32MX320F128L"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX340F128L__)
		#define	_CPU_NAME_	"32MX340F128L"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX360F256L__)
		#define	_CPU_NAME_	"32MX360F256L"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX3XX__

	#elif defined(__32MX360F512L__)
		#define	_CPU_NAME_	"32MX360F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX3XX__

	//************************************************************************
	//*	400 series

	#elif defined(__32MX420F032H__)
		#define	_CPU_NAME_	"32MX420F032H"
		#define	FLASHEND	(((32 - 4) * 1024L) - 1)
		#define	RAMEND		((8 * 1024L) - 1)
		#define	__PIC32MX4XX__

	#elif defined(__32MX440F128H__)
		#define	_CPU_NAME_	"32MX440F128H"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX4XX__

	#elif defined(__32MX440F256H__)
		#define	_CPU_NAME_	"32MX440F256H"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX4XX__

	#elif defined(__32MX440F512H__)
		#define	_CPU_NAME_	"32MX440F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX4XX__

	#elif defined(__32MX440F128L__)
		#define	_CPU_NAME_	"32MX440F128L"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX4XX__

	#elif defined(__32MX460F256L__)
		#define	_CPU_NAME_	"32MX460F256L"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX4XX__

	#elif defined(__32MX460F512L__)
		#define	_CPU_NAME_	"32MX460F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX4XX__

	//************************************************************************
	//*	500 series

	#elif defined(__32MX534F064H__)
		#define	_CPU_NAME_	"32MX534F064H"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX564F064H__)
		#define	_CPU_NAME_	"32MX564F064H"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX564F128H__)
		#define	_CPU_NAME_	"32MX564F128H"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX575F256H__)
		#define	_CPU_NAME_	"32MX575F256H"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX575F512H__)
		#define	_CPU_NAME_	"32MX575F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX534F064L__)
		#define	_CPU_NAME_	"32MX534F064L"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((16 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX564F064L__)
		#define	_CPU_NAME_	"32MX564F064L"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX564F128L__)
		#define	_CPU_NAME_	"32MX564F128L"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX575F256L__)
		#define	_CPU_NAME_	"32MX575F256L"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX5XX__

	#elif defined(__32MX575F512L__)
		#define	_CPU_NAME_	"32MX575F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX5XX__

	//************************************************************************
	//*	600 series

	#elif defined(__32MX664F064H__)
		#define	_CPU_NAME_	"32MX664F064H"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX664F128H__)
		#define	_CPU_NAME_	"32MX664F128H"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX675F256H__)
		#define	_CPU_NAME_	"32MX675F256H"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX675F512H__)
		#define	_CPU_NAME_	"32MX675F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX695F512H__)
		#define	_CPU_NAME_	"32MX695F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((128 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX664F064L__)
		#define	_CPU_NAME_	"32MX664F064L"
		#define	FLASHEND	(((64 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX664F128L__)
		#define	_CPU_NAME_	"32MX664F128L"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX675F256L__)
		#define	_CPU_NAME_	"32MX675F256L"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX675F512L__)
		#define	_CPU_NAME_	"32MX675F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX6XX__

	#elif defined(__32MX695F512L__)
		#define	_CPU_NAME_	"32MX695F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((128 * 1024L) - 1)
		#define	__PIC32MX6XX__

	//************************************************************************
	//*	700 series

	#elif defined(__32MX764F128H__)
		#define	_CPU_NAME_	"32MX764F128H"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX775F256H__)
		#define	_CPU_NAME_	"32MX775F256H"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX775F512H__)
		#define	_CPU_NAME_	"32MX775F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX795F512H__)
		#define	_CPU_NAME_	"32MX795F512H"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((128 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX764F128L__)
		#define	_CPU_NAME_	"32MX764F128L"
		#define	FLASHEND	(((128 - 4) * 1024L) - 1)
		#define	RAMEND		((32 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX775F256L__)
		#define	_CPU_NAME_	"32MX775F256L"
		#define	FLASHEND	(((256 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX775F512L__)
		#define	_CPU_NAME_	"32MX775F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((64 * 1024L) - 1)
		#define	__PIC32MX7XX__

	#elif defined(__32MX795F512L__)
		#define	_CPU_NAME_	"32MX795F512L"
		#define	FLASHEND	(((512 - 4) * 1024L) - 1)
		#define	RAMEND		((128 * 1024L) - 1)
		#define	__PIC32MX7XX__

	//************************************************************************
	#else
		#error CPU type is unknown, cpudefs.h needs to have additions
	#endif

#else
	#error unknown cpu architecture
#endif

//************************************************************************
#ifndef _CPU_NAME_
	#define	_CPU_NAME_	"Unknown"
#endif
