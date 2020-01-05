#ifndef _PIC_H_
#define _PIC_H_
#include <drivers/io.h>
#include <lib/stdint.h>

#define PIC_MASTER_COMMAND_PORT 0x20
#define PIC_MASTER_DATA_PORT    0x21
#define PIC_SLAVE_COMMAND_PORT  0xA0
#define PIC_SLAVE_DATA_PORT     0xA1

#define PIC_END_OF_INTERRUPT    0x20

#define PIC_MASTER_START_INTERRUPT 0x20
#define PIC_SLAVE_START_INTERRUPT  0x28
#define PIC_SLAVE_END_INTERRUPT   (PIC_SLAVE_START_INTERRUPT + 7)

void init_pic(void);
void pic_acknowledge(uint32_t interrupt);

#endif
