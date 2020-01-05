#include <drivers/framebuffer.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/keyboard.h>
#include <drivers/pic.h>
#include <drivers/pit.h>
#include <drivers/serial.h>
#include <kernel/kprint.h>

void test_key_handler(uint16_t scancode) {
    kprintf(DEST_ALL, "%s 0x%x\n",
            scancode & 0x80 ? "released" : "pressed",
            scancode);
}

void kmain(void) {
    init_gdt();
    init_idt();
    init_pic();
    init_pit();
    init_keyboard();

    add_keyboard_key_handler(test_key_handler);

    serial_configure(SERIAL_COM1);
    fb_clear();

    kprintf(DEST_ALL, "hello, world!\n");
}
