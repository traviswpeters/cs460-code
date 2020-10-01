// simple lock demo code

#define _XOPEN_SOURCE 700
// --> see: https://stackoverflow.com/a/18376848

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>   // for threads

// "NP" = "Not Portable." Don't count on this working elsewhere!
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP \
    { { 0, 0, 0, PTHREAD_MUTEX_RECURSIVE_NP, 0, { 0 } } }
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP \
    { { 0, 0, 0, PTHREAD_MUTEX_ERRORCHECK_NP, 0, { 0 } } }
#define PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP \
    { { 0, 0, 0, PTHREAD_MUTEX_ADAPTIVE_NP, 0, { 0 } } }

int main(int argc, char *argv[]) {
    int type;
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;

    if (argc >= 2) {
        switch (argv[1][0]) {
        case 'n':
            type = 0;
            break;
        case 'e':
            type = PTHREAD_MUTEX_ERRORCHECK_NP;
            break;
        case 'r':
            type = PTHREAD_MUTEX_RECURSIVE_NP;
            break;
        default:
            printf("invalid argument\n");
            exit(-1);
        }
    } else {
        printf("we need an argument: n, e, or r\n");
        exit(-1);
    }

    if (pthread_mutexattr_init(&attr) || pthread_mutexattr_settype(&attr, type) || pthread_mutex_init(&mutex,&attr)) {
        printf("pthread error\n");
        exit(-1);
    }

    printf("acquiring lock the first time\n");

    if (pthread_mutex_lock(&mutex)) {
        printf("hey, it failed!\n");
        exit(-1);
    }

    printf("success!\n");

    printf("acquiring lock the second time\n");
    printf("pausing, for dramatic effect\n");
    sleep(3);
    printf("here we go...\n");

    if (pthread_mutex_lock(&mutex)) {
        printf("hey, it failed!\n");
        exit(-1);
    }

    printf("success!\n");

    return 0;
}
