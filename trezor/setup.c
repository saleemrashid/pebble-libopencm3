#include "setup.h"

#include <stdio.h>

#include "usart.h"

void setup(void) {
    usart_setup();
    putc('\n', stdout);
    puts(__func__);
}
