// lcd_defines.h

#ifndef _LCD_DEFINES_H
#define _LCD_DEFINES_H

// LCD Command Name:  					// cmd val        			// Execution time
#define CLEAR_LCD          					0x01 					 	// -
#define RET_HOME 							0x02						// 1.52ms

#define ENTRY_MODE_SET_RIGHT				0x06						// 37us
#define ENTRY_MODE_SET_LEFT					0x07						// 37us

#define DSP_OFF								0x08						// 37us
#define DSP_ON_CUR_OFF						0x0C						// 37us
#define DSP_ON_CUR_NOBLINK					0x0E						// 37us
#define DSP_ON_CUR_BLINK					0x0F						// 37us

#define SHIFT_CUR_LEFT						0x10						// 37us
#define SHIFT_CUR_RIGHT						0x14						// 37us
#define SHIFT_DSP_LEFT						0x18						// 37us
#define SHIFT_DSP_RIGHT						0x1C						// 37us

#define MODE_4BIT_1LINE						0x20						// 37us
#define MODE_4BIT_2LINE						0x28						// 37us
#define MODE_8BIT_1LINE						0x30						// 37us
#define MODE_8BIT_2LINE						0x38						// 37us

#define GOTO_CGRAM_START					0x40						// 37us

#define GOTO_LINE1_POS0 					(0x80 + 0x00)				// 37us
#define GOTO_LINE2_POS0 					(0x80 + 0x40)				// 37us
#define GOTO_LINE3_POS0 					(0x80 + 0x14)				// 37us
#define GOTO_LINE4_POS0 					(0x80 + 0x54)				// 37us


#define LCD_DATA 0 // P0.0 to P0.7
#define LCD_RS 8 // P0.8
#define LCD_RW 10 // P0.10
#define LCD_EN 9 // P0.9

#endif
