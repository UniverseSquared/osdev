#ifndef _TTY_H_
#define _TTY_H_
#include <drivers/keyboard.h>
#include <lib/stdint.h>

void init_tty(void);
uint16_t tty_read_key(void);
size_t tty_read_line(char *buffer, size_t buffer_size);

#endif
