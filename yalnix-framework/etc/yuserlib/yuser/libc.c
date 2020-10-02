/* 
 * Yalnix Support Software for Linux/x86 
 *
 * Original SunOS/SPARC version by David Johnson, CMU/Rice. dbj@cs.rice.edu
 * 
 * Subsequently ported to Solaris/SPARC by the infamous Juan Leon
 *
 * Ported to Linux/x86 by S.W. Smith, Dartmouth Colleg.  Summer 2001
 * sws@cs.dartmouth.edu
 * (with help from David Johnson and Evan Knop)
 * 
 * "LINUX" compile flag == Linux AND x86
 * Linux version must support makecontext/getcontext... e.g., >= 2.4.8
 *
 * This file provides special versions of some standard libc functions.
 * for the Yalnix USER code to use.
 *
 * Port: trivial.
 *
 * Sept 2003: to get running on RH9, needed to define a few stubs
 * (so the linker would be happy) and to define a __default_morecore,
 * so the malloc trick works for user code.  See L2003
 *
 * Sep 2016: cleaned up TracePrintf
 *
 * Apr 2020: big clean-up
 */

#include <sys/types.h>
#include <errno.h>
#include <sys/param.h>
#include <stdarg.h>

#include "hardware.h"
#include "manuallink.h"


// prototypes so compiler won't throw warnings
int SysBrk (void *a);
void * sbrk(int incr);
int     brk(void * addr);
void _Exit (int a);




extern void *_end;		/* address is *linked* end of program */


static void * current_break = (void *)&_end;


void BadLib(char *name) {

  TracePrintf(0,"userland made illegal library call to %s; aborting\n",name);
  _Exit(-1);

}  

#include "../forbidden.c"

void *__libc_memalign(size_t boundary, size_t size) {

  TracePrintf(0,"__libc_memalign() called---error?\n");

  return NULL;
}


/* these go to macros in manuallink.h */
void YalnixEmulatorFakeMutexGet(void)
{
  CALL_MUTEX_GET();
}


void YalnixEmulatorFakeMutexRelease(void)
{
  CALL_MUTEX_RELEASE();
}


static int brk_unlocked (void * addr)
{
  int status;
  void * pageaddr;

  TracePrintf(10,"brk_unlocked(%x)\n",addr);

    /* round to double-word boundary */
  addr = (void *)((long)(addr + 7) & ~7);

  pageaddr = (void *)UP_TO_PAGE((long)(addr));
    
  if (pageaddr != (void *)UP_TO_PAGE((long)(current_break))) {
    status = SysBrk(pageaddr); 
    if (status != 0) {
      //      errno = ENOMEM;
      return (-1);
    }
    //    current_break = pageaddr;
  }
  current_break = addr;
  return 0;
}

// this is the brk() and sbrk() linked into the Yalnix "process" code.
// it calls malloc() in the standard C library, but when that calls
// sbrk/brk, it comes here.


#define PRE_STARTUP_HEAPSIZE  (4*PAGESIZE)


//======================================================================



const int USER_LIB = 1;

#define WHOSE_HEAP "USER"
#include "../new_heap.c"  // the common code


void
init_heap( ) {

  mblock_t *bp;
  int rc;

  TracePrintf(2, "USER heap initializing\n");

  heap_start = current_break;
  rc = brk_unlocked(current_break + PRE_STARTUP_HEAPSIZE);
  if (rc) {
    TracePrintf(2,"brk call failed; user heap will function oddly\n");
  }
  if (current_break < (heap_start + PRE_STARTUP_HEAPSIZE)) {
    TracePrintf(2,"brk did not give enough memory; user heap will function oddly\n");
  }
  heap_end   = current_break;
  

  bp = (mblock_t *)heap_start;
  bp->magic1 = MAGIC;
  bp->size = heap_end - heap_start - sizeof(mblock_t);
  bp->size_used = 0;
  bp->next = NULL;
  bp->previous = NULL;
  bp->magic2 = MAGIC;
  
  not_initialized = 0;
}


mblock_t *
grow_heap(u_long len) {


  mblock_t *bp;
  void *new_end;
  void *req;

  TracePrintf(4,"user grow_heap(0x%x)\n",len);
  if (NULL == heap_start) {
    TracePrintf(2,"we're not initialized yet!\n");
    return NULL;
  }

  req= (void *)UP_TO_PAGE(heap_end + len + sizeof(mblock_t));
  TracePrintf(8,"rounding up to 0x%x\n", req);

  if (brk(req)) {
    TracePrintf(4, "USER HEAP's brk failed #1\n");
    return NULL;
  }

  new_end = sbrk(0);

  if (new_end < req) {
    TracePrintf(4, "USER HEAP's brk failed #2\n");
    return NULL;
  }


  bp = (mblock_t *)heap_end;

  bp->magic1 = MAGIC;
  bp->size = (new_end - heap_end)  - sizeof(mblock_t);
  bp->size_used = 0;
  bp->next = NULL;
  bp->previous = NULL;
  bp->magic2 = MAGIC;
  heap_end = new_end;

  return bp;
}


//================================================================



void *
sbrk(int incr)
{
    void * new_break;
    void * old_break;
    int ret;

    //  if (NULL == current_break)
    //    current_break= (void *)(UP_TO_PAGE(&_end));

    TracePrintf(8,"user sbrk(%x)... current = %x\n",incr,current_break);



    if (incr == 0) {
      return (current_break);
    }

    YalnixEmulatorFakeMutexGet();
    new_break = current_break + incr;
    old_break = current_break;

    ret = brk_unlocked(new_break);
    YalnixEmulatorFakeMutexRelease();
    if (ret != 0) {
      return ((void *)(-1));
    }
    else {
      return (old_break);
    }
}


void *
_sbrk(int incr)
{
  return sbrk(incr);
}



// because the malloc in Linux links to a "__sbrk()"...
void * __sbrk(int incr) {
  TracePrintf(8,"__sbrk\n");
  return sbrk(incr);
}



// because in the new glibc (sep 2003), malloc.o goes to __sbrk
// via __default_morecore, which is somewhere else...

void *__default_morecore (int increment)
{
  void *result;
 
  TracePrintf(8,"__default_morecore\n");
  result = (void *) __sbrk (increment);
  if (result == (void *) -1)
    return NULL;
  return result;
}



int
brk(void * addr)
{
  int ret;


  //  if (NULL == current_break)
  //    current_break= (void *)(UP_TO_PAGE(&_end));


  /* Have to lock between looking and setting current_break
     * for SharedFork reentrance.  Cannot do it with a mutex
     * because that would freeze the whole shindig.
     */
  YalnixEmulatorFakeMutexGet();
  ret = brk_unlocked(addr);
  YalnixEmulatorFakeMutexRelease();
  return ret;
}


int _brk(void * addr)
{
  return brk(addr);
}



// because the malloc in Linux links to a "_sbrk()"...
int __brk(void * addr)
{
  TracePrintf(8,"__brk(%x)\n",addr);
  return brk(addr);
}



/* We want a call to Brk to set the currentbreak in user-level space,
 * so we need it to call our brk() stub.  We have renamed the Brk()
 * syscall to be SysBrk(), and added this to force user-explicit
 * calls to Brk() to call brk().
 */
int Brk(void * addr)
{
  int status;



  YalnixEmulatorFakeMutexGet();
  TracePrintf(8,"Brk(%x)\n",addr);
  status = SysBrk(addr);
  if (status == 0) {
    current_break = addr;
  }
  YalnixEmulatorFakeMutexRelease();
  return status;
}





void  *  __mmap(void  *start,  size_t length, int prot , int
		flags, int fd, off_t offset) {
  TracePrintf(0,"__mmap! error?\n");
  return ((void*)-1);

}





void
exit(status)
int status;
{
  //  fflush(NULL);
  TracePrintf(0,"user exit in libc.c\n");
  _Exit(status);
}


void
_exit(status)
int status;
{
  exit(status);
}


void
Exit(status)
int status;
{
  //  fflush(NULL);
  _Exit(status);
}


int
getpagesize()
{
  return (PAGESIZE);
}


int
_getpagesize()
{
  return (PAGESIZE);
}


void Pause(void)
{
  CALL_PAUSE();
}

#if(0)
void _start(void) {
  exit ((*main) (argc, argv, __environ));

}
#endif

#ifdef	DISK_STATS
int GetStatsReg(int which)
{
  return CALL_GETSTATSREG(which);
}


int SetStatsReg(int which, int val)
{
  return CALL_SETSTATSREG(which, val);
}
#endif



// In the RH9 environment, the linker is supposed to define these
// symbols.  But for the user programs, it doesn't.  I don't know why. 
 
void test_2003C(void) {
 
  int not_used;
 
  not_used = 0;
 
}
 
 
 
void *__init_array_start =&test_2003C;
void *__init_array_end =  &test_2003C;
void *__preinit_array_start =&test_2003C;
void *__preinit_array_end =  &test_2003C;
void *__fini_array_start = &test_2003C;
void *__fini_array_end = &test_2003C;
 

