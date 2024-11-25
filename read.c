#include<stdio.h>
#include<stdlib.h>

#include "project.h"

char * read(char fileName[15], int line, char buffer[100]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", fileName);
        exit(0);
    }

    int currentLine = 0;


    while (fgets(buffer, 100, file) != NULL) {
        currentLine++;
        if (currentLine == line) {
            fclose(file);
            return buffer;
        }
    }


    printf("Error: Line %d not found in file %s\n", line, fileName);
    fclose(file);
    exit(0);
}