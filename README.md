# pebble-libopencm3

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
```

## QEMU

```
make -C rainbow qemu # Start rainbow/snowy_fw.bin in QEMU
make -C rainbow gdb # Connect to QEMU with GDB
```

## Hardware

To test on real hardware, you can build a PBZ or you can use `rfcomm` and `flash.py`.

```
./flash.py --serial /dev/rfcomm0 --firmware rainbow/snowy_fw.bin --resources system_resources.pbpack
```

[1]: https://github.com/trezor/trezor-mcu
