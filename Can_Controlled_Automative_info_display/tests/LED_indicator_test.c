// LED_indicator_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../LED_indicator_defines.h"
#include "../LED_indicator.h"

#define SW_AL_0_8 8 // P0.8 Switch
#define SW_AL_0_9 9 // P0.9 Switch

int main()
{
	void (*indicator)(void) = (void *)0;
	
	// Cfg P0.0 to P0.7 pins as GPIO out pins
	WRITEBYTE(IODIR0, LED_AL_0_0, 255);
	
	Init_Timer0();
	
	while(1)
	{
		if (((IOPIN0>>SW_AL_0_8)&1) == 0)
		{
			// LEFT Indicator
			indicator = left_indicator;
		}
		else if (((IOPIN0>>SW_AL_0_9)&1) == 0)
		{
			// RIGHT Indicator
			indicator = right_indicator;
		}
		else
		{
			WRITEBYTE(IOPIN0, LED_AL_0_0, 0);
			indicator = (void*)0;
		}
		if (indicator != (void*)0)
			indicator();
	}
}
