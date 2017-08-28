#include "oled.h"

#include "display.h"

uint8_t display[DISPLAY_SIZE];

void __wrap_oledInit(void) {
    display_setup();

    oledClear();
    oledRefresh();
}

void __wrap_oledRefresh(void) {
    const uint8_t *oledbuffer = oledGetBuffer();

    for (size_t i = 0; i < OLED_BUFSIZE; i++) {
	uint8_t x = (OLED_BUFSIZE - 1 - i) % OLED_WIDTH;
	uint8_t y = (OLED_BUFSIZE - 1 - i) / OLED_WIDTH * 8 + 7;

	uint8_t shift = 0;
	for (uint8_t shift = 0; shift < 8; shift++, y--) {
	    uint8_t color = (oledbuffer[i] >> shift) & 1 ? GColorWhiteARGB8 : GColorBlackARGB8;

	    display_set(display, x, y, color);
	}
    }

    display_frame_begin(display);
}
