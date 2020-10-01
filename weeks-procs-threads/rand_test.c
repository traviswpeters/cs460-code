// basic demo showing how to use srand/rand to generate random numbers

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    // try chaging the seed value!
    int seed = 10;
    // try chaging the mod_num value!
    int mod_num = 2;

    srand(seed); // seed the PRNG
    for(;;) {
        printf(" %d \n", rand() % mod_num);
        sleep(1);
    }

    return 0;
}
