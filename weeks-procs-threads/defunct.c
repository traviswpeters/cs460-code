#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pid, rc;

    printf("Zombie demo.  Open another window!\n");

    pid = getpid();
    printf("I'm process %d.  Check ps -a in the other window.\n", pid);
    sleep(10);

    printf("I'm about to fork\n");

    rc  = fork();
    if (0 == rc) {
        pid = getppid();
        printf("Hi, I'm the child, and my parent is %d. \n", pid);
        printf("Check ps -a in the other window.\n");
        sleep(10);
        printf("Child says: goodbye!\n");
        printf("Check ps -a in the other window.\n");
        exit(-1);
    }

    pid = rc;
    printf("my child has pid %d\n", pid);
    printf("but i'll delay collecting its error code\n");
    sleep (20);
    rc = waitpid(pid,NULL,0);
    printf("Parent collected the error code.  Check ps -a now\n");
    sleep(10);
    return 0;

}
