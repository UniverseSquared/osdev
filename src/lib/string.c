#include <lib/string.h>

size_t strlen(const char *s) {
    size_t size = 0;
    while(s[size])
        size++;

    return size;
}

int strcmp(const char *s1, const char *s2) {
    size_t length = strlen(s1);
    for(size_t i = 0; i < length; i++)
        if(s1[i] != s2[i] || s1[i] == 0 || s2[i] == 0)
            return (int)(s1[i]) - (int)(s2[i]);

    return 0;
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
