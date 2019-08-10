CXX = g++
INCLUDE = -I../include -I../include/usr -I../include/system -I../lib
FILES = test.cpp
OBJECTS = test.o

$(OBJECTS): $(FILES)
	$(CXX) -c $(FILES) $(INCLUDE)

g++_build: $(OBJECTS)
	$(CXX) -o test $(OBJECTS) 

clean:
	rm *.o test