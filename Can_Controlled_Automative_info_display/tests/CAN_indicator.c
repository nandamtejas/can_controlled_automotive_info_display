// CAN_indicator.c

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "LED_indicator_defines.h"
#include "LED_indicator.h"
#include "CAN_defines.h"
#include "CAN.h"

void (*indicator)(void) = reset_indicator;

volatile CAN_F rxFrame;
typedef enum {IND_OFF, IND_LEFT, IND_RIGHT}	indMode;

volatile indMode rxFlag = IND_OFF;

// CAN RX ISR
void can_rx_isr(void) __irq
{
	// CAN receive ISR
	while(READBIT(C1ICR, RI_BIT)==0);
	// Can frame received

	rxFrame.ID = C1RID;
	rxFrame.bfv.RTR = C1RFS>>RTR_BIT;
	rxFrame.bfv.DLC = C1RFS>>DLC_BIT;

	if (rxFrame.bfv.RTR == 0) // Check the received frame type
	{
		// if the received frame type is data frame
		rxFrame.data1 = C1RDA;
		rxFrame.data2 = C1RDB;
	}
	
	// Clear Receive buffer
	C1CMR |= 1<<RRB_BIT;

	reset_indicator();
	if (rxFrame.data1 == 'l')
	{
		if (rxFlag==IND_LEFT)
		{
			 indicator = reset_indicator;
			 rxFlag=IND_OFF;
		}
		else{
			indicator = left_indicator;
			rxFlag=IND_LEFT;
		}

	}
	else if (rxFrame.data1 == 'r')
	{
		if (rxFlag==IND_RIGHT)
		{
			 indicator = reset_indicator;
			 rxFlag=IND_OFF;
		}
		else{
			indicator = right_indicator;
			rxFlag=IND_RIGHT;
		}

	}

	VICVectAddr = 0;

}


int main()
{
	Init_Timer0();
	InitCAN1();
	InitCAN1Int(can_rx_isr);

	WRITEBYTE(IODIR0, LED_AL_0_0, 0xFF);

	while(1)
	{
		indicator();
	}

}
