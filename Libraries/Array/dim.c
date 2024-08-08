#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dim.h"

// A Copy Of The Last Used DimArrayElement
DimArrayElement *CURRENT_DIM_ARR = NULL;

// == [ DimArray ] ==

DimArray *create_arr(int dimensions) {
    DimArray *a = (DimArray *)malloc(sizeof(DimArray));
    a->arr = (DimArrayElement **)malloc(sizeof(DimArrayElement *) * 1);
    memset(a->arr, '\0', sizeof(DimArrayElement *) * 1);

    a->rows = dimensions;
    for(int i = 0; i < a->rows; i++) {
        DimArrayElement *new_arr = create_dim_arr_element();
        a->arr[i] = new_arr;
    }

    a->Append = append2arr;
    a->Get = __getElementAt;
    a->Kill = __KillMap;

    return a;
}

DimArrayElement *append2arr(DimArray *a, int row, char *data) {
    for(int i = 0; i < a->rows; i++)
    {
        if(i == row) {
            a->arr[i] = __Append(a->arr[i], data);
            a->rows++;
            CURRENT_DIM_ARR = a->arr[i];
            return a->arr[i];
        }
    }
}

char *__getElementAt(DimArray *a, int row, int column) {
    if(row > a->rows || a->arr[row] == NULL)
        return NULL;

    if(column > a->arr[row]->columns)
        return NULL;

    return a->arr[row]->arr[column];
}

void __KillMap(DimArray *a) {
    for(int i = 0; i < a->rows; i++) {
        if(a->arr[i] == NULL)
            break;

        if(a->arr[i]->arr == NULL)
            break;

        for(int j = 0; j < a->arr[i]->columns; j++)
            free(a->arr[i]->arr[j]);
        
        free(a->arr[i]);
    }
    free(a->arr);
}

// == [ DimArrayElement ] ==

DimArrayElement *create_dim_arr_element() {
    DimArrayElement *new_arr = (DimArrayElement *)malloc(sizeof(DimArrayElement));
    new_arr->arr = (char **)malloc(sizeof(char *) * 1);
    new_arr->columns = 0;

    new_arr->Append = __Append;

    return new_arr;
}

DimArrayElement *__Append(DimArrayElement *e, char *data) {
    e->arr[e->columns] = strdup(data);
    e->columns++;
    e->arr = (char **)realloc(e->arr, sizeof(char *) * e->columns + 1);
    return e;
}