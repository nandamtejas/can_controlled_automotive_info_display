// utils.c

#include <LPC21xx.h>
#include "main_node_defines.h"
#include "utils_defines.h"

void indicator_blink(int32 ind_status, volatile uint32 *indBlink)
{
	int32 ind_symbol;
	
	StringLCD("  ");
	
	if (ind_status != IND_OFF)
	{
		CmdLCD(SHIFT_CUR_LEFT);
		if (ind_status == IND_LEFT)
		{
			ind_symbol = LEFT_IND_SYMBOL;
			CmdLCD(SHIFT_CUR_LEFT);
		}
		else if (ind_status == IND_RIGHT)
			ind_symbol = RIGHT_IND_SYMBOL;
		
		if (*indBlink == 1)
			CharLCD(ind_symbol);
		else
			CharLCD(' ');
		*indBlink = !(*indBlink);
		delay_ms(150);
	}
}

void display_fuel_indicator(float fuelPerc)
{
	int32 i;
	int32 nslice;
	int32 tslice = 100/FUEL_LEVEL_IND;
	

	nslice = (int32)fuelPerc / (int32)FUEL_LEVEL_IND;
	
	CharLCD(2);
	for (i=0; i<tslice; i++)
	{
		if ((nslice > 0) && (i < nslice))
			CharLCD(3);
		else
			CharLCD(' ');
	}
	
	CharLCD(93);
}
/*
void display_fuel_indicator(float *fuelPerc)
{
	// Function to read fuel level indicator
	int32 i;
	int32 npoint;
	int32 tpoint;
	

	tpoint = 100 / FUEL_LEVEL_IND;
	
	npoint = (int32)fuelPerc / (int32)FUEL_LEVEL_IND;
	CharLCD(2);
	for (i=0; i<tpoint; i++)
	{
		if (i < npoint)
			CharLCD(3);
		else
			CharLCD(' ');
	}
	
	CharLCD(93);
}
*/