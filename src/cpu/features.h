#ifndef _FEATURES_H_
#define _FEATURES_H_
#include <cpu/cpuid.h>
#include <lib/stdint.h>
#include <lib/util.h>

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
