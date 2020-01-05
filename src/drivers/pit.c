#include <drivers/pit.h>

unsigned int pit_tick = 0;

static void pit_timer_callback(cpu_state_t cpu_state) {
    (void)cpu_state;

    // kprintf(DEST_ALL, "tick %d\n", pit_tick);
    pit_tick++;
}

void init_pit(void) {
    /* Register our callback. */
    set_interrupt_handler(IRQ(0), pit_timer_callback);

    /* Calculate the divisor required to get a frequency of 100Hz. */
    uint32_t divisor = 1193180 / 100;

    port_write_byte(PIT_COMMAND_PORT,       0x36);
    port_write_byte(PIT_CHANNEL0_DATA_PORT, divisor & 0xFF);
    port_write_byte(PIT_CHANNEL0_DATA_PORT, (divisor >> 8) & 0xFF);
}
