#include <drivers/tty.h>

static int tty_waiting_for_keypress = 0;
static uint16_t tty_keypress = 0;

static void tty_key_handler(uint16_t scancode) {
    /* If we were waiting for a keypress, we don't need to wait any longer. */
    if(tty_waiting_for_keypress) {
        tty_waiting_for_keypress = 0;
        tty_keypress = scancode;
    }
}

void init_tty(void) {
    add_keyboard_key_handler(tty_key_handler);
}

uint16_t tty_read_key(void) {
    tty_waiting_for_keypress = 1;
    while(tty_waiting_for_keypress)
        asm volatile("hlt");

    return tty_keypress;
}
