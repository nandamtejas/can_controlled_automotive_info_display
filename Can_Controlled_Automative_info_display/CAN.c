// CAN.c
#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "CAN_defines.h"
#include "CAN.h"

void InitCAN1(void)
{
	// CAN Init

	// CFG p0.25 as CAN_RX1 pin
	CFG_PORT_PIN(PINSEL1, CAN_RX1_PIN, CAN_RX1_PIN_FUNC);
	
	C1MOD |= 1<<RM_BIT;
	
	// Modify the AFMR bits
	AFMR |= 1<<AccBP;
	AFMR &= ~(1<<AccOff);
	
	// BTR values
	C1BTR = (SAM_VAL<<23) | ((TSEG2-1)<<20) | ((TSEG1-1)<<16) | ((SJW-1)<<14) | (BRP-1);
	
	C1MOD &= ~(1<<RM_BIT);
}

void CANacceptID(int32 ID)
{
	int32 i;
	// setting to filtering the CAN IDs
	volatile uint32 *AF_RAM = (volatile uint32 *)AFRAM_BASE;

	// 1. Disable the Acceptance Filter by setting AccBP = 1
    //    and AccOff = 0.
    AFMR = 0x01;

	// 2. Clear the Acceptance Filter lookup tables.
    //    This example clears the entire RAM block for simplicity.
    for (i = 0; i < 512; i++) {
        AF_RAM[i] = 0;
    }

	// 3. Define the lookup table entry.
    //    The format for a standard ID entry is:
    //    [31:29] Reserved
    //    [28:18] ID (11 bits)
    //    [17:16] Controller No. (00=CAN1, 01=CAN2)
    //    [15:11] Reserved
    //    [10:0]  ID (11 bits)
	*AF_RAM = ((ID&0x7FF) | ((ID&0x7FF)<<18));

	// 4. Configure the start and end addresses of the lookup table.
    SFF_sa = AFRAM_BASE;
    SFF_GRP_sa = AFRAM_BASE + 4; // Start of Group Table (after our single entry)
    EFF_sa = AFRAM_BASE + 4; // Start of Extended Frame Table
    EFF_GRP_sa = AFRAM_BASE + 4; // Start of Extended Group Table
    ENDofTable = AFRAM_BASE + 4; // End of the configured table

	AFMR = 0x00;
}


void InitCAN1Int(void (*can_isr)(void)__irq, uint32 CAN_CHNO)
{
	// CAN Interrupt
	
	// VIC Settings
	// Enable VIC channel
	VICIntEnable |= (1<<CAN_CHNO);
	// Select CAN channel as IRQ interrupt type
	VICIntSelect &= ~(1<<CAN_CHNO);
	
	// Considering IRQ type as V-IRQ
	VICVectCntl2 = ((1<<5) | CAN_CHNO);
	VICVectAddr2 = (uint32)can_isr;
	
	// CAN settings
	C1IER = 1<<RIE_BIT;
}


void CAN1_Tx(CAN_F frame)
{
	// Transmit frame 
	
	// Check for the Transfer buffer is ready to transmit the frame
	while(READBIT(C1GSR, TBS_BIT) != 1);
	// Tansfer buffer is cleared
	// CAN is ready to tramsmit the frame
	
	C1TID1 = frame.ID;
	
	WRITEBIT(C1TFI1, RTR_BIT, frame.bfv.RTR);
	WRITEBYTE(C1TFI1, DLC_BIT, frame.bfv.DLC);
	
	// Check if the frame is message frame or remote frame
	if (frame.bfv.RTR == 0)
	{
		// Frame is data/message frame
		C1TDA1 = frame.data1;
		C1TDB1 = frame.data2;
	}
	
	// Now the frame is ready to transmit, raise Transmit request in Transmit buffer 1 
	C1CMR |= (1<<STB1_BIT) | (1<<TR_BIT);
	
	// wait till transmission is complete
	while(READBIT(C1GSR, TCS_BIT) != 1);
	
	// Transmission is completed
}

void CAN1_Rx(CAN_F *frame)
{
	// Receive Frame
	
	// Check the Receive buffer has received message
	while(READBIT(C1GSR, RBS_BIT) == 0);
	// Receive buffer has message
	
	frame->ID = C1RID;
	frame->bfv.RTR = READBIT(C1RFS, RTR_BIT);
	frame->bfv.DLC = READBYTE(C1RFS, DLC_BIT);
	
	// check if the received frame is message frame or data frame, if message frame extract data
	if (frame->bfv.RTR == 0)
	{
		frame->data1 = C1RDA;
		frame->data2 = C1RDB;
	}
	
	// Now release the buffer
	C1CMR |= 1<<RRB_BIT;
}

int32 CAN1_Rx_ID(CAN_F *frame, uint32 ID)
{
	// Receive Frame with ID
	
	// Check the Receive buffer has received message
	if (READBIT(C1GSR, RBS_BIT) == 1)
	{
		// Receive buffer has message
		
		if (C1RID != ID)
			return -1;
		
		frame->ID = C1RID;
		frame->bfv.RTR = READBIT(C1RFS, RTR_BIT);
		frame->bfv.DLC = READBYTE(C1RFS, DLC_BIT);
		
		// check if the received frame is message frame or data frame, if message frame extract data
		if (frame->bfv.RTR == 0)
		{
			frame->data1 = C1RDA;
			frame->data2 = C1RDB;
		}
		
		// Now release the buffer
		C1CMR |= 1<<RRB_BIT;
		return 0;
	}
	return -1;
}
