#include <stdio.h>   // (f)printf, stdout, stderr, etc.
#include <stdlib.h>  // exit, etc.
#include <unistd.h>  // fork, exec, sleep, etc.

// Error Codes:
//  -1: exec failed!

int main(void) {
    // Initializations.
    int rc;
    char * photo_in = "photo.jpg";
    char * photo_out = "photo_out.jpg";

    fprintf(stdout, "-> Converting: '%s'\n", photo_in);

    // Convert a photo.
    rc  = fork();
    if (0 == rc) {
        // see man execlp.  program name, then list of arguments as char strings.
        // arg list must be terminated by a NULL
        // and the zeroth arg is (by convention) the name of the program
        rc = execlp("convert", "convert", "-geometry", "50%", "-monochrome", photo_in, photo_out, NULL);
        fprintf(stderr, "**error: cannot convert '%s'.**\n", photo_in);
        exit(-1);
    }

    return 0;
}
