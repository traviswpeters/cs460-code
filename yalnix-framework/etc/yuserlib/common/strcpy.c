/*
 * strcpy.c
 *
 * strcpy()
 */

#include <string.h>

char *strcpy(char *dst, const char *src)
{
	char *q = dst;
	const char *p = src;
	char ch;

	do {
		*q++ = ch = *p++;
	} while (ch);

	return dst;
}


char *strncpy(char * dst, const char * src, size_t len) {


  int i;
  int zmode = 0;

  for (i = 0; i < len; i++) {

    if (zmode) 
      dst[i] = '\0';
    else {
      dst[i] = src[i];
      if (0==src[i])
	zmode = 1;
    }
  }
  
  return dst;


}
