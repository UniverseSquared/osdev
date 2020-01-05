#include <drivers/framebuffer.h>

uint16_t *framebuffer = (uint16_t*)0xB8000;
size_t fb_x = 0, fb_y = 0;

uint8_t fb_make_color(uint8_t fg, uint8_t bg) {
    return (bg << 4) | fg;
}

uint16_t fb_make_cell(char c, uint8_t color) {
    return (color << 8) | c;
}

void fb_write_cell(size_t index, char c, uint8_t fg, uint8_t bg) {
    framebuffer[index] = fb_make_cell(c, fb_make_color(fg, bg));
}

void fb_clear(void) {
    fb_move_cursor(FB_POS(0, 0));

    for(size_t i = 0; i < FB_SIZE; i++)
        fb_write_cell(i, ' ', FB_COLOR_BLACK, FB_COLOR_BLACK);
}

void fb_write_char(char c) {
    if(c == '\n') {
        fb_x = 0;
        fb_y++;
    } else if(c == '\r') {
        fb_x = 0;
    } else {
        size_t index = FB_WIDTH * fb_y + fb_x;
        fb_write_cell(index, c, FB_COLOR_LIGHT_GRAY, FB_COLOR_BLACK);
        fb_x++;
    }

    if(fb_y >= FB_HEIGHT) {
        memcpy(&framebuffer[0],
               &framebuffer[FB_POS(0, 1)],
               FB_WIDTH * (FB_HEIGHT - 1) * 2);

        for(size_t x = 0; x < FB_WIDTH; x++)
            framebuffer[FB_POS(x, FB_HEIGHT - 1)]
                = fb_make_cell(' ', fb_make_color(FB_COLOR_BLACK, FB_COLOR_BLACK));

        fb_y--;
    }
}

void fb_write(const char *s) {
    for(size_t i = 0; i < strlen(s); i++)
        fb_write_char(s[i]);
}

void fb_move_cursor(uint16_t position) {
    port_write_byte(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    port_write_byte(FB_DATA_PORT, (position >> 8) & 0xFF);
    port_write_byte(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    port_write_byte(FB_DATA_PORT, position & 0xFF);
}
