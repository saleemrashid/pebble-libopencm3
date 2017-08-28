TREZOR_DIR      := $(abspath trezor-mcu)

NAME            := snowy_fw

OBJS            += main.o
OBJS            += setup.o

CPPFLAGS        += -DBTN_PORT=GPIOG -DBTN_PIN_NO=GPIO4 -DBTN_PIN_YES=GPIO1
OBJS            += $(TREZOR_DIR)/buttons.o

LDFLAGS         += -Wl,-wrap,oledInit -Wl,-wrap,oledRefresh
OBJS            += oled.o
OBJS            += $(TREZOR_DIR)/oled.o

OBJS            += $(TREZOR_DIR)/layout.o
OBJS            += $(TREZOR_DIR)/rng.o
OBJS            += $(TREZOR_DIR)/util.o

OBJS            += $(TREZOR_DIR)/gen/bitmaps.o
OBJS            += $(TREZOR_DIR)/gen/fonts.o

LDLIBS          += -lpebble_opencm3
LIBDEPS         += $(TOP)libpebble_opencm3.a

include ../Makefile.include

CPPFLAGS        += -I$(TREZOR_DIR) -I$(TREZOR_DIR)/gen
