#ifndef _GDT_H_
#define _GDT_H_
#include <lib/stdint.h>

typedef struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt {
    uint16_t size;
    uint32_t address;
} __attribute__((packed)) gdt_t;

void init_gdt(void);
gdt_entry_t encode_gdt_entry(uint32_t base, uint32_t limit,
                             uint8_t access, uint8_t granularity);

extern void flush_gdt(uint32_t address);

#endif
