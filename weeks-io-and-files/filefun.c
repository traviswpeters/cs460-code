//
// travis peters, montana state university
// s.w. smith, dartmouth

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SPACER "        "

const char filename[] = "data";  // name of data file
const int filebytes       = 10;  // how many bytes to read

// channels to coordinate the two-process cases
int p2c_pipe[2];
int c2p_pipe[2];

// put an integer into a channel
void put(int stuff[]) {
    int size;
    int val = 1;

    size = write(stuff[1], &val, sizeof(val));
    if (sizeof(val) != size) {
        printf("put failed!\n");
        exit(-1);
    }
}

// get an integer from a channel
void get(int stuff[]) {
    int size;
    int val = 1;

    size = read(stuff[0], &val, sizeof(val));
    if (sizeof(val) != size) {
        printf("read failed!\n");
        exit(-1);
    }
}

int main(int argc, char *argv[]) {
    int i;
    int fd1, fd2;    // the two file descriptors
    // int pid1, pid2;    // the two pids
    int my_fd, my_pid; // for the "current process"
    char buff;
    int rc;

    printf("File Descriptor Fun\n");

    // control flags
    int two_processes   = 0;
    int interleaved     = 0;

    // examine arguments
    if (argc<= 1) {
        printf("options: -1 or -2 for number of processes;\n");
        printf("         -i or -s for interleaved or sequential\n");
        printf("         (or -I to do it via two processes from two different file descriptors!)\n");
        exit(-1);
    }

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-I") == 0) {
            two_processes = 1;
            interleaved = 2;
            break;
        } else if (strcmp(argv[i], "-1") == 0) {
            two_processes = 0;
        } else if (strcmp(argv[i], "-2") == 0) {
            two_processes = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            interleaved = 1;
        } else if (strcmp(argv[i], "-s") == 0) {
            interleaved = 0;
        }
    }

    if (two_processes)
        printf("Two processes requested;");
    else
        printf("One process requested;");

    if (interleaved)
        printf(" interleaving requested\n");
    else
        printf(" NO interleaving requested\n");

    // open first file
    fd1 = open(filename, O_RDONLY);
    if (-1 == fd1) {
        printf("error opening file!\n");
        exit(-1);
    }

    if (two_processes) {
        // set up pipes
        rc = pipe(p2c_pipe);
        if (rc) {
            printf("p2c creation failed\n");
            exit(-1);
        }

        rc = pipe(c2p_pipe);
        if (rc) {
            printf("c2p creation failed\n");
            exit(-1);
        }

        if (fork()) {
            //----------- parent----------------------
            my_fd = fd1;

            my_pid = getpid();

            // wait to the child to tell you to go
            get(c2p_pipe);

            for (i = 0; i < filebytes; i++) {

                // read a byte
                rc = read(my_fd, &buff, 1);
                if (1 != rc) {
                    printf("%s: error reading file!\n", filename);
                    break;
                }

                // print it out
                printf("Process %d, fd %d, %s byte %d = %c \n", my_pid, my_fd, SPACER, i, buff);

                // tell the child to go
                put(p2c_pipe);

                // wait to the child to tell you to go
                get(c2p_pipe);
            }
        } else {
            //-----------child---------------------
            switch(interleaved) {
            case 1:
                printf("child inherits parent's descriptor table\n");
                printf("as a consequence, it has the same file entry and same offset\n");
                printf("so, we'll see INTERLEAVED reads from the two processes.\n");
                my_fd = fd1;
                break;
            case 2:
                printf("child inherits parent's descriptor table\n");
                printf("as a consequence, it has the same file entry and same offset\n");
                printf("we use the dup call to get another descriptor to the same file entry\n");
                my_fd = dup(fd1);
                break;
            default:
                printf("child opens its own copy\n");
                printf("it has its own file entry and its own offset\n");
                printf("so, each process will read independently\n");
                fd2 = open(filename, O_RDONLY);
                my_fd = fd2;
                if (-1 == fd2) {
                    printf("error opening file!\n");
                    exit(-1);
                }
            }

            my_pid = getpid();

            // tell the parent to go
            put(c2p_pipe);

            for (i = 0; i < filebytes; i++) {

                // wait for the parent to tell you to go
                get(p2c_pipe);

                // read a byte
                rc = read(my_fd, &buff, 1);
                if (1 != rc) {
                    printf("%s: error reading file!\n", filename);
                    break;
                }

                // print it out
                printf("%s Process %d, fd %d, byte %d = %c \n", SPACER, my_pid, my_fd, i, buff);

                // tell the parent to go
                put(c2p_pipe);
            }
        }

    } else {
        // the one-process case
        my_pid = getpid();

        if (interleaved) {
            // get another file descriptor to the same file entry
            printf("we use the dup call to get another descriptor to the same file entry\n");
            printf("so, the reads from each file descriptor will be interleaved\n");
            fd2 = dup(fd1);
        } else {
            printf("we just open the file again, to get a new descriptor to a new file entry\n");
            printf("so, each file descriptor will read independently\n");
            fd2 = open(filename, O_RDONLY);
            if (-1 == fd1) {
                printf("error opening file!\n");
                exit(-1);
            }
        }

        for (i = 0; i < filebytes; i++) {
            // read a byte from first descriptor
            rc = read(fd1, &buff, 1);
            if (1 != rc) {
                printf("%s: error reading file!\n", filename);
                break;
            }
            // print it out
            printf("Process %d, fd %d, %s byte %d = %c \n", my_pid, fd1, SPACER, i, buff);

            // read a byte from 2nd descriptor
            rc = read(fd2, &buff, 1);
            if (1 != rc) {
                printf("%s: error reading file!\n", filename);
                break;
            }
            // print it out
            printf("%s Process %d, fd %d, byte %d = %c \n", SPACER, my_pid, fd2, i, buff);
        }
    }
}
