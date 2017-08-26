OPENCM3_DIR     := $(abspath libopencm3)

OBJS            += main.o

CFLAGS          += -std=c99 -O3 -ggdb3
CPPFLAGS        += -MD
LDSCRIPT        := linker.ld
LDFLAGS         += -static -nostartfiles
LDLIBS          += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

ARCH_FLAGS      += -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CPPFLAGS        += -I$(OPENCM3_DIR)/include -DSTM32F4
LDFLAGS         += -L$(OPENCM3_DIR)/lib
LDLIBS          += -lopencm3_stm32f4

include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: all clean

all: firmware.bin firmware.elf

clean:
	$(Q)git clean -fdX

include $(OPENCM3_DIR)/mk/gcc-rules.mk

-include $(OBJS:.o=.d)
