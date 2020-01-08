#ifndef _STRING_H_
#define _STRING_H_
#include <lib/stddef.h>
#include <lib/stdint.h>

size_t strlen(const char *s);
int streq(const char *s1, const char *s2);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

#endif
