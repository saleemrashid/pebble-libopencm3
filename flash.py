#!/usr/bin/env python3
import argparse

from libpebble2.communication import PebbleConnection
from libpebble2.communication.transports.serial import SerialTransport
from libpebble2.protocol.system import SystemMessage
from libpebble2.services.putbytes import PutBytes, PutBytesType
from libpebble2.util.bundle import PebbleBundle

parser = argparse.ArgumentParser()

parser.add_argument("--firmware", metavar="FILE", help="Firmware binary", required=True, type=argparse.FileType("rb"))
parser.add_argument("--resources", metavar="FILE", help="System resources pack", required=True, type=argparse.FileType("rb"))

group = parser.add_mutually_exclusive_group(required=True)
group.add_argument("--serial", metavar="DEVICE", dest="transport", type=SerialTransport)

args = parser.parse_args()

pebble = PebbleConnection(args.transport)
pebble.connect()
pebble.run_async()

pebble.send_and_read(SystemMessage(message_type=SystemMessage.Type.FirmwareUpdateStart), SystemMessage)

PutBytes(pebble, PutBytesType.Firmware, args.firmware.read(), bank=0).send()

PutBytes(pebble, PutBytesType.SystemResources, args.resources.read(), bank=0).send()

pebble.send_packet(SystemMessage(message_type=SystemMessage.Type.FirmwareUpdateComplete))
