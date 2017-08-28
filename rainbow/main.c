#include <stdbool.h>
#include <stdio.h>

#include "display.h"
#include "usart.h"

uint8_t display[DISPLAY_SIZE];

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

	    display_frame_begin(display);
        }
    }

    return 0;
}