// tdelay.c
/*
	This file contains the timer0 delay definitions
*/
#include <LPC21xx.h>
#include "types.h"
#include "tdelay_defines.h"

void Init_Timer0(void)
{
	T0TCR = TCR_ENABLE;
	T0MCR = MCR_MRS0;
}

void delay_us(uint32 dlyUS)
{
	T0TCR = TCR_RESET;
	T0PR = PR_1uSEC-1;
	T0TC = 0;
	T0MR0 = dlyUS;
	T0TCR = TCR_ENABLE;
	while((T0TCR>>0)&1);
}

void delay_ms(uint32 dlyMS)
{
	T0TCR = TCR_RESET;
	T0PR = PR_1mSEC-1;
	T0TC = 0;
	T0MR0 = dlyMS;
	T0TCR = TCR_ENABLE;
	while((T0TCR>>0)&1);
}

void delay_s(uint32 dlyS)
{
	T0TCR = TCR_RESET;
	T0PR = PR_1SEC-1;
	T0TC = 0;
	T0MR0 = dlyS;
	T0TCR = TCR_ENABLE;
	while((T0TCR>>0)&1);
}
