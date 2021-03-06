#include <stdbool.h>
#include <stdio.h>

#include "backlight.h"
#include "clock.h"
#include "display.h"
#include "usart.h"

uint8_t display[DISPLAY_SIZE];

#define BLOCK_SIZE 24

static inline void draw_block(uint8_t *buffer, uint8_t _x, uint8_t _y, uint8_t _w, uint8_t _h, uint8_t color) {
    for (uint8_t x = _x, w = _w; w > 0 && x < DISPLAY_WIDTH; x++, w--) {
	for (uint8_t y = _y, h = _h; h > 0 && y < DISPLAY_HEIGHT; y++, h--) {
	    display_set(buffer, x, y, color);
	}
    }
}

int main(void) {
    clock_setup();

    usart_setup();
    puts("\nHello World");

    display_setup();
    backlight_setup();

    static const uint8_t colors[] = {
	GColorRedARGB8,
	GColorOrangeARGB8,
	GColorYellowARGB8,
	GColorGreenARGB8,
	GColorBlueARGB8,
	GColorIndigoARGB8,
	GColorPurpleARGB8,
    };

    uint8_t index = 0;
    uint8_t backlight = 0;
    while (true) {
        for (uint8_t x = 0; x < DISPLAY_WIDTH; x += BLOCK_SIZE) {
	    index++;

            for (uint8_t y = 0; y < DISPLAY_HEIGHT; y += BLOCK_SIZE) {
		index = (index + 1) % sizeof(colors);
		draw_block(display, x, y, BLOCK_SIZE, BLOCK_SIZE, colors[index]);
            }

	    display_frame_begin(display);

	    for (uint32_t wait = 0; wait < 30000; wait++) {
		__asm__("nop");
	    }

	    backlight_set(backlight++);
        }
    }

    return 0;
}
