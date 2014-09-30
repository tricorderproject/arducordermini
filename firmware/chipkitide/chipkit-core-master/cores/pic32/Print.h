/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

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

#ifndef Print_h
#define Print_h

#ifndef _SYS_INTTYPES_H_
	#include <inttypes.h>
#endif
#ifndef	_STDIO_H_
	#include <stdio.h> // for size_t
#endif

#include "WString.h"

#define PRINT_DEC 10
#define PRINT_HEX 16
#define PRINT_OCT 8
#define PRINT_BIN 2
#define PRINT_BYTE 0

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

class Print
{
  private:
	void printNumber(unsigned long, uint8_t);
	void printFloat(double, uint8_t);
  public:
	virtual void write(uint8_t) = 0;
	virtual void write(const char *str);
	virtual void write(const uint8_t *buffer, size_t size);

	void print(const String &);
	void print(const char[]);
	void print(char, int = PRINT_BYTE);
	void print(unsigned char, int = PRINT_BYTE);
	void print(int, int = PRINT_DEC);
	void print(unsigned int, int = PRINT_DEC);
	void print(long, int = PRINT_DEC);
	void print(unsigned long, int = PRINT_DEC);
	void print(double, int = 2);

	void println(const String &s);
	void println(const char[]);
	void println(char, int = PRINT_BYTE);
	void println(unsigned char, int = PRINT_BYTE);
	void println(int, int = PRINT_DEC);
	void println(unsigned int, int = PRINT_DEC);
	void println(long, int = PRINT_DEC);
	void println(unsigned long, int = PRINT_DEC);
	void println(double, int = 2);
	void println(void);
};

#endif
