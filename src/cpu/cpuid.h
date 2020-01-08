#ifndef _CPUID_H_
#define _CPUID_H_
#include <lib/stdint.h>

enum {
    /* Returns the manufacturer ID string as an ASCII string in ebx, edx
     * and ecx, and the highest CPUID 'leaf' number supported by the CPU
     * in eax. */
    CPUID_LEAF_MANUFACTURER_ID = 0x0,

    /* Returns the CPU's model and family info in eax, feature info in edx and
     * ecx, and additional feature info in ebx. */
    CPUID_LEAF_PROCESSOR_INFO  = 0x1
};

void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx,
           uint32_t *ecx, uint32_t *edx);

#endif
