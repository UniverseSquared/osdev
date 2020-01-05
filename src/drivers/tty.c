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

size_t tty_read_line(char *buffer, size_t buffer_size) {
    size_t i = 0;
    while(i < buffer_size - 1) {
        fb_update_cursor();

        uint16_t key = tty_read_key();
        char ascii = asciify_scancode(key);

        if(key == ENTER_PRESSED) {
            break;
        } else if(ascii != 0) {
            buffer[i++] = ascii;
            fb_write_char(ascii);
        }
    }

    fb_write_char('\n');

    buffer[i++] = 0;
    return i;
}
