/*
 * Notes on syscalls for process control.
 */

// Unix programmers make frequent use of return values to communicate results
//
// For example,
//
// fork()...
// ...creates an identical process (with the exception of child PID and return value from fork())
//  - returns a negative value if there was an error
//  - returns 0 to the child process
//  - returns the child's PID (always > 0) to the parent process

////////////////////////////////////////////////////////////////////////////////////////////////////

pid = fork();
if (0 == pid) {
    // I'm the child
}
// I'm the parent

////////////////////////////////////////////////////////////////////////////////////////////////////

pid = fork();
if (pid < 0) {
    // fork failed!
} else if (0 == pid) {
    // child process
} else { // pid > 0
    // parent process; pid == child's process ID
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// For PA1

// convert - convert between image formats as well as resize an image, blur, crop, despeckle,
// dither, draw on, flip, join, re-sample, and much
//
// `man convert` says this is how we call it:
// $ convert [input-option] input-file [output-option] output-file

// display - displays an image or image sequence on any X server.
//
// `man display` says this is how we call it:
// $ display [options] input-file
