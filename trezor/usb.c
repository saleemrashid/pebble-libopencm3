#include <stdbool.h>
#include <stdint.h>

#include "usb.h"

#include <libopencm3/stm32/iwdg.h>

#include "bt.h"
#include "timer.h"

static bool tiny = false;

void usbInit(void) {
    bluetooth_setup();
}

void usbPoll(void) {
    iwdg_reset();

    bluetooth_poll();
}

void usbReconnect(void) {
}

char usbTiny(char set) {
    char old = tiny;
    tiny = set;
    return old;
}

void usbSleep(uint32_t millis) {
    uint32_t start = system_millis;

    while ((system_millis - start) < millis);
}
