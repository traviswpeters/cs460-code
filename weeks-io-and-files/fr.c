// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int fd, numbytes;
    unsigned int int_read;


    if (argc != 2) {
        printf("usage: fr filename\n");
        exit(-1);
    }

    // get filename
    printf("opening %s for reading\n", argv[1]);
    fd = open(argv[1], O_RDONLY);
    if (-1 == fd) {
        printf("open failed\n");
        exit(-1);
    }

    numbytes = read(fd, &int_read, sizeof(unsigned int));
    printf("read %d bytes: 0x%04x\n", numbytes, int_read);

    return 0;
}
