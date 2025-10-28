// RTC.h

#ifndef _RTC_H
#define _RTC_H

#include "types.h"

void InitRTC(void);
void setDate(uint32 day, uint32 month, uint32 year);
void setTime(uint32 hour, uint32 min, uint32 sec);
void displayRTC(void);

#endif
