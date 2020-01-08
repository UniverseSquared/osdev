#ifndef _PIT_H_
#define _PIT_H_
#include <drivers/interrupt.h>
#include <drivers/io.h>
#include <kernel/kprint.h>

#define PIT_CHANNEL0_DATA_PORT 0x40
#define PIT_CHANNEL1_DATA_PORT 0x41
#define PIT_CHANNEL2_DATA_PORT 0x42
#define PIT_COMMAND_PORT       0x43

extern unsigned int pit_tick;

void init_pit(unsigned int frequency);

#endif
