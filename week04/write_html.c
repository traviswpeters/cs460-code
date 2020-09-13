#include <stdio.h>
#include <stdlib.h>

// Things to note:
// - fprintf to write (HTML) to a file

// function declarations
void write_html(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    write_html(argc, argv);
    return 0;
}

void write_html(int argc, char* argv[]) {
    // Open HTML file for writing.
    char* outfilename = "index.html";
    FILE* fp = NULL;
    if ((fp = fopen(outfilename, "w")) == NULL) {
        fprintf(stderr, "**error: cannot open file '%s'.**\n", outfilename);
        exit(1);
    }

    // Write the BEGINNING parts of the basic structure of an HTML file.
    char* title = "This is a SUPER SIMPLE HTML file!";
    char* subtitle = "(You might want to add more, but hey, this is a SUPER SIMPLE example!)";
    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "<title>%s</title>\n", title);
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");

    // Write some content for the page
    fprintf(fp, "<h1>%s</h1>\n", title);
    fprintf(fp, "<h2>%s</h2>\n", subtitle);

    // Create an unordered list with items from the command line
    fprintf(fp, "<h2>Here are the command line args provided when you last ran %s:</h2>\n", argv[0]);
    fprintf(fp, "<ul>\n");
    for(int i = 0; i < argc; i++) {
        fprintf(fp, "\t<li>%s</li>\n", argv[i]);
    }
    fprintf(fp, "</ul>\n");

    // Write the END parts of the basic structure of an HTML file.
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

    // Wrap up...
	fclose(fp);
    fprintf(stdout, "~~> Done writing my super simple html file: '%s'!\n", outfilename);
}
