#include <LPC21xx.h>
#include "../types.h"
#include "../delay.h"
#include "../defines.h"
#include "../ADC_defines.h"
#include "../ADC.h"
#include "../lcd_defines.h"
#include "../lcd.h"


float fuelPerc=0;
float slice = 20;


void displayFuelInd(float fuelPerc)
{
	int32 i;
	int32 nslice;
	int32 tslice = 100/slice;
	

	nslice = (int32)fuelPerc / (int32)slice;
	S32LCD(nslice);
	CmdLCD(GOTO_LINE3_POS0);
	for (i=0; i<tslice; i++)
	{
		if ((nslice > 0) && (i < nslice))
			CharLCD(35);
		else
			CharLCD(' ');
	}
	
	CharLCD(93);
}

int main()
{
	float Vin;
	uint32 adcVal;
	
	Init_Timer0();
	InitADC_CH0();
	InitLCD();
	
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(GOTO_LINE1_POS0);
	StringLCD("  LCD ADC TEST ");
	delay_s(1);
	
	while(1)
	{
		CmdLCD(GOTO_LINE2_POS0);
		readADC(ADC_CH_NO, &Vin, &adcVal);
		
		fuelPerc = (Vin/VREF) * 100;
		
		displayFuelInd(fuelPerc);
		CharLCD(' ');
		F32LCD(fuelPerc, 2);
		delay_ms(500);
	}
}
