#ifndef _CPUID_H_
#define _CPUID_H_
#include <lib/stdint.h>
#include <lib/util.h>

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

enum {
    /* If set in ecx, the CPU supports the RDRAND instruction. */
    CPU_FEATURE_RDRND = BIT(30)
};

uint32_t supported_cpu_features_ecx(void);
uint32_t supported_cpu_features_edx(void);
int is_cpu_feature_supported_ecx(uint32_t feature);
int is_cpu_feature_supported_edx(uint32_t feature);

/* Convenience wrappers around is_cpu_feature_supported_*. */
int is_cpu_feature_rdrnd_supported(void);

#endif
