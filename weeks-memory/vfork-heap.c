// vfork demo code---what happens if the child abuses the heap?

// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DELTA 4096

void die(void) {
    exit(-1);
}

int main(void) {
    int pid;

    printf("Hi, I'm the parent, and my break is %p\n",sbrk(0));
    printf("vforking a child...\n");

    pid = vfork();
    if (0 == pid) {
        printf("-----Hi, I'm the child.  I'm going to try to increase my break by 0x%x\n",DELTA);
        printf("-----Child pauses dramatically....\n");
        sleep(4);
        sbrk(DELTA);
        printf("-----Child: my break is now %p\n", sbrk(0));
        printf("-----Child says goodbye!\n");
        die();
    }

    wait(NULL);
    printf("Parent pauses dramatically...\n");
    sleep(8);
    printf("Hi, I'm the parent, and my break is %p\n",sbrk(0));

    return 0;
}
