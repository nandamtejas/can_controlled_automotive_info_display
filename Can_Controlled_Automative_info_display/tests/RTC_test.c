// RTC_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../defines.h"
#include "../delay.h"
#include "../lcd_defines.h"
#include "../lcd.h"
#include "../RTC_defines.h"
#include "../RTC.h"

int main()
{
	Init_Timer0();
	InitLCD();
	
	CmdLCD(DSP_ON_CUR_OFF);
	StringLCD("   RTC TEST  ");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
	
	InitRTC();
	setDate(20, 9, 2025);
	setTime(23, 00, 0);
		
	while(1)
	{
		displayRTC();
	}
}
