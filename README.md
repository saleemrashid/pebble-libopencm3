# pebble-libopencm3

**DISCLAIMER: This is currently mostly untested and completely broken on actual hardware**

Custom firmware for Pebble Time (`snowy`) and Pebble Time Steel (`bobby`)

## Features

 * Custom display driver for the FPGA
 * Initial port of [TREZOR firmware][1] to Pebble
 * `stdout` and `stderr` redirect to QEMU serial (note: the `printf` family of
   functions do not work because they require an `sbrk` implementation)

## Building

```
git submodule update --init --recursive # Clone submodules
make # Build libpebble_opencm3.a
make -C lights # Build lights/snowy_fw.bin
make -C rainbow # Build rainbow/snowy_fw.bin
make -C trezor # Build trezor/snowy_fw.bin
```

## QEMU

```
make -C rainbow qemu # Start rainbow/snowy_fw.bin in QEMU
make -C rainbow gdb # Connect to QEMU with GDB
```

## Hardware

To test on real hardware, you can build a PBZ or you can use `rfcomm` and `flash.py`.

`lights` is functional on Pebble Time Steel:

```
./flash.py --serial /dev/rfcomm0 --firmware lights/snowy_fw.bin --resources system_resources.pbpack
```

You can use the Up and Down buttons to increase and decrease the backlight.

[1]: https://github.com/trezor/trezor-mcu
