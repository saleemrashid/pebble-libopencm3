BTSTACK_ROOT    := $(abspath btstack)
CHIPSET         := cc256x

NAME            := pebble_bluetooth

OBJS            += bt.o

OBJS            += bt_hal_cpu.o
OBJS            += bt_hal_time_ms.o
OBJS            += bt_hal_uart_dma.o

OBJS            += $(BTSTACK_ROOT)/src/ad_parser.o
OBJS            += $(BTSTACK_ROOT)/src/btstack_linked_list.o
OBJS            += $(BTSTACK_ROOT)/src/btstack_memory.o
OBJS            += $(BTSTACK_ROOT)/src/btstack_memory_pool.o
OBJS            += $(BTSTACK_ROOT)/src/btstack_run_loop.o
OBJS            += $(BTSTACK_ROOT)/src/btstack_util.o
OBJS            += $(BTSTACK_ROOT)/src/classic/btstack_link_key_db_memory.o
OBJS            += $(BTSTACK_ROOT)/src/hci.o
OBJS            += $(BTSTACK_ROOT)/src/hci_cmd.o
OBJS            += $(BTSTACK_ROOT)/src/hci_dump.o
OBJS            += $(BTSTACK_ROOT)/src/hci_transport_h4.o

OBJS            += $(BTSTACK_ROOT)/platform/embedded/btstack_run_loop_embedded.o
OBJS            += $(BTSTACK_ROOT)/platform/embedded/btstack_uart_block_embedded.o

OBJS            += bluetooth_init_cc2564B_1.5_BT_Spec_4.1.o

OBJS            += $(BTSTACK_ROOT)/chipset/$(CHIPSET)/btstack_chipset_$(CHIPSET).o

all: lib$(NAME).a

include ../Makefile.include

CFLAGS          += -Wno-error=implicit-fallthrough
CFLAGS          += -Wno-error=unused-parameter

CPPFLAGS        += -I.
CPPFLAGS        += -I$(BTSTACK_ROOT)/src
CPPFLAGS        += -I$(BTSTACK_ROOT)/platform/embedded
CPPFLAGS        += -I$(BTSTACK_ROOT)/chipset/$(CHIPSET)

include $(BTSTACK_ROOT)/chipset/$(CHIPSET)/Makefile.inc
