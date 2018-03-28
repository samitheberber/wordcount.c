/* file.c */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "file.h"

FILE* getFileR(char* filename) {
    FILE* file = stdin;

    /* Checks if file is readable */
    if ( (file = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Invalid filename '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    /* If everything went right, returns file */
    return file;
}

FILE* getFileW(char* filename) {
    FILE* file = stdin;

    /* Checks if file is readable */
    if ( (file = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Invalid filename '%s'.\n", filename);
        exit(EXIT_FAILURE);
    }

    /* If everything went right, returns file */
    return file;
}

void closeFile(FILE* file) {
    /* Closes file and exit failure if couldn't do it */
    if ( fclose(file) == EOF ) {
        fprintf(stderr, "Closing file occured error.\n");
        exit(EXIT_FAILURE);
    }
}
