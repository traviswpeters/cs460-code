// Fork Bomb Demo.
//
// compile: 
// gcc fork_bomb.c -o fb

#include <sys/types.h>
#include <stdio.h> 
#include <unistd.h>

int main() {
    while(1) {
        fork();
        printf("I'm a fork!\n"); 
    }
    return 0;
}
