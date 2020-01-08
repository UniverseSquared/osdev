#include <cpu/features.h>

int is_cpu_feature_supported(uint32_t feature, int reg) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(CPUID_LEAF_PROCESSOR_INFO, &eax, &ebx, &ecx, &edx);

    return (reg ? ecx : edx) & feature;
}

int is_cpu_feature_rdrnd_supported(void) {
    return is_cpu_feature_supported(CPU_FEATURE_RDRND, CPU_FEATURE_ECX);
}
