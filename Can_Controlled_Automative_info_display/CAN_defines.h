// CAN_defines.h

#ifndef _CAN_DEFINES_H
#define _CAN_DEFINES_H

#include "types.h"
#include "CLK_defines.h"

// bit timing configs
#define BITRATE (125*1e3)
#define QUANTA 20

#define SAMPLE_POINT (0.7*QUANTA)

#define BRP (uint32)(PCLK/(QUANTA*BITRATE))

#define TSEG1 ((uint32)SAMPLE_POINT-1)
#define TSEG2 (QUANTA - (TSEG1+1))

#define SJW ((TSEG2>=5) ? 4 : (TSEG2-1))

// CxMOD SFR configs (Configuration SFR)
#define RM_BIT 0  // Reset mode bit
#define LOM_BIT 1 // listen only mode bit

// CxCMR SFR configs (Command SFR) (Write-only)
#define TR_BIT 0 // Transmit request bit
#define RRB_BIT 2 // Release Receive buffer bit
#define STB1_BIT 5 // Tx Buffer 1 for transmission
#define STB2_BIT 6 // Tx Buffer 2 for transmission
#define STB3_BIT 7 // Tx Buffer 3 for transmission

// CxGSR SFR configs (Global Status Register) (Read-only)
#define RBS_BIT 0 // Receive Buffer Status
#define TBS_BIT 2 // Transmit Buffer Status
#define TCS_BIT 3 // Transmit Complete Status


// CxICR SFR Configs (Interrupt and Capture Register) (Read-only)
#define RI_BIT 0 // Receive Interrupt: This bit is set when RBS in CANSR and RIE in CANIER are both 1
#define TI1_BIT 1 // Transmit Interrupt: This bit is set when TBS in CANSR goes 0 to 1(indicates STB1 is available) and TIE1 in CANIER is 1

// CxIER SFR Configs (Interrupt Enable Register) (R/W register)
#define RIE_BIT 0 // Receive Interrupt Enable 
#define TIE1_BIT 1 // Transmit Interrupt Enable 1

// CxBTR SFR configs (Bus Timing Register)
// This SFR controls the CAN timings derived from VPB clock, can be written only when RM_BIT of CxMOD is 1
#define SAM_VAL 0 // SAM_BIT 23, 0-> recommended for high speed; 1-> recommended for low/medium speed
#define BRP_BIT 0 // Baud Rate Prescaler
#define SJW_BIT 1 // Synchronization Jump Width

// CxRFS SFR configs (Receive Frame Status) (Read-only) (Can be written when RM_BIT in CxMOD is 1)
#define DLC_BIT 16 // Data Length Code (4bits)
#define RTR_BIT 30 // Remote Transmission Request, 0-> data can be read from CxRDA and CxRDB; 1-> Remote frame
#define FF_BIT 31 // 0-> 11bit identifier; 1-> 29 bit identifier

// CxTFI1 SFR configs (Transmit Frame Information Register)
// ##Same defines as of CxRFS##

// AFMR SFR configs (Acceptance Filter Mode Register) 
#define AccOff 0
#define AccBP 1 // 1-> All Rx messages are accepted on enabled CAN controllers; 0-> All Rx messages on CAN bus are ignored
#define eFCAN 2

// CAN VIC channel
#define VIC_CAN1_RX_CHNO 26
#define VIC_CAN2_RX_CHNO 27

// CAN RX Pin
#define CAN_RX1_PIN 25
#define CAN_RX1_PIN_FUNC 1

#define AFRAM_BASE 0xE0038000


// message ID's
#define LEFT_IND_ID  1
#define RIGHT_IND_ID 2
#define FUEL_REQ_ID  3
#define FUEL_VAL_ID  4


#endif
