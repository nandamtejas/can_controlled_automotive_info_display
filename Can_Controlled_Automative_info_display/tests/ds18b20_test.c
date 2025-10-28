// ds18b20_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../lcd_defines.h"
#include "../lcd.h"
#include "../ds18b20_defines.h"
#include "../ds18b20.h"


int main()
{
	float temp;

	Init_Timer0();
	InitLCD();

	// IODIR0 |= 1<<21;

	CmdLCD(DSP_ON_CUR_OFF);
	StringLCD("  DS18B20 test  ");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
	while(1)
	{
		
		CmdLCD(GOTO_LINE1_POS0);
		StringLCD("TEMP: ");

		IOCLR0 = 1<<21;
		temp = readTemp();
		
		F32LCD(temp, 2);
		CharLCD(0xDF);
		CharLCD('C');
	}
}
