#include <unistd.h>

#include <stdio.h>


int
main(void) {

  int pid, ppid;
  printf("hello world!!!\n");

  pid = getpid();
  ppid = getppid();
  printf("child, after exec, has pid %d and ppid %d\n", pid, ppid);
  
  return(42);

}
