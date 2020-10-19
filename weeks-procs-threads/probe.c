// Inspired by a code example from Sean Smith's OS course @ Dartmouth---thanks!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;
int globalv;
char cstring[100];

int main(int argc, char *argv[], char* envp[]) {

    int localv, pid;
    void *stackaddr, *globaladdr, *argVaddr, *argaddr, *envVaddr, *envpaddr, *envaddr;
    void *heapaddr;

    pid = getpid();
    printf("\nHi, I am process %d! Thanks for running me and giving me %d args :-)\n", pid, argc);

    if (4==sizeof(stackaddr)) {
        printf("-> compiled as 32-bit program (-m32)\n");
    } else if (8==sizeof(stackaddr)) {
        printf("-> compiled as 64-bit program\n");
    } else {
        printf("uh...what?\n");
        return -1;
    }

    // use pmap to print the (userspace) memory layout of this process
    sprintf(cstring,"pmap -X %d | tac\n", pid);
    printf("-> Running pmap....\n\n");
    system(cstring);

    // now let's get some addresses!
    stackaddr  = (void *) &localv;
    globaladdr = (void *) &globalv;
    argVaddr   = (void *) argv;
    argaddr    = (void *) argv[0];
    envVaddr   = (void *) environ;
    envpaddr   = (void *) envp;
    envaddr    = (void *) getenv("PWD");
    heapaddr   = (void *) malloc(10);

    // Q: before looking at the output, do you know where these addresses will be?!
    printf("\n*** Can you see where each item below 'lives' in the pmap output?! ***\n\n");
    printf("-> the address of main   = %p\n", &main);
    printf("-> the address of printf = %p\n", &printf);
    printf("-> the address of getenv = %p\n", &getenv);
    printf("-> a stack address       = %p\n", stackaddr);
    printf("-> a global address      = %p\n", globaladdr);
    printf("-> the argv address      = %p\n", argVaddr);
    printf("-> argv[0]               = %p\n", argaddr);
    if (argaddr)
        printf("   value is [%s]\n", (char *) argaddr);
    printf("-> the environ address   = %p\n", envVaddr);
    printf("-> the envp address      = %p\n", envpaddr);
    printf("-> getenv(\"PWD\")         = %p\n", envaddr);
    if (envaddr)
        printf("   value is [%s]\n", (char *) envaddr);
    printf("-> a heap address        = %p\n", heapaddr);

    // Stay alive until forcefully terminated...
    // (allows us to look at a "live process" from other vantage points; e.g., procfs)
    printf("\nNow I'm going to loop forever...");
    fflush(stdout);
    while (1) {
        sleep(10);
        printf(".");
        fflush(stdout);
    }

    return 0; // not reached
}
