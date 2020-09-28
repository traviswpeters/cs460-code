# demo sequences

- _(Discussed in class / on slides: fork1.c, exec1.c)_
- fork2.c (simple demo)
- fork3.c (fork + wait)
- exec2.c
- pid.c
- pid2.c
- killer.c
- pipe.c

- fork2.c (simple demo)
- fork3.c (fork + wait)
- exec2.c
- pid.c
- pid2.c
- killer.c
- pipe.c

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

### Creating/Joining Threads

**Create 1 new thread:**

```c
rc = pthread_create(&cars[i], NULL, OneVehicle, (void *)vehicle[i]);
```

**Create `NUM_THREADS` new threads and wait for them to finish:**

```c
#define NUM_THREADS 10

// ... other code ...

// Create threads
for (int i = 0; i < NUM_THREADS; i++) {
    rc = pthread_create(&cars[i], NULL, OneVehicle, (void *)vehicle[i]);
    // Check return code!
    if (rc) {
        fprintf(stderr, "Creating thread with id=%d failed\n", i);
        exit(-2);
    }
}

// some time later after you've created all of your threads...

// Join threads
for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(cars[i], NULL);
    free(vehicle[i]);
}
```

### Synchronization: Locks

We can use as many locks as we need.
Below are some references to get you started.

**LockInit**

```c
// In pthreads, a lock is a pthread_mutex_t.
// You can initialize one statically:
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// OR dynamically:
rc = pthread_mutex_init(&mutex, NULL);
```

**Acquire**

```c
rc = pthread_mutex_lock(&mutex);
if (rc) {
    printf("hey, it failed!\n");
    exit(-1);
}
```

**Release**

```c
rc = pthread_mutex_unlock(&mutex);
if (rc) {
    printf("hey, it failed!\n");
    exit(-1);
}
```
### Synchronization: Condition Variables

We can use as many condition variable as we need.
Below are some references to get you started.

**CVarInit**

```c
// In pthreads, a cond. var. is a pthread_cond_t.
// ... you’ll also need a pthread_mutex_t (see next slide)

// You can initialize one statically:
pthread_cond_t cvar1 = PTHREAD_COND_INITIALIZER;

// Or dynamically:
rc = pthread_cond_init(&cvar1, NULL);
```

**CVarWait**

```c
// Precondition: Suppose you have some mutex that has been initialized...
pthread_cond_wait(&cvar1, &mutex); // rc always 0; see the man page
```

**CVarSignal / CVarBroadcast**

```c
/* after you’re done, signal waiter(s)... */
pthread_cond_signal(&cvar1);
// vs.
pthread_cond_broadcast(&cvar1);
```
