// CAN_test_rx_int.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../CAN_defines.h"
#include "../CAN.h"

CAN_F rxFrame;
#define CAN_STATUS_LED 16

void can_isr(void) __irq
{
	// CAN ISR
	// Check for interrupt Received
	while (READBIT(C1ICR, RI_BIT)==0);
	// CAN Frame received
	
	// Check from which frame it is received
	rxFrame.ID = C1RID;
	rxFrame.bfv.RTR = C1RFS>>RTR_BIT;
	rxFrame.bfv.DLC = C1RFS>>DLC_BIT;
	
	if (rxFrame.bfv.RTR == 0)
	{
		rxFrame.data1 = C1RDA;
		rxFrame.data2 = C1RDB;
	}
	
	C1CMR |= (1<<RRB_BIT);
	
	IOPIN0 ^= (1<<CAN_STATUS_LED);
	
	//C1IER |= (1<<RIE_BIT);
	//C1MOD |= 1<<RM_BIT;
	//C1GSR &= ~(1<<4);
	//C1MOD &= ~(1<<RM_BIT);
	VICVectAddr=0;
}


int main()
{
	Init_Timer0();
	InitCAN1();
	InitCAN1Int(can_isr, VIC_CAN1_RX_CHNO);
	
	WRITEBIT(IODIR0, CAN_STATUS_LED, 1);
	
	while(1)
	{
		delay_s(1);
	}
}
