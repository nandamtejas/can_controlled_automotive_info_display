// EXTINT_Interrupt.h

#ifndef _EXTINT_INT_H
#define _EXTINT_INT_H

void InitEXTInt(void (*EINT0ISR)(void) __irq, void (*EINT1ISR)(void) __irq);

// ISR's
void left_ind_ISR(void) __irq;
void right_ind_ISR(void) __irq;

#endif
