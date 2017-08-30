#include "flash.h"

#include <stddef.h>

bool storage_from_flash(void) {
    return false;
}

void storage_commit(void) {
}

void storage_clearPinArea(void) {
}

uint32_t *storage_getPinFailsPtr(void) {
    return NULL;
}

bool storage_increasePinFails(uint32_t *pinfailsptr) {
    (void) pinfailsptr;

    return true;
}

void storage_resetPinFails(uint32_t *pinfailsptr) {
    (void) pinfailsptr;
}

void storage_setU2FCounter(uint32_t u2fcounter) {
    (void) u2fcounter;
}
