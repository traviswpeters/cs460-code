// demo showing stack frames in action!

#include <stdio.h>

void f(int a);
void g(int a);

int depth = 0;

void print_depth(char *name, int arg, void *addr) {
    for (int i = 0; i < depth; i++)
        printf("   ");
    printf("%s(%d): stack address 0x%08x\n\n", name, arg, (unsigned int) addr);
}

int main(void) {
    int localvar;
    depth++;
    print_depth("into main", 0, &localvar);

    f(23);

    print_depth("out  main", 0, &localvar);
    depth--;
    return 0;
}

void f(int a) {
    int localvar;
    depth++;
    print_depth("into f", a, &localvar);
    g(3);
    print_depth("out  f", a, &localvar);
    depth--;
}

void g(int b) {
    int localvar;
    int z = b -1;

    depth++;
    print_depth("into g", b, &localvar);
    if (z > 0) {
        g(z);
    }
    print_depth("out  g", b, &localvar);
    depth--;
}
