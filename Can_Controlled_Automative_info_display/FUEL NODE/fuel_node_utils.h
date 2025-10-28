// utils.h

#ifndef _FUEL_NODE_UTILS_H
#define _FUEL_NODE_UTILS_H

void Init_Timer1(void);
void InitTimer1Int(void (*timer_isr)(void) __irq);

#endif
