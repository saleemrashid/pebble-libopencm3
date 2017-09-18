#include <hal_cpu.h>

#include <libopencmsis/core_cm3.h>

void hal_cpu_disable_irqs(void) {
#if 0
    cm_disable_interrupts();
#endif
}

void hal_cpu_enable_irqs(void) {
#if 0
    cm_enable_interrupts();
#endif
}

void hal_cpu_enable_irqs_and_sleep(void) {
#if 0
    cm_enable_interrupts();
    __asm__("wfe");
#endif
}
