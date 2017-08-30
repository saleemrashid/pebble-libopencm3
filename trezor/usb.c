#include <stdbool.h>
#include <stdint.h>

#include "usb.h"

#include "timer.h"

static bool tiny = false;

void usbInit(void) {
}

void usbPoll(void) {
}

void usbReconnect(void) {
}

char usbTiny(char set) {
    char old = tiny;
    tiny = set;
    return old;
}

void usbSleep(uint32_t millis) {
    uint32_t start = millis;

    while ((system_millis - start) < millis) {}
}
