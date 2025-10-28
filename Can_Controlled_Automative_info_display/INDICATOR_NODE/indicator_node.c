// indicator_node.c
/***************************************************************************************************************
INDICATOR NODE:

The `INDICATOR NODE` is responsible for controlling the vehicle's left and right indicator lights.
It continuously monitors the CAN message from the `MAIN NODE`, and whenever the indicator switch is pressed 
at `MAIN NODE`, the corresponding signal is received and execute with respect to it. Based on this input, 
`INDICATOR NODE` activates the left or right indicator LEDs to represents the vehicle's turn signal status.


***************************************************************************************************************/

#include <LPC21xx.h>
#include "indicator_node_defines.h"

#include "../lcd_defines.h"
#include "../lcd.h"

void (*indicator)(void) = reset_indicator;

volatile CAN_F rxFrame;


volatile indMode rxFlag = IND_OFF;

// CAN RX ISR
void can_rx_isr(void) __irq
{
	// CAN receive ISR
	while(READBIT(C1ICR, RI_BIT)==0);
	// Can frame received
	
	// If the received CANID = 1
	// i.e; The message is receiving from MAIN NODE, which sends the indicator status
	// if other than CANID=1 message is received in this INDICATOR node; ignore it
	
	if ((C1RID==LEFT_IND_ID) || (C1RID==RIGHT_IND_ID))
	{
		rxFrame.ID = C1RID;
		rxFrame.bfv.RTR = C1RFS>>RTR_BIT;
		rxFrame.bfv.DLC = C1RFS>>DLC_BIT;

		if (rxFrame.bfv.RTR == 0) // Check the received frame type
		{
			// if the received frame type is data frame
			rxFrame.data1 = C1RDA;
			rxFrame.data2 = C1RDB;
		}		
		reset_indicator();
		if (rxFrame.ID == LEFT_IND_ID)
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
		else if (rxFrame.ID == RIGHT_IND_ID)
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
	}
	
	// Clear Receive buffer
	C1CMR |= 1<<RRB_BIT;
	
	// Clear the interrupt
	VICVectAddr = 0;
}


int main()
{
	Init_Timer0();
	InitCAN1();
	// CANacceptID(1);
	InitCAN1Int(can_rx_isr, VIC_CAN1_RX_CHNO);

	//InitLCD();

	CmdLCD(DSP_ON_CUR_OFF);

	WRITEBYTE(IODIR0, LED_AL_0_0, 0xFF);

	while(1)
	{
		indicator();
	}

}
