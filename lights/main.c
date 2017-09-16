#include <stdbool.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/iwdg.h>
#include <libopencm3/stm32/rcc.h>

#include "backlight.h"

int main(void) {
    backlight_setup();

    rcc_periph_clock_enable(RCC_GPIOG);
    gpio_mode_setup(GPIOG, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO2 | GPIO3);

    uint8_t backlight = 0x80;
    while (true) {
	backlight_set(backlight);

	for (uint32_t wait = 0; wait < 50000; wait++) {
	    __asm__("nop");
	}

	uint32_t state = gpio_port_read(GPIOG);

	if ((state & (GPIO2 | GPIO3)) != (GPIO2 | GPIO3)) {
	    iwdg_reset();
	}

	if ((state & GPIO2) == 0 && backlight > 0) {
	    backlight--;
	}

	if ((state & GPIO3) == 0 && backlight < UINT8_MAX) {
	    backlight++;
	}
    }

    return 0;
}
