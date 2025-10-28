// utils.c

#include <LPC21xx.h>
#include "fuel_node_defines.h"
#include "utils_defines.h"

void Init_Timer1(void)
{
	// Timer 1 Init 
	// Timer 1 is for Interrupt purpose
	// T1TCR = TCR_ENABLE;
	
	// Raise interrupt on match
	T1MCR = MCR_MRI0;
}

void InitTimer1Int(void (*timer_isr)(void) __irq)
{
	// Init Timer 1 Interrupt
	
	// VIC Block settings
	
	// Enable the timer interrupt
	VICIntEnable |= (1<<TIMER1_VIC_CHNO);
	
	// Select Interrupt as IRQ
	VICIntSelect &= ~(1<<TIMER1_VIC_CHNO);
	
	// Considering V-IRQ
	VICVectCntl0 = (1<<5) | TIMER1_VIC_CHNO;
	VICVectAddr0 = (uint32)timer_isr;

	// Timer 1 settings
	T1TCR = TCR_RESET;
	T1PR = PR_1mSEC-1;
	T1TC = 0;
	T1MR0 = TxPERIOD;
	T1TCR = TCR_ENABLE;
}
