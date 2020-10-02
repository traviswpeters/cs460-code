/* 
 * Yalnix Support Software for Linux/x86 
 *
 * Original SunOS/SPARC version by David Johnson, CMU/Rice. dbj@cs.rice.edu
 * 
 * Subsequently ported to Solaris/SPARC by the infamous Juan Leon
 *
 * Ported to Linux/x86 by S.W. Smith, Dartmouth College.  Summer 2001
 * sws@cs.dartmouth.edu
 * (with help from David Johnson and Evan Knop)
 * 
 * "LINUX" compile flag == Linux AND x86
 * Linux version must support makecontext/getcontext... e.g., >= 2.4.8

 * This file: calls.c provides the Yalnix syscalls for the Yalnix user
 * code.  (Replaces yalnixcall.S in the Solaris version)
 *
 * modified oct 2002: sws  custom calls
 *
 * modified oct 2008: sws  pipes
 *
 * apr 2020: big clean-up
 */


#include "yalnix.h"


// Linux/x86 of syscall library

#define	YALNIX_TRAP	16 
// number of trap entries

// basic macro: move the 4 args and the code into registers,
// and throw a software trap (picked up in support/exception.c)

// ideally, we should have a different version of this macro for
// each argument count.

void helper_check_heap(char *msg);

unsigned int lkra; // user version

#define YSYSCALL(code,A,B,C,D) \
  int rc; \
  lkra = (unsigned int)(__builtin_return_address(0)); \
  helper_check_heap("into sycall"); \
  __asm__ __volatile__ ( "int $04\n\t"          \
                       : "=eax" (rc)            \
                       : "eax"(A), "b"(B), "c"(C),"d"(D), "D" (code) ); \
  helper_check_heap("back from syscall"); \
  lkra = 0; \
  return rc

#define YSYSCALL_NOCHECK(code,A,B,C,D) \
  int rc;                         \
  __asm__ __volatile__ ( "int $04\n\t"          \
                       : "=eax" (rc)            \
                       : "eax"(A), "b"(B), "c"(C),"d"(D), "D" (code) ); \
  return rc

#define YSYSCALL_NR(code,A,B,C,D) \
  int rc;                         \
  __asm__ __volatile__ ( "int $04\n\t"          \
                       : "=eax" (rc)            \
                       : "eax"(A), "b"(B), "c"(C),"d"(D), "D" (code) ); 





int Nop (int a, int b, int c, int d) {
  YSYSCALL(YALNIX_NOP, a, b, c, d);
}

int helper_maybort(char *msg) {
  int zero_out_lkra = 0;
  unsigned int ra;

  if (0==lkra) {
    ra = (unsigned int)(__builtin_return_address(0));
    zero_out_lkra = 1;
  } else ra = lkra;
  
  YSYSCALL_NOCHECK(YALNIX_ABORT, msg,ra,0,0);

  if (zero_out_lkra)
    lkra =0;

  

}

int Fork (void) {
  YSYSCALL(YALNIX_FORK, 0, 0, 0, 0);
}

int Exec (char *a, char **b) {
  YSYSCALL(YALNIX_EXEC, a, b, 0, 0);
}

void _Exit (int a) {
  YSYSCALL_NR(YALNIX_EXIT, a, 0 , 0 ,0);
  // should not return...
}

int Wait (int *a) {
  YSYSCALL(YALNIX_WAIT, a, 0, 0, 0);
}

int GetPid (void) {
  YSYSCALL(YALNIX_GETPID, 0, 0, 0, 0);
}

int SysBrk (void *a) {
  YSYSCALL_NOCHECK(YALNIX_BRK, a, 0, 0, 0);
}

int Delay (int a) {
  YSYSCALL(YALNIX_DELAY, a, 0, 0, 0);
}

int TtyRead (int a, void *b, int c) {
  YSYSCALL(YALNIX_TTY_READ, a, b, c, 0);
}

int TtyWrite (int a, void *b, int c) {
  YSYSCALL(YALNIX_TTY_WRITE, a, b, c, 0);
}

int Register (unsigned int a) {
  YSYSCALL(YALNIX_REGISTER, a, 0, 0, 0);
}

int Send (void *a, int b) {
  YSYSCALL(YALNIX_SEND, a, b, 0, 0);
}

int Receive (void * a) {
  YSYSCALL(YALNIX_RECEIVE, 0, 0, 0, 0);
}

int ReceiveSpecific (void *a, int b) {
  YSYSCALL(YALNIX_RECEIVESPECIFIC, a, b, 0, 0);
}

int Reply (void *a, int b) {
  YSYSCALL(YALNIX_REPLY, a, b, 0, 0);
}

int Forward (void *a, int b, int c) {
  YSYSCALL(YALNIX_FORWARD, a, b, c, 0);
}

int CopyFrom (int a, void *b, void *c, int d) {
  YSYSCALL(YALNIX_COPY_FROM, a, b, c, d);
}

int CopyTo (int a, void *b, void *c, int d) {
  YSYSCALL(YALNIX_COPY_TO, a, b, c, d);
}

int ReadSector (int a, void * b) {
  YSYSCALL(YALNIX_READ_SECTOR, a, b, 0, 0);
}

int WriteSector (int a, void * b) {
  YSYSCALL(YALNIX_WRITE_SECTOR, a, b, 0, 0);
}

int PipeInit(int *a) {
  YSYSCALL(YALNIX_PIPE_INIT, a, 0, 0, 0);
}

int PipeRead (int a, void *b, int c) {
  YSYSCALL(YALNIX_PIPE_READ, a, b, c, 0);
}

int PipeWrite (int a, void *b, int c) {
  YSYSCALL(YALNIX_PIPE_WRITE, a, b, c, 0);
}

int SemInit(int *a, int b) {
  YSYSCALL(YALNIX_SEM_INIT, a, b, 0, 0);
}

int SemUp(int a) {
  YSYSCALL(YALNIX_SEM_UP, a, 0, 0, 0);
}

int SemDown(int a) {
  YSYSCALL(YALNIX_SEM_DOWN, a, 0, 0, 0);
}

int LockInit(int *a) {
  YSYSCALL(YALNIX_LOCK_INIT, a, 0, 0, 0);
}

int Acquire(int a) {
  YSYSCALL(YALNIX_LOCK_ACQUIRE, a, 0, 0, 0);
}

int Release(int a) {
  YSYSCALL(YALNIX_LOCK_RELEASE, a, 0, 0, 0);
}


int CvarInit(int *a) {
  YSYSCALL(YALNIX_CVAR_INIT, a, 0, 0, 0);
}


int CvarWait(int a, int b) {
  YSYSCALL(YALNIX_CVAR_WAIT, a, b, 0, 0);
}


int CvarSignal(int a) {
  YSYSCALL(YALNIX_CVAR_SIGNAL, a, 0, 0, 0);
}

int CvarBroadcast(int a) {
  YSYSCALL(YALNIX_CVAR_BROADCAST, a, 0, 0, 0);
}

int Reclaim(int a) {
  YSYSCALL(YALNIX_RECLAIM, a, 0, 0, 0);
}

int Custom0 (int a, int b, int c, int d) {
  YSYSCALL(YALNIX_CUSTOM_0, a, b, c, d);
}

int Custom1 (int a, int b, int c, int d) {
  YSYSCALL(YALNIX_CUSTOM_1, a, b, c, d);
}

int Custom2 (int a, int b, int c, int d) {
  YSYSCALL(YALNIX_CUSTOM_2, a, b, c, d);
}





























