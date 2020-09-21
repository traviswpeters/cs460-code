/*
 * readline.h - a utility function to safely read one line of input
 * See readline.c for documentation.
 */

#ifndef __READLINE_H__
#define __READLINE_H__

#include <stdbool.h>

extern bool readLine(char *buf, const int len);

#endif //  __READLINE_H__
