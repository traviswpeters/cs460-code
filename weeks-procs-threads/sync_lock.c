// demo code for locks

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>   // for threads

#define KIDS  4

// statically
pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;
// or dynamically
// rc = pthread_mutex_init(&mutex,  NULL);

// helper function for pretty printing
char *spaces(int kid) {
    switch (kid) {
    case 0:
        return ":";
    case 1:
        return "--";
    case 2:
        return "++++";
    case 3:
        return "======";
    }
    return "********";
}

// a simple function demonstrating use of locks
void *lockfun(void *vargp) {
    int me = (int) vargp;
    // int me = *((int *)vargp);
    int rc;

    printf("%s Thread %d: wants to work on the complex data structure.\n", spaces(me), me);
    printf("%s Thread %d: trying to acquire lock...\n",spaces(me), me);

    rc = pthread_mutex_lock(&lock);
    if (rc) {
        printf("Thread %d: acquire failed!\n", me);
        exit(-1);
    }

    printf("%s Thread %d: acquired the lock!\n", spaces(me), me);
    printf("%s Thread %d: In critical section.  Now I can work on the data structure and temporarily make the invariant false!\n", spaces(me), me);
    sleep(1);
    printf("%s Thread %d: pretending to work on the data\n", spaces(me), me);
    sleep(1);
    printf("%s Thread %d: All done. I've restored the invariant. About to release lock...\n", spaces(me), me);

    rc = pthread_mutex_unlock(&lock);
    if (rc) {
        printf("Thread %d: release failed!\n", me);
        exit(-1);
    }

    printf("%s Thread %d: exiting.\n",spaces(me), me);

    return NULL;
}

int main(void) {
    int rc;
    int i;

    // some number of kids (threads)
    pthread_t kids[KIDS];

    for (i = 0; i < KIDS; i++) {
        rc = pthread_create(&kids[i],    // thread data structure to be written
                            NULL,        // attributes (we'll ignore)
                            lockfun,     // the function to be run
                            (void *) i); // the argument to the function
                            // (void *) &i); // the argument to the function
        if (rc) {
            printf("pthread_create failed!\n");
            exit(-1);
        }
    }

    for (i = 0; i < KIDS; i++) {
        rc = pthread_join(kids[i],  // thread to wait for
                          NULL);    // where to save the rc from pthread_exit(),
        // (check rc if we care. for this example, we don't)
    }

    return 0;
}
