// ADC_defines.h

#ifndef _ADC_DEFINES_H
#define _ADC_DEFINES_H

#include "types.h"

// ADC Calculations
#include "CLK_defines.h"

#define ADC_CLK (3*1e6)
#define CLKDIV_VAL (uint32)((PCLK/ADC_CLK)-1)
#define VREF 3.3 // Vref = 3.3V
#define RESOLUTION 10 // 10bit ADC resolution
#define STEP_SIZE (VREF/((1<<RESOLUTION)-1))

// ADCR SFR defines
#define SEL_CHNO_0 (1<<0)
#define SEL_CHNO_1 (1<<1)
#define SEL_CHNO_2 (1<<2)
#define SEL_CHNO_3 (1<<3)

#define CLKDIV_BIT 8  // CLKDIV BITS (8bits)
#define PDN_BIT 21 // PDN BIT, 1->ADC Operational; 0-> ADC Power down
#define START_BITS 24 // (3 bits) Start bit value should be 1


// ADGDR SFR defines
#define RESULT_BITS 6 // 6:15 bits (10 bits) result
#define DONE_BIT 31 // This bit indicates the ADC conversion completed


#define ADC_PIN_NO 27 // ADC pin number P0.27
#define ADC_PINFUNC 1 // ADC pin function 1
#define ADC_CH_NO 0 // ADC Channel number 0

#endif
