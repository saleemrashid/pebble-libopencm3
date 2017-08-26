MEMORY
{
	rom (rx)  : ORIGIN = 0x08004000, LENGTH = 512K - 16K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

INCLUDE libopencm3_stm32f4.ld
