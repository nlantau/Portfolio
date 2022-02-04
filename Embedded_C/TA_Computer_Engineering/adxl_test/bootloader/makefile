# nlantau, 2021-05-17
# MakeFile for Arch Linux - Burn bootloader or Arduino IDE compiled .hex
#
##############################################################################
#
# AVR Makefile for ATmega328p bootloader and Arduino IDE .hex
#
# Make sure to runt make with sudo
#
##############################################################################

# Path to 'Arduino328p.hex'
BOOTLOADER       = Arduino328p

# Write program in Arduino IDE. Compile in Arduino IDE. Grab /tmp-folder from where the compile .hex is
# Run: `find /tmp -name "*.ino.hex" 2>/dev/null` to find the .hex otherwise...

SKETCH           = Blink123
TMPPATH          = /tmp/arduino_build_469325
INO              = $(TMPPATH)/$(SKETCH).ino


# Change PORT and PROGRAMMER as needed
PORT             = /dev/ttyACM0
MCU              = atmega328p
PROGRAMMER       = avrispMkII
BAUD             = 115200
HZ               = 16000000L

AVRDUDE          = avrdude

#***** FUSES ****************************************************************#
# Low : 0xFF = Nothing programmed in clock byte
# High: 0xD6 = SPIEN, EESAVE, BOOTRST
# Ext : 0xFF = Brown-out detection disabled
# Ext : 0xFD = Brown-out detection at VCC=2.7V

FUSEARGS         = lfuse:w:0xff:m -U hfuse:w:0xd6:m -U efuse:w:0xff:m
AVRDUDEFLAGS     = -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U $(FUSEARGS) -U flash:w:$(MAIN).hex:i

all:
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U $(FUSEARGS) -U flash:w:$(INO).hex:i

bootloader:
	$(AVRDUDE) -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U $(FUSEARGS) -U flash:w:$(BOOTLOADER).hex:i



# All below is not working

LIBRARIES        = /home/nlantau/Arduino/libraries
HW               = /usr/share/arduino/hardware
TOOLS            = /usr/share/arduino/tools-builder
HPATH            = /tmp/arduino_build_147980/$(SKETCH)
BCACHE           = /tmp/arduino_cache_396624
BUILDPATH        = /tmp/arduino_build_147980
PRECOMPILEDCORE  = /arduino_cache_396624/core/core_archlinux-arduino_avr_uno_33334de5e2d3c2672266eacd2ab9ae3a.a

compile:
	arduino-builder -dump-prefs -logger=machine -hardware $(HW) -tools $(TOOLS) -libraries $(LIBRARIES) \
			-fqbn=archlinux-arduino:avr:uno -vid-pid=1FFB_00BB -ide-version=10815 \
			-build-path $(BUILDPATH) -warnings=none -build-cache $(BCACHE) \
			-prefs=build.warn_data_percentage=75 -verbose $(INO)

	arduino-builder -compile -logger=machine -hardware $(HW) -tools $(TOOLS) -libraries $(LIBRARIES) \
			-fqbn=archlinux-arduino:avr:uno -vid-pid=1FFB_00BB -ide-version=10815 \
			-build-path $(BUILDPATH) -warnings=none -build-cache $(BCACHE) \
			-prefs=build.warn_data_percentage=75 -verbose $(INO)

	avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections \
			-fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC \
			-mmcu=$(MCU) -DF_CPU=$(HZ) -DARDUINO=10815 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR \
			-I$(HW)/archlinux-arduino/avr/cores/arduino \
			-I$(HW)/archlinux-arduino/avr/variants/standard $(BUILDPATH)/sketch/$(SKETCH).cpp -o /dev/null

	avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections \
			-fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC \
			-mmcu=$(MCU) -DF_CPU=$(HZ) -DARDUINO=10815 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR \
			-I$(HW)/archlinux-arduino/avr/cores/arduino \
			-I$(HW)/archlinux-arduino/avr/variants/standard \
			$(BUILDPATH)/sketch/$(SKETCH).cpp -o $(BUILDPATH)/preproc/ctags_target_for_gcc_minus_e.cpp

	arduino-ctags -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns \
			--line-directives $(BUILDPATH)/preproc/ctags_target_for_gcc_minus_e.cpp

	avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections \
			-fno-threadsafe-statics -Wno-error=narrowing -MMD -flto \
			-mmcu=$(MCU) -DF_CPU=$(HZ) -DARDUINO=10815 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR \
			-I$(HW)/archlinux-arduino/avr/cores/arduino \
			-I$(HW)/archlinux-arduino/avr/variants/standard $(BUILDPATH)/sketch/$(SKETCH).cpp -o $(BUILDPATH)/sketch/$(SKETCH).cpp.o

	avr-gcc -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(MCU) -o $(HPATH).elf $(BUILDPATH)/sketch/$(SKETCH).cpp.o \
			$(BUILDPATH)/..$(PRECOMPILEDCORE) -L$(BUILDPATH) -lm

	avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings \
			--change-section-lma .eeprom=0 $(BUILDPATH)/$(SKETCH).elf $(BUILDPATH)/$(SKETCH).eep

	avr-objcopy -O ihex -R .eeprom $(HPATH).elf $(HPATH).hex

	avr-size -A $(HPATH).elf