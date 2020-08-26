
PROGRAM1 = example1
PROGRAM2 = example2
PROGRAM3 = example3

INCLUDEDIRS = \
	-I../src

CXXSOURCES1 = \
	example1.cpp

CXXSOURCES2 = \
	example2.cpp

CXXSOURCES3 = \
	example3.cpp

CXXOBJECTS1 = $(CXXSOURCES1:.cpp=.o)
CXXOBJECTS2 = $(CXXSOURCES2:.cpp=.o)
CXXOBJECTS3 = $(CXXSOURCES3:.cpp=.o)

CXXFLAGS = $(INCLUDEDIRS) -O3 -Wall -std=c++17

CXX = g++

all: $(PROGRAM1) $(PROGRAM2) $(PROGRAM3)

$(PROGRAM1): $(CXXOBJECTS1)
	$(CXX) -o $@ $(CXXOBJECTS1) $(LDFLAGS)

$(PROGRAM2): $(CXXOBJECTS2)
	$(CXX) -o $@ $(CXXOBJECTS2) $(LDFLAGS)

$(PROGRAM3): $(CXXOBJECTS3)
	$(CXX) -o $@ $(CXXOBJECTS3) $(LDFLAGS)

example1.o: example1.cpp ../src/trie.h
	$(CXX) $(CXXFLAGS) -c -o example1.o example1.cpp

example2.o: example2.cpp ../src/trie.h
	$(CXX) $(CXXFLAGS) -c -o example2.o example2.cpp

example3.o: example3.cpp ../src/trie.h
	$(CXX) $(CXXFLAGS) -c -o example3.o example3.cpp

clean:
	$(RM) $(CXXOBJECTS1) $(CXXOBJECTS2) $(CXXOBJECTS3) \
	$(PROGRAM1) $(PROGRAM2) $(PROGRAM3)

run:
	./$(PROGRAM1) ./$(PROGRAM2) ./$(PROGRAM3)