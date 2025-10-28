// tdelay_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"


int main()
{
	Init_Timer0();
	
	while(1)
	{
		delay_us(1);
		delay_us(10);
		delay_us(100);
		delay_us(1000);
		delay_ms(100);
		delay_ms(500);
		delay_s(1);
		delay_s(5);
	}
}
