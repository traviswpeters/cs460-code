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
# CFLAGS=-ggdb -Wall -Wextra -std=c11 -m32
CFLAGS=-ggdb -Wall -Wextra -std=gnu11 -m32
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = fault psize32 psize64 new_heap strider \
		brkfun vfork vfork-abuse vfork-heap sharing nullpointer

.PHONY: all clean

# targets
all: $(EXECS)
	@echo "\nDone! ~~> $(EXECS)"

### DEMOS

# also recall memory-related demos from processes & threads:
# - probe.c
# - address32.c
# - address64.c
# - sf.c
# - malloc_mystery.c

fault: fault.c
	-$(CC) $(CFLAGS) -o $@ $^

psize32: psize.c
	-$(CC) -ggdb -Wall -Wextra -std=c11 -m32 -o $@ $^

psize64: psize.c
	-$(CC) -ggdb -Wall -Wextra -std=c11 -m64 -o $@ $^

new_heap:
	@echo ''
	@echo 'new_heap.c is a simple implementation of heap code written for Yalnix'
	@echo 'after the glibc implementation got too complex for its own good. Thanks, Sean!'
	@echo '-> https://github.com/traviswpeters/yalnix-framework/blob/main/new_heap.c'
	@echo ''

strider: strider.c
	-$(CC) $(CFLAGS) -o $@ $^

### Advanced Topics

brkfun: brkfun.c
	-$(CC) $(CFLAGS) -o $@ $^

vfork: vfork.c
	-$(CC) $(CFLAGS) -o $@ $^

vfork-abuse: vfork-abuse.c
	-$(CC) $(CFLAGS) -o $@ $^

vfork-heap: vfork-heap.c
	-$(CC) $(CFLAGS) -o $@ $^

sharing: sharing.c
	-$(CC) $(CFLAGS) -o $@ $^

nullpointer: nullpointer.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(EXECS) *.o *.i *.s *~
	@rm -rf *.dSYM/ # oops - compiled on mac! :)
