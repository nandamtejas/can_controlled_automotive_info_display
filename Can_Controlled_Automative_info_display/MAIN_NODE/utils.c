// utils.c

#include <LPC21xx.h>
#include "main_node_defines.h"
#include "utils_defines.h"

void indicator_blink(int ind_symbol, volatile uint32 *indBlink)
{
	if (ind_symbol == RIGHT_IND_SYMBOL)
		CmdLCD(SHIFT_CUR_RIGHT);
	
	if (*indBlink == 1)
		CharLCD(ind_symbol);
	else
		CharLCD(' ');
	*indBlink = !(*indBlink);
}
