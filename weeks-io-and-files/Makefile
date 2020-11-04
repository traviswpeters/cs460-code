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
EXECS = foo1 foo2 fpr fspy \
		fw fr \
		filefun bytes \
		writer reader

.PHONY: all clean

# targets
all: $(EXECS)
	@echo "\nDone! ~~> $(EXECS)"

### DEMOS - I/O Buffering

# - what's going on here?
# - where do you think the buffering might be happening?

foo1: foo1.c
	-$(CC) $(CFLAGS) -o $@ $^

foo2: foo2.c
	-$(CC) $(CFLAGS) -o $@ $^

fpr: fpr.c
	-$(CC) $(CFLAGS) -o $@ $^

### DEMOS - File Structure

fspy: fspy.c # text files
	-$(CC) $(CFLAGS) -o $@ $^
	@echo "Try:"
	@echo "./fspy onlinux.txt 100"
	@echo "./fspy onmac.txt 100"
	@echo "./fspy onwindows.txt 100"
	@echo "-> also try ./fspy on other types of files... /dev/*? /proc/*? pipes?"

fw: fw.c # binary files
	-$(CC) $(CFLAGS) -o $@ $^

fr: fr.c # binary files
	-$(CC) $(CFLAGS) -o $@ $^

### DEMOS - File Systems

filefun: filefun.c
	-$(CC) $(CFLAGS) -o $@ $^

bytes: bytes.c
	-$(CC) $(CFLAGS) -o $@ $^

### DEMOS - File Systems + Disks

# - use writer to create a 100K foo.dat
# - check its size with ls ­lh
# - check its diskspace with du ­h
# - use reader to check that it's all there
# - try making a copy with cp
# - what do ls ­lh and du ­h say about the copy size?
# - what's going on?

writer: writer.c
	-$(CC) $(CFLAGS) -o $@ $^

reader: reader.c
	-$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(EXECS) *.o *.i *.s *~ mystery.txt
	@rm -rf *.dSYM/ # oops - compiled on mac! :)
