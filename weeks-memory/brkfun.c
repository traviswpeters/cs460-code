// demo code to experiment with calling brk/sbrk with a variety of addresses and sizes.

// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DELTA 17

int main(int argc, char *argv[]) {
    int rc;
    char c;
    int pid;
    char cstring[100];
    char *old,*new;

    pid = getpid();
    sprintf(cstring, "more /proc/%d/maps \n", pid);
    printf("\n\nRunning %s.\n\nLooking at the map....\n", argv[0]);
    system(cstring);
    printf("\n\n");

    old = sbrk(0);
    printf("My break is 0x%08x\n", (unsigned int)old);
    printf("Does that make sense with memory map?\n");
    sleep(4);

    if (1 == argc) {
        printf("Trying to incease the brk by %d bytes\n", DELTA);
        printf("Pausing dramatically...\n");
        sleep(4);

        rc = (int) sbrk(DELTA);
        if (rc == -1)
            printf("rc == %d\n", rc);

        new = sbrk(0);
        printf("new brk is 0x%08x\n", (unsigned int)new);
        printf("That's %d (0x%x) bytes higher\n", (int)(new-old), (int) (new-old));
        printf("reading from the new break\n");
        printf("Pausing dramatically...\n");
        sleep(4);

        c = *( (char *) new);
        printf("success (%d)???\n", c);

        sleep(1);
        printf("\n\nRunning pmap....\n");
        system(cstring);
        printf("\n\n");
    } else {
        printf("Trying to set brk to &main\n");
        printf("Pausing dramatically...\n");
        sleep(4);

        rc = (int) brk(&main);
        printf("rc == %d\n", rc);
        new = sbrk(0);
        printf("new brk is 0x%08x\n", (unsigned int)sbrk(0));
    }

    return 0;
}
