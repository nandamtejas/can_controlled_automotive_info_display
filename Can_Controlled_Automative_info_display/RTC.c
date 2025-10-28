// RTC.c

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "RTC_defines.h"

void InitRTC(void)
{
	// RTC Initialization
	CCR = CLKEN;
	
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
}

void setDate(uint32 day, uint32 month, uint32 year)
{
	// SET DATE
	DOM = day;
	MONTH = month;
	YEAR = year;
}
	
void setTime(uint32 hour, uint32 min, uint32 sec)
{
	// SET TIME
	HOUR = hour;
	MIN = min;
	SEC = sec;
}

void displayRTC(void)
{
	// display time
	
	CmdLCD(GOTO_LINE1_POS0);
	
	// display date
	CharLCD((DOM/10)+'0');
	CharLCD((DOM%10)+'0');
	CharLCD('/');
	CharLCD((MONTH/10)+'0');
	CharLCD((MONTH%10)+'0');
	CharLCD('/');
	CharLCD(((YEAR/100)/10)+'0');
	CharLCD(((YEAR/100)%10)+'0');
	CharLCD(((YEAR%100)/10)+'0');
	CharLCD((YEAR%10)+'0');
	
	// display DAY
	switch(DOW)
	{
		case 0: StringLCD("  SUN"); break;
		case 1: StringLCD("  MON"); break;
		case 2: StringLCD("  TUE"); break;
		case 3: StringLCD("  WED"); break;
		case 4: StringLCD("  THU"); break;
		case 5: StringLCD("  FRI"); break;
		case 6: StringLCD("  SAT"); break;
	}
	
	CmdLCD(GOTO_LINE2_POS0);
	
	// Display Time
	CharLCD((HOUR/10)+'0');
	CharLCD((HOUR%10)+'0');
	CharLCD(':');
	CharLCD((MIN/10)+'0');
	CharLCD((MIN%10)+'0');
	CharLCD(':');
	CharLCD((SEC/10)+'0');
	CharLCD((SEC%10)+'0');
	
}
