#ifndef _ykernel_h
#define _ykernel_h

#include <ylib.h>
#include <yalnix.h>
#include <hardware.h>

int helper_new_pid( struct pte *ptbr1);
void helper_retire_pid(int pid);
void helper_abort(char *msg);
void helper_maybort(char *msg);
void helper_check_heap(char *msg);


#ifndef SUCCESS
#define	SUCCESS			( 0)
#endif

#ifndef ERROR
#define	ERROR			(-1)
#endif

// A special error for LoadProgram:
// the operation cannot be completed, but the old
// region1 has already been thrown away
#ifndef KILL
#define	KILL                    (-2)
#endif




#endif
