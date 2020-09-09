# A good Makefile reference: http://www.csheeet.com/en/latest/notes/c_make.html

CC = gcc
CFLAGS = -ggdb #-Wall -std=c11
EXECS = probe address32 address64 test

.PHONY: all clean

all: $(EXECS)
	@echo "\nDone!\n~~> $(EXECS)"

probe: probe.c
	$(CC) $(CFLAGS) probe.c -o $@

address32: address.c
	$(CC) $(CFLAGS) -m32 address.c -o $@

address64: address.c
	$(CC) $(CFLAGS) address.c -o $@

test: test.c
	$(CC) $(CFLAGS) test.c -o $@

clean:
	rm -f $(EXECS)
	rm -rf *.dSYM/
