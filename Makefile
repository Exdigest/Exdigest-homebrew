DEVKITPRO ?= /opt/devkitpro
DEVKITPPC ?= $(DEVKITPRO)/devkitPPC

include $(DEVKITPRO)/libogc/base_rules

TARGET := boot
BUILD  := build
SOURCES := source

LIBS := -logc -lwiiuse -lbte -lasnd -lmad -logg -lvorbisidec -lvorbis -lm

CFLAGS := -O2 -mrvl -mcpu=750 -meabi -mhard-float

LDFLAGS :=

all: $(TARGET).dol
