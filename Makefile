TARGET := boot
BUILD  := build
SOURCES := source

# tell make where devkitPro is
DEVKITPRO ?= /opt/devkitpro

CFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))

OFILES := $(CFILES:.c=.o)

CC := $(DEVKITPRO)/devkitPPC/bin/powerpc-eabi-gcc

CFLAGS := -O2 -mrvl -mcpu=750 -meabi -mhard-float

all: $(TARGET).dol

$(TARGET).elf: $(OFILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).dol: $(TARGET).elf
	@echo "Build complete (ELF ready). Convert to DOL if needed."
