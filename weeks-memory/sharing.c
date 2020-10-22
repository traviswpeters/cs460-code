// more memory management demo code

// travis peters, montana state university
// s.w. smith, dartmouth

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define LOOPS 20

char cstring[100];

int main(int argc, char *argv[]) {
    char c;
    void *p1;
    int i;
    int pid;
    int demo = 0;
    int flags;

    // pull out argument
    if (argc >= 2) {
        if ( ('-' == argv[1][0]) && (c = argv[1][1]) && (isdigit(c)) )
            demo = c - '0';
    } else {
        printf("-0: MAP_ANON | MAP_SHARED mappping\n");
        printf("-1: MAP_ANON | MAP_PRIVATE mappping\n");
        exit(0);
    }

    switch (demo) {
    case 0:
        flags = MAP_ANON | MAP_SHARED;
        break;
    default:
        flags = MAP_ANON | MAP_PRIVATE;
    }

    pid = getpid();
    sprintf(cstring,"pmap -x %d | tac\n", pid);
    printf("\n\nParent running pmap....\n");
    system(cstring);
    printf("\n\n");

    p1 = mmap(NULL, 0x8, PROT_READ | PROT_WRITE, flags, -1, 0);

    sleep(2);
    printf("parent mmap 0x%08x returned 0x%p\n",(int) 0, p1);
    sleep(2);
    printf("\n\nParent running pmap after mmap....\n");
    system(cstring);
    printf("\n\n");
    printf("Parent storing 1 at 0x%p\n", p1);
    fflush(stdout);
    *(int *)p1 = 1;
    printf("Parent pausing dramatically\n");
    sleep(10);
    printf("Parent forking!\n");

    if (0 == fork()) {
        int i;
        for (i = 0; i < LOOPS; i++) {
            printf("child sees %d at 0x%p\n", *(int *)p1, p1);
            fflush(stdout);
            sleep(1);
        }
        exit(0);
    }

    for (i = 0; i < LOOPS; i++) {
        printf("parent increments value at 0x%p\n", p1);
        fflush(stdout);
        *(int *)p1 = 1 + ( *(int *)p1);
        sleep(1);
    }

    return 0;
}
