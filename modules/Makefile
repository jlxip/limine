CC = ../../toolchain/bin/i386-elf-gcc

CFLAGS = -Os -pipe -Wall -Wextra

INTERNAL_CFLAGS = \
	-ffreestanding \
    -ffunction-sections \
    -fno-pic \
	-masm=intel \
	-mno-sse \
	-mno-sse2 \
	-mno-mmx \
	-mno-80387 \
    -mpreferred-stack-boundary=2 \
	-ffreestanding \
	-fno-stack-protector \
	-I. -I../../src \
	-Wno-address-of-packed-member

LDFLAGS = -O2

INTERNAL_LDFLAGS = \
	-nostdlib \
	-no-pie \
	-lgcc \
	-static-libgcc \
	-T../linker.ld

.PHONY: all clean

C_FILES := $(shell find ./ -type f -name '*.c' | sort)
OBJ := $(C_FILES:.c=.o) ../trampoline.o

all: $(MODNAME).mod

$(MODNAME).mod: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(INTERNAL_LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INTERNAL_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
