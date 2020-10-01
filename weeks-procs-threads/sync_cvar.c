// demo code for cvars

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>   // for threads
#include <semaphore.h> // for semaphores

#define KIDS  4

// static initalization of both lock a cond. var.
pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cvar = PTHREAD_COND_INITIALIZER;

// condition initially true => first caller won't block
int condition = 1;

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

void *critfun(void *vargp) {
    int me = (int) vargp;
    int rc;

    while (1) {

        sleep(1);
        printf("%s Thread %d: would like to mess with the data structure, but only if the condition is true\n", spaces(me), me);
        printf("%s Thread %d: trying to acquire lock (so we don't race when testing the condition)\n", spaces(me), me);

        rc = pthread_mutex_lock(&lock);
        if (rc) {
            printf("Thread %d: acquire failed!\n", me);
            exit(-1);
        }

        printf("%s Thread %d: acquired the lock! Now, I'll test the condition\n", spaces(me), me);
        while (!condition) {
            printf("%s Thread %d: the condition is false, I'll wait (and release lock)\n", spaces(me), me);
            pthread_cond_wait(&cvar, &lock);
            printf("%s Thread %d: I'm back, with the lock. I'll test again\n", spaces(me), me);
        }

        printf("%s Thread %d: I have the lock, and the condition is true!\n", spaces(me), me);
        sleep(1);
        printf("%s Thread %d: I'm making the condition false, and releasing the lock\n", spaces(me), me);

        condition  = 0;
        rc = pthread_mutex_unlock(&lock);
        if (rc) {
            printf("hey, it failed!\n");
            exit(-1);
        }

        sleep(3);
        printf("%s Thread %d: trying to acquire lock...\n" ,spaces(me), me);

        rc = pthread_mutex_lock(&lock);
        if (rc) {
            printf("Thread %d: acquire failed!\n", me);
            exit(-1);
        }

        printf("%s Thread %d: acquired the lock! I'll make the condition true\n", spaces(me), me);
        condition = 1;
        printf("%s Thread %d: I'll signal the cvar, in case anyone was waiting for that\n", spaces(me), me);
        pthread_cond_signal(&cvar);
        printf("%s Thread %d: All done.  About to release lock...\n", spaces(me), me);

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

    for (i = 0; i < KIDS; i++) {
        rc = pthread_create(&kids[i],    // thread data structure to be written
                            NULL,        // attributes (we'll ignore)
                            critfun,     // the function to be run
                            (void *) i); // the argument to the function
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
