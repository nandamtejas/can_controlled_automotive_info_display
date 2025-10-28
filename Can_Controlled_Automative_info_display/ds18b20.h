// ds18b20.h

#ifndef _DS18B20_H
#define _DS18B20_H

#include "types.h"

uint8 resetPulse(void);
void writeBit(uint8 Dbit);
void writeByte(uint8 Dbyte);
uint8 readBit(void);
uint8 readByte(void);
float readTemp(void);
void displayTemp(float *temp);

#endif
