#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "multi_type.h"

uArray *new_array(void) {
    uArray *a = (uArray *)malloc(sizeof(uArray));
    a->arr = (void **)malloc(sizeof(void *) + 1);

    a->Append = __appendelement;
    CARRAY = a;

    return a;
}

uArray *__appendelement(int sz, void *data) {
    if(CARRAY == NULL)
        return CARRAY;

    CARRAY->arr[CARRAY->idx] = (void *)malloc(sz);
    CARRAY->arr[CARRAY->idx] = data;
    CARRAY->idx++;
    CARRAY->arr = (void **)realloc(CARRAY->arr, sizeof(void *) * CARRAY->idx + 1);
    return CARRAY;
}