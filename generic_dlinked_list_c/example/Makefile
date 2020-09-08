
SOURCES := example.c ../src/dlinked_list.c
OBJS := $(SOURCES:.c=.o)
CC := gcc

INCLUDEDIRS = \
        -I../src

CFLAGS +=  $(INCLUDEDIRS) -Wall -std=c99 -pedantic -g

example: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

example.o: example.c ../src/dlinked_list.h
	$(CC) $(CFLAGS) -c $<

dlinked_list.o: ../src/dlinked_list.c ../src/dlinked_list.h
	$(CC) $(CFLAGS) -c $<
   
clean:
	rm -f *.o ../src/*.o example
