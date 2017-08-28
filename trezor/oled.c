#include "oled.h"

#include "display.h"

uint8_t display[DISPLAY_SIZE];

#define DISPLAY_OFFSET_X ((DISPLAY_WIDTH  - OLED_WIDTH)  / 2)
#define DISPLAY_OFFSET_Y ((DISPLAY_HEIGHT - OLED_HEIGHT) / 2)

static inline void display_draw(uint8_t x, uint8_t y, bool set) {
    uint8_t color = set ? GColorWhiteARGB8 : GColorBlackARGB8;

    display_set(display, DISPLAY_OFFSET_X + x, DISPLAY_OFFSET_Y + y, color);
}

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

	for (uint8_t shift = 0; shift < 8; shift++, y--) {
	    display_draw(x, y, (oledbuffer[i] >> shift) & 1);
	}
    }

    display_frame_begin(display);
}
