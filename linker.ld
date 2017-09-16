MEMORY
{
	rom (rx)  : ORIGIN = 0x08004000, LENGTH = 1024K - 16K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
}

INCLUDE libopencm3_stm32f4.ld
