// Dangerous ATM code
// S.W. Smith, CS58, Dartmouth College

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>   // for threads

//--------------------------------------------------------

#define ALICE   1
#define BOB     0
#define PLAYERS 2
#define name(x)  ( (x) ? "Alice" : "      Bob" )

//--------------------------------------------------------

// state of the system
typedef struct {
    int balance;
    int wallets[PLAYERS];
} state_t;

//--------------------------------------------------------

// pthread child functions take a void * for an argument.
// You can send more complex stuff by passing a pointer to a structure.
// Like this:
typedef struct {
    int who;
    state_t *sp;
    int amount;
    int coin;
} childarg;

//--------------------------------------------------------

// first call: initialize random_byte
// next 8 calls: return a random bit
int flip_coin(void) {
    static int fd;
    static int initialized = 0;
    static int bits_left = 0;
    static unsigned char random_byte;
    int random_bit;

    if (!initialized) {
        fd = open("/dev/urandom", O_RDONLY);
        if (fd < 0) {
            fprintf(stderr,"open failed\n");
            exit(-1);
        }
        initialized = 1;
    }

    if (0 == bits_left) {
        if (sizeof(random_byte) != read(fd, &random_byte, sizeof(random_byte))) {
            fprintf(stderr, "read failed\n");
            exit(-1);
        }
        bits_left = 8;
    }

    random_bit = random_byte & 0x01;
    random_byte >>= 1;
    bits_left--;

    return random_bit;
}

//--------------------------------------------------------

// randomly sleep. (can cause a thread switch)
void consider_interleaving(void) {
    if (flip_coin())
        sleep(1);
}

//--------------------------------------------------------

// this will be the function a child thread runs, to withdraw some money
// pthreads says: childfuns take void * and return void *
// so... we pass it  pointer to a childarg struct
void *withdraw(void *vargp) {
    childarg *argp = (childarg *) vargp; // convert the void-* to a childarg-*
    int amount  = argp->amount;
    state_t *sp = argp->sp;
    int me      = argp->who;

    consider_interleaving();
    printf("%s tries to withdraw $%d\n", name(me), amount);
    fflush(stdout);

    // try to withdraw some money...
    if (sp->balance >= amount) {
        consider_interleaving();
        sp->balance -= amount;
        sp->wallets[me] += amount;
        printf("%s's withdraw succeeds\n", name(me));
        fflush(stdout);
    } else {
        printf("%s's withdraw fails\n", name(me));
        fflush(stdout);
    }

    return NULL;
}

//--------------------------------------------------------

// print state of the system
void print_state(state_t *sp) {
    if (NULL == sp) {
        fprintf(stderr,"careful with that NULL pointer, Eugene\n");
        exit(-1);
    }

    printf("balance = %d, alice has %d, bob has %d\n",
            sp->balance, sp->wallets[ALICE], sp->wallets[BOB]);

    fflush(stdout);
}

int main(void) {
    pthread_t child1, child2;
    int rc;
    state_t state;
    childarg alice_arg, bob_arg;

    // set up state
    state.balance        = 100;
    state.wallets[ALICE] = 0;
    state.wallets[BOB]   = 0;

    flip_coin();

    // set up child arguments
    alice_arg.who        = ALICE;
    alice_arg.sp         = &state;
    alice_arg.amount     = 90;

    bob_arg.who          = BOB;
    bob_arg.sp           = &state;
    bob_arg.amount       = 80;

    print_state(&state);

    // launch kids
    rc = pthread_create(&child1,              // thread data structure to be written
                        NULL,                 // thread attributes (we'll ignore)
                        withdraw,             // the function to be run
                        (void *) &alice_arg); // the argument to the function

    if (rc) {
        printf("hey, child1 failed!\n");
        exit(-1);
    }

    rc = pthread_create(&child2,            // thread data structure to be written
                        NULL,               // thread attributes (we'll ignore)
                        withdraw,           // the function to be run
                        (void *) &bob_arg); // the argument to the function

    if (rc) {
        printf("hey, child2 failed!\n");
        exit(-1);
    }

    // now, wait until child exits
    rc = pthread_join(child1,  // thread to wait for
                      NULL);   // where to save the rc from pthread_exit(),
    // (check rc if we care. for this example, we don't)

    // now, wait until child exits
    rc = pthread_join(child2,  // thread to wait for
                      NULL);   // where to save the rc from pthread_exit(),
    // (check rc if we care. for this example, we don't)

    print_state(&state);
    return 0;
}
