CFLAGS=-std=c99 -pedantic -Wall

.PHONY: all clean
all: polybios

clean:
	rm -f polybios

polybios: polybios.c
	gcc ${CFLAGS} -o $@ polybios.c
