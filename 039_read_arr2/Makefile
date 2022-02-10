CC= gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -O3
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

myProgram: $(OBJS)
	gcc -o $@ $(OBJS)

.PHONY: clean depend
clean:
	rm -f *~ *.o myProgram *.bak
depend:
	makedepend -I /usr/include/x86_64-linux-gnu/ -I /usr/include/linux -I /usr/include/c++/ -I /usr/include/c++/7/tr1  -I /usr/include/c++/7 $(SRCS)
# DO NOT DELETE

test.o: /usr/include/c++/7/tr1/stdio.h /usr/include/c++/7/tr1/cstdio
test.o: /usr/include/c++/7/tr1/cstdio /usr/include/c++/7/tr1/stdlib.h
test.o: /usr/include/c++/7/tr1/cstdlib /usr/include/c++/7/tr1/cstdlib
test.o: /usr/include/linux/string.h
