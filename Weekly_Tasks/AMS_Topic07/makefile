# CAB202 Teensy Makefile
# Lawrence Buckingham, September 2017.
# Queensland University of Technology.

# Replace these targets with your target (hex file) name, including the .hex part.

TARGETS = \
Exercise_1_Blink_LED0.hex \
Exercise_2_Bit_Fiddling.hex \
Exercise_3_Led_Buttons.hex \
Exercise_4_Game_Controller.hex

#	teensy_hello.hex \
#	teensy_lines.hex \
#	teensy_pixels.hex \
#	teensy_sprites.hex \
#	turn_on_led.hex

# Set the name of the folder containing libcab202_teensy.a

CAB202_TEENSY_FOLDER = ../cab202_teensy 

# ---------------------------------------------------------------------------
#	Leave the rest of the file alone.
# ---------------------------------------------------------------------------

all: $(TARGETS)

TEENSY_LIBS = -lcab202_teensy -lprintf_flt -lm 
TEENSY_DIRS =-I$(CAB202_TEENSY_FOLDER) -L$(CAB202_TEENSY_FOLDER)
TEENSY_FLAGS = \
	-std=gnu99 \
	-mmcu=atmega32u4 \
	-DF_CPU=8000000UL \
	-funsigned-char \
	-funsigned-bitfields \
	-ffunction-sections \
	-fpack-struct \
	-fshort-enums \
	-Wall \
	-Werror \
	-Wl,-u,vfprintf \
	-Os 

clean:
	for f in $(TARGETS); do \
		if [ -f $$f ]; then rm $$f; fi; \
		if [ -f $$f.elf ]; then rm $$f.elf; fi; \
		if [ -f $$f.obj ]; then rm $$f.obj; fi; \
	done

rebuild: clean all

%.hex : %.c
	avr-gcc $< $(TEENSY_FLAGS) $(TEENSY_DIRS) $(TEENSY_LIBS) -o $@.obj
	avr-objcopy -O ihex $@.obj $@