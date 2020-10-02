#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include "trace.h"
#include "manuallink.h"


int strlen(char *str);
int TtyWrite (int, void *, int);
void helper_check_heap(char *msg);

static char tty_buff[4096];		/* really big */

extern int lkra;




#ifndef TR_IM_WHO
#define TR_IM_WHO TR_IM_USER
#endif

int
TtyPrintf(int tty_id, char * fmt, ...)
{
  unsigned int ra;
  int zero_out_lkra = 0;
  int rc;

  if (0==lkra) {
    lkra = (unsigned int)(__builtin_return_address(0));
    zero_out_lkra = 1;
  }
  
  va_list args;

  va_start(args, fmt);
  vsprintf(tty_buff, fmt, args);
  va_end(args);



  rc = TtyWrite(tty_id, tty_buff, strlen(tty_buff));
  if (zero_out_lkra)
    lkra = 0;
      
    
  return rc;
}


void
TracePrintf(int level, char * fmt, ...)
{
  unsigned int ra;
  int zero_out_lkra = 0;



  if (0==lkra) {
    lkra = (unsigned int)(__builtin_return_address(0));
    zero_out_lkra = 1;
  }
    
  //  helper_check_heap("TracePrintf");

  va_list args;

  va_start(args, fmt);
  CALL_V_TRACE_PRINTF(TR_IM_WHO, level, fmt, args);
  va_end(args);

  if (zero_out_lkra)
    lkra = 0;
}


