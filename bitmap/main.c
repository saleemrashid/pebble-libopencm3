#include "display.h"

#include "bitmap.h"

int main(void) {
    display_setup();

    uint8_t display[DISPLAY_SIZE];
    display_draw_bitmap(display, MagickImage);
    display_frame_begin(display);

    return 0;
}
