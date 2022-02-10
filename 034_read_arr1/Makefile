CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -O3
DBGFLAGS = -Wall -pedantic -std=gnu99 -ggdb3 -DDEBUG 
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
DBGOBJS = $(patsubst %.c, %.dbg.o, $(SRCS))

myProgram: $(OBJS)
	gcc -o $@ $(OBJS)
myProgram-debug: $(DBGOBJS)
	gcc -o $@ -ggdb3  $(DBGOBJS)
%.dbg.o: %.c
	gcc $(DBGFLAGS) -c -o $@ $<
.PHONY: clean depend
clean:
	rm -f *~ myProgram *.bak *.o myProgram-debug
depend:
	makedepend $(SRCS)
	makedepend -a -o .dbg.o $(SRCS)

# DO NOT DELETE

test.o: /usr/include/stdio.h /usr/include/stdlib.h

test.dbg.o: /usr/include/stdio.h /usr/include/stdlib.h
