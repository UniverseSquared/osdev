#ifndef _TTY_H_
#define _TTY_H_
#include <drivers/keyboard.h>
#include <lib/stdint.h>

void init_tty(void);
uint16_t tty_read_key(void);

#endif
