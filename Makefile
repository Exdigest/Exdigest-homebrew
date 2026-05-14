TARGET := boot
BUILD  := build
SOURCES := source

LIBOGC := $(DEVKITPRO)/libogc

CFLAGS := -O2 -mrvl -mcpu=750 -meabi -mhard-float
LDFLAGS :=

all:
	@echo "If this runs, toolchain exists"
