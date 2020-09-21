CC = gcc
CFLAGS = -ggdb -Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = probe sf defunct simple thread_spy atm

# targets
all: $(EXECS)
	@echo "Done! ~~> $(EXECS)"

### demos

probe: probe.c
	-$(CC) $(CFLAGS) -m32 -o $@ $^

sf: sf.c
	-$(CC) $(CFLAGS) -m32 -o $@ $^

defunct: defunct.c
	-$(CC) $(CFLAGS) -o $@ $^

simple: simple.c
	-$(CC) $(CFLAGS) -m32 -o $@ $^

thread_spy: thread_spy.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^

atm: atm.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^

clean:
	@rm -f $(EXECS) *.o *.i *.s *~
