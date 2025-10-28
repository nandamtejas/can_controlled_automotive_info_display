// main_node.c

/***************************************************************************************************************
MAIN NODE: 

The `MAIN NODE` acts as the Central Dashboard display. It continuously reads the engine temperature and 
RTC values, and displays them on LCD. It also receives Fuel level information from `FUEL NODE` via CAN bus
and shows the fuel percentage on the LCD. Additionally, The `MAIN NODE` handles the left and right indicator
switch inputs, sends their status to the `INDICATOR NODE` via same CAN bus,and updates the indicator 
status on display.

***************************************************************************************************************/

#include <LPC21xx.h>
#include "main_node_defines.h"
#include "utils_defines.h"
#include "utils.h"


// CGRAM LUT
const uint8 cgram_lut[][8] = {
	{0x08, 0x0C, 0x1E, 0x1F, 0x1E, 0x0C, 0x08, 0x00}, // RIGHT INDICATOR (0)
	{0x02, 0x06, 0x0F, 0x1F, 0x0F, 0x06, 0x02, 0x00}, // LEFT INDICATOR (1)
	{0x1E, 0x10, 0x11, 0x1C, 0x11, 0x10, 0x1E, 0x00}, // Fuel indicator (E:)
	{0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00}, // Fuel point 
};



// Indicator FLAG
volatile indMode txInd = IND_OFF;
// Indicator blink flag; 0-> hide the indicator and set to 1; 1-> show the indicator and clear to 0
volatile uint32 IndBlinkFlag = 0; 

struct floatNInt engineFuel;

volatile union fni fuelPerc;


volatile uint32 CAN_indNode = 0;

// ISR definitions
volatile CAN_F txFrame;
volatile CAN_F txFrameReq;
CAN_F rxFrame;

void left_ind_ISR(void) __irq
{
	// LEFT INDICATOR ISR
	
	// Activity Starts
	
	txFrame.ID = LEFT_IND_ID;
	txFrame.bfv.RTR = 0;
	txFrame.bfv.DLC = 1;
	
	txFrame.data1 = 'l';
	txFrame.data2 = 0;
	
	// CAN1_Tx(txFrame);
	CAN_indNode = 1;
	
	// indicator status change
	if (txInd != IND_LEFT)
		txInd = IND_LEFT;
	else
		txInd = IND_OFF;

	// Indicator Blink remove
//	CmdLCD(GOTO_LINE1_POS0+13);
//	StringLCD("  ");
	
	// Reset the Indicator Blink Flag
	IndBlinkFlag = 0;
	
	// Activity Ends
	EXTINT |= 1<<EINT0_PIN;
	VICVectAddr = 0;
}

void right_ind_ISR(void) __irq
{
	// RIGHT INDICATOR ISR
	
	// Activity Starts
	
	txFrame.ID = RIGHT_IND_ID;
	txFrame.bfv.RTR = 0;
	txFrame.bfv.DLC = 1;
	
	txFrame.data1 = 'r';
	txFrame.data2 = 0;
	
	// CAN1_Tx(txFrame);
	CAN_indNode = 1;

	// indicator status change
	if (txInd != IND_RIGHT)
		txInd = IND_RIGHT;
	else
		txInd = IND_OFF;

	// Indicator Blink remove
//	CmdLCD(GOTO_LINE1_POS0+13);
//	StringLCD("  ");
	
	// Reset the Indicator Blink Flag
	IndBlinkFlag = 0;
	
	IOPIN1 ^= (1<<17);
	
	// Activity Ends
	EXTINT |= 1<<EINT1_PIN;
	VICVectAddr = 0;
}

void can_rx_isr(void) __irq
{
	// ISR to receive fuel percentage

	// CAN receive ISR
	while(READBIT(C1ICR, RI_BIT)==0);
	// Can frame received

	if ((CAN_indNode == 0) && (C1RID == FUEL_VAL_ID))
	{

		rxFrame.ID = C1RID;
		rxFrame.bfv.RTR = READBIT(C1RFS, RTR_BIT);
		rxFrame.bfv.DLC = READBYTE(C1RFS, DLC_BIT);
	
		// check if the received frame is message frame or data frame, if message frame extract data
		if (rxFrame.bfv.RTR == 0)
		{
			rxFrame.data1 = C1RDA;
			rxFrame.data2 = C1RDB;
		}

		fuelPerc.ival = rxFrame.data1;
	}


	// Clear Receive buffer
	C1CMR |= 1<<RRB_BIT;
	
	// Clear the interrupt
	VICVectAddr = 0;
}

int main()
{
	float temp;
	
	// Required Initialization
	Init_Timer0();
	InitCAN1();
	//CANacceptID(3);
	InitCAN1Int(can_rx_isr, VIC_CAN1_RX_CHNO);
	InitLCD();
	
	// Build CGRAM for indicator display in LCD
	BuildCGRAMLUT(cgram_lut, 4);
	InitRTC();
	
	// Init External Interrupt with Left and right indicator ISR
	InitEXTInt(left_ind_ISR, right_ind_ISR);
	
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	
	
	setDate(28, 10, 2025);
	setTime(15, 45, 0);
		
	while(1)
	{
		// RTC
		displayRTC();

		// send indicator status to indicator node if required.
		if (CAN_indNode == 1)
		{
			 // Tx txFrame message to indicator node
			 CAN1_Tx(txFrame);
			 CAN_indNode = 0;
		}
		else
		{
			// Request for fuel level information to fuel node
			txFrameReq.ID = FUEL_REQ_ID;
			txFrameReq.bfv.RTR = 1;
			txFrameReq.bfv.DLC = 0;
			CAN1_Tx(txFrameReq);
		}
		
		// Blink indicator if required
		CmdLCD(GOTO_LINE2_POS0+13);
		indicator_blink(txInd, &IndBlinkFlag);
		
		// Engine Temperature
		temp = readTemp();
		displayTemp(&temp); 	
		
		// fuel level indicator
		CmdLCD(GOTO_LINE4_POS0);
		display_fuel_indicator(fuelPerc.fval);
		F32LCD(fuelPerc.fval, 2);
		CharLCD('%');
	}
}
