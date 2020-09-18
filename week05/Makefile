CC = gcc
CFLAGS = -ggdb# -Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = probe sf defunct

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

clean:
	@rm -f $(EXECS) *.o *.i *.s *~
