// demo: examine file structure (e.g., line endings) used on different OSs.
//  - onlinux.txt
//  - onmac.txt
//  - onwindows.txt
//
// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int i,j, fd, count, numread;
    char c, *buf;
    int reverse = 0;

    if ( (argc < 3) || (argc > 4) ) {
        printf("to read bytes from file: fspy filename bytes\n");
        printf("to read bytes, but display reverse order:  fspy filename bytes -r\n");
        exit(-1);
    }

    if (4 == argc)
        reverse = 1;

    // get filename
    printf("opening %s\n", argv[1]);
    fd = open(argv[1], O_RDONLY);
    if (-1 == fd) {
        printf("open failed\n");
        exit(-1);
    }

    // get count of chars
    count = atoi(argv[2]);

    buf = malloc(count);
    if (NULL == buf) {
        printf("malloc failed\n");
        exit(-1);
    }

    numread = read(fd, buf, count);

    for (i = 0; i < numread; i++) {
        if (reverse)
            j = numread - 1 -i;
        else
            j = i;

        c = buf[j];
        printf("%04d: 0x%02x", j, (unsigned char)c);
        if (isprint(c))
            printf(" (%c)\n",c);
        else
        printf("\n");
    }

    return 0;
}
