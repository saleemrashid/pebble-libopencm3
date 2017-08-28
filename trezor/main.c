#include "buttons.h"
#include "layout.h"
#include "oled.h"
#include "setup.h"

int main(void) {
#ifndef APPVER
    setup();
    oledInit();
#else
    setupApp();
#endif

    const char *desc = NULL;

    while (true) {
	layoutDialog(&bmp_icon_info,
		"btnNo",
		"btnYes",
		desc,
		"line1",
		"line2",
		"line3",
		"line4",
		"line5",
		"line6");
	oledRefresh();

	do {
	    buttonUpdate();
	} while (!button.YesUp && !button.NoUp);

	if (button.YesUp) {
	    desc = "desc";
	} else if (button.NoUp) {
	    desc = NULL;
	}
    }
}
