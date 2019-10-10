CXX = g++
AVR_CXX = avr-g++
INCLUDE = -I../src -I../src/usr -I../src/system -I../lib -I/usr/avr/include
SRC_DIR = ../src
FILES = test.cpp
OBJECTS = test.o

g++_build:
	$(CXX) -c $(FILES) $(INCLUDE)
	$(CXX) -o test $(OBJECTS) 

avr_build:
	$(AVR_CXX) -std=c++17 -Os -c $(FILES) $(INCLUDE)
	$(AVR_CXX) -o test.elf $(OBJECTS)

clean:
	rm *.o test
