/*
  EEPROM.cpp - EEPROM library
  Copyright (c) 2006 David A. Mellis.  All right reserved.

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
//************************************************************************
//*	Edit History
//************************************************************************
//*	Dec 14,	2011	<MLS> Issue #165 the 'value' parameter in write() should be uint8_t.
//************************************************************************

/******************************************************************************
 * Includes
 ******************************************************************************/

extern "C" {
	#include "Deeprom.h"
}

#include "EEPROM.h"

//************************************************************************
EEPROMClass::EEPROMClass()
{
}

//************************************************************************
void EEPROMClass::setMaxAddress(unsigned int value)
{
	setMax(value);
}

//************************************************************************
unsigned int EEPROMClass::getMaxAddress()
{
	return getMax();
}

//************************************************************************
void EEPROMClass::clear()
{
	clearEeprom();
}

//************************************************************************
uint8_t EEPROMClass::read(unsigned int address)
{
	uint8_t data;

    readEeprom((uint32_t)address, &data);

	return data;
}

//************************************************************************
void EEPROMClass::write(unsigned int address, uint8_t value)
{
	writeEeprom((uint32_t)address, (uint8_t)value);
}

EEPROMClass EEPROM;