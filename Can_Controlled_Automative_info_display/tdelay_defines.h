// tdelay_defines.h

#ifndef _TDELAY_DEFINES_H
#define _TDELAY_DEFINES_H

// Timer Calculations
#include "CLK_defines.h"

#define PR_1SEC PCLK
#define PR_1mSEC (PCLK/1e3)
#define PR_1uSEC (PCLK/1e6)

// TCR SFR defines
#define TCR_ENABLE (1<<0)
#define TCR_RESET (1<<1)

// MCR SFR defines
#define MCR_MRI0 (1<<0) // Interrupt on match in MCR0
#define MCR_MRR0 (1<<1) // Reset on match in MCR0
#define MCR_MRS0 (1<<2) // Stop on match in MCR0


// VIC Block Timer interrupt channel numbers
#define TIMER0_VIC_CHNO  4
#define TIMER1_VIC_CHNO  5

#endif
