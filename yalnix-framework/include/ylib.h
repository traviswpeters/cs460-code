#ifndef _YLIB_H_
#define _YLIB_H_


#ifndef size_t
typedef unsigned int size_t;
#endif



/*
 *  All Yalnix kernel calls return ERROR in case of any error.
 */
#ifndef ERROR
#define	ERROR			(-1)
#endif

#ifndef NULL
#define NULL 0
#endif



extern void Pause (void);
extern void TracePrintf (int, char *, ...);

// you may also use assert(expression)
#include <assert.h>

//void abort(void);

int atoi(const char *nptr);
long atol(const char *nptr);
void bzero(void *s, size_t n);
void *calloc(size_t nmemb, size_t size);
void helper_check_heap(char *msg);
void free(void *addr);
int isalnum(int c);
int isalpha(int c);
int isascii(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
long jrand48(unsigned short xsubi[3]);
void *malloc(size_t len);
void *memccpy(void *dst, const void *src, int c, size_t n);
void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
void *memmem(const void *haystack, size_t n, const void *needle, size_t m);
void *memmove(void *dst, const void *src, size_t n);
void *memrchr(const void *s, int c, size_t n);
void *memset(void *dst, int c, size_t n);
void memswap(void *m1, void *m2, size_t n);
long mrand48(void);
int rand(void);
void *realloc(void *ptr, size_t size);
int sprintf(char *buffer, const char *format, ...);
void srand(unsigned int seed);
void srand48(long seedval);
int sscanf(const char *str, const char *format, ...);
char *strcat(char *dst, const char *src);
char *strchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *s);
char *strncat(char *dst, const char *src, size_t n);
char *strcpy(char *dst, const char *src);

int strncmp(const char *s1, const char *s2, size_t n);
char *strncpy(char * dst, const char * src, size_t len);
size_t strnlen(const char *s, size_t maxlen);
//uintmax_t strntoumax(const char *nptr, char **endptr, int base, size_t n);
char *strpbrk(const char *s, const char *accept);
char *strsep(char **stringp, const char *delim);
char *strtok(char *s, const char *delim);
size_t __strxspn(const char *s, const char *map, int parity);
int tolower(int c);
int toupper(int c);

#endif


