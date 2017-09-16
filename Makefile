NAME            := pebble_opencm3

OBJS            += backlight.o
OBJS            += clock.o
OBJS            += display.o
OBJS            += usart.o

OBJS            += FPGA.o

all: lib$(NAME).a

include Makefile.include

FPGA.o: FPGA.bin
	@printf "  OBJCOPY $@\n"
	$(Q)$(OBJCOPY) -I binary -O elf32-littlearm -B arm --rename-section .data=.rodata $< $@
