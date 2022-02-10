CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -O3 
breaker: breaker.o
	gcc -o $@ breaker.o

.PHONY: clean
clean:
	rm -f *~ breaker
