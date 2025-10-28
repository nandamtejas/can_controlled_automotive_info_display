// ADC_test.c

#include <LPC21xx.h>
#include "../types.h"
#include "../defines.h"
#include "../delay.h"
#include "../ADC_defines.h"
#include "../ADC.h"
#include "../lcd_defines.h"
#include "../lcd.h"


int main()
{
	uint32 dVal;
	float eAR;
	Init_Timer0();
	InitLCD();
	InitADC_CH0();
	
	CmdLCD(DSP_ON_CUR_OFF);
	StringLCD(" ADC TEST ");
	delay_s(1);
	CmdLCD(CLEAR_LCD);
	
	while(1)
	{
		readADC(ADC_CH_NO, &eAR, &dVal);
		CmdLCD(GOTO_LINE1_POS0);
		StringLCD("dVal: ");
		S32LCD(dVal);
		CmdLCD(GOTO_LINE2_POS0);
		StringLCD("eAR: ");
		F32LCD(eAR, 3);
	}
}
