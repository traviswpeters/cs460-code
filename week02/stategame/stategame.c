/*
 * stategame.c - read in a list of state names from stdin
 *   (sorted linked list - but then remove duplicates)
 *
 * usage: ./stategame < infile
 * stdin: list of state names, one per line
 * stdout: list of state names, one per line
 *
 * Travis Peters, Montana State University (August 2020)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "readline.h" // a custom helper for readling lines in a standard, sensical way.

// A structure for each node (a name and a pointer to the next node) in a linked list.
struct listnode {
    char *name;
    struct listnode *next;
};

// function declarations
struct listnode *newNode(char *name);
bool listInsert(struct listnode *head, char *name);
void removeDuplicates(struct listnode *head, int *n);
void freeNode(struct listnode *node);
void freeAllNodes(struct listnode *head);
void printNames(struct listnode *head, int n);
char* toLower(char* s);

int main()
{
    struct listnode head = {NULL, NULL}; // dummy node at head of empty list
    const int lineLength = 50;           // maximum length of a name
    char line[lineLength];               // buffer for reading lines
    int n = 0;                           // number of names read

    // read input from stdin (e.g,. state names on separate lines, piped/redirected file)
    while (!feof(stdin)) {
        if (readLine(line, lineLength)) {
            // TODO: ACTIVITY: Fill in part of `listInsert()` (given the basic structure, fill in insertion logic).
            if (listInsert(&head, line)) {
                n++; // only increment if no error
            }
        }
    }

    // remove duplicates from list
    removeDuplicates(&head, &n);
    // TODO: ACTIVITY: Fill in part of `removeDuplicates()` (given the basic structure, fill in insertion logic).

    // print the list of state names collected from the user
    printNames(&head, n);

    // clean up all the nodes before we exit
    freeAllNodes(&head);
    // TODO: ACTIVITY: Write a `freeAllNodes()` routine that frees each item in the list before exiting.
    // - Follow-up: is your approach efficient? (remember, this is a SLL with only a pointer to "head")

    return 0;
}

// newNode: create a new node to store the given name.
// returns pointer to new node, if successful, else returns NULL.
struct listnode *newNode(char *name)
{
    // allocate memory for the new node
    struct listnode *node = malloc(sizeof(struct listnode));

    if (NULL == node) {
        return NULL;
    } else {
        // initialize node contents
        node->next = NULL;
        node->name = malloc(strlen(name)+1);
        if (NULL == node->name) {
            // clean up and return failure
            free(node);
            return NULL;
        } else {
            // store the name in the node
            strcpy(node->name, toLower(name));
        }
    }

    return node;
}

// listInsert: insert the given name into the list (in order)
// return true if success, false if failure.
//
// Examples:
// insert: alabama
//      (before) head - montana - ohio - washington
//      (after)  head - [X] - montana - ohio - washington
// insert: utah
//      (before) head - alabama - montana - ohio - washington
//      (after)  head - alabama - montana - ohio - [X] - washington
// insert: wyoming
//      (before) head - alabama - montana - ohio - utah - washington
//      (after)  head - alabama - montana - ohio - utah - washington - [X]
bool listInsert(struct listnode *head, char *name)
{
    struct listnode *node = newNode(name);

    if (head == NULL || node == NULL) {
        return false;
    } else {
        // insert the new node at alphabetical place in list
        struct listnode *place = head;
        while (place->next != NULL && strcmp(name, place->next->name) > 0) {
            place = place->next;
        }
        // On exit, place points at last item on the list, or
        // place points at a middle item, but new name comes before place->next.
        // Thus, we want to insert 'node' after place and before place->next.
        node->next = place->next;
        place->next = node;
    }
    return true;
}

// removeDuplicates: remove duplicates from list (+ update counter)
void removeDuplicates(struct listnode *head, int *n)
{
    for (struct listnode *node = head->next; node != NULL; ) {
        if (node->next != NULL && strcmp(node->name, node->next->name) == 0) {
            // duplicate detected; remove node->next from list
            struct listnode *duplicate = node->next;
            node->next = node->next->next;
            freeNode(duplicate);
            (*n)--;
        } else {
            // only advance when we do not find a duplicate
            node = node->next;
        }
    }
}

// freeNode: delete memory for the given node
void freeNode(struct listnode *node)
{
    if (node != NULL) {
        if (node->name != NULL) {
            free(node->name);
            node->name = NULL;
            free(node);
            node = NULL;
            // NOTE: some people like to set an item to NULL after free()-ing it;
            // others don't like this practice.
        }
    }
}

// freeAllNodes: free all nodes starting at the head of the list
void freeAllNodes(struct listnode *head)
{
    // TODO: fill me in, please! :-)
}

// printNames: step through the list and print the names
void printNames(struct listnode *head, int n)
{
    printf("You have %d states:\n", n);
    for (struct listnode *node = head->next; node != NULL; node = node->next) {
        printf("%s", node->name);
    }
}

// toLower: lowercase each ASCII character in a null-terminated string.
// returns a pointer to the lower-cased string.
char* toLower(char* s)
{
    for (char *p = s; *p; p++) {
        *p = tolower(*p);
    }
    return s;
}
