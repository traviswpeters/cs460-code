// Inspired by a code example from Sean Smith's OS course @ Dartmouth---thanks!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;
int globalv;
char cstring[100];

int main(int argc, char *argv[], char* envp[]) {

    int localv, pid;
    void *stackaddr, *globaladdr, *argVaddr, *argaddr, *envVaddr, *envaddr;
    void *heapaddr;

    pid = getpid();
    printf("\nHi, I am process %d! Thanks for running me :-)\n", pid);

    sprintf(cstring,"pmap -X %d\n", pid);
    printf("\nRunning pmap....\n\n");
    system(cstring);

    stackaddr = (void *) &localv;
    globaladdr = (void *) &globalv;
    argVaddr  = (void *) argv;
    argaddr   = (void *) argv[0];
    envVaddr  = (void *) environ;
    envaddr   = (void *) getenv("PWD");
    heapaddr  = (void *) malloc(10);

    printf("\n");
    printf("the address of main   = %p\n", &main);
    printf("the address of printf = %p\n", &printf);
    printf("the address of getenv = %p\n", &getenv);
    printf("a stack address       = %p\n", stackaddr);
    printf("a global address      = %p\n", globaladdr);
    printf("the argv address      = %p\n", argVaddr);
    printf("argv[0]               = %p\n", argaddr);
    if (argaddr)
        printf("  value is [%s]\n", (char *) argaddr);

    printf("the environ address   = %p\n",envVaddr);
    printf("getenv(\"PWD\")         = %p\n", envaddr);
    if (envaddr)
        printf("   value is [%s]\n", (char *) envaddr);

    printf("a heap address        = %p\n\n", heapaddr);

    return 42;
}
