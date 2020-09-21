#include <unistd.h>
#include <stdio.h>

int main(void) {
    printf("hello world (from hello.c)!!!\n");

    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("child, after exec, has pid %d and ppid %d\n", pid, ppid);

    return 42;
}
