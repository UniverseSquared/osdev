#ifndef _PORT_H_
#define _PORT_H_
#include <lib/stdint.h>

uint8_t port_read_byte(uint16_t port);
void port_write_byte(uint16_t port, uint8_t byte);

#endif
