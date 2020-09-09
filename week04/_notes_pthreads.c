/*
 * Notes on pthreads.
 */

// According to the POSIX Threads Programming, the correct ways
// to compile pthreads applications is with '-pthread'.
// --> https://computing.llnl.gov/tutorials/pthreads/#Compiling
//
// gcc -pthread	...
//

////////////////////////////////////////////////////////////////////////////////////////////////////

rc = pthread_create(&cars[i], NULL, OneVehicle, (void *)vehicle[i]);

////////////////////////////////////////////////////////////////////////////////////////////////////

// Init a mutexes ("locks")
pthread_mutex_t lock =  PTHREAD_MUTEX_INITIALIZER;

// Init a bunch of mutexes ("locks")
pthread_mutex_t lock[NLOCKS];
for (int i = 0; i < NLOCKS; i++) {
    pthread_mutex_init(&lock[i], NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Init a condition variable
pthread_cond_t someCondition = PTHREAD_COND_INITIALIZER;

// e.g.,
pthread_cond_t cvar_direction = PTHREAD_COND_INITIALIZER; 		// condition variable for bridge direction
pthread_cond_t cvar_numcars = PTHREAD_COND_INITIALIZER; 		// condition variable for cars on bridge

////////////////////////////////////////////////////////////////////////////////////////////////////

// Create threads
for (int i = 0; i < NUM_THREADS; i++) {
    rc = pthread_create(&cars[i], NULL, OneVehicle, (void *)vehicle[i]);
    // Check return code!
    if (rc) {
        fprintf(stderr, "Creating thread with id=%d failed\n", i);
        exit(-2);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Join threads
for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(cars[i], NULL);
    free(vehicle[i]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

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
