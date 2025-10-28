// CAN_test_rx.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../CAN_defines.h"
#include "../CAN.h"

CAN_F rxFrame;
#define CAN_STATUS_LED 16
/*
void can_isr(void)
{
	// CAN ISR
	// Check for interrupt Received
	if (READBIT(C1ICR, RI_BIT))
	{
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
		
		C1CMR |= 1<<RRB_BIT;
		
		WRITEBIT(IOPIN0, CAN_STATUS_LED, (~(READBIT(IOPIN0, CAN_STATUS_LED))));
		
		WRITEBIT(C1ICR, RI_BIT, 0);
	}
	C1IER |= (1<<RIE_BIT);
	VICVectAddr=0;
}
*/

int main()
{
	Init_Timer0();
	InitCAN1();
	//InitCAN1Int(can_isr);
	
	WRITEBIT(IODIR0, CAN_STATUS_LED, 1);
	
	while(1)
	{
		//delay_s(1);
		CAN1_Rx(&rxFrame);
		IOPIN0 ^= 1<<CAN_STATUS_LED;
	}
}
