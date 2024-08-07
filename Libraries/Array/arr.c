/*
*       [ C String Array Library ]
*
*   @author: Algorithm
*   @github: @AdvancedAlgorithm
*   @description: This software is release "AS-IS" for public use. 
*                 any bugs or issues must be reported for fixures.
*
*   LIST OF FEAUTRES
*   new_array       ( new_string(char *arr) )               Array      DONE
*   Append          ( a->Append(Array *a, char *data) )    int         DONE
*   Remove          ( a->Remove(Array *a, int idx) )       int         DONE
*   Merge           ( a->Merge(Array *a, char **arr) )     int         DONE
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arr.h"

Arr *Array(char **c_arr) {
    Arr *a = (Arr *)malloc(sizeof(Arr));
    a->idx = 0;

    a->Append = __AppendElement;
    // a->IsInArray = is_in_arr;
    a->Kill = _killArray;

    if(c_arr != NULL) {
        int count = count_arr(c_arr);
        a->arr = (char **)malloc(sizeof(char *) * count);
        for(int i = 0; i < count; i++) {
            if(c_arr[i] != NULL && strlen(c_arr[i]) > 0) {
                a->arr[i] = strdup(c_arr[i]);
                a->idx++;
            }
        }
        return a;
    }
    
    a->arr = (char **)malloc(sizeof(char *) * 1);
    return a;
}

void __AppendElement(Arr *a, char *data) {
    a->arr = (char **)realloc(a->arr, sizeof(char *) * (a->idx + 1));
    a->arr[a->idx] = strdup(data);
    a->idx++;
}

void __RemoveElement(Arr *a, int idx) {
    if(idx >= a->idx)
        return;
        
    a->arr[idx] = NULL;
}

void _killArray(Arr *a) {
    for(int i = 0; i < a->idx; i++) {
        if(a->arr[i] != NULL)
            free(a->arr[i]);
    }
}

int count_arr(char **data) {
    int i = 0;
    while(data[i] != NULL)
        i++;
    
    return i;
}