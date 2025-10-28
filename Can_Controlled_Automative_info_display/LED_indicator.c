// LED_indicator.c

#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "LED_indicator_defines.h"

void reset_indicator(void)
{
	// Reset Indicator

	// Reset the indicator
	WRITEBYTE(IOPIN0, LED_AL_0_0, 0xFF);
}

void right_indicator()
{
	uint8 temp;
	
	// RIGHT INDICATOR (LEFT ROTATE)
	if (READBYTE(IOPIN0, 0)==0xFF)
		WRITEBIT(IOPIN0, 0, 0);
	else if (READBYTE(IOPIN0, 0)==0)
		WRITEBYTE(IOPIN0, 0, 0xFF);
	else
	{
		temp = (IOPIN0&0xFF)<<1;
		WRITEBYTE(IOPIN0, 0, temp);
	}
	
	delay_ms(100);
}
void left_indicator()	
{
	uint8 temp;
	
	// LEFT INDICATOR (RIGHT ROTATE)
	
	if (READBYTE(IOPIN0, 0)==0xFF)
		WRITEBIT(IOPIN0, 7, 0);
	else if (READBYTE(IOPIN0, 0)==0)
		WRITEBYTE(IOPIN0, 0, 0xFF);
	else
	{
		temp = ((IOPIN0&0xFF)>>1);
		WRITEBYTE(IOPIN0, 0, temp);
	}
	
	delay_ms(100);
}



