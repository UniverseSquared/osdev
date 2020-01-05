#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include <drivers/interrupt.h>
#include <drivers/io.h>
#include <kernel/kprint.h>

#define KEYBOARD_MAX_KEY_HANDLERS 10

#define KEYBOARD_DATA_PORT 0x60

/* https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html */
/* TODO: Many scancodes are omitted (see above ^), add them. */
enum {
#define DEF_KEY(keyname, scancode)              \
    keyname ## _PRESSED  = scancode,                \
    keyname ## _RELEASED = scancode + 0x80

    DEF_KEY(ESCAPE,        0x01),
    DEF_KEY(ONE,           0x02),
    DEF_KEY(TWO,           0x03),
    DEF_KEY(THREE,         0x04),
    DEF_KEY(FOUR,          0x05),
    DEF_KEY(FIVE,          0x06),
    DEF_KEY(SIX,           0x07),
    DEF_KEY(SEVEN,         0x08),
    DEF_KEY(EIGHT,         0x09),
    DEF_KEY(NINE,          0x0A),
    DEF_KEY(ZERO,          0x0B),
    DEF_KEY(HYPHEN,        0x0C),
    DEF_KEY(EQUALS,        0x0D),
    DEF_KEY(BACKSPACE,     0x0E),
    DEF_KEY(TAB,           0x0F),
    DEF_KEY(Q,             0x10),
    DEF_KEY(W,             0x11),
    DEF_KEY(E,             0x12),
    DEF_KEY(R,             0x13),
    DEF_KEY(T,             0x14),
    DEF_KEY(Y,             0x15),
    DEF_KEY(U,             0x16),
    DEF_KEY(I,             0x17),
    DEF_KEY(O,             0x18),
    DEF_KEY(P,             0x19),
    DEF_KEY(LEFT_BRACKET,  0x1A),
    DEF_KEY(RIGHT_BRACKET, 0x1B),
    DEF_KEY(ENTER,         0x1C),
    DEF_KEY(LEFT_CTRL,     0x1D),
    DEF_KEY(A,             0x1E),
    DEF_KEY(S,             0x1F),
    DEF_KEY(D,             0x20),
    DEF_KEY(F,             0x21),
    DEF_KEY(G,             0x22),
    DEF_KEY(H,             0x23),
    DEF_KEY(J,             0x24),
    DEF_KEY(K,             0x25),
    DEF_KEY(L,             0x26),
    DEF_KEY(SEMICOLON,     0x27),
    DEF_KEY(QUOTE,         0x28),
    DEF_KEY(BACKTICK,      0x29),
    DEF_KEY(LEFT_SHIFT,    0x2A),
    DEF_KEY(BACKSLASH,     0x2B),
    DEF_KEY(Z,             0x2C),
    DEF_KEY(X,             0x2D),
    DEF_KEY(C,             0x2E),
    DEF_KEY(V,             0x2F),
    DEF_KEY(B,             0x30),
    DEF_KEY(N,             0x31),
    DEF_KEY(M,             0x32),
    DEF_KEY(SPACE,         0x39),
    DEF_KEY(DELETE,        0xE053)

#undef DEF_KEY
};

typedef void (*keyboard_key_handler_t)(uint16_t);

void init_keyboard(void);
uint8_t keyboard_read_scancode(void);
unsigned char asciify_scancode(uint8_t scancode);
void add_keyboard_key_handler(keyboard_key_handler_t handler);

#endif
