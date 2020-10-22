// a program that issues data addresses in a very non-local way
// (on 64-bit machines, should be built with -m64 in order to see the fun behavior)

// travis peters, montana state university
// s.w. smith, dartmouth

#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

#define PAGESIZE  4096  // guess
#define MAX_K     20
#define MAXPAGES  (1<<MAX_K)
#define LOOPS     (MAXPAGES << 8)

long tv_to_usecs(struct timeval *tvp) {
    long secs, usecs;
    secs  = tvp->tv_sec;
    usecs = tvp->tv_usec;
    return ( (secs * 1000 * 1000) + usecs);
}

long tvdiff(struct timeval *tvp1, struct timeval *tvp2) {
    long t1, t2;
    t1 = tv_to_usecs(tvp1);
    t2 = tv_to_usecs(tvp2);
    return (t1 - t2);
}

int main(void) {
    int **page_array;
    int *addr;
    int round,pages,page,loop;
    struct rusage start, stop;
    long utime, stime, ttime, setsize, pagefaults;

    page_array = calloc(MAXPAGES, sizeof(int*));
    if (NULL == page_array) {
        printf("failed to malloc page_array\n");
        exit(-1);
    }

    printf("Trying %d loops spread over varying numbers of pages....\n\n", LOOPS);

    for (round = 4; round <= MAX_K; round +=2 ) {
        pages = 1 << round;
        printf("Spread over %d different pages....\n",  pages);

        for (page = 0; page < pages; page++) {
            if (NULL == page_array[page]) {
                page_array[page] = malloc(PAGESIZE);
                if (NULL == page_array[page]) {
                    printf("failed to malloc page %d\n", page);
                    exit(-1);
                }
            }
        }

        // start timing
        if (-1 == getrusage(RUSAGE_SELF, &start)) {
            printf("error getting start time\n");
            exit(-1);
        }

        for (loop = 0; loop < LOOPS; loop++) {
            page = loop % pages;
            addr = page_array[page];
            *addr = *addr + 1;
        }

        // stop timing
        if (-1 == getrusage(RUSAGE_SELF, &stop)) {
            printf("error getting stop time\n");
            exit(-1);
        }

        utime      = tvdiff(&stop.ru_utime, &start.ru_utime);
        stime      = tvdiff(&stop.ru_stime, &start.ru_stime);
        ttime      = utime + stime;
        setsize    = stop.ru_maxrss - start.ru_maxrss;
        pagefaults = stop.ru_majflt - start.ru_majflt;

        printf("over %d ``pages'' of size %d:\n%ld usecs (%ld user + %ld system)\n%ld setsize\n%ld pagefaults\n\n",
               pages, PAGESIZE, ttime, utime, stime, setsize, pagefaults);
    }
}
