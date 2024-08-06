#pragma once

#ifndef ARR_H
#define ARR_H

#include "../global.h"
#include "../String/str.h"

typedef enum ArrTools {
    __NONE,

    // Checking Tools

    // Modifying Tools
    __NEW,
    __APPEND,
    __MERGE,
    __REMOVE,
    __REPLACEARR,
    __REPLACEELEMENT,

} ArrTools;

typedef struct Arr {
    char        **arr;
    long        idx;

    void *      (*Utils) (struct Arr *a, ArrTools mode, ...);
    void *      (*Kill) (struct Arr *a);
} Arr;

Arr *Array(const char **data);
void *__ArrUtils(Arr *a, ArrTools mode, ...);
void *__ArrAppend(Arr *a, const char *data);
void *__ArrAppendBulk(Arr *a, const char **arr);
// void *__KillArr(Arr *a);

#endif