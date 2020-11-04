//
// travis peters, montana state university
// s.w. smith, dartmouth

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int fd;
  int delta;
  int foo = 23;
  char *path;

  if (argc < 3) {
    printf("usage: writer filename delta (in Kbytes)\n");
    return -1;
  }

  delta = atoi(argv[2]);
  delta <<= 10;
  path  = argv[1];

  printf("creating %s with initial pad of 0x%x\n", path, delta);

  fd = creat(path, S_IREAD | S_IWRITE);

  write(fd, &foo, 4);
  lseek(fd, delta, SEEK_SET);
  foo++;
  write(fd,&foo,4);

  return 0;
}
