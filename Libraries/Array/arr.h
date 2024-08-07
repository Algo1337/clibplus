#pragma once

#ifndef ARR_H
#define ARR_H

#include "../global.h"
#include "../global_memory.h"

typedef enum ArrTools {
    __NONE,
    
    // Checking Tools
    __IN_ARRAY,

    // Modifying Tools
    __APPEND,           // Append Element
    __APPEND_AT,        // Append Element @ a IDX position provided
    __REMOVE_BY_IDX,    // Remove Element By Idx
    __REMOVE_BY_STRING, // Remove Element Matching String Provided
    __REMOVE_BY_SUBSTR, // Remove Element Containing a Substr
    __MERGE_ARR,        // Append an entire array into the current one
    __GET_ELEMENT       // Get Element By IDX
} ArrTools;

typedef struct Arr {
    char    **arr;
    long    idx;
    
    void *  (*Utils) (struct Arr *a, ArrTools mode, ...);
    void    (*Kill) (struct Arr *a);
} Arr;

Arr     *Array(char **c_arr);
void    *__ArrUtils(Arr *a, ArrTools mode, ...);
long    __AppendElement(Arr *a, char *data);
long    __AppendElementAt(Arr *a, int idx, char *data);
long    __RemoveElement(Arr *a, int idx);
long    __in_array(Arr *a, char *data);
void    _killArray(Arr *a);
int     count_arr(char **data);

#endif