// A simple example of some pitfalls of working with threads.
// Author: Travis W. Peters, Montana State University (Fall 2019)
// Inspired by 
//      http://pages.cs.wisc.edu/~remzi/OSTEP/threads-intro.pdf
//      https://computing.llnl.gov/tutorials/pthreads/


// To build this program: 
//  gcc -std=c99 threads01.c -o t1 -lpthread


#include <stdio.h>     // printf()
#include <stdlib.h>    // exit()
#include <pthread.h> 

#define NUM_THREADS 10

static int target = 1000;
// static int target = 10000000;
static volatile int counter = 0;

// mythread()
// Simply adds 1 to counter repeatedly, in a loop
void *mythread(void *arg) {
    for (int i = 0; i < target; i++) {
        counter += 1;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    printf("main: begin (counter = %d)\n", counter);

    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    
    // create threads (pthread_create) that count
    for(t=0; t<NUM_THREADS; t++){
       rc = pthread_create(&threads[t], NULL, mythread, (void *)t);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    // wait for the threads to finish (pthread_join)
    // pthread_join() blocks the calling thread until the specified thread terminates.
    for(t=0; t<NUM_THREADS; t++){
       rc = pthread_join(threads[t], NULL);
       if (rc){
          fprintf(stderr, "ERROR; return code from join() is %d\n", rc);
          exit(-2);
       }
    }

    printf("main: done with both (counter = %d)\n", counter);

    pthread_exit(NULL);

    return 0;
}
