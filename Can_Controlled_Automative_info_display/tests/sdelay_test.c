// sdelay_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"

#define LED_STATUS_PIN 2 // P0.2

int main()
{
	uint32 i = 10;
	IODIR0 = 1<<LED_STATUS_PIN;
	
	while(1)
	{
		IOSET0=1<<LED_STATUS_PIN;
		delay_us(i);
		IOCLR0=1<<LED_STATUS_PIN;
		delay_us(i);
		
		i = (i*10)%(1000000);
		i = (i==0)?10:i;
	}
	
	
}
