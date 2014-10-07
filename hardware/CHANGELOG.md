Change Log
======

**Motherboard**  
*rev1* (Oct 2014)
- Corrected two sets of switched power pins on the PIC32 (15/16, and 62/65)
- Added missing 4.7k pull-up resistors (R17, R18) for SDA1/SCL1.  These were previously added to the Magnetic Field Sensor r0 board as optional in the interim.  
- ERRATA NOTE: The FT232 lights appear to be on when the USB is connected, but the device (3.3V main bus) is off.  This should leave VCCIO at 0V, which might lead to unpredictable behaviour, or might be plain out of specifications. RESPONSE: Options are to power the FT232 internally, with VCCIO at its 3.3V output, which should pull-up UART lines, and may provide unintended partial power to PIC32.  This might lead to unpredictable boot-up behaviour of the PIC32, so we'll leave this as-is for now. 
- Radiation sensor connector (CN3) part number identified as Samtec PHF-106-01-L-S.  Drills on connector increased to 1.2mm to accommodate. 
- Capacitive touch sensor (CN4) has alignment holes, and there is no low-profile (<3mm) yet mechanically stable connector option that I'm aware of.  Added four 2mm mount points at the four corners of the capacitive touch board, intended for 4x M2 machine screws, and 4x nylon stand-offs (3mm height). 
- Board sized increased slightly -- 4mm in width and 4mm in width.  This was required to accommodate the mount points. 
- ERRATA: A few pixels on the OLED occasionally stay on when the power switch is off.  Double check that the pull-down on the 13V boost enable line is functioning properly.  RESPONSE: After a fresh look, the architecture of the FAN5331 booster circuit appears to allow the VIN current to pass through when the booster is disabled.  This has the undesired effect of leaving 3-5V on the OLED voltage line when the device should be powered down, both drawing power and leaving a few stray pixels illuminated.  Changed the FAN5331 voltage input source from VIN to 3.3V, after the primary TPS63001 buck/boost regulator.  This lowers efficiency a bit, but means the FAN5331 booster will have no voltage source when the device is off, and will prevent power drain. 
- Moved capacitive touch board connector to a lower position, to facilitate the mount holes on the mating connector not intersecting with the capacitive touch wheel. 
- Increased and oversized power trace widths to OLED, and CC3000.  There weren't any previous issues with the CC3000, but the OLED would flicker if the display was full white, full intensity (~300ma).  

