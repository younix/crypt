CFLAGS=-std=c99 -pedantic -Wall

.PHONY: all clean
all: polybios vigenere

clean:
	rm -f polybios vigenere

polybios: polybios.c
	gcc ${CFLAGS} -o $@ polybios.c

vigenere: vigenere.c
	gcc ${CFLAGS} -o $@ vigenere.c
