#pragma once

#ifndef ARR_H
#define ARR_H

#include "../global.h"
#include "../String/str.h"

typedef enum ArrTools {
    __NONE,
    
    // Checking Tools
    __IN_ARRAY,

    // Modifying Tools
    __APPEND,           // Append Element
    __APPEND_AT,        // Append Element @ a IDX position provided
    __REMOVE_BY_IDX,    // Remove Element By Idx
    __REMOVE_BY_STRING, // Remove Element Matching String Provided
    __MERGE_ARR,        // Append an entire array into the current one
    __GET_ELEMENT       // Get Element By IDX
} ArrTools;

typedef struct Arr {
    char    **arr;
    long    idx;
    
    // Array Utilities
    void *  (*Utils)    (struct Arr *a, ArrTools mode, ...);

    // Clean The Struct
    void    (*Kill)     (struct Arr *a);
} Arr;

//
//      Create an instance of Arr taking an array or creating an empty one
//
Arr     *Array(char **c_arr);

//
//      Array Utilities
//
void    *__ArrUtils(Arr *a, ArrTools mode, ...);

//
//      Convert the current array into a string
//
char    *__toStr(Arr *a);

//
//
//
char   *__arr2str(Arr *a, const char delim);

//
//      Get Element By Idx
//
char    *__get(Arr *a, int idx);

//
//      Append an Element
//
long    __AppendElement(Arr *a, char *data);

//
//      Append an Element @ Idx
//
long    __AppendElementAt(Arr *a, int idx, char *data);

//
//      Remove Element with Idx
//
long    __RemoveElement(Arr *a, int idx);

//
//      Merge an array into the current one
//
void    *__Merge(Arr *a, char **arr);

//
//      Check if the element provided is in the array
//
long    __in_array(Arr *a, char *data);

//
//      Count a dptr array
//
int     count_arr(char **data);

//
//      Clean the struct up
//
void    _killArray(Arr *a);

#endif