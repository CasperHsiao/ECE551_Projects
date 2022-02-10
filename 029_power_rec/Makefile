CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -O3
DBGFLAGS = -Wall -pedantic -std=gnu99 -ggdb3 -DDEBUG
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
DBGOBJS = $(patsubst %.c, %.dbg.o, $(SRCS))
.PHONY: clean makedepend all
# Set mP and mP-dbg to both compile when make
all: myProgram myProgram-debug
myProgram: $(OBJS)
	gcc -o $@ $(OBJS)
myProgram-debug: $(DBGOBJS)
	gcc -o $@ -ggdb3 $(DBGOBJS)
# -o $@ specifies the name of the object to be %.dbg.o.
# Otherwise, it will be named %.o by default.
%.dbg.o: %.c
	gcc $(DBGFLAGS) -c -o $@ $<
clean:
	rm -f *.o *~ myProgram myProgram-debug
depend:
	makedepend $(SRCS)
	# -o .dbg.o specifies the object suffix
	# -a indicates appending dependencies to end
	makedepend -a -o .dbg.o $(SRCS)

# DO NOT DELETE

test-power.o: /usr/include/stdint.h /usr/include/stdio.h
test-power.o: /usr/include/stdlib.h
power.o: /usr/include/stdint.h /usr/include/stdio.h /usr/include/stdlib.h

test-power.dbg.o: /usr/include/stdint.h /usr/include/stdio.h
test-power.dbg.o: /usr/include/stdlib.h
power.dbg.o: /usr/include/stdint.h /usr/include/stdio.h /usr/include/stdlib.h
