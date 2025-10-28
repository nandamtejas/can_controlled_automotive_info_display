// lcd.c

#include <LPC21xx.h>
#include "types.h"
#include "defines.h"
#include "delay.h"
#include "lcd_defines.h"


void WriteLCD(uint8 byte)
{
	// Function to write byte in LCD
	
	// Write byte into LCD
	WRITEBYTE(IOPIN0, LCD_DATA, byte);
	// To write into LCD, RW set to LOW
	IOCLR0 = 1<<LCD_RW;
	
	// after writing the data byte into LCD, we need to trigger Enable pin in Falling Edge @1us
	//	then wait for 1.44ms for completing the operation
	IOSET0 = 1<<LCD_EN;
	delay_us(1);
	IOCLR0 = 1<<LCD_EN;
	delay_ms(2);
}

void CmdLCD(uint8 cmd)
{
	// Function to write Command in LCD
	
	// To write command to LCD, RS should be LOW
	IOCLR0 = 1<<LCD_RS;
	WriteLCD(cmd);
}

void InitLCD(void)
{
	// Function for LCD Initialization
	
	// We assume the VDD pin connected to LCD is +5V
	delay_ms(15);
	
	// CFG LCD_DATA pins as GPIO output pins
	WRITEBYTE(IODIR0, LCD_DATA, 0xFF);
	WRITEBIT(IODIR0, LCD_RS, 1);
	WRITEBIT(IODIR0, LCD_RW, 1);
	WRITEBIT(IODIR0, LCD_EN, 1);
	
	// Following the Initialization steps mentioned in DATASHEET
	CmdLCD(0x30);
	delay_ms(4); // 4ms
	delay_us(100); // 0.1ms
	
	CmdLCD(0x30);
	delay_us(110);
	
	CmdLCD(0x30);
	
	// Initialization steps are completed
	// Next initialization steps for 8BIT-2LINE mode as follows:
	
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_BLINK);
	CmdLCD(CLEAR_LCD);
	CmdLCD(ENTRY_MODE_SET_RIGHT);
	CmdLCD(GOTO_LINE1_POS0);
	
}
	
void CharLCD(uint8 ascii)
{
	// Function to write Char byte data or ascii value
	
	// To write data into LCD, RS should be HIGH
	IOSET0 = 1<<LCD_RS;
	WriteLCD(ascii);
}
	
void StringLCD(uint8 *str)
{
	// Function to write string into LCD
	
	while(*str)
		CharLCD(*str++);
}
	
void U32LCD(uint32 num)
{
	// Function to write unsigned number into LCD
	
	// LCD can only write 1byte data, hence the number to be mandatorily converted into string (perform itoa)
	int32 i=0;
	uint8 str_num[17];
	
	// Special case: num = 0
	if (num == 0)
	{
		CharLCD('0');
		return;
	}
	
	// store each digits into str_num array
	while (num)
	{
		str_num[i++] = (num%10)+'0'; // Conversion of integer digit to ascii digit by adding '0' (48) to it
		num = num/10;
	}
	
	// write each char in str_num 
	for (--i; i>=0; i--)
	{
		CharLCD(str_num[i]);
	}
}
	
void S32LCD(int32 num)
{
	// Function to write signed number into LCD
	
	// Check for negative number, if yes, display '-' sign in LCD
	if (num < 0)
	{
		CharLCD('-');
		num = -num;
	}
	
	// Call the U32LCD function, as the steps to write a positive integer is same
	U32LCD(num);
}

void F32LCD(float fnum, uint8 precision)
{
	// Function to write floating point numbers
	uint32 num;
	uint8 i=0;
	// Check for negative numbers, if yes, display '-' sign in LCD
	if (fnum<0)
	{
		CharLCD('-');
		fnum = -fnum;
	}
	
	// integral part of the number is written in the LCD first
	num = (uint32)fnum;
	U32LCD(num);
	
	// display '.' for indicating decimal number
	CharLCD('.');
	
	// now display the fractional part
	for(i=0; i<precision; i++)
	{
		fnum = fnum-num;
		fnum = fnum*10;
		num = (uint32)fnum;
		CharLCD(num+'0');
	}
}
	
void HexLCD(int32 num)
{
	// Function to display HEX of number
	uint32 u32num = (uint32)num;
	uint8 hex_arr[8];
	uint32 rem;
	int32 i=0;
	
	// Special case: zero
	if (u32num == 0)
	{
			StringLCD("0x0");
			return;
	}
	
	while(u32num)
	{
		rem = u32num%16;
		hex_arr[i++] = (rem<10) ? rem+'0' : ('A' + (rem-10));
		u32num = u32num / 16;
	}
	
	// Display Prefix
	StringLCD("0x");
	
	// Display digits in reverse order
	for (--i; i>=0; i--)
	{
		CharLCD(hex_arr[i]);
	}
	
}
	
void BuildCGRAM(const uint8 *bytes, uint32 byteLen)
{
	// Function to write byteLen bytes in CGRAM
	uint32 i;
	
	// The cursor should point to CGRAM memory
	CmdLCD(GOTO_CGRAM_START);
	// Now the cursor points to CGRAM memory
	
	// Then enable the LCD in command mode by setting the RS register 
	IOSET0 = 1<<LCD_RS;
	
	for (i=0; i<byteLen; i++)
	{
		WriteLCD(bytes[i]);
	}
	
	// now return the cursor pointer to DDRAM display
	CmdLCD(GOTO_LINE1_POS0);
}

void BuildCGRAM_v2(const uint8 *bytes, uint32 index)
{
	/*
	Version 2
	This function is to create custom symbols to be written in CGRAM of LCD
	**NOTE: This function should be used in setup mode**
	
	Inputs:
		- *bytes -> array of 8 bytes
		- index -> CGRAM index
	*/
	uint32 i;
	
	// The LCD cursor which is pointing to DDRAM memory (display),  should point to the desired index position of CGRAM memory
	
	CmdLCD(GOTO_CGRAM_START+(8*index));
	
	// Then enable the LCD in command mode by clearing the RS register 
	IOSET0 = 1<<LCD_RS;
	
	// for write the bytes in CGRAM memory
	for (i=0; i<8; i++)
	{
		WriteLCD(bytes[i]);
	}
	
	// now return the cursor pointer to DDRAM display
	CmdLCD(GOTO_LINE1_POS0);
}
	
void BuildCGRAMLUT(const uint8 (*bytes)[8], uint32 nElem)
{
	/*
	This function is to create custom symbols to be written in CGRAM of LCD
	**NOTE: This function should be used in setup mode**
	
	Inputs:
		- *bytes -> pointer to an array of 8 elements
		- nElem -> no of elements / symbols (8 bytes) to write in CGRAM memory 
	*/
	uint32 i;
	
	// call BuildCGRAM_v2 to write into CGRAM
	for (i=0; i<nElem; i++)
	{
		BuildCGRAM_v2(bytes[i], i);
	}
}
