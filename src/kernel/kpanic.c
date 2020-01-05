#include <kernel/kpanic.h>

void kpanic(const char *msg) {
    kprintf(DEST_ALL, "Kernel panic: %s\n", msg);
    asm volatile("halt: cli\n"
                 "      hlt\n"
                 "      jmp halt");
}
