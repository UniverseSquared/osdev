#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#include <drivers/pic.h>
#include <kernel/kpanic.h>
#include <kernel/kprint.h>
#include <lib/stdint.h>

#define IRQ(n) ((n) + 32)

typedef struct isr_cpu_state {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error_code;
    uint32_t eip, cs, eflags, user_esp, ss;
} cpu_state_t;

typedef void (*interrupt_handler_t)(cpu_state_t);

extern interrupt_handler_t interrupt_handlers[256];

void isr_handler(cpu_state_t cpu_state);
void irq_handler(cpu_state_t cpu_state);

void set_interrupt_handler(uint8_t n, interrupt_handler_t handler);

#endif
