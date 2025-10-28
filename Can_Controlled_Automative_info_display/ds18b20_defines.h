// ds18b20_defines.h

#ifndef _DS18B20_DEFINES_H
#define _DS18B20_DEFINES_H

// ROM Command defines
#define READ_ROM 0x33
#define SKIP_ROM 0xCC
#define MATCH_ROM 0x55
#define SEARCH_ROM 0xF0

// Memory command defines
#define WRITE_SCRATCHPAD 0x4E
#define READ_SCRATCHPAD 0xBE
#define CONVERT_TEMP 0x44
#define COPY_SCRATCHPAD 0x48
#define RECALL_E2 0xB8
#define READ_POWER_SUPPLY 0xB4

#define DQ_PIN 16

#endif
