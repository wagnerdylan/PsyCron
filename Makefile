BIN=bin/PsyTest
OBJS=test/test.o
ODIR=bin

CC = avr-gcc
CXX = avr-g++
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BIN).elf $(BIN).hex $(OBJS)