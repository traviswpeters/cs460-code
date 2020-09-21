// Demo exec.

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>  // because man waitpid() said we'd need this

char *indent = "===============";

// Play with lines 34-35.
// Try:
//  1. exec hello
//  2. exec bogus

int main(void) {
    int pid, rc, status, ppid;

    pid = getpid();
    printf("%s I'm process %d, and I'm about to fork\n", indent, pid);

    rc  = fork();
    if (0 == rc) {
        pid = getpid();
        ppid = getppid();
        printf("Hi, I'm the child %d, and my parent is %d\n", pid, ppid);

        // see man execlp.  program name, then list of arguments as char strings.
        // arg list must be terminated by a NULL
        // and the zeroth arg is (by convention) the name of the program

        // try uncommenting this line and commenting out the next
        // rc = execlp("bogus", "bogus", "hello world", NULL);
        rc = execlp("./hello", "hello",  NULL);

        printf("do you think this line will ever be printed? rc = %d\n", rc);
        exit(-1);
    }

    pid = rc;
    printf("%s my child has pid %d\n", indent, pid);
    printf("%s i'll wait for it to be done\n\n", indent);

    // trust me: this means the parent will keep running until the child dies
    rc = waitpid(pid, &status, 0);
    printf("%s back from waitpid. rc = %d and status = %d\n", indent, rc, status);

    if (WIFEXITED(status)) {
        printf("WIFEXITED(%d) is true\n", status);
        printf("WEXITSTATUS(%d) == %d\n", status, WEXITSTATUS(status));
    } else {
        printf("WIFEXITED(%d) is FALSE.  Ha!\n", status);
    }

    return 0;
}
