#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *indent = "===============";

int
main(void) {

  int pid, rc, status;


  pid = getpid();

  printf("%s I'm process %d, and I'm about to fork\n", indent, pid);
  
  rc  = fork();

  if (0 == rc) {

    pid = getpid();
    printf("Hi, I'm the child, and my pid is %d\n", pid);
    printf("Now, I will exec and print my pid via the exec'd program\n");
    // see man execlp.  program name, then arg list.
    // arg list must be terminated by a NULL
    // and the zeroth arg is (by convention) the name of the program
    rc = execlp("./pid", "pid",  NULL);
    printf("do you think this line will ever be printed? %d\n", rc);
    exit(-1); // 
  }

  return 0;

}
