// can_text_rx.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../lcd_defines.h"
#include "../lcd.h"
#include "../CAN_defines.h"	 // E:\V24HE9T2\ARM\LABSHIFT_V4\CAN_defines.h // E:\v24he9t2\ARM\LABSHIFT_v4\tests\can_text_rx.c
#include "../CAN.h"

CAN_F rxFrame;

#define RXID 2

void can_rx_isr(void) __irq
{
	// CAN receive ISR
	while(READBIT(C1ICR, RI_BIT)==0);

	if (C1RID == 	RXID)
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
	InitCAN1Int(can_rx_isr, VIC_CAN1_RX_CHNO);	

	InitLCD();
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(GOTO_LINE1_POS0);
	StringLCD("CANA RX TEST");
	delay_s(1);

	while(1)
	{
		CmdLCD(GOTO_LINE1_POS0);
		StringLCD("Recvd: ");
		S32LCD(rxFrame.data1);
	}

}
