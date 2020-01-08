#include <cpu/rdrand.h>

uint32_t rdrand(void) {
    uint32_t eax;
    asm volatile("rdrand %%eax" : "=a"(eax));
    return eax;
}
