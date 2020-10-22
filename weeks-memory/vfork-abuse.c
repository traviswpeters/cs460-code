// vfork abuse code

// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int global = 0;

void vforker(void) {
    int value = 0;
    // int do_vfork = 1;
    int pid;
    // int i;

    printf("Hi, I'm the parent %d. Local = %d, global = %d\n", getpid(), value, global);
    printf("vforking a child...\n");

    pid = vfork();
    if (0 == pid) {
        printf("Hi, I'm the child %d. I'm changing both variables\n", getpid());
        value++;
        global++;
        printf("Child pauses dramatically...\n");
        sleep(5);
        printf("Child returns from vforker to sub...\n");
        return;
    }

    printf("Hi, I'm the parent again. Local = %d, global = %d\n", value, global);
    printf("Parent pauses dramatically\n");
    sleep(5);
    printf("Parent now returns from vforker to sub!\n");
    return;
}

void stacktrasher(void) {
    int array[512];
    int i;
    printf("process %d trashing the stack\n", getpid());
    for (i = 0; i < 512; i++)
        array[i] = 0;
    return;
}

void sub(void) {
    printf("yahoo---process %d calling vforker\n", getpid());
    vforker();
    printf("yahoo---process %d back from vforker\n", getpid());
    return;
}

int main(void) {
    sub();
    printf("yahoo---process %d back from sub, calling stacktrasher\n", getpid());
    stacktrasher();
    printf("yahoo---process %d back from stacktrasher\n", getpid());
    printf("process %d says goodbye!\n", getpid());
    return 0;
}
