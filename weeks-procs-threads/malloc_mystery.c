// use `make test` to compile
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LEN0 30
#define LEN1 (2<<20)

char dest[LEN0];

int main() {
    char *src = "there is no dark side of the moon, really";
    void *ptr;

    strncpy(dest, src, LEN0);

    printf("mallocing 0x%0x bytes...\n", LEN0);

    ptr = malloc(LEN0);
    if (ptr == NULL) {
        exit(-1);
    }

    printf("return %p\n", ptr);

    printf("mallocing 0x%0x bytes...\n", LEN1);

    ptr = malloc(LEN1);
    if (ptr == NULL) {
        exit(-1);
    }

    printf("return %p\n", ptr);

    return 0;
}

// After playing with the code and thinking about its output:

// 1. Run `strace ./test` to get a feel for what calls in the code above
//    do/do not translate to syscalls (as seen by strace)

// 2. Check out some of the discussion on Stack Overflow around this topic.
// https://stackoverflow.com/a/30542698
