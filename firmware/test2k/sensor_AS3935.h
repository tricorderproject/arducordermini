/*
  AS3935.h - AS3935 Franklin Lightning Sensor™ IC by AMS library
  Copyright (c) 2012 Raivis Rengelis (raivis [at] rrkb.lv). All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef AS3935_h
#define AS3935_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <limits.h>

// register access macros - register address, bitmask
#define AS3935_AFE_GB		0x00, 0x3E
#define AS3935_PWD		0x00, 0x01
#define AS3935_NF_LEV		0x01, 0x70
#define AS3935_WDTH		0x01, 0x0F
#define AS3935_CL_STAT		0x02, 0x40
#define AS3935_MIN_NUM_LIGH	0x02, 0x30
#define AS3935_SREJ		0x02, 0x0F
#define AS3935_LCO_FDIV	0x03, 0xC0
#define AS3935_MASK_DIST	0x03, 0x20
#define AS3935_INT		0x03, 0x0F
#define AS3935_DISTANCE	0x07, 0x3F
#define AS3935_DISP_LCO	0x08, 0x80
#define AS3935_DISP_SRCO	0x08, 0x40
#define AS3935_DISP_TRCO	0x08, 0x20
#define AS3935_TUN_CAP		0x08, 0x0F

// other constants
#define AS3935_AFE_INDOOR	0x12
#define AS3935_AFE_OUTDOOR	0x0E

class AS3935
{
public:
	AS3935(int irq);
	void registerWrite(byte reg, byte mask, byte data);
	byte registerRead(byte reg, byte mask);
	void reset();
	bool calibrate();
	void powerDown();
	void powerUp();
	int interruptSource();
	void disableDisturbers();
	void enableDisturbers();
	int getMinimumLightnings();
	int setMinimumLightnings(int minlightning);
	int lightningDistanceKm();
	void setIndoors();
	void setOutdoors();
	int getNoiseFloor();
	int setNoiseFloor(int noisefloor);
	int getSpikeRejection();
	int setSpikeRejection(int srej);
	int getWatchdogThreshold();
	int setWatchdogThreshold(int wdth);
	void clearStats();
private:
	byte (*SPITransferFunc)(byte);
        byte _SPITransfer2(byte high, byte low);
	int  _CSPin, _IRQPin;
	byte _rawRegisterRead(byte reg);
	byte _ffsz(byte mask);
};

#endif
