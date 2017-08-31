#include "backlight.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

void backlight_setup(void) {
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_TIM12);

    /* B14 */
    gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO14);
    gpio_set_af(GPIOB, GPIO_AF9, GPIO14);

    /* TIM12 */
    timer_reset(TIM12);
    timer_set_mode(TIM12, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_period(TIM12, BACKLIGHT_MAX);
    timer_set_prescaler(TIM12, 0);
    timer_set_repetition_counter(TIM12, 0);
    timer_enable_counter(TIM12);

    /* TIM_OC1 */
    timer_set_oc_mode(TIM12, TIM_OC1, TIM_OCM_PWM2);
    timer_set_oc_polarity_low(TIM12, TIM_OC1);
    timer_enable_oc_output(TIM12, TIM_OC1);
}

void backlight_set(uint8_t value) {
    timer_set_oc_value(TIM12, TIM_OC1, value);
    timer_enable_oc_output(TIM12, TIM_OC1);
}
