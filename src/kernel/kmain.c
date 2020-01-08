#include <cpu/cpuid.h>
#include <cpu/features.h>
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

static int print_scancodes = 0;

void print_scancode_key_handler(uint16_t scancode) {
    if(print_scancodes) {
        int ascii = asciify_scancode(scancode);

        if(ascii != 0)
            kprintf(DEST_FB, "scancode: 0x%x (%c)\n", scancode, ascii);
        else
            kprintf(DEST_FB, "scancode: 0x%x\n", scancode);

        if(scancode == Q_PRESSED)
            print_scancodes = 0;
    }
}

void kmain(void) {
    serial_configure(SERIAL_COM1);
    fb_clear();

    init_gdt();
    init_idt();
    init_pic();
    init_pit();
    init_keyboard();
    init_tty();

    add_keyboard_key_handler(print_scancode_key_handler);

    kprintf(DEST_ALL, "hello, world!\n");

    uint32_t eax;
    char manufacturer_id[13] = { 0 };
    cpuid(CPUID_LEAF_MANUFACTURER_ID, &eax,
          &manufacturer_id[0], &manufacturer_id[8], &manufacturer_id[4]);

    kprintf(DEST_ALL, "highest cpuid leaf supported: 0x%x\n", eax);
    kprintf(DEST_ALL, "manufacturer id: %s\n", manufacturer_id);

    int supports_rdrnd = is_cpu_feature_rdrnd_supported();
    kprintf(DEST_ALL, "cpu supports rdrand: %s\n",
            supports_rdrnd ? "yes" : "no");

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
        } else if(strcmp(buffer, "scancode") == 0) {
            kprintf(DEST_FB, "Press Q to exit\n");
            print_scancodes = 1;

            while(print_scancodes)
                asm volatile("hlt");
        }
    }
}
