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
 *
 * This file: external definitions for the Yalnix kernel user interface.
 *
 * Port: new way of encoding system calls, and a "Nop" call for testing
 * the hardware support.
 *
 *
 * modified oct 2002: custom syscalls  sws
 *
 * modified oct 2008: pipes  sws
 *
 * sep 2016: defined pipe buffer len
 *
 * apr 2020: overhauled by sws
 */

#ifndef	_yalnix_h
#define	_yalnix_h




/*
 * Define the kernel call number for each of the supported kernel calls.
 */



#define YALNIX_PREFIX            0xabcdef00    
#define YALNIX_MASK              0x000000FF

#define	YALNIX_FORK		( 0x1 | YALNIX_PREFIX)
#define	YALNIX_EXEC		( 0x2 | YALNIX_PREFIX)
#define	YALNIX_EXIT		( 0x3 | YALNIX_PREFIX)
#define	YALNIX_WAIT		( 0x4 | YALNIX_PREFIX)
#define YALNIX_GETPID           ( 0x5 | YALNIX_PREFIX)
#define	YALNIX_BRK		( 0x6 | YALNIX_PREFIX)
#define	YALNIX_DELAY		( 0x7 | YALNIX_PREFIX)

#define	YALNIX_TTY_READ		( 0x21 | YALNIX_PREFIX)
#define	YALNIX_TTY_WRITE	( 0x22 | YALNIX_PREFIX)

#define	YALNIX_REGISTER		( 0x31 | YALNIX_PREFIX)
#define YALNIX_SEND		( 0x32 | YALNIX_PREFIX)
#define YALNIX_RECEIVE		( 0x33 | YALNIX_PREFIX)
#define YALNIX_RECEIVESPECIFIC	( 0x34 | YALNIX_PREFIX)
#define YALNIX_REPLY		( 0x35 | YALNIX_PREFIX)
#define YALNIX_FORWARD		( 0x36 | YALNIX_PREFIX)
#define YALNIX_COPY_FROM	( 0x37 | YALNIX_PREFIX)
#define YALNIX_COPY_TO		( 0x38 | YALNIX_PREFIX)

#define YALNIX_READ_SECTOR	( 0x41 | YALNIX_PREFIX)
#define YALNIX_WRITE_SECTOR	( 0x42 | YALNIX_PREFIX)

#define YALNIX_PIPE_INIT        ( 0x48 | YALNIX_PREFIX)
#define YALNIX_PIPE_READ        ( 0x49 | YALNIX_PREFIX)
#define YALNIX_PIPE_WRITE       ( 0x4A | YALNIX_PREFIX)

#define YALNIX_NOP	        ( 0x50 | YALNIX_PREFIX)

#define YALNIX_SEM_INIT         ( 0x60 | YALNIX_PREFIX)
#define YALNIX_SEM_UP           ( 0x61 | YALNIX_PREFIX)
#define YALNIX_SEM_DOWN         ( 0x62 | YALNIX_PREFIX)
#define YALNIX_LOCK_INIT        ( 0x63 | YALNIX_PREFIX)
#define YALNIX_LOCK_ACQUIRE     ( 0x64 | YALNIX_PREFIX)
#define YALNIX_LOCK_RELEASE     ( 0x65 | YALNIX_PREFIX)
#define YALNIX_CVAR_INIT        ( 0x66 | YALNIX_PREFIX)
#define YALNIX_CVAR_SIGNAL      ( 0x67 | YALNIX_PREFIX)
#define YALNIX_CVAR_BROADCAST   ( 0x68 | YALNIX_PREFIX)
#define YALNIX_CVAR_WAIT        ( 0x69 | YALNIX_PREFIX)
#define YALNIX_RECLAIM          ( 0x6A | YALNIX_PREFIX)

#define YALNIX_CUSTOM_0         ( 0x70 | YALNIX_PREFIX)
#define YALNIX_CUSTOM_1         ( 0x71 | YALNIX_PREFIX)
#define YALNIX_CUSTOM_2         ( 0x72 | YALNIX_PREFIX)

#define YALNIX_ABORT            ( 0xF0 | YALNIX_PREFIX)
#define YALNIX_BOOT             ( 0xFF | YALNIX_PREFIX)

#define PIPE_BUFFER_LEN         256



extern void *_kernel_data_start;
extern void *_kernel_data_end;
extern void *_kernel_orig_brk;


#endif /*!_yalnix_h*/
