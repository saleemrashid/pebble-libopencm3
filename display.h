#include <stddef.h>
#include <stdint.h>

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
void display_draw(const uint8_t *buffer);
void display_draw_scene(PDisplayScene scene);
