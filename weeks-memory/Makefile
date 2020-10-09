#
# NOTE:
# THIS IS NOT A GOOD REFERENCE FOR MAKEFILES IN GENERAL.
# THIS MAKEFILE JUST MAKES IT EASY TO BUILD A BUNCH OF DIFFERENT DEMOS WE LOOK AT IN CLASS.
#
# FOR GOOD MAKEFILE REFERENCES, SEE
# - THE SLIDES/LINKS FROM CLASS
# - THE STARTER FILES FOR ASSIGNMENTS (e.g., pa1_release, pa2_release)
#

CC=gcc
CFLAGS=-ggdb -Wall -Wextra -std=c11 -m32
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = fault #heap psize32 psize64 strider

.PHONY: all clean

# targets
all: $(EXECS)
	@echo "\nDone! ~~> $(EXECS)"

### DEMOS

# also recall memory-related demos from processes & threads:
# - probe.c
# - address32.c
# - address64.c
# - ssf.c
# - malloc_mystery.c

fault: fault.c
	-$(CC) $(CFLAGS) -o $@ $^

heap: heap.c
	-$(CC) $(CFLAGS) -o $@ $^

psize32: psize.c
	-$(CC) -ggdb -Wall -Wextra -std=c11 -m32 -o $@ $^

psize64: psize.c
	-$(CC) -ggdb -Wall -Wextra -std=c11 -m64 -o $@ $^

strider: strider.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(EXECS) *.o *.i *.s *~
	@rm -rf *.dSYM/ # oops - compiled on mac! :)
