/*
 * Encrypt (encode) plain text into something unintelligible.
 * This program will read in a file of text and map each letter to another letter using the following array:
 *  char key[27] = “efghijklmnopqrstuvwxyzabcd”;
 * This means that if you encounter the letter ‘a’, then you will replace it with the letter ‘e’, etc.
 * If you encounter any other characters in the input file (example: ‘A’ or space, etc), write them as is.
 *
 * Write each line of text (unencrypted and encrypted) to another text file.
 *
 * Adapted from CSCI 112 @ Montana State University (thanks, Mary Ann Cummings!).
 */

#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 100

void encode(char* line, FILE* optr) {
    char key[127] = "efghijklmnopqrstuvwxyzabcd";
    // a = 97

    for (unsigned int i = 0; i < strlen(line); ++i) {
        int ascii_place = line[i];
        if (97 <= ascii_place && ascii_place <= 122) {
            fprintf(optr, "%c", key[ascii_place-97]);
        }
        else {
            fprintf(optr, "%c", line[i]);
        }
    }
    return;
}

int main(void) {
    FILE* infptr = fopen("./tinyTale.txt", "r");
    FILE* outfptr = fopen("out.txt", "w");

    char line[MAX_LINE_SIZE];

    if (infptr == NULL) {
        printf("ERROR: could not open input file\n");
        return(1);
    } else {
        while (fgets(line, MAX_LINE_SIZE, infptr) != NULL) {
            fprintf(outfptr, "%s", line);
            encode(line, outfptr);
        }
    }
    return(0);
}
