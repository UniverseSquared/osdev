#include <lib/string.h>

size_t strlen(const char *s) {
    size_t size = 0;
    while(s[size])
        size++;

    return size;
}

int streq(const char *x, const char *y) {
    size_t x_length = strlen(x);
    size_t y_length = strlen(y);

    if(x_length != y_length)
        return 0;

    for(size_t i = 0; i < x_length; i++)
        if(x[i] != y[i])
            return 0;

    return 1;
}

void *memcpy(void *dest, const void *src, size_t n) {
    uint8_t *dest_bytes = (uint8_t*)dest;
    const uint8_t *src_bytes = (const uint8_t*)src;

    for(size_t i = 0; i < n; i++)
        dest_bytes[i] = src_bytes[i];

    return dest_bytes;
}

void *memset(void *s, int c, size_t n) {
    uint8_t *bytes = (uint8_t*)s;

    for(size_t i = 0; i < n; i++)
        bytes[i] = c;

    return s;
}
