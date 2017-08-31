#ifndef _BACKLIGHT_H_
#define _BACKLIGHT_H_

#include <stdint.h>

#define BACKLIGHT_MAX (UINT8_MAX)

void backlight_setup(void);
void backlight_set(uint8_t value);

#endif /* _BACKLIGHT_H_ */
