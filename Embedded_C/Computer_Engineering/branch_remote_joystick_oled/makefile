# nlantau, 2020-10-04
# AVR Makefile for Lab 5, atmega328p
# Don't forget to change 'clean:'-options
# if using for other project
#

MAIN		= main
SRC		= $(MAIN).c

# Tree structure
# . (MAIN in root dir)
# └── lib

LIBDIR1		= lib

# Change PORT and PROGRAMMER as needed
PORT		= /dev/cu.usbmodem003186532
MCU		= atmega328p
PROGRAMMER	= avrisp2
BAUD		= 115200

# generate list of objects
CFILES    = $(filter %.c, $(SRC))
EXT1     := $(foreach dir, $(LIBDIR1), $(wildcard $(dir)/*.c))
OBJ       = $(CFILES:.c=.o) $(EXT1:.c=.o)

# include path
INCLUDE := $(foreach dir, $(LIBDIR1), -I$(dir))

CC		= avr-gcc
CFLAGS		= -Wall -Os -mmcu=$(MCU) $(INCLUDE)
OBJCOPY		= avr-objcopy
OFLAGS		= -j .text -j .data -O ihex $(MAIN).elf $(MAIN).hex
SIZE		= avr-size
SIZEFLAGS	= --format=avr --mcu=$(MCU) $(MAIN).elf
AVRDUDE		= avrdude
AVRTESTFLAG	= -c $(PROGRAMMER) -P $(PORT) -p $(MCU) -v
AVRDUDEFLAGS	= -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(MAIN).hex:i


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
