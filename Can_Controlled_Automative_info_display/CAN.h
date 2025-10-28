// CAN.h

#ifndef _CAN_H
#define _CAN_H

#include "types.h"




void InitCAN1(void);
void InitCAN1Int(void (*can_isr)(void)__irq, uint32 CAN_CHNO);
void CAN1_Tx(CAN_F frame);
void CAN1_Rx(CAN_F *frame);
int32 CAN1_Rx_ID(CAN_F *frame, uint32 ID);
void CANacceptID(int32 ID);

#endif
