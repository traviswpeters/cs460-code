#define _POSIX_SOURCE
#include <stdio.h>   // (f)printf, stdout, stderr, etc.
#include <stdlib.h>  // exit, etc.
#include <unistd.h>  // fork, exec, sleep, etc.
#include <signal.h>  // for the kill() call
#include <string.h>
#include <errno.h>

// Things to note:
// - use of `errno` and `strerror()` - more detailed feedback on error/error type
extern int errno;

// Error Codes:
//  -1: insufficient arguments
//  -2: exec failed!
//  -3: kill failed!

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Please provide a path to a photo to `display`.\n");
        fprintf(stderr, " $ ./exec_display PHOTO\n");
        exit(-1);
    }

    // Initializations.
    int rc, display_pid;
    char * photo = argv[1];

    fprintf(stdout, "-> Displaying: '%s'\n", photo);
    fprintf(stdout, "  (It may take a few seconds to start X...)\n");

    // Display a photo with a background process.
    display_pid  = fork();
    if (0 == display_pid) {
        rc = execlp("display", "display", photo, NULL);
        fprintf(stderr, "**error: cannot display '%s'.**\n", photo);
        exit(-2);
    }

    // a hacky way to make the 'parent' "wait" for a little bit...
    sleep(10);

    // kill display... and report errors
    rc = kill(display_pid, SIGTERM);
    if (rc < 0) {
        int errnum = errno;
        fprintf(stderr, "Value of errno: %d (%s)\n", errnum, strerror(errnum));
        exit(-3);
    }

    // -> in general, you should be nice and "wait" for the user to close the display.

    return 0;
}
