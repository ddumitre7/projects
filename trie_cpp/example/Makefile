
PROGRAM = example

INCLUDEDIRS = \
	-I../src

CXXSOURCES = \
	example.cpp

CXXOBJECTS = $(CXXSOURCES:.cpp=.o)

CXXFLAGS = $(INCLUDEDIRS) -O3 -Wall -std=c++17

CXX = g++

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

example.o: example.cpp ../src/trie.h
	$(CXX) $(CXXFLAGS) -c -o example.o example.cpp

clean:
	$(RM) $(CXXOBJECTS) $(PROGRAM)

run:
	./$(PROGRAM)