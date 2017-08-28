NAME            := snowy_fw

OBJS            += main.o

LDFLAGS         += -Wl,-wrap,oledInit -Wl,-wrap,oledRefresh
OBJS            += oled.o

OBJS            += setup.o

CPPFLAGS        += -DBTN_PORT=GPIOG -DBTN_PIN_NO=GPIO4 -DBTN_PIN_YES=GPIO1
OBJS            += trezor-mcu/buttons.o

OBJS            += trezor-mcu/layout.o
OBJS            += trezor-mcu/oled.o
OBJS            += trezor-mcu/rng.o
OBJS            += trezor-mcu/util.o

OBJS            += trezor-mcu/gen/bitmaps.o
OBJS            += trezor-mcu/gen/fonts.o

LDLIBS          += -lpebble_opencm3
LIBDEPS         += $(TOP)libpebble_opencm3.a

include ../Makefile.include

CPPFLAGS        += -Itrezor-mcu -Itrezor-mcu/gen
