#include "clock.h"

#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>

#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/pwr.h>

volatile uint32_t system_millis;

void clock_setup(void) {
    rcc_osc_on(RCC_HSI);
    rcc_wait_for_osc_ready(RCC_HSI);

    rcc_set_sysclk_source(RCC_CFGR_SW_HSI);
    rcc_wait_for_sysclk_status(RCC_HSI);

    rcc_periph_clock_enable(RCC_PWR);
    pwr_set_vos_scale(PWR_SCALE1);

    rcc_set_hpre(RCC_CFGR_HPRE_DIV_NONE);
    rcc_set_ppre1(RCC_CFGR_PPRE_DIV_4);
    rcc_set_ppre2(RCC_CFGR_PPRE_DIV_2);

    rcc_set_main_pll_hsi(16, 200, 2, 15, 0);

    rcc_osc_on(RCC_PLL);
    rcc_wait_for_osc_ready(RCC_PLL);

    flash_set_ws(FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS);

    rcc_set_sysclk_source(RCC_CFGR_SW_PLL);
    rcc_wait_for_sysclk_status(RCC_PLL);

    rcc_ahb_frequency = 100000000;
    rcc_apb1_frequency = 25000000;
    rcc_apb2_frequency = 50000000;
}

void timer_setup(void) {
    system_millis = 0;

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_set_reload((rcc_ahb_frequency / 1000) - 1);
    systick_clear();
    systick_counter_enable();
    systick_interrupt_enable();
}

void sys_tick_handler(void) {
    system_millis++;
}
