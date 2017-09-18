#include <hal_time_ms.h>

#include "clock.h"

uint32_t hal_time_ms(void) {
    return system_millis;
}
