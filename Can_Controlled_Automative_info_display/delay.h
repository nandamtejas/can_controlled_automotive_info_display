// delay.h
/*
	#############################################
	# This header file is applicable for both   #
	# Hardware Delays (Timer delays) and        #
	# Software delays (User-defined delays)     #
	#############################################
*/


#include "types.h"

#ifndef _DELAY_H
#define _DELAY_H

void Init_Timer0(void);
void delay_us(uint32 dlyUS);
void delay_ms(uint32 dlyMS);
void delay_s(uint32 dlyS);

#endif
