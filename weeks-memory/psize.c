// basic memory exploration
// (this is more interesting if you build it with -m64)

// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>

int main(void) {
    void *pointer;
    int bits;
    long int gigs, g2;
    int g3;

    bits = sizeof(pointer)<<3;
    gigs = ((long) 1) << (bits - 30);
    g2   = (       1) << (bits - 30);
    g3   = (       1) << (bits - 30);

    printf("An address has %d bits\n", bits);
    printf("That means the address space is %ld gigabytes\n", gigs);
    printf("How much RAM is in this computer?\n\n");

    // what do these printfs show?  why?
    printf("(but if i don't cast before dividing, i only get %ld)\n", g2);
    printf("(and if i use an int, i only get %d)\n", g3);
    return 0;
}
