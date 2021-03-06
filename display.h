#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stddef.h>
#include <stdint.h>

#include "colors.h"

typedef enum {
    PSDISPLAYCMD0_NULL = 0,
    PSDISPLAYCMD0_SET_PARAMETER = 1,
    PSDISPLAYCMD0_DISPLAY_OFF = 2,
    PSDISPLAYCMD0_DISPLAY_ON = 3,
    PSDISPLAYCMD0_DRAW_SCENE = 4,
} PDisplayCmd0;

typedef enum {
    PSDISPLAYCMD1_FRAME_BEGIN = 5,
} PDisplayCmd1;

typedef enum {
    PSDISPLAYSCENE_BLACK = 0,
    PSDISPLAYSCENE_SPLASH = 1,
    PSDISPLAYSCENE_UPDATE = 2,
    PSDISPLAYSCENE_ERROR = 3,
} PDisplayScene;

#define DISPLAY_WIDTH 144
#define DISPLAY_HEIGHT 168

#define DISPLAY_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)

void display_setup(void);
void display_frame_begin(const uint8_t *buffer);

#define DISPLAY_OFFSET_MSB(x, y) ((x) * DISPLAY_HEIGHT + (DISPLAY_HEIGHT - (y) - 1) / 2)
#define DISPLAY_OFFSET_LSB(x, y) (DISPLAY_OFFSET_MSB(x, y) + DISPLAY_HEIGHT / 2)

#define DISPLAY_MASK_LSB 0b010101
#define DISPLAY_MASK_MSB (DISPLAY_MASK_LSB << 1)

static inline void display_set(uint8_t *buffer, uint8_t x, uint8_t y, uint8_t color) {
    buffer[DISPLAY_OFFSET_LSB(x, y)] = (buffer[DISPLAY_OFFSET_LSB(x, y)] & (DISPLAY_MASK_LSB << (~y & 1))) | (color & DISPLAY_MASK_LSB) <<  (y & 1);
    buffer[DISPLAY_OFFSET_MSB(x, y)] = (buffer[DISPLAY_OFFSET_MSB(x, y)] & (DISPLAY_MASK_MSB >>  (y & 1))) | (color & DISPLAY_MASK_MSB) >> (~y & 1);
}

static inline uint8_t display_get(const uint8_t *buffer, uint8_t x, uint8_t y) {
    return ((buffer[DISPLAY_OFFSET_LSB(x, y)] >>  (y & 1)) & DISPLAY_MASK_LSB)
         | ((buffer[DISPLAY_OFFSET_MSB(x, y)] << (~y & 1)) & DISPLAY_MASK_MSB);
}

static inline void display_draw_bitmap(uint8_t *display, const uint8_t *bitmap) {
    for (uint8_t y = 0; y < DISPLAY_HEIGHT; y++) {
	for (uint8_t x = 0; x < DISPLAY_WIDTH; x++) {
	    display_set(display, x, y, *bitmap++);
	}
    }
}

#endif /* _DISPLAY_H_ */
