// vfork demo code

// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void die(void) {
    exit(-1);
}

int main(int argc, char *argv[]) {
    int value = 0;
    int do_vfork = -1;
    int pid;
    int i;

    for (i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-v")) {
            do_vfork = 1;
        } else if (0 == strcmp(argv[i], "-f")) {
            do_vfork = 0;
        }
    }

    if (-1 == do_vfork) {
        printf("requires -v or -f argument\n");
        exit(-1);
    }

    printf("Hi, I'm the parent, and my local variable = %d\n", value);

    if (do_vfork) {
        printf("vforking a child...\n");
        pid = vfork();
    } else {
        printf("forking a child...\n");
        pid = fork();
    }

    if (0 == pid) {
        printf("-----Hi, I'm the child. The local variable = %d\n", value);
        value++;
        printf("-----Hi, I'm the child. I changed it to %d\n", value);
        printf("-----Child now waits dramatically befoe dying....\n");
        sleep(6);
        printf("-----Child dying!\n");
        die();
    }

    printf("Hi, I'm the parent. I'll read the local variable, but only after the child dies\n");
    wait(NULL);
    printf("Hi, I'm the parent again. The local variable = %d\n", value);

    return 0;
}
