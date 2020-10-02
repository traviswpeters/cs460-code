#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


void __libc_csu_fini(void) {}
void __libc_csu_init(void) {}






int
__libc_start_main (int (*main) (int, char **, char ** MAIN_AUXVEC_DECL),
		 int argc, char **ubp_av,
		   __typeof (main) init,   // __libc_csu_init
		   void (*fini) (void),   // __lib_csu_fini
		 void (*rtld_fini) (void), void *stack_end)
{

  int result;
  char **argv = ubp_av;
  char **ev = &argv[argc + 1];

  result = main (argc, argv, ev);

   _exit(result);


}
