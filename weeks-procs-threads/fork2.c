// Demo fork.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>  // because man waitpid() said we'd need this

char *indent = "===============";

// try
//   1. 2nd sleep only
//   2. 1st sleep only
//   3. no exit, first sleep

int main(void) {
    int pid, rc;

    pid = getpid();
    printf("%s I'm process %d, and I'm about to fork\n", indent, pid);

    rc  = fork();
    if (0 == rc) {
        pid = getppid();
        // sleep(5);  // (1st sleep) try reducing or eliminating this!
        printf("Hi, I'm the child, and my parent is %d\n", pid);
        exit(21); // try eliminating this, but adding the next
        // indent = "(who is saying this?)";
    }

    sleep(5); // (2nd sleep) try reducing or eliminating this!
    pid = rc;
    printf("%s my child has pid %d\n", indent, pid);

    return 0;
}
