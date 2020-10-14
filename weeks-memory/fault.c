// memory management demo code

// note that the brk/sbrk cases (-3 and -4) give unexpected
// results on OSX... but see "man sbrk" on OSX.

// this code treats addresses as 32 bits......
// -> buld with -m32
// -> build with -ggdb will let you look at core files more easily!

// travis peters, montana state university
// s.w. smith, dartmouth

#define _DEFAULT_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char *global_var = "abcdef";
// #define JUMP 8192
#define JUMP (8192<<2)
#define HEAPJUMP   0xF0000
#define STACKJUMP  0xF0000
#define MLOOPS 32

char cstring[100];
char pfstring[100];

void bigstack(void) {
    char big_array[STACKJUMP];
    printf("-----inside the subroutine, an address on the stack is:  0x%08x\n", (int) &big_array[0]);
    printf("\n\n[2] Running pmap....\n");
    system(cstring);
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    char c;
    void *text, *data, *heap, *nowhere, *stack, *belowstack;  // pointers
    void *nullpointer = NULL;
    void *brk_value;
    void *p1, *p2;
    int i, j;
    int pid;
    void *mvals[MLOOPS];
    int demo = 0;

    // pull out argument
    if (argc >= 2) {
        if ( ('-' == argv[1][0]) && (c = argv[1][1]) && (isdigit(c)) )
            demo = c - '0';
    }

    if (argc < 2) {
        printf("Memory Management Demo\n");
        printf("-0: tries to read from, then write to, a null pointer address\n");
        printf("-1: tries to read from nowhere address\n");
        printf("-2: tries to read from, then write to, a text address\n");
        printf("-3: tries to read from just before the brk, then from the brk itself\n");
        printf("-4: sees if malloc increases the brk address\n");
        printf("    NOTE: this may give unexpected results on OSX (see man sbrk there).\n");
        printf("-5-7: tries to read from below the stack\n");
        exit(0);
    }

    // note that we initialized demo to 0; demo > 0 is an an illegal value
    if ( (demo > 7) ) {
        printf("requires an argument: -0 ... -7\n");
        exit(-1);
    }

    text  =  main;        // the entry of main() is in the text segment
    data  = &global_var;  // the address of global_var is in the data segment
    stack = &text;        // the address of a local var is on the stack
    heap  =  malloc(256); // this is an address in the heap
    if (NULL == heap)     // ALWAYS test for malloc errors!
        exit(-1);

    nowhere = heap + HEAPJUMP; // we hope this is past the the heap,
                               // but not far enough to get into the
                               // libraries or stack...

    belowstack = stack - STACKJUMP;

    pid = getpid();
    sprintf(cstring, "pmap -X %d | tac\n", pid);
    printf("\n\n[1] Running pmap....\n");
    system(cstring);
    printf("\n\n");

    brk_value = sbrk(0);

    int pagesize = sysconf(_SC_PAGESIZE); // https://stackoverflow.com/a/37897870
    printf("page size                     : 0x%08x (%d)\n", pagesize, pagesize);

    printf("an address on the stack       : 0x%08x\n", (int) stack);
    printf("an address below the stack    : 0x%08x\n", (int) belowstack);
    printf("an address out in nowhere     : 0x%08x\n", (int) nowhere);
    printf("the brk                       : 0x%08x\n", (int) brk_value);
    printf("an address in the heap        : 0x%08x\n", (int) heap);
    printf("an address in the data segment: 0x%08x\n", (int) data);
    printf("an address in the text segment: 0x%08x\n", (int) text);
    printf("\n\n");

    switch (demo) {
    case 0:
        printf("trying to read from a null pointer...");
        fflush(stdout);
        sleep(2);
        c =  *(char*) nullpointer;   // try reading from this address...
        printf("ok\n");

        printf("trying to write to a null pointer...");
        fflush(stdout);
        sleep(2);
        *(char*) nullpointer = 'A';  // try writing to this address...
        printf("ok\n");
        break;

    case 1:
        printf("trying to write to the nowhere address...");
        fflush(stdout);
        sleep(2);
        *((char*) nowhere) = 'a';  // try writing to this address...
        printf("ok\n");

        printf("trying to read from the nowhere address...");
        fflush(stdout);
        sleep(2);
        c =  *(char*) nowhere;    // try reading from this address...
        printf("ok\n");
        break;

    case 2:
        printf("trying to read from the text address...");
        fflush(stdout);
        sleep(2);
        c =  *(char*) text;   // try reading from this address...
        printf("ok\n");

        printf("trying to write to the text address...");
        fflush(stdout);
        sleep(2);
        *(char*) text = 'A';  // try writing to this address...
        printf("ok\n");
        break;

    case 3:
        p2 = sbrk(0);  // lowest address after heap...
        p1 = p2 - 1;
        printf("the break is 0x%08x\n", (int) p2);
        printf("trying to read from 0x%08x (just before brk)...", (int) p1);
        fflush(stdout);
        sleep(2);
        c =  *(char*) p1;   // try reading from this address...
        printf("ok\n");

        printf("trying to read from 0x%08x (the brk itself)...", (int) p2);
        fflush(stdout);
        sleep(2);
        c =  *(char*) p2;   // try reading from this address...
        printf("ok\n");
        break;

    case 4:
        // do a bunch of mallocs
        printf(  "the break is now 0x%08x\n", (int) sbrk(0));
        for (i = 0; i < MLOOPS; i++) {
            printf("malloc'ing 0x%x bytes...", JUMP);
            fflush(stdout);
            sleep(2);
            mvals[i] = malloc(JUMP);
            if (NULL == mvals[i])
                exit(-1);
            printf("got 0x%08x, ", (int) mvals[i]);
            printf("the break is now 0x%08x\n", (int) sbrk(0));
        }

        printf("The break has grown!\n");
        printf("Dramatic pause...\n");
        sleep(3);

        // do a bunch of frees
        for (j = i-1; j >= 0; j--) {
            printf("freeing 0x%08x....", (int) mvals[j]);
            fflush(stdout);
            sleep(2);
            free(mvals[j]);
            printf("the break is now 0x%08x\n", (int) sbrk(0));
        }

        break;

    case 5:
        // format command to get info current proc's page faults
        // -> Thanks, https://www.cyberciti.biz/faq/linux-command-to-see-major-minor-pagefaults/
        sprintf(pfstring, "ps -o min_flt,maj_flt %d\n", pid);

        for (i = 0; i < 32; i++) {
            // examine minor/major page faults each time we try to read/write further down in the addr space.
            system(pfstring);

            printf("trying to read from below the stack...0x%08x\n", (int) belowstack);
            printf("(0x%08x bytes below the address of the local variable 'stack')\n", STACKJUMP*(i+1));
            fflush(stdout);
            sleep(2);
            c =  *(char*) belowstack;   // try reading from this address...
            printf("ok\n");

            printf("trying to write below the stack...0x%08x\n", (int) belowstack);
            sleep(2);
            *((char*) belowstack) = 'a';  // try writing to this address...
            printf("ok\n");

            belowstack = belowstack - STACKJUMP;
        }

        break;

    case 6:
        printf("calling a subroutine with a big local array\n");
        fflush(stdout);
        sleep(2);
        bigstack();
        break;

    case 7:
        printf("calling a subroutine with a big local array\n");
        fflush(stdout);
        sleep(2);
        bigstack();

        printf("back from the subroutine...\n");
        printf("trying to read from below the stack...0x%08x\n", (int) belowstack);
        printf("(0x%08x bytes below the address of the local variable 'stack')\n", STACKJUMP);
        fflush(stdout);
        sleep(2);
        c =  *(char*) belowstack;   // try reading from this address...
        printf("ok\n");
        break;

    }

    return 0;
}
