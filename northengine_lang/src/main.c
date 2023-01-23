//
// Created by deshik on 20.01.2023.
//


#include <stdio.h>
#include <stdlib.h>

#include "function.h"

int main() {
    // read file
    FILE *file = fopen("test.ne", "r");
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *fileText = malloc(size + 1);
    fread(fileText, 1, size, file);
    fileText[size] = '\0';
    fclose(file);

    struct funcData *functions = getFunctions(fileText);
    for (int i = 0; i < 3; i++) {
        struct funcData func = functions[i];
        for(int j = 0; j < func.size; j++) {
            printf("%c", func.start[j]);
        }
        printf("\n\n-------\n\n");
    }
    return 0;
}
