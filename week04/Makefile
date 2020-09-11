CC = gcc
CFLAGS = -ggdb# -Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = fork1 fork2 fork3 forkbomb \
		exec1 exec2 pid pid2 killer pipe \
		hello hello-static mystery1 uid \
		threads1 threads2

# targets
all: $(EXECS)
	@echo "\nDone!\n~~> $(EXECS)"

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

killer : killer.c
	-$(CC) $(CFLAGS) -o $@ $^ # kill demo

pipe: pipe.c
	-$(CC) $(CFLAGS) -o $@ $^ # pipes (thanks, doug!)

### THREADING

threads1: threads1.c
	-$(CC) $(CFLAGS) -o $@ $^ -pthread # no synchronization...

threads2: threads2.c
	-$(CC) $(CFLAGS) -o $@ $^ -pthread # pthreads for synchronization

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
