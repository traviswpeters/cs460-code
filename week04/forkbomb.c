// Fork Bomb Demo.

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    while(1) {
        fork();
        printf("fork!\n");
    }
    return 0;
}
