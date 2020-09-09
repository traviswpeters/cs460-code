CC = gcc
CFLAGS = -ggdb# -Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

# executables
EXECS = fork1 forkbomb threads1 threads2 uid mystery1 \
		fork-demo-simple fork-demo-wait exec-demo piddemo pid hello maine pipe killer

# targets
all: $(EXECS)
	@echo "\nDone!\n~~> $(EXECS)"

### DEMO CODE

fork1:
	-$(CC) $(CFLAGS) -o $@ $@.c

forkbomb:
	-$(CC) $(CFLAGS) -o $@ $@.c

threads1:
	-$(CC) $(CFLAGS) -o $@ threads1.c -pthread # no synchronization...

threads2:
	-$(CC) $(CFLAGS) -o $@ threads2.c -pthread # pthreads for synchronization

uid:
	-$(CC) $(CFLAGS) -o $@ uid_example.c

mystery1:
	-$(CC) $(CFLAGS) -o $@ mystery1.c # try: ./mystery1 what does this do ?

### OTHERS EXAMPLES

fork-demo-simple : fork-demo-simple.c
	-$(CC) $(CFLAGS) -o fork-demo-simple fork-demo-simple.c

fork-demo-wait : fork-demo-wait.c
	-$(CC) $(CFLAGS) -o fork-demo-wait fork-demo-wait.c

exec-demo : exec-demo.c
	-$(CC) $(CFLAGS) -o exec-demo exec-demo.c

piddemo : piddemo.c
	-$(CC) $(CFLAGS) -o piddemo piddemo.c

pid : pid.c
	-$(CC) $(CFLAGS) -o pid pid.c

hello : hello.c
	-$(CC) $(CFLAGS) -o hello hello.c

maine : maine.c
	-$(CC) $(CFLAGS) -static -L/usr/lib/debug/usr/lib64 -o maine maine.c

pipe : pipe.c
	-$(CC) $(CFLAGS) -o pipe pipe.c

killer : killer.c
	-$(CC) $(CFLAGS) -o killer killer.c

clean:
	@rm -f $(EXECS) *.o *.i *.s *~
