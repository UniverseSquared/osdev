#include <drivers/pic.h>

void init_pic(void) {
    asm volatile("cli");

    uint8_t master_mask = port_read_byte(PIC_MASTER_DATA_PORT);
    uint8_t slave_mask  = port_read_byte(PIC_SLAVE_DATA_PORT);

    /* ICW1: Initialization, specify that we're going to send ICW4. */
    port_write_byte(PIC_MASTER_COMMAND_PORT, 0x11);
    port_write_byte(PIC_SLAVE_COMMAND_PORT,  0x11);

    /* ICW2: Set the offsets of the PIC interrupts. */
    port_write_byte(PIC_MASTER_DATA_PORT, PIC_MASTER_START_INTERRUPT);
    port_write_byte(PIC_SLAVE_DATA_PORT,  PIC_SLAVE_START_INTERRUPT);

    /* ICW3: Tell both PICs which of the master's interrupt the slave occupies. */
    port_write_byte(PIC_MASTER_DATA_PORT, 0x04);
    port_write_byte(PIC_SLAVE_DATA_PORT,  0x02);

    /* ICW4: Enable 8086 mode. */
    port_write_byte(PIC_MASTER_DATA_PORT, 0x01);
    port_write_byte(PIC_SLAVE_DATA_PORT,  0x01);

    /* Restore the previously stored interrupt masks. */
    port_write_byte(PIC_MASTER_DATA_PORT, master_mask);
    port_write_byte(PIC_SLAVE_DATA_PORT,  slave_mask);

    /* Enable interrupts. */
    asm volatile("sti");
}

void pic_acknowledge(uint32_t interrupt) {
    if(interrupt >= PIC_SLAVE_START_INTERRUPT)
        port_write_byte(PIC_SLAVE_COMMAND_PORT, PIC_END_OF_INTERRUPT);

    port_write_byte(PIC_MASTER_COMMAND_PORT, PIC_END_OF_INTERRUPT);
}
