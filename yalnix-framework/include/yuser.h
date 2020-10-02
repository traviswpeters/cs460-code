#ifndef _YUSER_H_
#define _YUSER_H_

#include <ylib.h>

// syscall wrappers

extern int Nop (int,int,int,int);

extern int Fork (void);
extern int Exec (char *, char **);
extern void Exit (int);
extern int Wait (int *);
extern int GetPid (void);
extern int Brk (void *);
extern int Delay (int);
extern int TtyRead (int, void *, int);
extern int TtyWrite (int, void *, int);
extern int Register (unsigned int);
extern int Send (void *, int);
extern int Receive (void *);
extern int ReceiveSpecific (void *, int);
extern int Reply (void *, int);
extern int Forward (void *, int, int);
extern int CopyFrom (int, void *, void *, int);
extern int CopyTo (int, void *, void *, int);
extern int ReadSector (int, void *);
extern int WriteSector (int, void *);

extern int PipeInit (int *);
extern int PipeRead (int, void *, int);
extern int PipeWrite (int, void *, int);

extern int SemInit (int *, int);
extern int SemUp (int);
extern int SemDown (int);
extern int LockInit (int *);
extern int Acquire (int);
extern int Release (int);
extern int CvarInit (int *);
extern int CvarWait (int, int);
extern int CvarSignal (int);
extern int CvarBroadcast (int);

extern int Reclaim (int);

extern int Custom0 (int,int,int,int);
extern int Custom1 (int,int,int,int);
extern int Custom2 (int,int,int,int);

/*
 * A Yalnix library function: TtyPrintf(num, format, args) works like
 * printf(format, args) on terminal num.
 */
extern int TtyPrintf (int, char *, ...);





#endif
