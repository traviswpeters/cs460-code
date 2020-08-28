/*
 * readline.c - a utility function to safely read one line of input
 * Safely read a line of input into `buf` (with room for `len` chars);
 * guaranteeing we won't over-run the end of the buffer,
 * guaranteeing a newline-terminated, null-terminated string in the buffer;
 * returning true if success and false if EOF or any error.
 * If the user enters more than len-2 characters, that is considered an error.
 * If end-of-file is reached before newline, that is considered an error.
 * If an error occurs, buf may have been written but should be untrusted.
 */

#include <stdio.h>
#include <string.h>
#include "readline.h"

bool readLine(char *buf, const int len) {
  // if fgets encounters an error, or EOF after no input, it returns NULL.
  if (fgets(buf, len, stdin) == NULL)
    return false;

  // this should not happen, but I want to protect the subscript below
  if (strlen(buf) == 0)
    return false;

  // fgets guarantees the string is null-terminated, but there may not be a
  // newline if the buffer filled before a newline was encountered.
  // if that happens, clear the stdio input until newline or EOF.
  if (buf[strlen(buf)-1] != '\n') {
    // strip characters until end of file or newline is reached
    while ( !feof(stdin) && getchar() != '\n' )
      ; // discard the rest of characters on input line
    return false;
  }

  return true;
}
