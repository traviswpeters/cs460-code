# A good Makefile reference: http://www.csheeet.com/en/latest/notes/c_make.html

CC = gcc
CFLAGS = -ggdb#-Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = fork1 fork2 fork3 forkbomb \
		exec1 exec2 pid pid2 killer pipe \
		write_html exec_display exec_convert \
		hello hello-static mystery1 uid \
		probe address32 address64 malloc_mystery \
		sf defunct \
		threads0 threads1 threads2 thread_spy thread_atm

.PHONY: all clean

# targets
all: $(EXECS)
	@echo "\nDone! ~~> $(EXECS)"

### PROCESSES & PROCESS CONTROL

fork1: fork1.c
	-$(CC) $(CFLAGS) -o $@ $^ # fork demo (1)

fork2: fork2.c
	-$(CC) $(CFLAGS) -o $@ $^ # fork demo (2)

fork3: fork3.c
	-$(CC) $(CFLAGS) -o $@ $^ # fork & wait demo

forkbomb: forkbomb.c
	-$(CC) $(CFLAGS) -o $@ $^ # fork bomb! (be careful where you run this...)

exec1: exec1.c
	-$(CC) $(CFLAGS) -o $@ $^ # exec demo (1)

exec2: exec2.c
	-$(CC) $(CFLAGS) -o $@ $^ # exec demo (2)

pid: pid.c
	-$(CC) $(CFLAGS) -o $@ $^

pid2: pid2.c
	-$(CC) $(CFLAGS) -o $@ $^

killer: killer.c
	-$(CC) $(CFLAGS) -o $@ $^ # kill demo

defunct: defunct.c
	-$(CC) $(CFLAGS) -o $@ $^

pipe: pipe.c
	-$(CC) $(CFLAGS) -o $@ $^ # pipes (thanks, doug!)

### EXTRA PA1 DEMOS / REFERENCES

write_html: write_html.c
	-$(CC) $(CFLAGS) -o $@ $^ # example: write an (html) file

exec_convert: exec_convert.c
	-$(CC) $(CFLAGS) -o $@ $^ # example: 'convert' a photo

exec_display: exec_display.c
	-$(CC) $(CFLAGS) -o $@ $^ # example: 'display' a photo

### THREADING

# All thread examples should be compiled with:
# -m32 (32-bit address spaces are a bit easier than 64-bit address spaces)
# -pthread (the preferred way to link to pthreads using gcc)

threads0: threads0.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^ # very simple pthreads demo (create/join)

threads1: threads1.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^ # pthreads - no synchronization...

threads2: threads2.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^ # pthreads - simple synchronization w/ mutexes

thread_spy: thread_spy.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^

thread_atm: thread_atm.c
	-$(CC) $(CFLAGS) -pthread -m32 -o $@ $^

### ADDRESS SPACE DEMOS

probe: probe.c
	-$(CC) $(CFLAGS) -m32 -o $@ $^

address32: address.c
	-$(CC) $(CFLAGS) -m32 -o $@ $^ # compile program in 32-bit mode

address64: address.c
	-$(CC) $(CFLAGS) -o $@ $^ # compile program in 64-bit mode (default)

sf: sf.c
	-$(CC) $(CFLAGS) -m32 -o $@ $^

malloc_mystery: malloc_mystery.c
	-$(CC) $(CFLAGS) -o $@ $^

### OTHER DEMOS

mystery1: mystery1.c
	-$(CC) $(CFLAGS) -o $@ $^ # try: ./mystery1 what does this do ?

hello: hello.c
	-$(CC) $(CFLAGS) -o $@ $^ # simple "hello world" support program

hello-static: hello-static.c
	-$(CC) $(CFLAGS) -static -L/usr/lib/debug/usr/lib64 -o $@ $^ # demo staticly linked lib!

uid: uid.c
	-$(CC) $(CFLAGS) -o $@ $^ # demo uid vs. euid

clean:
	@rm -f $(EXECS) *.o *.i *.s *~
	@rm -f index.html # produced by write_html
	@rm -rf *.dSYM/ # oops - compiled on mac! :)
