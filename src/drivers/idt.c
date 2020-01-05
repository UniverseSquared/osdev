#include <drivers/idt.h>

idt_entry_t idt_entries[256];
idt_t idt;

void init_idt(void) {
    memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

#define SET_ISR_HANDLER(n)                                              \
    idt_entries[n] = encode_idt_entry((uint32_t)isr##n, 0x08, 0x8E)

#define SET_IRQ_HANDLER(x, y)                                           \
    idt_entries[x] = encode_idt_entry((uint32_t)irq##y, 0x08, 0x8E)

    SET_ISR_HANDLER(0);
    SET_ISR_HANDLER(1);
    SET_ISR_HANDLER(2);
    SET_ISR_HANDLER(3);
    SET_ISR_HANDLER(4);
    SET_ISR_HANDLER(5);
    SET_ISR_HANDLER(6);
    SET_ISR_HANDLER(7);
    SET_ISR_HANDLER(8);
    SET_ISR_HANDLER(9);
    SET_ISR_HANDLER(10);
    SET_ISR_HANDLER(11);
    SET_ISR_HANDLER(12);
    SET_ISR_HANDLER(13);
    SET_ISR_HANDLER(14);
    SET_ISR_HANDLER(15);
    SET_ISR_HANDLER(16);
    SET_ISR_HANDLER(17);
    SET_ISR_HANDLER(18);
    SET_ISR_HANDLER(19);
    SET_ISR_HANDLER(20);
    SET_ISR_HANDLER(21);
    SET_ISR_HANDLER(22);
    SET_ISR_HANDLER(23);
    SET_ISR_HANDLER(24);
    SET_ISR_HANDLER(25);
    SET_ISR_HANDLER(26);
    SET_ISR_HANDLER(27);
    SET_ISR_HANDLER(28);
    SET_ISR_HANDLER(29);
    SET_ISR_HANDLER(30);
    SET_ISR_HANDLER(31);

    SET_IRQ_HANDLER(32, 0);
    SET_IRQ_HANDLER(33, 1);
    SET_IRQ_HANDLER(34, 2);
    SET_IRQ_HANDLER(35, 3);
    SET_IRQ_HANDLER(36, 4);
    SET_IRQ_HANDLER(37, 5);
    SET_IRQ_HANDLER(38, 6);
    SET_IRQ_HANDLER(39, 7);
    SET_IRQ_HANDLER(40, 8);
    SET_IRQ_HANDLER(41, 9);
    SET_IRQ_HANDLER(42, 10);
    SET_IRQ_HANDLER(43, 11);
    SET_IRQ_HANDLER(44, 12);
    SET_IRQ_HANDLER(45, 13);
    SET_IRQ_HANDLER(46, 14);
    SET_IRQ_HANDLER(47, 15);

#undef SET_IRQ_HANDLER
#undef SET_ISR_HANDLER

    idt.size    = (sizeof(idt_entry_t) * 256) - 1;
    idt.address = (uint32_t)&idt_entries;

    flush_idt((uint32_t)&idt);
}

/* TODO: encode_ -> make (?) in GDT/IDT code */
idt_entry_t encode_idt_entry(uint32_t base, uint16_t selector, uint8_t flags) {
    idt_entry_t entry;

    entry.base_low  = base & 0xFFFF;
    entry.base_high = (base >> 16) & 0xFFFF;

    entry.selector  = selector;
    entry.reserved  = 0;
    entry.flags     = flags;

    return entry;
}
