#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 100

void encode(char* line, FILE* optr) {

    char key[127] = "efghijklmnopqrstuvwxyzabcd";

    for (int i = 0; i < strlen(line); ++i) {
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
    }
    else {
        while (fgets(line, MAX_LINE_SIZE, infptr) != NULL) {
            fprintf(outfptr, "%s", line);
            encode(line, outfptr);
        }
    }
    return(0);
}
