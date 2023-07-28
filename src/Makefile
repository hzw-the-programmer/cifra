# Makefile.rules
CC = armcc
AR = armar

IGNOR_WARNNINGS = --diag_suppress 1,9,61,66,68,111,117,144,152,167,170,174,177,186,188,191,223,226,236,494,513,550,940,1134,1287,1294,1295,1296,1381,1441,1608,1652,1764,1786,3017,3052
CFLAGS += --cpu cortex-a7 -O2 --apcs /interwork/ $(IGNOR_WARNNINGS) --fpu VFPv4 --enum_is_int \
	  -D_RTOS -D_DEBUG --loose_implicit_cast --c99 --gnu
CPPFLAGS += -I./ext

ARFLAGS = --create

SOURCES = aes.o sha256.o sha512.o chash.o hmac.o pbkdf2.o modes.o eax.o \
	  gf128.o blockwise.o cmac.o salsa20.o chacha20.o curve25519.o \
	  gcm.o cbcmac.o ccm.o sha3.o sha1.o poly1305.o \
	  norx.o chacha20poly1305.o drbg.o ocb.o sha3_shake.o

cifra.a: $(SOURCES)
	$(AR) $(ARFLAGS) $@ $?

clean:
	@del /F /Q /S *.o *.a
