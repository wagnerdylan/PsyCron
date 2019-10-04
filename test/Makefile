CXX = g++
INCLUDE = -I../src -I../src/usr -I../src/system -I../lib
SRC_DIR = ../src
FILES = test.cpp
OBJECTS = test.o

$(OBJECTS): $(FILES)
	$(CXX) -c $(FILES) $(INCLUDE)

g++_build: $(OBJECTS)
	$(CXX) -o test $(OBJECTS) 

clean:
	rm *.o test