// Demo fork & wait

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>  // because man waitpid() said we'd need this

char *indent = "===============";

// try:
//   1. with the first return uncommented
//   2. then with it commented out
//   3. then with the child exit bigger than 255

int main(void) {
    int pid, rc, status;

    pid = getpid();
    printf("%s I'm process %d, and I'm about to fork\n", indent, pid);

    rc  = fork();
    if (0 == rc) {
        pid = getppid();
        printf("Hi, I'm the child, and my parent is %d\n", pid);
        printf("Now I shall sleep.\n");
        sleep(5);
        printf("I'm the child and I've woken up.  NOw I'll die!\n");
        exit(42); // try changing this to something bigger than 255
    }

    pid = rc;
    printf("%s my child has pid %d\n", indent, pid);
    printf("%s i'll wait for it to be done\n\n", indent);

    rc = waitpid(pid, &status, 0);
    printf("%s back from waitpid. rc = %d and status = %d\n", indent, rc, status);

    // return 0;

    if (WIFEXITED(status)) {
        printf("WIFEXITED(%d) is true\n", status);
        printf("WEXITSTATUS(%d) == %d\n", status, WEXITSTATUS(status));
    } else {
        printf("WIFEXITED(%d) is FALSE.  Ha!\n", status);
    }

    return 0;

}
