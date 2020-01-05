#include <drivers/framebuffer.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/keyboard.h>
#include <drivers/pic.h>
#include <drivers/pit.h>
#include <drivers/serial.h>
#include <drivers/tty.h>
#include <kernel/kprint.h>

void kmain(void) {
    init_gdt();
    init_idt();
    init_pic();
    init_pit();
    init_keyboard();
    init_tty();

    serial_configure(SERIAL_COM1);
    fb_clear();

    kprintf(DEST_ALL, "hello, world!\n");

    uint16_t key = tty_read_key();
    kprintf(DEST_ALL, "read key: 0x%x\n", key);
}
