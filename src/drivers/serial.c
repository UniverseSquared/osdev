#include <drivers/serial.h>

void serial_configure_baud_rate(uint16_t com, uint16_t divisor) {
    port_write_byte(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    port_write_byte(SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);
    port_write_byte(SERIAL_DATA_PORT(com), divisor & 0xFF);
}

void serial_configure(uint16_t com) {
    /* Configure the baud rate for the port to 115200 / 3 = 38400. */
    serial_configure_baud_rate(com, 3);

    /* Configure a byte length of 8 bits, no parity bit, one stop bit and
     * break control disabled. */
    port_write_byte(SERIAL_LINE_COMMAND_PORT(com), 0x03);

    /* Enable FIFO, clear both tx and rx queues and use 14 bytes as the queue
     * size. */
    port_write_byte(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);

    /* Disable interrupts and specify that we're ready to send data. */
    port_write_byte(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(uint16_t com) {
    /* If the sixth bit of the line status is set, the
     * transmission FIFO is empty. */
    return port_read_byte(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write_char(uint16_t com, char c) {
    /* Wait for the transmit FIFO to be empty, and then write the data. */
    while(!serial_is_transmit_fifo_empty(com));

    port_write_byte(SERIAL_DATA_PORT(com), c);
}

void serial_write(uint16_t com, const char *s) {
    for(size_t i = 0; i < strlen(s); i++)
        serial_write_char(com, s[i]);
}
