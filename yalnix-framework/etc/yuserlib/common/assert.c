/*
 * assert.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void * TracePrintf(int level, char *fmt, ... );




void
__assert_fail(const char *expr, const char *file, unsigned int line, const char *func)
{
  TracePrintf(0,"Assertion %s failed, file %s, line %u, func %s\n", expr, file, line, func);
	abort();
}
