// sample pipe code

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define RPIPE 0  // the pipe we read from
#define WPIPE 1  // the pipe we write to

char *indent = "===============";

int main(void) {
    int sv1[2];
    int sv2[2];
    int pid, other_pid;
    int to_child, from_child;
    int bytes;
    int size_of_int = sizeof(int); // avoids comparisons of incompatible types

    if (pipe(sv1) < 0) {
        fprintf(stderr,"pipe error (1)!\n");
        exit(-1);
    }

    if (pipe(sv2) < 0) {
        fprintf(stderr,"pipe error (2)!\n");
        exit(-1);
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stderr,"fork error!\n");
        exit(-1);
    } else if (0 == pid) {
        //----------------------child-------------------

        int to_parent, from_parent;

        // close the other ends
        close(sv1[WPIPE]);
        close(sv2[RPIPE]);

        // use meaningful names
        to_parent   = sv2[WPIPE];
        from_parent = sv1[RPIPE];

        pid = getpid();

        // write my pid to the parent
        bytes = write(to_parent, &pid, size_of_int);
        if (bytes != size_of_int) {
            fprintf(stderr,"error!\n");
            exit(1);
        }

        // get pid of parent
        bytes = read(from_parent, &other_pid, size_of_int);
        if (bytes < size_of_int) {
            fprintf(stderr,"error\n");
            exit(-1);
        }

        printf("child: the parent's pid is %d\n", other_pid);

        printf("child is exiting\n");
        exit(0);
    }
    //----------------------parent-------------------

    // close the other ends
    close(sv1[RPIPE]);
    close(sv2[WPIPE]);

    // use meaningful names
    to_child   = sv1[WPIPE];
    from_child = sv2[RPIPE];

    // get the pid of child
    bytes = read(from_child, &other_pid, size_of_int);
    if (bytes < size_of_int) {
        fprintf(stderr,"error\n");
        exit(-1);
    }

    printf("%s parent: the child's pid is %d\n", indent, other_pid);

    pid = getpid();

    // send our pid to child
    bytes = write(to_child, &pid, size_of_int);
    if (bytes != size_of_int) {
        fprintf(stderr,"error!\n");
        exit(1);
    }

    printf("%s parent is exiting\n", indent);
    return 0;
}
