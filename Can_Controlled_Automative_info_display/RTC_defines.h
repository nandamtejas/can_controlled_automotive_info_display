// RTC_defines.h

#ifndef _RTC_DEFINES_H
#define _RTC_DEFINES_H

#include "types.h"
#include "CLK_defines.h"

// CCR SFR defines
#define CLKEN (1<<0)

// RTC Prescaler SFR values
#define PREINT_VAL ((uint32)(PCLK/32768)-1)
#define PREFRAC_VAL (PCLK - ((PREINT+1)*32768))

#endif
