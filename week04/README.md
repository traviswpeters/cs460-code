# demo sequences

- _(Discussed in class / on slides: fork1.c, exec1.c)_
- fork2.c (simple demo)
- fork3.c (fork + wait)
- exec2.c
- pid.c
- pid2.c
- killer.c
- pipe.c
- hello-static.c

# Notes on syscalls for process control.

Unix programmers make frequent use of return values to communicate results

For example,

`fork()`...
- ...creates an identical process (with the exception of child PID and return value from fork())
- returns a negative value if there was an error
- returns 0 to the child process
- returns the child's PID (always > 0) to the parent process

A simple look at using `fork`:
```c
pid = fork();
if (0 == pid) {
    // I'm the child
}
// I'm the parent
```

A more correct way to `fork` and check return values / perform conditional logic:
```c
pid = fork();
if (pid < 0) {
    // fork failed!
} else if (0 == pid) {
    // child process
} else { // pid > 0
    // parent process; pid == child's process ID
}
```

### (Some) Image Tools for PA1

```bash
# convert - convert between image formats as well as resize an image, blur, crop, despeckle,
# dither, draw on, flip, join, re-sample, and much
# `man convert` says this is how we call it:
$ convert [input-option] input-file [output-option] output-file
```

```bash
# display - displays an image or image sequence on any X server.
# `man display` says this is how we call it:
$ display [options] input-file
```

# Some Command Line Tools To Check Out

```bash
# list open files
lsof
lsof -u vagrant
lsof -p pid
lsof +D /usr/
lsof +D /lib/
lsof /lib/x86_64-linux-gnu/ld-2.27.so
```

```bash
# strace picks up right after fork() --> should start at 'exec()'
strace cat /dev/null # syscall trace; notice open/read
strace -c cat /dev/null # summary of syscalls
strace cat not_a_real_file

strace ./mystery1 what does this do ?
strace -c ./mystery1 what does this do ?

ltrace # similar to strace; for tracing library calls
```

```bash
ps m # enable thread info in ps
ps m -o pid,tid,command # custom format that shows thread ID
```

```bash
top
top -p pid
htop # way better than top!
```

```bash
time ls # use shell's implementation of 'time'
/usr/bin/time ls # use kernel's implementation of 'time'
```

# Notes on pthreads

According to the POSIX Threads Programming, the correct ways to compile pthreads applications is with `-pthread`.

https://computing.llnl.gov/tutorials/pthreads/#Compiling

```bash
# how to compile programs that use pthreads
gcc -pthread ...
```

### Basics

```c
rc = pthread_create(&cars[i], NULL, OneVehicle, (void *)vehicle[i]);
```

```c
// Create threads
for (int i = 0; i < NUM_THREADS; i++) {
    rc = pthread_create(&cars[i], NULL, OneVehicle, (void *)vehicle[i]);
    // Check return code!
    if (rc) {
        fprintf(stderr, "Creating thread with id=%d failed\n", i);
        exit(-2);
    }
}
```

```c
// Join threads
for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(cars[i], NULL);
    free(vehicle[i]);
}
```

### Synchronization

```c
// Init a mutexes ("locks")
pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;

// Init a bunch of mutexes ("locks")
pthread_mutex_t lock[NLOCKS];
for (int i = 0; i < NLOCKS; i++) {
    pthread_mutex_init(&lock[i], NULL);
}
```

```c
// lock
rc = pthread_mutex_lock(&hanoverLock);
if (rc) {
    fprintf(stderr, "Thread %d's attempt to aquire Lock failed\n", id);
    exit(-3);
}

// ...do stuff while holding lock...

// unlock
rc = pthread_mutex_unlock(&hanoverLock);
if (rc) {
    fprintf(stderr, "Thread %d's attempt to release Lock failed\n", id);
    exit(-3);
}
```

```c
// Init a condition variable
pthread_cond_t someCondition = PTHREAD_COND_INITIALIZER;
```

```c
// Example conditions / condition variables:
pthread_cond_t cvar_direction = PTHREAD_COND_INITIALIZER; 		// condition variable for bridge direction
pthread_cond_t cvar_numcars = PTHREAD_COND_INITIALIZER; 		// condition variable for cars on bridge
```
