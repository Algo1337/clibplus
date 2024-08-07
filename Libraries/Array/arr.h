#pragma once

#ifndef ARR_H
#define ARR_H

typedef enum ArrTools {
    __NONE
} ArrTools;

typedef struct Arr {
    char    **arr;
    long    idx;
    
    void    (*Append) (struct Arr *a, char *data);
    void    (*Remove) (struct Arr *a, int idx);
    int     (*InArray) (struct Arr *a, char *element);
    void    (*Kill) (struct Arr *a);
} Arr;

Arr *Array(char **c_arr);
void *__ArrUtils(Arr *a, ArrTools mode, ...);
void __AppendElement(Arr *a, char *data);
void __RemoveElement(Arr *a, int idx);
int in_array(Arr *a, char *data);
void _killArray(Arr *a);
int count_arr(char **data);

#endif