/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 *
 * Description
 *  Unlike the AVR micrcontrollers used on the Arduino boards,
 *  the PIC32 microcontrollers used on the chipKIT boards don't
 *  have internal EEPROM memory. Instead, FLASH memory is used
 *  to simulate EEPROM. There are two major differences between
 *  FLASH and EEPROM. 1) EEPROM is byte erasable and rewritable.
 *  With FLASH an entire page must be erased before any byte can
 *  be rewritten. 2) FLASH can't be erased and rewritten as many
 *  times as EEPROM. After a limited number of erase/write
 *  cycles, the FLASH page will 'wear out', and additional
 *  writes may not store the correct value. EEPROM can also
 *  wear out, but it typically takes many more writes to wear
 *  it out.
 *  To address these issues, the chipKIT EEPROM library uses a
 *  page of FLASH memory to simulate EEPROM.
 *  The FLASH is used as content addressable memory. A 32-bit
 *  word is used for each simulated EEPROM byte. The word stores
 *  both the EEPROM address and the byte value. When a write is
 *  performed, the page is searched for an unused location, when
 *  one is found, the address/data is written to that word. When
 *  reading, the page is searched for the address, and then the
 *  value is returned. If a location is being rewritten, the old
 *  location is marked as invalid and a new location written as
 *  described above.
 *  If there are no unused locations available in the page when a
 *  write is being attempted, then the page must be erased before
 *  the value can be written. The contents of the page is copied
 *  to a memory buffer, the page erased, and then the old values
 *  plus new value are written back to the FLASH page. This
 *  method reduces the number of times that the page must be
 *  erased and rewritten.
 *  The PIC32 FLASH page size is 4K (4096) bytes, which allows for
 *  simulation of up to 1K (1024) bytes of EEPROM.
 *  There is a degenerate case, however, that can lead to rapid
 *  wearout of the FLASH page being used. If all of the simulated
 *  EEPROM locations have been written (i.e. all simulated EEPROM
 *  addresses have been written to), then each additional write
 *  results in the page being erased and rewritten, eliminating
 *  the benefit of the wear leveling algorithm being used.
 *  This library uses two methods to help reduce this problem.
 *  The first is adding the clear() method. This method erases
 *  the flash page, erasing all simulated EEPROM. If a sketch has
 *  been run that uses a large amount of the simulated EEPROM,
 *  clear() should be used when that EEPROM content is not longer
 *  needed. This will reduce the number of values in the EEPROM
 *  that need to be preserved, reducing the number of times that
 *  the FLASH page will have to be erased and rewritten. The
 *  second method used to reduce the liklihood of premature FLASH
 *  wearout is to limit the default EEPROM memory size. By default
 *  this library implements 512 bytes of simulated EEPROM. This
 *  reserves at least half of the FLASH page to handle rewrites.
 *  It is possible to increase the simulated EEPROM size if a
 *  larger amount is needed. Two new methods have been added to
 *  accomodate this. getMaxAddress returns the current size of
 *  the simulated EEPROM. setMaxAddress allows setting it to
 *  a different size up to 1024.  
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;

void setup()
{
}

void loop()
{
  // need to divide by 4 because analog inputs range from
  // 0 to 1023 and each byte of the EEPROM can only hold a
  // value from 0 to 255.
  int val = analogRead(0) / 4;
  
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.
  EEPROM.write(addr, val);
  
  // advance to the next address.  there are 512 bytes in 
  // the EEPROM, so go back to 0 when we hit 512.
  addr = addr + 1;
  if (addr == 512)
    addr = 0;
  
  delay(100);
}
