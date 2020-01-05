OBJS = \
	src/lib/string.o \
	src/drivers/io.o \
	src/drivers/serial.o \
	src/drivers/framebuffer.o \
	src/drivers/interrupt.o \
	src/drivers/isr.o \
	src/drivers/flush_gdt.o \
	src/drivers/flush_idt.o \
	src/drivers/gdt.o \
	src/drivers/idt.o \
	src/drivers/pic.o \
	src/drivers/pit.o \
	src/drivers/keyboard.o \
	src/drivers/tty.o \
	src/kernel/kprint.o \
	src/kernel/kpanic.o \
	src/kernel/kmain.o \
	src/boot/boot.o
BIN = kernel.elf

CC = i686-elf-gcc
CFLAGS = -nostdlib -Isrc -Wall -Wextra -g
AS = nasm
ASFLAGS = -felf32 -g
LD = i686-elf-ld
LDFLAGS = -T linker.ld -m elf_i386 -g

.PHONY: all clean qemu

all: $(BIN)

clean:
	rm -f $(BIN) $(OBJS)

qemu: $(BIN)
	qemu-system-i386 -kernel $(BIN) -serial stdio

$(BIN): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)

%.o: %.s
	$(AS) -o $@ $< $(ASFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
