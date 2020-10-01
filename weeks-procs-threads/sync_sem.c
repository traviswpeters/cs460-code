// demo code for semaphores

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>   // for threads
#include <semaphore.h> // for semaphores

#define KIDS  4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
int count;

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

void *upfun(void *vargp) {
    int me = (int) vargp;
    int rc;

    while (1) {
        sleep(2);

        printf("%s Thread %d: trying to acquire lock...\n",spaces(me), me);

        rc = pthread_mutex_lock(&lock);
        if (rc) {
            printf("Thread %d: acquire failed!\n", me);
            exit(-1);
        }

        printf("%s Thread %d: acquired the lock!\n", spaces(me), me);
        printf("%s Thread %d: In critical section.  Now I'll pretend to add an object to our queue\n", spaces(me), me);
        count++;
        sleep(2);
        printf("%s Thread %d: All done.  I've restored the invariant. About to release lock...\n", spaces(me), me);
        printf("%d %s now on queue\n", count, count == 1 ? "object" : "objects");

        rc = pthread_mutex_unlock(&lock);
        if (rc) {
            printf("Thread %d: release failed!\n", me);
            exit(-1);
        }

        printf("%s Thread %d: upping the semaphore, in case anyone needs that object\n", spaces(me), me);

        rc = sem_post(&sem);
        if (rc) {
            printf("hey, it failed!\n");
            exit(-1);
        }
    }

    // not reached; this program runs until you kill it :-)

    return NULL;
}

void *downfun(void *vargp) {
    int me = (int) vargp;
    int rc;

    while (1) {
        sleep(2);

        printf("%s Thread %d: I'd like to take an object.  I'll sem down...\n",spaces(me), me);
        sem_wait(&sem);
        printf("%s Thread %d: I got the semaphore\n", spaces(me), me);
        printf("%s Thread %d: trying to acquire lock...\n",spaces(me), me);

        rc = pthread_mutex_lock(&lock);
        if (rc) {
            printf("Thread %d: acquire failed!\n", me);
            exit(-1);
        }

        printf("%s Thread %d: acquired the lock!\n", spaces(me), me);
        printf("%d %s now on queue\n", count, count == 1 ? "object" : "objects");
        printf("%s Thread %d: In critical section.  I'll pretend to take an object.\n", spaces(me), me);
        sleep(2);
        count--;
        printf("%d %s now on queue\n", count, count == 1 ? "object" : "objects");
        printf("%s Thread %d: All done.  I've restored the invariant. About to release lock...\n", spaces(me), me);

        rc = pthread_mutex_unlock(&lock);
        if (rc) {
            printf("Thread %d: release failed!\n", me);
            exit(-1);
        }
    }

    // not reached; this program runs until you kill it :-)

    return NULL;
}

int main(void) {
    int i, rc;

    // some number of kids (threads)
    pthread_t kids[KIDS];

    rc = sem_init(&sem, // the semaphore
                  0,    // stay within this process
                  0);   // initial value of semaphore
    if (rc) {
        printf("hey, it failed  rc=%d!\n",rc);
        exit(-1);
    }

    for (i = 0; i < KIDS; i++) {
        if (i % 2) {
            rc = pthread_create(&kids[i],    // thread data structure to be written
                                NULL,        // attributes (we'll ignore)
                                upfun,       // the function to be run
                                (void *) i); // the argument to the function
        } else {
            rc = pthread_create(&kids[i],    // thread data structure to be written
                                NULL,        // attributes (we'll ignore)
                                downfun,     // the function to be run
                                (void *) i); // the argument to the function
        }

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
