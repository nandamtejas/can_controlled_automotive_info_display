// fuel_node.c
/***************************************************************************************************************
FUEL NODE:

The `FUEL NODE` is dedicated to monitoring the vehicle's fuel level. Using on-chip ADC, it continuously samples 
the sensor signal and calculates the fuel percantage. The updated fuel level information is transmitted to 
`MAIN NODE` periodically (500 milliseconds) via CAN message BUS, where it is displayed on `MAIN NODE` dashboard.


***************************************************************************************************************/

#include <LPC21xx.h>
#include "fuel_node_defines.h"
#include "utils_defines.h"
#include "fuel_node_utils.h"
#include "../lcd_defines.h"
#include "../lcd.h"


// CAN frame global variable
volatile CAN_F txFrame;
struct floatNInt fuelVal;

float fuelPerc;

volatile int32 fuelTx=0;

// Timer 1 ISR
void CAN_Tx_on_match(void) __irq
{
	// Timer 1 ISR
	
	// ISR Activity Starts
	
	// send the frame via CAN bus
	CAN1_Tx(txFrame);
	
	// ISR Activity ends
	T1IR = 1<<0;
	T1TC = 0;
	
	VICVectAddr = 0;
}

// CAN1 Rx ISR
void can_rx_isr(void) __irq
{
	// ISR to ignore all the received all messages

	// CAN receive ISR
	while(READBIT(C1ICR, RI_BIT)==0);
	// Can frame received

	// Here check if the received message is of ID = 2 and RTR == 1

	if ((C1RID == FUEL_REQ_ID) && (READBIT(C1RFS, RTR_BIT) == 1))
	{
		// main node is asking for latest fuel percentage transmission
		fuelTx = 1;
	}

	// Clear Receive buffer
	C1CMR |= 1<<RRB_BIT;
	
	// Clear the interrupt
	VICVectAddr = 0;
}

int main()
{
	union fni fp;
	// FUEL NODE
	Init_Timer0();
	//Init_Timer1();
	//InitTimer1Int(CAN_Tx_on_match);
	InitADC_CH0();
	InitCAN1();
	InitCAN1Int(can_rx_isr, VIC_CAN1_RX_CHNO);

	/*
	---- Debugging ----
	InitLCD();
	CmdLCD(DSP_ON_CUR_OFF);
	StringLCD("FUEL NODE");
	delay_s(1);
	CmdLCD(CLEAR_LCD); 
	---- Debugging ----
	*/

	// Frame information
	txFrame.ID = FUEL_VAL_ID; // Fuel node ID = FUEL_VAL_ID
	txFrame.bfv.RTR = 0; // RTR = 0 means this frame is Data transmission frame
	txFrame.bfv.DLC = 4; // Data transmission Length (4bytes)
	
	while(1)
	{
		// Read the fuel value continuously
		readADC(ADC_CH_NO, &(fuelVal.fVal), &(fuelVal.iVal));
		
		// fuelVal.fVal = (fuelVal.fVal / ((1<<RESOLUTION)-1))*100;
		fuelPerc = (fuelVal.fVal / VREF) * 100;
		fp.fval = fuelPerc;
		
		// Add data to CAN FRAME
		txFrame.data1 = fp.ival;
		txFrame.data2 = 0;

		if (fuelTx == 1)
		{
			CAN1_Tx(txFrame);
			fuelTx = 0;
		}

		/*
		---- Debugging ----
		CmdLCD(GOTO_LINE1_POS0);
		StringLCD("Fuel Perc: ");
		F32LCD(fuelPerc, 2);
		CharLCD('%');
		---- Debugging ----
		*/
	}
	
}
