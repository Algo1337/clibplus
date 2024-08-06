#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "arr.h"

Arr *Array(const char **data) {
    Arr *a = (Arr *)malloc(sizeof(Arr));
    a->idx = 0;

    if(data == NULL) {
        a->arr = (char **)alloc2(1);
    } else {
        int i = 0;
        a->arr = (char **)alloc2(1);
        while(data[i] != NULL) {
            a->arr[a->idx] = strdup(data[i]);
            a->idx++;
            a->arr = (char **)realloc(a->arr, a->idx + 1);
        }
    }

    a->Utils   = __ArrUtils;
    // a->Kill    = __KillArr;

    return a;
}

void *__ArrUtils(Arr *a, ArrTools mode, ...) {
    int first = 1, sec = 2;
    va_list args;
    va_start(args, first);

    switch(mode) {
        case __NEW: { return (void *)Array((const char **)get_va_args_dptr_str(args)); }
        case __APPEND: { return (void *)__ArrAppend(a, get_va_arg_str(args)); }
        case __MERGE: { return (void *)__ArrAppendBulk(a, (const char **)get_va_args_dptr_str(args)); }
        default:
            return NULL;
    }
    
    return 0;
}

void *__ArrAppend(Arr *a, const char *data) {
    a->idx++;
    printf("%ld\n", a->idx);
    a->arr[a->idx] = strdup(data);
    a->arr = (char **)realloc(a->arr, a->idx + 1);
}

void *__ArrAppendBulk(Arr *a, const char **arr) {
    int i = 0;
    while(arr[i] != NULL) {
        if(!strcmp(arr[i], "\0"))
            break;

        a->arr = (char **)realloc(a->arr, a->idx + 1);
        a->arr[a->idx] = strdup(arr[i]);
        a->idx++;
        i++;
    }
}