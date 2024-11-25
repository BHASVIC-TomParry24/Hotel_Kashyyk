#include <stdio.h>
#include <stdlib.h>

void writeFile(char fileName[30], int line, char text[30]) {
    char buffer[30];
    int counter = 0;
    FILE *file = NULL;
    FILE *temp = NULL;
    file = fopen(fileName, "r");
    temp = fopen("temp.txt", "w");

    if (!file)
    {
        printf("Unable to open the input file!!\n");
        return;
    }
    if (!temp)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(file);
        return;
    }

    while (fgets(buffer, 30, file) != NULL)
    {
        counter++;

        if (counter == line) {
            fputs(text, temp);
            fputs("\n", temp);
        }
        else if (counter < 12) {
            fputs(buffer, temp);
        }
        else {
            break;
        }
    }

    fclose(file);
    fclose(temp);
    remove(fileName);
    rename("temp.txt", fileName);
    return;
}