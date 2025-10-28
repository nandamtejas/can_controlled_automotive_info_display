// types.h

#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short int uint16;
typedef short int int16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long uint64;
typedef long int64;

typedef enum {IND_OFF, IND_LEFT, IND_RIGHT}	indMode;

struct floatNInt {
	uint32 iVal;
	float fVal;
};

union fni {
	float fval;
	int32 ival;
};

// CAN Frame
typedef struct CAN_FRAME {
	uint32 ID;
	struct {
		uint8 RTR;
		uint8 DLC;
	} bfv;
	uint32 data1, data2;
} CAN_F;

#endif
