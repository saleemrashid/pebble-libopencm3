TREZOR_DIR      := $(abspath trezor-mcu)

NAME            := snowy_fw

OBJS            += flash.o
OBJS            += timer.o
OBJS            += usb.o

CPPFLAGS        += -DBTN_PORT=GPIOG -DBTN_PIN_NO=GPIO4 -DBTN_PIN_YES=GPIO1
OBJS            += $(TREZOR_DIR)/buttons.o

LDFLAGS         += -Wl,-wrap,oledInit -Wl,-wrap,oledRefresh
OBJS            += oled.o
OBJS            += $(TREZOR_DIR)/oled.o

LDFLAGS         += -Wl,-wrap,setup -Wl,-wrap,setupApp
OBJS            += setup.o
OBJS            += $(TREZOR_DIR)/setup.o

OBJS            += $(TREZOR_DIR)/layout.o
OBJS            += $(TREZOR_DIR)/rng.o
OBJS            += $(TREZOR_DIR)/util.o

OBJS            += $(TREZOR_DIR)/gen/bitmaps.o
OBJS            += $(TREZOR_DIR)/gen/fonts.o

OBJS            += $(TREZOR_DIR)/firmware/trezor.o

OBJS            += $(TREZOR_DIR)/firmware/coins.o
OBJS            += $(TREZOR_DIR)/firmware/crypto.o
OBJS            += $(TREZOR_DIR)/firmware/ethereum.o
OBJS            += $(TREZOR_DIR)/firmware/ethereum_tokens.o
OBJS            += $(TREZOR_DIR)/firmware/fsm.o
OBJS            += $(TREZOR_DIR)/firmware/layout2.o
OBJS            += $(TREZOR_DIR)/firmware/messages.o
OBJS            += $(TREZOR_DIR)/firmware/pinmatrix.o
OBJS            += $(TREZOR_DIR)/firmware/protect.o
OBJS            += $(TREZOR_DIR)/firmware/recovery.o
OBJS            += $(TREZOR_DIR)/firmware/reset.o
OBJS            += $(TREZOR_DIR)/firmware/signing.o
OBJS            += $(TREZOR_DIR)/firmware/storage.o
OBJS            += $(TREZOR_DIR)/firmware/transaction.o

OBJS            += $(TREZOR_DIR)/firmware/protob/pb_decode.o
OBJS            += $(TREZOR_DIR)/firmware/protob/pb_encode.o
OBJS            += $(TREZOR_DIR)/firmware/protob/messages.pb.o
OBJS            += $(TREZOR_DIR)/firmware/protob/storage.pb.o
OBJS            += $(TREZOR_DIR)/firmware/protob/types.pb.o

OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/address.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/base32.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/base58.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/bignum.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/bip32.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/bip39.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/curves.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ecdsa.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/hmac.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/nist256p1.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/pbkdf2.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ripemd160.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/secp256k1.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/sha2.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/sha3.o

OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/aes/aescrypt.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/aes/aeskey.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/aes/aestab.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/aes/aes_modes.o

OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/curve25519-donna-32bit.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/curve25519-donna-helpers.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/modm-donna-32bit.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/ed25519-donna-basepoint-table.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/ed25519-donna-32bit-tables.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/ed25519-donna-impl-base.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/ed25519.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/curve25519-donna-scalarmult-base.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/ed25519-sha3.o
OBJS            += $(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna/ed25519-keccak.o

OBJS            += $(TREZOR_DIR)/vendor/trezor-qrenc/qr_encode.o

LDLIBS          += -lpebble_opencm3
LIBDEPS         += $(TOP)libpebble_opencm3.a

LDLIBS          += -lpebble_bluetooth
LIBDEPS         += $(TOP)bluetooth/libpebble_bluetooth.a

include ../Makefile.include

CPPFLAGS        += -I.
CPPFLAGS        += -I$(TREZOR_DIR)
CPPFLAGS        += -I$(TREZOR_DIR)/gen
CPPFLAGS        += -I$(TREZOR_DIR)/firmware
CPPFLAGS        += -I$(TREZOR_DIR)/firmware/protob -DPB_FIELD_16BIT=1
CPPFLAGS        += -I$(TREZOR_DIR)/vendor/trezor-crypto -DUSE_ETHEREUM=1
CPPFLAGS        += -I$(TREZOR_DIR)/vendor/trezor-crypto/aes
CPPFLAGS        += -I$(TREZOR_DIR)/vendor/trezor-crypto/ed25519-donna
CPPFLAGS        += -I$(TREZOR_DIR)/vendor/trezor-qrenc -DQR_MAX_VERSION=0
