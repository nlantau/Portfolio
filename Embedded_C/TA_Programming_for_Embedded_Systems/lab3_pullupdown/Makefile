# nlantau, 2021-04-15
# MakeFile for Gentoo Linux
#
##############################################################################
#
# AVR Makefile for ATmega328p without bootloader
# Don't forget to change 'clean:'-options
#
# Make sure to runt make with sudo
#
# Commands:
# make flash # This will compile and link the binary, then flash mcu with binary
# make clean # This will remove all object .hex, .o and .elf (binaries created after compilation)
#
##############################################################################

MAIN             = main
SRC              = $(MAIN).c

# Tree structure
# . (MAIN in root dir)
# └── lib <- everything else in lib folder (uart.h, uart.c, adc.c, adc.h, etc)

# LIBDIR1          = lib
LIBDIR1          = lib

# Change PORT and PROGRAMMER as needed
PORT             = /dev/ttyACM0
MCU              = atmega328p
PROGRAMMER       = avrispMkII
BAUD             = 115200
F_CPU            = 16000000

# generate list of objects
CFILES           = $(filter %.c, $(SRC))
EXT1            := $(foreach dir, $(LIBDIR1), $(wildcard $(dir)/*.c))
OBJ              = $(CFILES:.c=.o) $(EXT1:.c=.o)

# include path
INCLUDE         := $(foreach dir, $(LIBDIR1), -I$(dir))

CC               = avr-gcc
CFLAGS           = -Wall -Os -mmcu=$(MCU) $(INCLUDE) -DF_CPU=$(F_CPU)UL
OBJCOPY          = avr-objcopy
OFLAGS           = -j .text -j .data -O ihex $(MAIN).elf $(MAIN).hex
SIZE             = avr-size
SIZEFLAGS        = $(MAIN).elf
AVRDUDE          = avrdude
AVRTESTFLAG      = -c $(PROGRAMMER) -P $(PORT) -p $(MCU) -v


#***** FUSES ****************************************************************#
# Low : 0xFF = Nothing programmed in clock byte
# High: 0xD6 = SPIEN, EESAVE, BOOTRST
# Ext : 0xFF = Brown-out detection disabled
# Ext : 0xFD = Brown-out detection at VCC=2.7V

FUSEARGS         = lfuse:w:0xff:m -U hfuse:w:0xd6:m -U efuse:w:0xff:m
AVRDUDEFLAGS     = -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U $(FUSEARGS) -U flash:w:$(MAIN).hex:i


# Compile all files
all: $(MAIN).hex

# Test connection with programmer and MCU
test:
	$(AVRDUDE) $(AVRTESTFLAG)

# Use this to flash the MCU
flash: all
	$(AVRDUDE) $(AVRDUDEFLAGS)

# generate disassembly files for debugging
disasm: $(MAIN).elf
	$(OBJDUMP) -d $(MAIN).elf

# remove compiled files
clean:
	rm -f *.hex *.elf *.o
	$(foreach dir, $(LIBDIR1), rm -f $(dir)/*.o;)

# other targets
# objects from c files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# elf file
$(MAIN).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN).elf $(OBJ)

# hex file
$(MAIN).hex: $(MAIN).elf
	rm -f $(MAIN).hex
	$(OBJCOPY) $(OFLAGS)
	$(SIZE) $(SIZEFLAGS) $(MAIN).elf

debug:
	@echo
	@echo "CFILES:" $(CFILES)
	@echo "LIBDIR1:" $(LIBDIR1)
	@echo "EXT1:" $(EXT1)
	@echo
	@echo "OBJ" $(OBJ)
	@echo "INCLUDE:" $(INCLUDE)
	@echo

.PHONY: all clean flash
