PORT=/dev/ttyACM0
MCU=atmega328p
F_CPU=16000000
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
CC=avr-gcc
OBJCOPY=avr-objcopy
TARGET=main
OBJECTS=${TARGET}.o serial.o

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	rm -f $(TARGET).hex
	$(OBJCOPY) -j .text -j .data -O ihex ${TARGET}.elf ${TARGET}.hex

$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJECTS)

disasm: $(TARGET).elf
	avr-objdump -d $(TARGET).elf

flash: $(TARGET).hex
	sudo avrdude -p $(MCU) -v -c arduino -P $(PORT) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)

