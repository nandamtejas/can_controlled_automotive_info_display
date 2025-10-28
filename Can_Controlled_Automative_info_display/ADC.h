// ADC.h

#ifndef _ADC_H
#define _ADC_H

#include "types.h"

void InitADC_CH0(void);
void readADC(uint8 chNo, float *Vin, uint32 *adcVal);

#endif
