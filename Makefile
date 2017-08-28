NAME            := pebble_opencm3

OBJS            += display.o
OBJS            += usart.o

OBJS            += FPGA.o

all: lib$(NAME).a

include Makefile.include
