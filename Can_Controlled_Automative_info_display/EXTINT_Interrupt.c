// EXTINT_Interrupt.c

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "EXTINT_Interrupt_defines.h"
#include "CAN_defines.h"
#include "CAN.h"

void InitEXTInt(void (*EINT0ISR)(void) __irq, void (*EINT1ISR)(void) __irq)
{
	// EXTINT interrput Init function
	
	// VIC init
	VICIntEnable |= (1<<EINT0_VIC_CHNO) | (1<<EINT1_VIC_CHNO);
	VICIntSelect &= ~((1<<EINT0_VIC_CHNO) | (1<<EINT1_VIC_CHNO)) ;
	
	// EINT0 VIC settings
	VICVectCntl0 = (1<<5) | EINT0_VIC_CHNO;
	VICVectAddr0 = (uint32)EINT0ISR;
	
	// EINT1 VIC settings
	VICVectCntl1 = (1<<5) | EINT1_VIC_CHNO;
	VICVectAddr1 = (uint32)EINT1ISR;
	
	// CFG EINT0 pins as EINT functionality
	CFG_PORT_PIN(PINSEL1, EINT0_PIN, EINT0_PINFUNC);
	CFG_PORT_PIN(PINSEL0, EINT1_PIN, EINT1_PINFUNC);
	
	// EXTINT settings
	// Enabling EINT0 and EINT1
	EXTINT = 3<<0; 
	
	// selecting Edge trigger mode for EINT0 and EINT1
	EXTMODE = 3<<0;
	
	// selecting falling edge polarity
	EXTPOLAR = 0;
}
