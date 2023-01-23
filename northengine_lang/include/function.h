//
// Created by deshik on 20.01.2023.
//

#ifndef NORTH_ENGINE_LANG_FUNCTION_H
#define NORTH_ENGINE_LANG_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>

struct funcData {
    char *start;
    size_t size;
};

struct funcData *getFunctions(char *fileText) {
    struct funcData *functions = malloc(sizeof(struct funcData));
    char *end = fileText;

    size_t i = 0;
    char * line_start = 0;

    while (*end != '\0') {
        if (*end == '\n') {
            line_start = end;
        } else if (*end == '{') {
            functions[i].start = line_start;
            while (*end != '}') {
                end++;
            }
            functions[i].size = end - functions[i].start;
            i++;
        }
        end++;
    }
    return functions;
}

#endif //NORTH_ENGINE_LANG_FUNCTION_H
