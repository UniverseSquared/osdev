#include <drivers/interrupt.h>

interrupt_handler_t interrupt_handlers[256];

void isr_handler(cpu_state_t cpu_state) {
    (void)cpu_state;

    kpanic("unhandled exception");
}

void irq_handler(cpu_state_t cpu_state) {
    pic_acknowledge(cpu_state.interrupt);

    if(interrupt_handlers[cpu_state.interrupt] != NULL) {
        interrupt_handlers[cpu_state.interrupt](cpu_state);
    } else {
        kprintf(DEST_ALL, "unhandled irq %d\n", cpu_state.interrupt);
    }
}

void set_interrupt_handler(uint8_t n, interrupt_handler_t handler) {
    interrupt_handlers[n] = handler;
}
