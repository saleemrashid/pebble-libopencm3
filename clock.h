#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <stdint.h>

extern volatile uint32_t system_millis;

void clock_setup(void);
void timer_setup(void);

#endif /* _CLOCK_H_ */
