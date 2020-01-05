#ifndef _SERIAL_H_
#define _SERIAL_H_
#include <drivers/io.h>
#include <lib/string.h>

#define SERIAL_COM1 0x3F8

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* Tell the serial port to expect the highest 8 bits of the divisor, followed
 * by the lowest 8 bits. */
#define SERIAL_LINE_ENABLE_DLAB 0x80

void serial_configure_baud_rate(uint16_t com, uint16_t divisor);
void serial_configure(uint16_t com);
int serial_is_transmit_fifo_empty(uint16_t com);
void serial_write_char(uint16_t com, char c);
void serial_write(uint16_t com, const char *s);

#endif
