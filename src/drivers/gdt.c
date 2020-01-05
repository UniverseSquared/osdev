#include <drivers/gdt.h>

gdt_entry_t gdt_entries[3];
gdt_t gdt;

void init_gdt(void) {
    /* The first GDT entry must be an empty null entry. */
    gdt_entries[0] = encode_gdt_entry(0, 0, 0, 0);

    /* The next entry will be the kernel code segment. (RX) */
    gdt_entries[1] = encode_gdt_entry(0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The final entry will be the kernel data segment. (RW) */
    gdt_entries[2] = encode_gdt_entry(0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt.size    = (sizeof(gdt_entry_t) * 3) - 1;
    gdt.address = (uint32_t)&gdt_entries;

    flush_gdt((uint32_t)&gdt);
}

gdt_entry_t encode_gdt_entry(uint32_t base, uint32_t limit,
                             uint8_t access, uint8_t granularity) {
    gdt_entry_t entry;

    entry.base_low    = base & 0xFFFF;
    entry.base_middle = (base >> 16) & 0xFF;
    entry.base_high   = (base >> 24) & 0xFF;

    entry.limit_low   = limit & 0xFFFF;
    entry.granularity = (limit >> 16) & 0xF;

    entry.granularity |= granularity & 0xF0;
    entry.access      = access;

    return entry;
}
