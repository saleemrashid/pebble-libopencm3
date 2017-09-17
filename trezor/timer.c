#include "timer.h"

#include "clock.h"

uint32_t system_millis_lock_start;

void timer_init(void) {
    timer_setup();
}
