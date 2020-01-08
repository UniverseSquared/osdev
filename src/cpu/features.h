#ifndef _FEATURES_H_
#define _FEATURES_H_
#include <cpu/cpuid.h>
#include <lib/stdint.h>
#include <lib/util.h>

enum {
    /* If set in ecx, the CPU supports the RDRAND instruction. */
    CPU_FEATURE_RDRND = BIT(30)
};

enum {
    /* Used to specify which register the feature flag is set in. */
    CPU_FEATURE_EDX = 0,
    CPU_FEATURE_ECX = 1
};

int is_cpu_feature_supported(uint32_t feature, int reg);

/* Convenience wrappers around is_cpu_feature_supported. */
int is_cpu_feature_rdrnd_supported(void);

#endif
