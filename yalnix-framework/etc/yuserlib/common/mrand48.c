/*
 * mrand48.c
 */

#include <stdlib.h>
#include <stdint.h>

unsigned short __rand48_seed[3];	/* Common with lrand48.c, srand48.c */

int rand(void) {

  int rc;

  rc = (int) jrand48(__rand48_seed);

  if  (rc < 0) rc = -rc;

  return rc;

}

long mrand48(void)
{
	return jrand48(__rand48_seed);
}
