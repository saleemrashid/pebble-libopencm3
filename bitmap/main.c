#include "backlight.h"
#include "display.h"

#include "bitmap.h"

int main(void) {
    backlight_setup();
    display_setup();

    backlight_set(BACKLIGHT_MAX);

    uint8_t display[DISPLAY_SIZE];
    display_draw_bitmap(display, MagickImage);
    display_frame_begin(display);

    return 0;
}
