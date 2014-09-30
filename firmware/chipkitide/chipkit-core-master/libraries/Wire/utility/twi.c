/*
  twi.c - TWI/I2C library for Wiring & Arduino (chipKit line)
  Copyright (c) 2011 Digilent.  All right reserved.
  Based on source Copyright (c) 2006 Nicholas Zambetti.
  Author: Oliver Jones
  Revision Date: 5/20/2011

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

#define OPT_SYSTEM_INTERNAL
#define OPT_BOARD_INTERNAL
#include <p32xxxx.h>
#include <sys/attribs.h>
#include <p32_defs.h>
#include <pins_arduino.h>
#include "twi.h"

static volatile uint8_t twi_state;
static uint8_t twi_slarw;

static volatile uint8_t TW_STATUS;

static void (*twi_onSlaveTransmit)(void);
static void (*twi_onSlaveReceive)(uint8_t*, int);

static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_masterBufferIndex;
static uint8_t twi_masterBufferLength;

static uint8_t twi_txBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_txBufferIndex;
static volatile uint8_t twi_txBufferLength;

static uint8_t twi_rxBuffer[TWI_BUFFER_LENGTH];
static volatile uint8_t twi_rxBufferIndex;
static volatile uint8_t twi_rxBufferLength;

static volatile uint8_t twi_error;

/* Forware declarations for internal utility functions.
*/
uint32_t twi_computeBrg(uint32_t frqReq);
void __attribute__((interrupt(),nomips16)) I2CHandler(void);


/* Variables used to manage access to the I2C controller and interrupt
** registers.
*/
static p32_i2c *	ptwi;			// pointer to I2C controller registers
static p32_regset *	pregIfs;		// pointer to the interrupt flag register
static p32_regset *	pregIec;		// pointer to the interrupt enable register		
static uint32_t		bitBus;			// IEC/IFS bit for BUS interrupt
static uint32_t		bitSlv;			// IEC/IFS bit for SLAVE interrupt
static uint32_t		bitMst;			// IEC/IFS bit for MASTER interrupt

/* 
 * Function twi_init
 * Desc     readys twi pins and sets twi bit rate
 * Input    none
 * Output   none
 */
void twi_init(p32_i2c * ptwiT, uint8_t irqBus, uint8_t irqSlv, uint8_t irqMst, uint8_t vec)
{
	p32_regset *	pregIpc;
	int				bnVec;

	ptwi = ptwiT;

    setIntVector(_TWI_VECTOR, I2CHandler);

	/* Compute the address of the interrupt enable and interrupt flag registers.
	** This can be computed from the IRQ numbers. The assumption is made that
	** all of the enable and flag bits for the I2C interrupts for this port are
	** in the same IEC and IFS registers.
	*/
	pregIec = ((p32_regset *)&IEC0) + (irqBus / 32);	// interrupt enable control register
	pregIfs = ((p32_regset *)&IFS0) + (irqBus / 32);	// interrupt flag register

	bitBus	= 1 << (irqBus % 32);	// bus interrupt flag/enable bit
	bitSlv	= 1 << (irqSlv % 32);	// slave interrupt flag/enable bit
	bitMst	= 1 << (irqMst % 32);	// master interrupt flag/enable bit

	/* Compute the address of the interrupt priority control register
	** for the specified interrupt vector. Each IPC register contains the
	** the priority bits for four vectors. Each byte of an IPC registger contains
	** the priority and sub-priority bits arranged such that bits 0-1 are
	** the sub-priority, bits 2-4 the priority, and bits 5-7 unused.
	*/
	pregIpc = ((p32_regset *)&IPC0) + (vec / 4);

	/* Compute the bit position of the interrupt priority bits for
	** this interrupt vector.
	*/
	bnVec = 8 * (vec % 4);

	/* Set the interrupt priority and sub-priority bits.
	*/
	pregIpc->clr = (0x1F << bnVec);
	pregIpc->set = ((_TWI_IPL << 2) + _TWI_SPL) << bnVec;

	/* Clear the interrupt flags and enable I2C interrupts
	*/
	pregIfs->clr = bitBus + bitSlv + bitMst;
	pregIec->set = bitBus + bitSlv + bitMst;

	/* Enable the interrupt controller and turn on clock stretching.
	*/
	ptwi->ixCon.reg = (1 << _I2CCON_ON) | (1 << _I2CCON_STREN);

	/* Set the baud rate generator for the default frequency.
	*/
	ptwi->ixBrg.reg = twi_computeBrg(TWI_FREQ);

}

/* 
 * Function twi_slaveInit
 * Desc     sets slave address
 * Input    none
 * Output   none
 */
void twi_setAddress(uint8_t address)
{
  // set twi slave address
	ptwi->ixAdd.reg = address;

}

/* 
 * Function twi_readFrom
 * Desc     attempts to become twi bus master and read a
 *          series of bytes from a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes to read into array
 * Output   number of bytes read
 */
uint8_t twi_readFrom(uint8_t address, uint8_t* data, uint8_t length)
{
  unsigned int i;

  if (address < 8)
  {
	  return 0;
  }

  // Ensure data will fit into buffer
  if (TWI_BUFFER_LENGTH < length){
    return 0;
  }

  // reset error state (0xFF.. no error occured)
  twi_error = 0xFF;

  // initialize buffer iteration vars
  twi_masterBufferIndex = 0;
  twi_masterBufferLength = length;

   // send start condition
  TW_STATUS = TW_START;
  twi_slarw = (address << 1) + 1;
  ptwi->ixCon.set = (1 << _I2CCON_SEN);

  // wait for read operation to complete
  while(TW_IDLE != TW_STATUS)
  {
	asm volatile("nop");
  }

  // Set length to what was actualy sent
  length = twi_masterBufferIndex;

  // copy twi buffer to data
  for(i = 0; i < length; i++){
    data[i] = twi_masterBuffer[i];
  }

  return length;
}

/* 
 * Function twi_writeTo
 * Desc     attempts to become twi bus master and write a
 *          series of bytes to a device on the bus
 * Input    address: 7bit i2c device address
 *          data: pointer to byte array
 *          length: number of bytes in array
 *          wait: boolean indicating to wait for write or not
 * Output   0 .. success
 *          1 .. length to long for buffer
 *          2 .. address send, NACK received
 *          3 .. data send, NACK received
 *          4 .. other twi error (lost bus arbitration, bus error, ..)
 */
uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait)
{
  uint8_t i;

  if(address < 8)
  {
	  return 0;
  }

  // ensure data will fit into buffer
  if (TWI_BUFFER_LENGTH < length)
  {
    return 1;
  }

  // reset error state (0xFF.. no error occured)
  twi_error = 0xFF;

  // initialize buffer iteration vars
  twi_masterBufferIndex = 0;
  twi_masterBufferLength = length;
  
  // copy data to twi buffer
  for (i = 0; i < length; ++i)
  {
    twi_masterBuffer[i] = data[i];
  }
  
  // send start condition
  TW_STATUS = TW_START;
  twi_slarw = (address << 1);
  ptwi->ixCon.set = (1 << _I2CCON_SEN);

  // wait for write operation to complete
  while (wait && TW_IDLE != TW_STATUS)
  {
	asm volatile("nop");
  }

  if (twi_error == 0xFF)
  {
    return 0;	// success
  }
  else if (twi_error == TW_MT_SLA_NACK)
  {
    return 2;	// error: address send, nack received
  }
  else if (twi_error == TW_MT_DATA_NACK)
  {
    return 3;	// error: data send, nack received
  }
  else
  {
    return 4;	// other twi error
  }
}

/* 
 * Function twi_transmit
 * Desc     fills slave tx buffer with data
 *          must be called in slave tx event callback
 * Input    data: pointer to byte array
 *          length: number of bytes in array
 * Output   1 length too long for buffer
 *          2 not slave transmitter
 *          0 ok
 */
uint8_t twi_transmit(uint8_t* data, uint8_t length)
{
  uint8_t i;

  // ensure data will fit into buffer
  if(TWI_BUFFER_LENGTH < length)
  {
    return 1;
  }
  
  // set length and copy data into tx buffer
  twi_txBufferLength = length;
  for(i = 0; i < length; ++i
 ){
    twi_txBuffer[i] = data[i];
  }
  
  return 0;
}

/* 
 * Function twi_attachSlaveRxEvent
 * Desc     sets function called before a slave read operation
 * Input    function: callback function to use
 * Output   none
 */
void twi_attachSlaveRxEvent( void (*function)(uint8_t*, int) )
{
  twi_onSlaveReceive = function;
}

/* 
 * Function twi_attachSlaveTxEvent
 * Desc     sets function called before a slave write operation
 * Input    function: callback function to use
 * Output   none
 */
void twi_attachSlaveTxEvent( void (*function)(void) )
{
  twi_onSlaveTransmit = function;
}

/* ---------- Internal Utility Functions ---------- */
/* 
 * Function twi_computeBrg
 * Desc     compute the baud rate value for a given I2C clock frequency
 * Input    requested clock frequency
 * Output   value to load into baud rate generator register
 */

uint32_t twi_computeBrg(uint32_t frqReq)
{
	uint32_t	tpgd;

	/* The formula is slightly modified from what is shown in the
	** PIC32 Family Reference Manual. It is rewritten as follows:
	**	I2CxBRG = (PBCLK / (2*FSCK) - (PBCLK * Tpgd)) - 2;
	** The calculation of (PBCLK * Tpgd) will overflow if done in
	** the obvious way: ((PBCLK * 104) / 1000000000)
	** It is done instead as follows:
	*/
	tpgd = ((CLK_PBUS / 8) * 104) / 125000000;

	return (CLK_PBUS / (2 * TWI_FREQ) - tpgd) - 2;
}		

/* ---------- Interrupt Service Routine ---------- */
/* 
 * Function I2CHandler
 * Desc     Handler for slave and master interrupt requests
 * Input    none
 * Output   none
 */
void __attribute__((interrupt(),nomips16)) I2CHandler(void)
{
	if (ptwi->ixStat.reg & (1 << _I2CSTAT_BCL) ) 
	{
		// Bus collision occurred exit
		ptwi->ixStat.clr = (1 << _I2CSTAT_BCL);
		TW_STATUS = TW_ARB_LOST;
	}
	else if (pregIfs->reg & bitMst)
	{
		asm volatile("nop");
	}
	else if (pregIfs->reg & bitSlv)
	{
		// Slave interrupt occurred
		if(!(ptwi->ixStat.reg & (1 << _I2CSTAT_DA)))
		{
			// Clear receive register
			twi_slarw = ptwi->ixRcv.reg;

			if(twi_slarw & 1)
			{
				// Data was Requested
				TW_STATUS = TW_ST_SLA;
			}
			else
			{
				// Data will be recieved
				TW_STATUS = TW_SR_SLA;
			}
		}
	}

	switch (TW_STATUS)
	{
		case TW_START: // sent start condition
			// Check if data will be sent or received
			if (twi_slarw & 1)
			{
				TW_STATUS = TW_MR_SLA;
			}
			else
			{
				TW_STATUS = TW_MT_SLA;
			}
			ptwi->ixTrn.reg = twi_slarw;
			break;

		case TW_STOP:
			// Set status to idle to exit while loop
			TW_STATUS = TW_IDLE;
			break;

		//Master Transmitter
		case TW_MT_SLA:
  		    // Check if adress was acked or nacked
			if (ptwi->ixStat.reg & (1 << _I2CSTAT_ACKSTAT))
			{	
				twi_error = TW_MT_SLA_NACK;		
				TW_STATUS = TW_STOP;
				ptwi->ixCon.set = (1 << _I2CCON_PEN);
				break;
			}
			TW_STATUS = TW_MT_DATA; //No break, immediately send data
		case TW_MT_DATA:
			if (ptwi->ixStat.reg & (1 << _I2CSTAT_ACKSTAT))
			{
				// Data was nacked send stop bit
				twi_error = TW_MT_DATA_NACK;
				TW_STATUS = TW_STOP;
				ptwi->ixCon.set = (1 << _I2CCON_PEN);
			}
			else
			{
				// Check if there is more data to send
				if (twi_masterBufferIndex < twi_masterBufferLength)
				{
					// More data to send load transmit buffer
					ptwi->ixTrn.reg = twi_masterBuffer[twi_masterBufferIndex];
					twi_masterBufferIndex++;
				}
				else
				{
					// No more data to send
					TW_STATUS = TW_STOP;
					// Send stop condition
					ptwi->ixCon.set = (1 << _I2CCON_PEN);
				}
			}	
			break;
		
		//Master Receiver
		case TW_MR_SLA: // address sent, ack received
			// Check if adress was acked or nacked
			if (ptwi->ixStat.reg & (1 << _I2CSTAT_ACKSTAT))
			{	
				twi_error = TW_MR_SLA_NACK;		
				TW_STATUS = TW_STOP;
				ptwi->ixCon.set = (1 << _I2CCON_PEN);
				break;
			}
			ptwi->ixCon.set = ( 1 << _I2CCON_RCEN);
			TW_STATUS = TW_MR_DATA;
			break;

		case TW_MR_DATA: // data received
			// put byte into buffer
			twi_masterBuffer[twi_masterBufferIndex] = ptwi->ixRcv.reg;
			twi_masterBufferIndex++;
			// ack if more bytes are expected, otherwise nack
			if (twi_masterBufferIndex < twi_masterBufferLength)
			{
				ptwi->ixCon.clr = (1 << _I2CCON_ACKDT); // Send Ack
				ptwi->ixCon.set = (1 << _I2CCON_ACKEN);
				TW_STATUS = TW_MR_ACK_SENT;
			}
			else
			{		
				ptwi->ixCon.set = (1 << _I2CCON_ACKDT); // Send Nack
				ptwi->ixCon.set = (1 << _I2CCON_ACKEN);
				TW_STATUS = TW_MR_NACK_SENT;
			}
			break;

		case TW_MR_ACK_SENT:
			// Set I2C for recieving
			ptwi->ixCon.set = (1 << _I2CCON_RCEN);
			TW_STATUS = TW_MR_DATA;
			break;

		case TW_MR_NACK_SENT:
			// Send stop bit
			ptwi->ixCon.set = (1 << _I2CCON_PEN);
			TW_STATUS = TW_STOP;
			break;

		//Slave Reciever
		case TW_SR_SLA:
			twi_rxBufferIndex = 0;
			TW_STATUS = TW_SR_DATA;
			// Release clock line
			ptwi->ixCon.set = (1 << _I2CCON_SCLREL);
			break;

		case TW_SR_DATA:
			twi_rxBuffer[0] = ptwi->ixRcv.reg;
			twi_onSlaveReceive(twi_rxBuffer, 1);
			// Release clock line
			ptwi->ixCon.set = (1 << _I2CCON_SCLREL);
			ptwi->ixStat.clr = (1 << _I2CSTAT_I2COV) | (1 << _I2CSTAT_RBF);
			break;

		//Slave Transmitter
		case TW_ST_SLA:
			twi_txBufferIndex = 0;
			twi_txBufferLength = 0;
			TW_STATUS = TW_ST_DATA;
			
			twi_onSlaveTransmit();

			if (0 == twi_txBufferLength)
			{
				twi_txBufferLength = 1;
				twi_txBuffer[0] = 0x00;
			} // No break, immediately send data
		case TW_ST_DATA:
			if (ptwi->ixStat.reg & (1 << _I2CSTAT_ACKSTAT))
			{
				ptwi->ixCon.set = (1 << _I2CCON_SCLREL);
				break; // Master requires no more data
			}
			else
			{
				// Check if there is more data to send otherwise send null
				if(twi_txBufferIndex < twi_txBufferLength)
				{
					ptwi->ixTrn.reg = twi_txBuffer[twi_txBufferIndex++];			
				}
				else
				{
					ptwi->ixTrn.reg = 0;
				}
				ptwi->ixCon.set = (1 << _I2CCON_SCLREL);
			}
			break;

		case TW_ARB_LOST: // lost bus arbitration
			TW_STATUS = TW_IDLE;
			twi_error = TW_ARB_LOST;
			break;
	}
	pregIfs->clr = bitBus + bitSlv + bitMst;
}


