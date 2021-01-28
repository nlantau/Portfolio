#***** INFO *************************************************************************************************#
# nlantau, 2020-10-04
# updated, 2020-10-20
#
# AVR Makefile for ATmega328P
#
# Tree structure
# . (MAIN in root dir)
# └── lib
#

#***** SOURCE FILE ******************************************************************************************#

MAIN    = main
SRC     = $(MAIN).c

#***** LIB FOLDER *******************************************************************************************#
# This Makefile only allows for one (1) lib folder

LIBDIR1    = lib

#***** PORT & PROGRAMMER ************************************************************************************#

PORT       = /dev/cu.usbmodem003186532
MCU		   = atmega328p
PROGRAMMER = avrisp2
BAUD       = 115200

#***** GENERATE OBJECTS *************************************************************************************#

CFILES    = $(filter %.c, $(SRC))
EXT1     := $(foreach dir, $(LIBDIR1), $(wildcard $(dir)/*.c))
OBJ       = $(CFILES:.c=.o) $(EXT1:.c=.o)

#***** INCLUDE PATH *****************************************************************************************#

INCLUDE := $(foreach dir, $(LIBDIR1), -I$(dir))

#***** FLAGS & EXECUTABLES **********************************************************************************#

CC          = avr-gcc
CFLAGS      = -Wall -Os -mmcu=$(MCU) $(INCLUDE)
OBJCOPY     = avr-objcopy
OBJDUMP     = avr-objdump
OFLAGS      = -j .text -j .data -O ihex $(MAIN).elf $(MAIN).hex
SIZE        = avr-size
SIZEFLAGS   = --format=avr --mcu=$(MCU) $(MAIN).elf
AVRDUDE     = avrdude
AVRTESTFLAG = -c $(PROGRAMMER) -P $(PORT) -p $(MCU) -v

#***** FUSES ************************************************************************************************#
# Low : 0xFF = Nothing programmed in clock byte
# High: 0xD6 = SPIEN, EESAVE, BOOTRST
# Ext : 0xFF = Brown-out detection disabled
# Ext : 0xFD = Brown-out detection at VCC=2.7V

FUSEARGS        = lfuse:w:0xff:m -U hfuse:w:0xd6:m -U efuse:w:0xfd:m
AVRDUDEFLAGS    = -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U $(FUSEARGS) -U flash:w:$(MAIN).hex:i

# Targets
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
