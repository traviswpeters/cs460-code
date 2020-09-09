// gcc mystery1.c -o mystery1 && ./mystery1 what does this do ?
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("%d, %s, %s, %s, %s\n", argc, argv[0], argv[1], argv[5], argv[6]);
    return 0;
}
