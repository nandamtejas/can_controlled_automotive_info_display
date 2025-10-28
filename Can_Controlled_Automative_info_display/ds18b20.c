// ds18b20.c

#include <LPC21xx.h>
#include "delay.h"
#include "defines.h"
#include "types.h"
#include "ds18b20_defines.h"
#include "lcd_defines.h"
#include "lcd.h"


uint8 resetPulse(void)
{
	// Reset pulse returns with presence pulse
	uint8 presence;
	
	IODIR1 |= 1<<DQ_PIN;
	// Host pulls data line to low for 480us
	IOCLR1 = 1<<DQ_PIN;
	delay_us(480);
	
	// release the data line by setting the data line to one and change to input mode 
	IOSET1 = 1<<DQ_PIN;
	IODIR1 &= ~(1<<DQ_PIN);
	
	// wait period of 50us and detect for presence pulse
	delay_us(70);
	
	// wait for presence pulse
	presence = ((IOPIN1>>DQ_PIN)&1);
	
	delay_us(410);
	return presence;
	
}

void writeBit(uint8 Dbit)
{
	// write bit to DS18B20
	// write bit should be sent within 60us
	
	IODIR1 |= 1<<DQ_PIN;
	// send a low pulse to start write operation
	IOCLR1 = 1<<DQ_PIN;
	
	if (Dbit)
	{
		// to write '1' pull down the data line and release after 10us
		delay_us(10);
		IOSET1 = 1<<DQ_PIN;
		// and wait for 50us
		delay_us(50);
	}
	else
	{			
		// if write '0', pull down the data line for 60us
		delay_us(60); // total 60us
	}	
	// after writing, set the line high
	IOSET1 = 1<<DQ_PIN;
	IODIR1 &= ~(1<<DQ_PIN);
	
	// wait for recovery time
	delay_us(5);
}

void writeByte(uint8 Dbyte)
{
	// Write byte function to write data bytes to DS18B20
	
	uint32 i;
	
	for (i=0; i<8; i++)
	{
		writeBit((Dbyte>>i)&1);
	}
}

uint8 readBit(void)
{
	// Read bit from DS18B20
	uint8 bit;
	// Host pull the data pin low to initiate read bit from ds18b20
	IODIR1 |= (1<<DQ_PIN);
	
	IOCLR1 = 1<<DQ_PIN;
	delay_us(2);
	
	// change the line to input
	IODIR1 &= ~(1<<DQ_PIN);
	
	// wait for the 15us
	delay_us(13);
	bit = (IOPIN1>>DQ_PIN)&1;
	// wait for the 45us to complete the 60us read-time slot
	delay_us(45);
	return bit;
}

uint8 readByte(void)
{
	// Read bytes from the sensor
	uint8 i, Din=0;
	
	for (i=0; i<8; i++)
	{
		Din |= (readBit() << i);
	}
	return Din;
}


float readTemp()
{
	uint16 tp, tfp;
	float dp;
	
	// Read temperature from DS18B20
	int32 presence;
	int16 temp;
	uint8 buff[2];
	
	// start with resetPulse
	presence = resetPulse();
	if (presence)
		return -1;
	
	// skip ROM command
	writeByte(SKIP_ROM);
	
	// send convert temp command
	writeByte(CONVERT_TEMP);
	
	// sensor will convert the temperature in 750ms.
	// we have two options, wait for 750ms for conversion
	// or, send a read bit time slots to the sensor, and checks, whether the sensor returns 1 for successful conversion
	// if returns 1, sensor is ready converting the temperature
	
	// choosing 1st option
	// delay_ms(750);
	
	// choosing 2nd option
	while(readBit() == 0);
	
	// after conversion, read the temperature
	
	presence = resetPulse();
	if (presence)
		return -1;
	
	// skip rom
	writeByte(SKIP_ROM);
	
	writeByte(READ_SCRATCHPAD);
	
	// now read the temperature and store it in buffer
    buff[0] = readByte(); // Read LSB
    buff[1] = readByte(); // Read MSB
	
	temp = buff[1];
	temp = (temp<<8) | buff[0];
	
	// convert to centigrade temperature
	tp = temp >> 4;
	tfp = (temp & 0xF);
	
	dp = ((float)tfp/16.0);
	
	return ((float)tp + dp);
}


void displayTemp(float *temp)
{
	int32 i, k;

	if ((*temp >= -1) && (*temp < 100))
		k=12;
	else if ((*temp	>= 100) && (*temp < 1000))
		k=13;
	else if ((*temp	>= 1000) && (*temp < 10000))
		k=14;
	else if ((*temp	>= 10000) && (*temp < 100000))
		k=15;
	// display Temperature on LCD
	CmdLCD(GOTO_LINE3_POS0+k);

	// Clear the line
	for (i=k; i<20; i++)
	{
		CharLCD(' ');
	}
	CmdLCD(GOTO_LINE3_POS0);
	StringLCD("Temp: ");
	F32LCD(*temp, 1);
	CharLCD(0xDF);
	CharLCD('C');
}
