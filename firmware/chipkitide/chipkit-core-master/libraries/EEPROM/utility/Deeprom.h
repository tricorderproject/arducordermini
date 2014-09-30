/************************************************************************/
/*																		*/
/*	Deeprom.h	--	eeprom routine declarations							*/
/*																		*/
/************************************************************************/
/*	Author: 	Oliver Jones											*/
/*	Copyright 2011, Digilent Inc.										*/
/************************************************************************/
/*
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
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	09/01/2011(OliverJ): created										*/
/*																		*/
/************************************************************************/

#include <stdint.h>

#define fTrue 1
#define fFalse 0

typedef uint32_t BOOL;

typedef union {
	struct {
		//Bit deterimes whether a segment is usable or not
		unsigned valid : 1;
		//Bit dtermines whether the segment is in use or free to be used
		unsigned taken : 1;
		unsigned address : 22;
		unsigned data : 8;
	} temp;
	unsigned int data;
} eeSeg;

BOOL setMax(uint32_t value);
uint32_t getMax();
void clearEeprom();
BOOL writeEeprom(uint32_t address, uint8_t data);
BOOL readEeprom(uint32_t address, uint8_t * data);
BOOL putEeprom(eeSeg * eeprom, uint32_t address, uint8_t data);
BOOL getEeprom(eeSeg * eeprom, uint32_t address, uint8_t * data);
uint32_t putBuffer(eeSeg * eeprom, uint8_t * buffer);
void getBuffer(eeSeg * eeprom, uint8_t * buffer);
eeSeg pack(uint32_t address, uint8_t data);
uint32_t getAddress(eeSeg segment);
uint8_t getData(eeSeg segment);
BOOL getValid(eeSeg segment);
BOOL getTaken(eeSeg segment);