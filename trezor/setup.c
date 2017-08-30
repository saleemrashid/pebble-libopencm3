#include "setup.h"

#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/rng.h>

#include "rng.h"

extern vector_table_t vector_table;

void __wrap_setup(void) {
	// Pebble bootloader doesn't relocate the vector table
	SCB_VTOR = (uint32_t) &vector_table;

	// set SCB_CCR STKALIGN bit to make sure 8-byte stack alignment on exception entry is in effect.
	// This is not strictly necessary for the current TREZOR system.
	// This is here to comply with guidance from section 3.3.3 "Binary compatibility with other Cortex processors"
	// of the ARM Cortex-M3 Processor Technical Reference Manual.
	// According to section 4.4.2 and 4.4.7 of the "STM32F10xxx/20xxx/21xxx/L1xxxx Cortex-M3 programming manual",
	// STM32F2 series MCUs are r2p0 and always have this bit set on reset already.
	SCB_CCR |= SCB_CCR_STKALIGN;

	// setup clock
	struct rcc_clock_scale clock = rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_120MHZ];
	rcc_clock_setup_hse_3v3(&clock);

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
