// lcd_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../lcd_defines.h"
#include "../lcd.h"


int main()
{
	Init_Timer0();
	
	InitLCD();
	
	CmdLCD(DSP_ON_CUR_NOBLINK);
	StringLCD("  LCD TEST  ");
	delay_ms(500);
	CmdLCD(DSP_ON_CUR_OFF);
	
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		U32LCD(25);
		delay_ms(500);
		
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE2_POS0);
		S32LCD(-32);
		delay_ms(500);
		
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE3_POS0);
		F32LCD(95.23, 3);
		delay_ms(500);
		
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE4_POS0);
		F32LCD(-25.6548945, 4);
		delay_ms(500);
		
		CmdLCD(CLEAR_LCD);
		HexLCD(25);
		delay_ms(500);
		
		CmdLCD(CLEAR_LCD);
		HexLCD(-26);
		delay_ms(500);
		
		
	}
}
