#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#include "display.h"

#define USART_CONSOLE USART3

uint8_t display[DISPLAY_SIZE];

static void usart_setup(void);

int main(void) {
    usart_setup();
    puts("\nHello World");

    display_setup();

    static const uint8_t colors[] = {
	0b110000, // Red
	0b110100, // Orange
	0b111100, // Yellow
	0b001100, // Green
	0b000011, // Blue
	0b010010, // Indigo
	0b100010, // Purple
    };

    uint8_t index = 0;
    while (true) {
        for (uint8_t x = 0; x < DISPLAY_WIDTH; x += 2) {
	    index++;

            for (uint8_t y = 0; y < DISPLAY_HEIGHT; y += 2) {
		index = (index + 1) % sizeof(colors);

		uint8_t color = colors[index];

                display_set(display, x,     y, color);
                display_set(display, x,     y + 1, color);
                display_set(display, x + 1, y, color);
                display_set(display, x + 1, y + 1, color);
            }

	    display_draw(display);
        }
    }

    return 0;
}

void usart_setup(void) {
    rcc_periph_clock_enable(RCC_USART3);

    usart_set_baudrate(USART3, 115200);
    usart_set_databits(USART3, 8);
    usart_set_stopbits(USART3, USART_STOPBITS_1);
    usart_set_parity(USART3, USART_PARITY_NONE);
    usart_set_flow_control(USART3, USART_FLOWCONTROL_NONE);
    usart_set_mode(USART3, USART_MODE_TX_RX);

    usart_enable(USART3);
}

ssize_t _write(int fd, const char *buf, size_t count) {
    switch (fd) {
    case STDOUT_FILENO:
    case STDERR_FILENO:
	for (size_t i = 0; i < count; i++) {
	    if (buf[i] == '\n') {
		usart_send_blocking(USART_CONSOLE, '\r');
	    }

	    usart_send_blocking(USART_CONSOLE, buf[i]);
	}

	return count;

    default:
	errno = EIO;
	return -1;
    }
}
