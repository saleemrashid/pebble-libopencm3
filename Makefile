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

GDB_TCP_PORT	?= 63770
QEMU		?= qemu-pebble
QEMUFLAGS	?= -rtc base=localtime -serial null -serial null -serial stdio -gdb tcp::$(GDB_TCP_PORT),server
PEBBLE_SDK	?= $(HOME)/.pebble-sdk/SDKs/current/sdk-core/pebble

.PHONY: all clean qemu gdb

all: firmware.bin firmware.elf

clean:
	$(Q)git clean -fdX

qemu: snowy.bin snowy_spi.bin
	$(Q)$(QEMU) -machine pebble-snowy-bb -cpu cortex-m4 $(QEMUFLAGS) $(addprefix -pflash ,$^)

gdb:
	$(Q)$(GDB) -ex "target remote localhost:$(GDB_TCP_PORT)" -ex "sym $(abspath firmware.elf)"

snowy.bin: snowy_boot.bin firmware.bin
	$(Q)cat $^ > $@

# Empty recipe to override libopencm3 recipes
$(PEBBLE_SDK)/%:
	@

snowy_boot.bin: $(PEBBLE_SDK)/basalt/qemu/qemu_micro_flash.bin
	$(Q)head -c 16384 $< > $@

snowy_spi.bin: $(PEBBLE_SDK)/basalt/qemu/qemu_spi_flash.bin.bz2
	$(Q)bzcat $< > $@

include $(OPENCM3_DIR)/mk/gcc-rules.mk

-include $(OBJS:.o=.d)
