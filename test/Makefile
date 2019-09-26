CXX = g++
INCLUDE = -I../include -I../include/usr -I../include/system -I../lib
SRC_DIR = ../src
FILES = test.cpp
OBJECTS = test.o PsyRail.o

$(OBJECTS): $(FILES)
	$(CXX) -c $(FILES) $(SRC_DIR)/PsyRail.cpp $(INCLUDE)

g++_build: $(OBJECTS)
	$(CXX) -o test $(OBJECTS) 

clean:
	rm *.o test