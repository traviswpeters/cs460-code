// demo from discussion around I/O buffering.
//
// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    FILE *fp;
    fp = fopen("mystery.txt", "w");
    fprintf(fp, "yow \n");
    {
        if ( 0 == fork() ) {
            exit(0);
        }
    }
}
