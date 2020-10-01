// A simple example of some pitfalls of working with threads.
// Author: Travis W. Peters, Montana State University (Fall 2019)
// Inspired by
//      http://pages.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf
//      https://computing.llnl.gov/tutorials/pthreads/

// Try playing with the value of 'target'

#include <stdio.h>     // printf()
#include <stdlib.h>    // exit()
#include <pthread.h>   // for threads

#define NUM_THREADS 20

static int target = 1000;
// static int target = 10000000; // now try uncommenting me.... (and commenting out the line above)

// a global variable shared by all threads...
static volatile int counter = 0;

// mythread()
// Simply adds 1 to counter repeatedly, in a loop
void *mythread(void *arg) {
    printf("%d: begin\n", (int) arg);
    for (int i = 0; i < target; i++) {
        counter += 1;
    }
    printf("%d: done\n", (int) arg);
    pthread_exit(NULL);
}

int main(void) {
    printf("main: begin (counter = %d)\n", counter);

    pthread_t threads[NUM_THREADS];
    int rc;
    int t;

    // create threads that count
    for (t = 0; t < NUM_THREADS; t++){
       rc = pthread_create(&threads[t], NULL, mythread, (void *)t);  //<<<<<<<<<<<<<<<<<<<< create threads
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    // wait for the threads to finish
    // -> pthread_join() blocks the calling thread until the specified thread terminates.
    for (t = 0; t < NUM_THREADS; t++){
       rc = pthread_join(threads[t], NULL); //<<<<<<<<<<<<<<<<<<<< wait for threads to finish
       if (rc){
          fprintf(stderr, "ERROR; return code from pthread_join() is %d\n", rc);
          exit(-2);
       }
    }

    printf("main: done (counter = %d)\n", counter);

    pthread_exit(NULL);

    return 0;
}
