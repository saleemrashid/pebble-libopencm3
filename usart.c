#include "usart.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

#define USART_CONSOLE USART3

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
