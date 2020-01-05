#ifndef _KPRINT_H_
#define _KPRINT_H_
#include <drivers/framebuffer.h>
#include <drivers/serial.h>
#include <lib/stdint.h>
#include <lib/util.h>
#include <stdarg.h>

enum {
    DEST_FB     = BIT(0),
    DEST_SERIAL = BIT(1),
    DEST_ALL    = 0xFF
};

void kprintf(uint8_t destination, const char *format, ...);

#endif
