CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -O3
SCRS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SCRS))

myProgram: $(OBJS)
	gcc -o $@ $(OBJS)

.PHONY: clean depend
clean:
	rm -f *~ *.bak myProgram *.o
depend:
	makedepend $(SRCS)
