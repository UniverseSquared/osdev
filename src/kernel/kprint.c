#include <kernel/kprint.h>

static const char *lowercase_digits = "0123456789abcdef";
static const char *uppercase_digits = "0123456789ABCDEF";

/* TODO: Should it be possible to write to serial ports other than COM1? */
#define kprintf_write(str)                      \
    do {                                        \
        if(destination & DEST_FB)               \
            fb_write(str);                      \
                                                \
        if(destination & DEST_SERIAL)           \
            serial_write(SERIAL_COM1, str);     \
    } while(0)

#define kprintf_write_char(c)                   \
    do {                                        \
        if(destination & DEST_FB)               \
            fb_write_char(c);                   \
                                                \
        if(destination & DEST_SERIAL)           \
            serial_write_char(SERIAL_COM1, c);  \
    } while(0)


static void kprintf_write_int(uint8_t destination,
                              unsigned int n,
                              unsigned int base,
                              int uppercase) {
    if(n >= base)
        kprintf_write_int(destination, n / base, base, uppercase);

    kprintf_write_char(uppercase
                       ? uppercase_digits[n % base]
                       : lowercase_digits[n % base]);
}

void kprintf(uint8_t destination, const char *format, ...) {
    va_list args;
    va_start(args, format);

    size_t i = 0;
    while(i < strlen(format)) {
        if(format[i] == '%') {
            char format_specifier = format[++i];

            switch(format_specifier) {
            case 's': {
                char *s = va_arg(args, char *);
                kprintf_write(s);
            } break;

            case 'c': {
                char c = va_arg(args, int);
                kprintf_write_char(c);
            } break;

            case 'd': {
                int n = va_arg(args, int);
                kprintf_write_int(destination, n, 10, 0);
            } break;

            case 'X':
            case 'x': {
                unsigned int n = va_arg(args, unsigned int);
                kprintf_write_int(destination, n, 0x10,
                                  format_specifier == 'X');
            } break;

            case '%':
                kprintf_write_char('%');
                break;
            }
        } else {
            kprintf_write_char(format[i]);
        }

        i++;
    }

    va_end(args);
}

#undef kprint_write_char
#undef kprintf_write
