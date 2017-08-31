#include "display.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/spi.h>

#include <stdio.h>

#define SPI_DISPLAY   SPI6
#define CLOCK_SPI     RCC_SPI6

#define PORT_DISPLAY  GPIOG
#define CLOCK_DISPLAY RCC_GPIOG

#define PIN_RST	      GPIO15
#define PIN_CS	      GPIO8
#define PIN_MISO      GPIO12
#define PIN_MOSI      GPIO14
#define PIN_SCK	      GPIO13
#define PIN_RST_DONE  GPIO9
#define PIN_INTN      GPIO10

static void display_cs(bool enabled);
static void display_draw_scene(PDisplayScene scene);

static bool display_fpga_wait_ready(uint32_t wait);
static void display_fpga_reset(bool cs);
static void display_fpga_program(void);

static inline void display_send(uint8_t data);
static inline void display_send_all(const uint8_t *data, size_t size);
static inline void delay(uint32_t wait);

void display_setup(void) {
    rcc_periph_clock_enable(CLOCK_DISPLAY);
    rcc_periph_clock_enable(CLOCK_SPI);

    /* GPIO_MODE_OUTPUT */
    gpio_mode_setup(PORT_DISPLAY, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, PIN_CS | PIN_RST);

    /* GPIO_MODE_INPUT */
    gpio_mode_setup(PORT_DISPLAY, GPIO_MODE_INPUT, GPIO_PUPD_NONE, PIN_RST_DONE | PIN_INTN);

    /* SPI_DISPLAY */
    gpio_mode_setup(PORT_DISPLAY, GPIO_MODE_AF, GPIO_PUPD_NONE, PIN_MISO | PIN_MOSI | PIN_SCK);
    gpio_set_af(PORT_DISPLAY, GPIO_AF5, PIN_MISO | PIN_MOSI | PIN_SCK);
    spi_set_master_mode(SPI_DISPLAY);
    spi_set_dff_8bit(SPI_DISPLAY);
    spi_set_clock_polarity_1(SPI_DISPLAY);
    spi_set_clock_phase_1(SPI_DISPLAY);
    spi_set_baudrate_prescaler(SPI_DISPLAY, SPI_CR1_BR_FPCLK_DIV_8);
    spi_enable_software_slave_management(SPI_DISPLAY);
    spi_set_nss_high(SPI_DISPLAY);
    spi_send_msb_first(SPI_DISPLAY);
    spi_enable(SPI_DISPLAY);

    /* Initialize display */
    for (uint8_t i = 0; i < 20; i++) {
	display_draw_scene(PSDISPLAYSCENE_SPLASH);

	if (display_fpga_wait_ready(1000)) {
	    break;
	}

	display_fpga_reset(false);
    }

    display_fpga_reset(true);
    display_fpga_program();
}

void display_frame_begin(const uint8_t *buffer) {
    delay(20);
    display_cs(true);
    delay(2000);
    display_send(PSDISPLAYCMD1_FRAME_BEGIN);
    display_cs(false);
    display_cs(true);
    display_send_all(buffer, DISPLAY_SIZE);
    display_cs(false);
}

void display_draw_scene(PDisplayScene scene) {
    delay(20);
    display_cs(true);
    delay(2000);
    display_send(PSDISPLAYCMD0_DRAW_SCENE);
    display_send(scene);
    display_cs(false);
}

void display_cs(bool enabled) {
    /* Inverted */
    if (enabled) {
	gpio_clear(PORT_DISPLAY, PIN_CS);
    } else {
	gpio_set(PORT_DISPLAY, PIN_CS);
    }
}

bool display_fpga_wait_ready(uint32_t wait) {
    while (--wait > 0) {
	if (!gpio_get(PORT_DISPLAY, PIN_INTN)) {
	    return true;
	}

	delay(4000);
    }

    return false;
}

void display_fpga_reset(bool cs) {
    display_cs(cs);
    gpio_clear(PORT_DISPLAY, PIN_RST);
    display_cs(true);
    delay(20);
    gpio_set(PORT_DISPLAY, PIN_RST);
    delay(20);
}

void display_fpga_program(void) {
    extern int _binary_FPGA_bin_start, _binary_FPGA_bin_size;

    const uint8_t *firmware = (uint8_t *) &_binary_FPGA_bin_start;
    size_t size = (size_t) &_binary_FPGA_bin_size;

    display_cs(true);
    display_send_all(firmware, size);
    display_cs(false);
}

void display_send(uint8_t data) {
    spi_send(SPI_DISPLAY, data);
}

void display_send_all(const uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
	display_send(data[i]);
    }
}

void delay(uint32_t wait) {
    while (--wait > 0) {
	__asm__("nop");
    }
}
