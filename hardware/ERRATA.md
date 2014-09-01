Known Errata
======

**Motherboard**  
*rev0*
- Two sets of power pins on the PIC32 are switched (15/16, and 62/65)
- SDA1/SCL1 are missing 4.7k pull-up resistors on the motherboard.  These were added to the Magnetic Field Sensor r0 board as optional in the interum.
- The FT232 lights appear to be on when the USB is connected, but the device (3.3V main bus) is off.  This should leave VCCIO at 0V, which might lead to unpredictable behaviour, or might be plain out of specifications. 
- Radiation sensor connector (CN3) still needs a part number.  The holes may have to be increased slightly, and location may have to shift a little. 
- Capacitive touch sensor (CN4) likely needs a bit more mechanically steady mounting, perhaps a different connector near the bottom of the board/USB connector.  If the same connector is used, the pads for the mount point need to be extended out about 0.5mm . 
- A few pixels on the OLED occasionally stay on when the power switch is off.  Double check that the pull-down on the 13V boost enable line is functioning properly. 

**Capacitive Touch Sensor board**  
*rev0*
- R1 should be 75k (not 75 ohms)
- C1 should be Hirose DF12 series.  (I believe DF12(3.0)-10DS-0.5V(86) )

*rev1*
- The parts likely need to be moved to the bottom of the board to ease placing a dialectric overlay on top.
- The RTC should be moved to the motherboard, if possible. 
- Connector to motherboard (CN1) likely needs to be more mechanically stable to keep the board in place during touch events, perhaps by using a different connector near the bottom of the board/USB connector, or mount points to the case.  I believe the pads for the mount points on this connector have already been extended out 0.5mm, incase the same connector is reused. 

**Sensor Board: Magnetic Field/IMU board**  
*rev0*
- SJ1 I2C address solder jumper for the MPU9150 should be set to bridge 3.3V instead of GND by default, to set the MPU9150 address to 0x69 by default, and not conflict with the real time clock. 

**Sensor Board: Atmospheric Sensor board**  
*rev0*
- MiCS-6814 gas sensor needs 3 MOSFETs to drive the 3 heater lines, since the current will be more than the PIC32 lines can supply. 
- BMP180 sensor uncontacted, but I think the sensors I purchased from China during the BMP180 shortage may be counterfeit. 
- Analog and digital pins for the MiCS-6814 were swapped on the sensor board header

**Sensor Board: Lightning/UV/Sound board**  
*rev0*

**Sensor Board: Radiation board (with mini speaker)**  
*rev0*
- Connector to motherboard (CN1) still needs a part number.  The holes may have to be increased slightly, and location may have to shift a little. 
- R7 part number needs to be specified
- SJ1 VREF source for audio out needs to be determined (and SJ1 removed in the next revision)
- Precision pull-up resistors for output signals (OUT, SIG, NS)

**Sensor Board: Spectroscopy / Thermal Camera board**  
*rev0*

