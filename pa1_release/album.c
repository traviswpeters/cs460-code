/*
 * album.c
 *
 * Some sample code to collect input from the user.
 * This can serve as a nice starting point for your assignment!
 *
 * NOTE:
 * ----
 * Sometimes, when you want both single-char input and longer text input, using scanf and getc and
 * such, one fetch may leave unconsumed characters in stdin that confuses subsequent fetches.
 * Trailing newlines also can cause trouble. Should these things cause you problems in pa1,
 * this code (specifically readline) may prove helpful.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "readline.h"

/*
 * A basic main() function that accepts arguments from the commpand line
 * and illustrates an example of using the readline code.
 */
int main(int argc, char * argv[])
{
    const int lineLength = 50;           // maximum length of line
    char line[lineLength];               // buffer for reading lines

    // read input from stdin (e.g,. manual input on separate lines, piped/redirected file)
    while (!feof(stdin)) {
        printf("> ");
        if (readLine(line, lineLength)) {
            printf("|-> %s", line);
        }
    }

    return 0;
}
