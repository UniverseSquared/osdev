#include <drivers/keyboard.h>

static size_t keyboard_key_handler_count = 0;
static keyboard_key_handler_t keyboard_key_handlers[KEYBOARD_MAX_KEY_HANDLERS] = { 0 };

static uint8_t last_pressed_scancode = 0;

static void keyboard_key_handler(cpu_state_t cpu_state) {
    (void)cpu_state;

    uint16_t scancode = keyboard_read_scancode();

    if(last_pressed_scancode == 0xE0) {
        scancode |= last_pressed_scancode << 8;
    }

    if(scancode != 0xE0)
        for(size_t i = 0; i < keyboard_key_handler_count; i++)
            keyboard_key_handlers[i](scancode);

    last_pressed_scancode = scancode;
}

void init_keyboard(void) {
    set_interrupt_handler(IRQ(1), keyboard_key_handler);
}

uint8_t keyboard_read_scancode(void) {
    return port_read_byte(KEYBOARD_DATA_PORT);
}

unsigned char asciify_scancode(uint8_t scancode) {
    /* TODO: Complete when other scancodes are added. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
    switch(scancode) {
    case LEFT_BRACKET_PRESSED: return '[';
    case RIGHT_BRACKET_PRESSED: return ']';
    case ENTER_PRESSED: return '\n';
    case SEMICOLON_PRESSED: return ';';
    case QUOTE_PRESSED: return '\'';
    case BACKTICK_PRESSED: return '`';
    case BACKSLASH_PRESSED: return '\\';
    case SPACE_PRESSED: return ' ';
    }
#pragma GCC diagnostic pop

    if(scancode >= Q_PRESSED && scancode < A_PRESSED) {
        return "qwertyuiop"[scancode - Q_PRESSED];
    } else if(scancode >= A_PRESSED && scancode < Z_PRESSED) {
        return "asdfghjkl"[scancode - A_PRESSED];
    } else if(scancode >= Z_PRESSED && scancode <= M_PRESSED) {
        return "zxcvbnm"[scancode - Z_PRESSED];
    }

    return 0;
}

void add_keyboard_key_handler(keyboard_key_handler_t handler) {
    if(keyboard_key_handler_count < KEYBOARD_MAX_KEY_HANDLERS) {
        keyboard_key_handlers[keyboard_key_handler_count++] = handler;
    }
}
