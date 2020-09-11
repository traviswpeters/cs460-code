#include <unistd.h>
#include <stdio.h>

int main(void) {
    int pid;

    pid = getpid();
    printf("I'm process %d\n", pid);

    return 0;
}
