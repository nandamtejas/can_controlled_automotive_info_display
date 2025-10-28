// utils.h

#ifndef _MAIN_NODE_UTILS_H
#define _MAIN_NODE_UTILS_H

#include "../types.h"

void indicator_blink(int32 ind_status, volatile uint32 *indBlink);
void display_fuel_indicator(float fuelPerc);
	
#endif
