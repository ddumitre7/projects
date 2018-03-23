# Compiler
CC=g++
# Flags
CFLAGS=-c -Wall -std=c++11

all: cb_exec

cb_exec: main.o circular_buffer_uint32.o
	$(CC) main.o circular_buffer_uint32.o -o cb_exec

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

circular_buffer_uint32.o: circular_buffer_uint32.cpp
	$(CC) $(CFLAGS) circular_buffer_uint32.cpp

clean:
	rm *o cb_exec

