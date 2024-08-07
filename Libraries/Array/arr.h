#pragma once

#ifndef ARR_H
#define ARR_H

typedef struct Arr {
    char    **arr;
    long    idx;
    
    void    (*Append) (struct Arr *a, char *data);
    int     (*IsInArray) (struct Arr *a, char *element);
    void    (*Kill) (struct Arr *a);
} Arr;

Arr *Array(char **c_arr);
void __AppendElement(Arr *a, char *data);
void __RemoveElement(Arr *a, int idx);
void _killArray(Arr *a);
int count_arr(char **data);

#endif