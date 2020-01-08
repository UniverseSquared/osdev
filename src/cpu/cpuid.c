#include <cpu/cpuid.h>

void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx,
           uint32_t *ecx, uint32_t *edx) {
    asm volatile("cpuid"
                 : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                 : "a"(leaf));
}

uint32_t supported_cpu_features_ecx(void) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(CPUID_LEAF_PROCESSOR_INFO, &eax, &ebx, &ecx, &edx);

    return ecx;
}

uint32_t supported_cpu_features_edx(void) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(CPUID_LEAF_PROCESSOR_INFO, &eax, &ebx, &ecx, &edx);

    return edx;
}

int is_cpu_feature_supported_ecx(uint32_t feature) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(CPUID_LEAF_PROCESSOR_INFO, &eax, &ebx, &ecx, &edx);

    return ecx & feature;
}

int is_cpu_feature_supported_edx(uint32_t feature) {
    uint32_t eax, ebx, ecx, edx;
    cpuid(CPUID_LEAF_PROCESSOR_INFO, &eax, &ebx, &ecx, &edx);

    return edx & feature;
}

int is_cpu_feature_rdrnd_supported(void) {
    return is_cpu_feature_supported_ecx(CPU_FEATURE_RDRND);
}
