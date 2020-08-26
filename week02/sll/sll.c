/*
 * An example with singly linked lists (SLL).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
    Nameval *next;
};

/* Standardize how we malloc and report if there is an  error. */
void *emalloc(size_t n)
{
    void *p;
    p = malloc(n);
    if (NULL == p)
    {
        fprintf(stderr, "emalloc: malloc of %lu bytes failed.\n", n);
        exit(2); /* conventional value for failed execution */
    }
    // else {
    //     fprintf(stderr, "emalloc: malloc-ed %lu bytes!\n", n);
    // }
    return p;
}

/* Create a new item from a name and value. */
Nameval *newitem(char *name, int value)
{
    Nameval *newp;
    newp = (Nameval *) emalloc(sizeof(Nameval)); // see emalloc() above
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

/* Add a (pointer to a) new item to the front of list. */
Nameval *addfront(Nameval *listp, Nameval *newp)
{
    newp->next = listp;
    return newp;
}

/* Add newp to end of list. */
Nameval *addend(Nameval *listp, Nameval *newp)
{
    Nameval *p;
    if (NULL == listp)
        return newp;
    for (p = listp; p->next != NULL; p = p->next)
        ;
    p->next = newp;
    return listp;
}

/* free all elements of listp */
void freeall(Nameval *listp)
{
    Nameval *next;
    for ( ; listp != NULL; listp = next)
    {
        next = listp->next;
        free(listp); // assumes 'name' is freed elsewhere
    }
}

/* delete the first "name" from the list */
Nameval *delitem(Nameval *listp, char *name)
{
    Nameval *p, *prev;
    prev = NULL;
    for (p = listp; p != NULL; p = p->next) {
        if (strcmp(name, p->name) == 0) {
            if (NULL == prev) {
                listp = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            return listp;
        }
        prev = p;
    }
    fprintf(stderr, "delitem: %s not found in list.", name);
    return NULL;
}

/* Sequentially search the list for 'name'. */
Nameval *lookup(Nameval *listp, char *name)
{
    for ( ; listp != NULL; listp = listp->next)
    {
        if (strcmp(name, listp->name) == 0)
            return listp;
    }
    return NULL; // no match
}

/* (use apply) print name and value using format in arg. */
void printnv(Nameval *p, void *arg)
{
    char *fmt = (char *) arg;
    printf(fmt, p->name, p->value);
}

/* (use apply) count the elements in the list. */
void inccounter(Nameval *p, void *arg)
{
    // note: p is unused (all we are doing here is counting)
    int *ip;
    ip = (int *) arg;
    (*ip)++;
}

/* Walk the list and apply a given function (fn) to each element in the list. */
void apply(Nameval *listp, void (*fn)(Nameval *, void*), void *arg)
{
    for ( ; listp != NULL; listp = listp->next)
    {
        // call the function!
        // (a pointer to a function that takes two arguments and returns void)
        (*fn)(listp, arg);
    }
}

int main(void)
{
    Nameval *nvlist = NULL;

    // add some items
    nvlist = addfront(nvlist, newitem("travis", 0x01));
    nvlist = addend(nvlist, newitem("benjamin", 0x02));
    nvlist = addfront(nvlist, newitem("joe", 0x03));
    nvlist = addend(nvlist, newitem("mary", 0x04));

    int n;

    // view the list
    n = 0;
    apply(nvlist, inccounter, &n);
    printf("%d elements in the list:\n", n);
    apply(nvlist, printnv, " - %s (%x)\n");

    // delete an item
    nvlist = delitem(nvlist, "joe");

    // view the list
    n = 0;
    apply(nvlist, inccounter, &n);
    printf("%d elements in the list:\n", n);
    apply(nvlist, printnv, " - %s (%x)\n");

    // delete all of the items
    freeall(nvlist);

    return 0;
}
