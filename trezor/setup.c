#include "setup.h"

#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/rng.h>

#include "clock.h"
#include "rng.h"

extern vector_table_t vector_table;

void __wrap_setup(void) {
	// Pebble bootloader doesn't relocate the vector table
	SCB_VTOR = (uint32_t) &vector_table;

	clock_setup();

	// enable RNG
	rcc_periph_clock_enable(RCC_RNG);
	RNG_CR |= RNG_CR_RNGEN;
	// to be extra careful and heed the STM32F205xx Reference manual, Section 20.3.1
	// we don't use the first random number generated after setting the RNGEN bit in setup
	random32();

	// enable CSS (Clock Security System)
	RCC_CR |= RCC_CR_CSSON;

	// set GPIO for buttons
	rcc_periph_clock_enable(RCC_GPIOG);
	gpio_mode_setup(GPIOG, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO4 | GPIO1);
}
