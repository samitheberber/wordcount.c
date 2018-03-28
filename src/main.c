/* main.c */
#include<stdio.h>
#include<stdlib.h>

#include "file.h"
#include "structure.h"

char* getFilename(void);
FILE* validFilename(char *filename);

int main(int argc, char *argv[]) {

    /* Presents the variables */
    FILE* input = stdin;
    FILE* output = stdout;
    StorageP storage = buildStorage();

    /* Checks the arguments */
    if (argc > 3) {
        /* Arguments aren't valid so print error and exit */
        fprintf(stderr, "Invalid arguments. This program takes only one argument, the filename, and it is also optional.\n");
        exit(EXIT_FAILURE);
    } else if (argc == 3) {
        /* Input and output -files setted */
        input = getFileR(argv[1]);
        output = getFileW(argv[2]);
    } else if (argc == 2) {
        /* Input-file setted */
        input = getFileR(argv[1]);
    }

    /* Insert words and chars from input-file */
    insertWords(storage, input);

    /* Closes input-file */
    closeFile(input);

    /* Prints words in output-file and clears words hash */
    printAndEmptyWords(output);

    /* Clear storage */
    unbuildStorage(storage, output);

    /* Closes output-file*/
    closeFile(output);

    /* Exits succesfully */
    exit(EXIT_SUCCESS);
}
