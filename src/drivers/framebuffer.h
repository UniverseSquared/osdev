#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_
#include <drivers/io.h>
#include <lib/stddef.h>
#include <lib/stdint.h>
#include <lib/string.h>

#define FB_WIDTH  80
#define FB_HEIGHT 25
#define FB_SIZE   (FB_WIDTH * FB_HEIGHT)

#define FB_POS(x, y) (FB_WIDTH * (y) + (x))

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

typedef enum fb_color {
    FB_COLOR_BLACK,
    FB_COLOR_BLUE,
    FB_COLOR_GREEN,
    FB_COLOR_CYAN,
    FB_COLOR_RED,
    FB_COLOR_MAGENTA,
    FB_COLOR_BROWN,
    FB_COLOR_LIGHT_GRAY,
    FB_COLOR_DARK_GRAY,
    FB_COLOR_LIGHT_BLUE,
    FB_COLOR_LIGHT_GREEN,
    FB_COLOR_LIGHT_CYAN,
    FB_COLOR_LIGHT_RED,
    FB_COLOR_PINK,
    FB_COLOR_YELLOW,
    FB_COLOR_WHITE
} fb_color_t;

extern uint16_t *framebuffer;
extern size_t fb_x, fb_y;

uint8_t fb_make_color(uint8_t fg, uint8_t bg);
uint16_t fb_make_cell(char c, uint8_t color);
void fb_write_cell(size_t index, char c, uint8_t fg, uint8_t bg);
void fb_clear(void);
void fb_write_char(char c);
void fb_write(const char *s);
void fb_move_cursor(uint16_t position);

#endif
