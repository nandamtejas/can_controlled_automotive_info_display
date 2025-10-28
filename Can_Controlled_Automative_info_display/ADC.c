// ADC.c

#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "ADC_defines.h"

void InitADC_CH0(void)
{
	// Init ADC with CHNO 0
	
	// cfg ADC pin as AIN0
	CFG_PORT_PIN(PINSEL1, ADC_PIN_NO, ADC_PINFUNC);
	
	// cfg ADCR register
	ADCR = SEL_CHNO_0 | (CLKDIV_VAL<<CLKDIV_BIT) | (1<<PDN_BIT);
}

void readADC(uint8 chNo, float *Vin, uint32 *adcVal)
{
	// Read ADC values
	
	// clear the previous channel selection
	WRITEBYTE(ADCR, 0, ~0xFF);
	
	// select the channel and start conversion
	ADCR = (ADCR &~ ((1<<PDN_BIT) | (7<<START_BITS))) | ( (1<<PDN_BIT) | (1<<START_BITS) );
	
	// wait for conversion
	while(READBIT(ADDR, DONE_BIT) == 0);
	// Conversion completed
	// Fetch the result value
	*adcVal = ((ADDR>>RESULT_BITS)&0x3FF);
	*Vin = (*adcVal * STEP_SIZE);
			
}
