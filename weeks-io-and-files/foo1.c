// demo from discussion around I/O buffering.
//
// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int rc;

    printf("parent ");
    rc = fork();
    if (0 == rc) {
        printf("child ");
        exit(42);
    }
    wait(NULL); // for child to die

    printf("\n");
}
