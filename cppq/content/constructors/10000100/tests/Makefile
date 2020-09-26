
PROGRAM = main

INCLUDEDIRS = \
	-I./

CXXSOURCES = \
	../main.cpp

CXXOBJECTS = $(CXXSOURCES:.cpp=.o)

CXXFLAGS = $(INCLUDEDIRS) -O3 -Wall -std=c++17

CXX = g++

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

main.o: ../main.cpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

clean:
	$(RM) $(CXXOBJECTS) \
	$(PROGRAM)

run:
	./$(PROGRAM)