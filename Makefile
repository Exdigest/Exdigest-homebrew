TARGET		:= boot
BUILD		:= build
SOURCES		:= .
DATA		:= .
INCLUDES	:=

LIBS := -lpngu -lfat -lwiiuse -lbte -logc -lm

include $(DEVKITPPC)/wii_rules
