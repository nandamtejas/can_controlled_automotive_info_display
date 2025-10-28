// CAN_test_tx.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../CAN_defines.h"
#include "../CAN.h"

#define SW 0

int main()
{
	CAN_F frame;
	
	Init_Timer0();
	InitCAN1();
	
	frame.ID = 1;
	frame.bfv.RTR = 0;
	frame.bfv.DLC = 4;
	frame.data1 = 1;
	frame.data2 = 0;
	
	while(1)
	{
		if (READBIT(IOPIN0, SW) == 0)
		{
			CAN1_Tx(frame);
			frame.data1 = ((frame.data1 + 1) % 26 );
			frame.ID = (frame.ID == 2) ? 1 : 2;
			delay_ms(500);
		}
	}
	
}
