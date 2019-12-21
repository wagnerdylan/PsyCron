CXX = g++
AVR_CXX = avr-g++
INCLUDE = -I../src -I../src/usr -I../src/system -I../lib -I/usr/avr/include
SRC_DIR = ../src
FILES = ../src/PsyCron.cpp test.cpp 
OBJECTS = PsyCron.o test.o 

g++_build:
	$(CXX) -DPSYCRON_BUFFER_SIZE=1000 -c $(FILES) $(INCLUDE)
	$(CXX) -o test $(OBJECTS) 

avr_build:
	$(AVR_CXX) -DPSYCRON_BUFFER_SIZE=1000 -std=c++17 -Os -c $(FILES) $(INCLUDE)
	$(AVR_CXX) -o test.elf $(OBJECTS)
	avr-objcopy -j .text -j .data -O ihex test.elf test.hex

g++_queue:
	$(CXX) -o test_split_queue test_split_queue.cpp $(INCLUDE)

clean:
	rm *.o test test_split_queue
