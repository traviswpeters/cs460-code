// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int i, count, num;
    unsigned char c;

    if ( (argc != 2) ) {
        fprintf(stderr,"usage: bytecopy bytes\n");
        exit(-1);
    }

    // get count of chars
    count = atoi(argv[1]);

    for (i = 0; i < count; i++) {
        num = read(0,&c,1);
        if (num!=1)  {
            fprintf(stderr,"read failed %d", num);
            exit(-1);
        }
        num = write(1,&c,1);
        if (num!=1)  {
            fprintf(stderr,"write failed %d", num);
            exit(-1);
        }
    }

    return 0;
}
