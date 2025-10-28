// lcd.h

#ifndef _LCD_H
#define _LCD_H

#include "types.h"

void WriteLCD(uint8 byte);
void CmdLCD(uint8 cmd);
void InitLCD(void);
void CharLCD(uint8 ascii);
void StringLCD(uint8 *str);
void U32LCD(uint32 num);
void S32LCD(int32 num);
void F32LCD(float fnum, uint8 precision);
void HexLCD(int32 num);
void BuildCGRAM(const uint8 *bytes, uint32 byteLen);
void BuildCGRAM_v2(const uint8 *bytes, uint32 index);
void BuildCGRAMLUT(const uint8 (*bytes)[8], uint32 nElem);

#endif
