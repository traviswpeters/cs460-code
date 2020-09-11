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
