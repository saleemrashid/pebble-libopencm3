#include <hal_uart_dma.h>
#include <hal_time_ms.h>

#include <btstack_config.h>

#include <stddef.h>

#include <libopencm3/cm3/nvic.h>

#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

static void (*block_received)(void) = NULL;
static void (*block_sent)(void) = NULL;
static void (*csr_irq_handler)(void) = NULL;

void hal_uart_dma_init(void) {
    rcc_periph_clock_enable(RCC_GPIOA);

    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO9 | GPIO10);
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11 | GPIO12);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10 | GPIO11 | GPIO12);

    rcc_periph_clock_enable(RCC_USART1);

    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_RTS_CTS);
    usart_set_mode(USART1, USART_MODE_TX_RX);

    usart_enable(USART1);

    rcc_periph_clock_enable(RCC_DMA2);

    nvic_enable_irq(NVIC_DMA2_STREAM7_IRQ);
    nvic_enable_irq(NVIC_DMA2_STREAM2_IRQ);

    bluetooth_power_cycle();
}

static void bluetooth_power_cycle(void) {
    gpio_clear(GPIOA, GPIO3);
    msleep(250);
    gpio_set(GPIOA, GPIO3);
    msleep(500);
}

void hal_uart_dma_set_block_received(void (*block_handler)(void)) {
    block_received = block_handler;
}

void hal_uart_dma_set_block_sent(void (*block_handler)(void)) {
    block_sent = block_handler;
}

int hal_uart_dma_set_baud(uint32_t baud) {
    usart_disable(USART1);
    usart_set_baudrate(USART1, baud);
    usart_enable(USART1);

    return 0;
}

static inline void usart_dma_transfer(uint32_t dma, uint8_t stream, uint32_t channel, uint32_t usart, uint32_t direction, const uint8_t *buffer, uint16_t len) {
    dma_stream_reset(dma, stream);

    dma_set_peripheral_address(dma, stream, (uint32_t) &USART_DR(usart));
    dma_set_memory_address(dma, stream, (uint32_t) buffer);
    dma_set_number_of_data(dma, stream, len);
    dma_set_transfer_mode(dma, stream, direction);
    dma_enable_memory_increment_mode(dma, stream);
    dma_set_peripheral_size(dma, stream, DMA_SxCR_PSIZE_8BIT);
    dma_set_memory_size(dma, stream, DMA_SxCR_MSIZE_8BIT);
    dma_set_priority(dma, stream, DMA_SxCR_PL_HIGH);
    dma_enable_transfer_complete_interrupt(dma, stream);
    dma_channel_select(dma, stream, channel);

    dma_enable_stream(dma, stream);
}

void hal_uart_dma_send_block(const uint8_t *buffer, uint16_t len) {
    usart_dma_transfer(DMA2, DMA_STREAM7, DMA_SxCR_CHSEL_4, USART1, DMA_SxCR_DIR_MEM_TO_PERIPHERAL, buffer, len);
    usart_enable_tx_dma(USART1);
}

void dma2_stream7_isr(void) {
    if (dma_get_interrupt_flag(DMA2, DMA_STREAM7, DMA_TCIF)) {
	dma_clear_interrupt_flags(DMA2, DMA_STREAM7, DMA_TCIF);
	usart_disable_tx_dma(USART1);
	dma_disable_transfer_complete_interrupt(DMA2, DMA_STREAM7);
	dma_disable_stream(DMA2, DMA_STREAM7);

	if (block_sent != NULL) {
	    block_sent();
	}
    }
}

void hal_uart_dma_receive_block(uint8_t *buffer, uint16_t len) {
    usart_dma_transfer(DMA2, DMA_STREAM2, DMA_SxCR_CHSEL_4, USART1, DMA_SxCR_DIR_PERIPHERAL_TO_MEM, buffer, len);
    usart_enable_rx_dma(USART1);
}

void dma2_stream2_isr(void) {
    if (dma_get_interrupt_flag(DMA2, DMA_STREAM2, DMA_TCIF)) {
	dma_clear_interrupt_flags(DMA2, DMA_STREAM2, DMA_TCIF);
	usart_disable_rx_dma(USART1);
	dma_disable_transfer_complete_interrupt(DMA2, DMA_STREAM2);
	dma_disable_stream(DMA2, DMA_STREAM2);

	if (block_received != NULL) {
	    block_received();
	}
    }
}

void hal_uart_dma_set_csr_irq_handler(void (*irq_handler)(void)) {
    csr_irq_handler = irq_handler;

    if (irq_handler == NULL) {
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO11);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO11);

	nvic_disable_irq(NVIC_EXTI15_10_IRQ);
    } else {
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO11);

	nvic_enable_irq(NVIC_EXTI15_10_IRQ);
	exti_select_source(EXTI11, GPIOA);
	exti_set_trigger(EXTI11, EXTI_TRIGGER_RISING);
	exti_enable_request(EXTI11);
    }
}

void exti15_10_isr(void) {
    exti_reset_request(EXTI11);

    if (csr_irq_handler != NULL) {
	csr_irq_handler();
    }
}

void hal_uart_dma_set_sleep(uint8_t sleep) {
    if (sleep) {
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
	gpio_set(GPIOA, GPIO12);
    } else {
	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO12);
	gpio_set_af(GPIOA, GPIO_AF7, GPIO12);
    }
}
