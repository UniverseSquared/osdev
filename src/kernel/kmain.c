#include <drivers/framebuffer.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/keyboard.h>
#include <drivers/pic.h>
#include <drivers/pit.h>
#include <drivers/serial.h>
#include <drivers/tty.h>
#include <kernel/kprint.h>
#include <lib/string.h>

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

    char buffer[128] = { 0 };

    while(1) {
        fb_write("> ");
        tty_read_line(buffer, sizeof(buffer));

        if(strcmp(buffer, "hello") == 0) {
            kprintf(DEST_FB, "hello!\n");
        } else if(strcmp(buffer, "halt") == 0) {
            kprintf(DEST_FB, "halting\n");
            asm volatile(".halt: hlt\n"
                         "       jmp .halt");
        }
    }
}
