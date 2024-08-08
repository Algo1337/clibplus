
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "arr.h"

Arr *Array(char **c_arr) {
    Arr *a = (Arr *)malloc(sizeof(Arr));
    a->idx = 0;

    a->Utils = __ArrUtils;
    a->Kill = _killArray;

    if(c_arr != NULL) {
        int count = count_arr(c_arr);
        a->arr = (char **)alloc2(count);
        for(int i = 0; i < count; i++) {
            if(c_arr[i] != NULL && strlen(c_arr[i]) > 0) {
                a->arr[i] = strdup(c_arr[i]);
                a->idx++;
            }
        }
        return a;
    }
    
    a->arr = (char **)alloc2(1);
    return a;
}

void *__ArrUtils(Arr *a, ArrTools mode, ...) {
    int first = 1, sec = 2;
	va_list args;
    va_start(args, sec);

	switch(mode) {
        // Checks
        case __IN_ARRAY:        { return (void *)__in_array(a, get_va_arg_str(args)); }
        case __GET_ELEMENT:     { return (void *)__get(a, (int)get_va_arg_char(args)); }

        // Modifying
		case __APPEND:          { return (void *)__AppendElement(a, get_va_arg_str(args)); }
        case __APPEND_AT:       { 
            int ch = get_va_arg_char(args);
            char *str = get_va_arg_str(args);
            return (void *)__AppendElementAt(a, ch, str); }
		case __REMOVE_BY_IDX:   { return (void *)__RemoveElement(a, get_va_arg_char(args)); }
        case __MERGE_ARR:       { return (void *)__Merge(a, get_va_args_dptr_arr(args)); }
	}

    va_end(args);
	return 0;
}

char *__toStr(Arr *a) {
    int i = 0, count = 0;
    while(a->arr[i] != NULL)
        count += strlen(a->arr[i++]);

    char *buff = (char *)alloc(count + a->idx + 1);
    strcat(buff, "[");
    i = 0;
    while(a->arr[i] != NULL) {
        strncat(buff, a->arr[i], strlen(a->arr[i]));
        strcat(buff, ", ");
        i++;
    }

    strcat(buff, "]");

    return buff;
}

long __AppendElementAt(Arr *a, int idx, char *data) {
    if(idx >= a->idx || data == NULL)
        return 0;

    char **new = (char **)alloc2(a->idx + 1);

    int i = 0, j = 0;
    while(i < idx)
        new[i++] = a->arr[j++];

    new[i++] = data;
    while(i < a->idx + 1)
        new[i++] = a->arr[j++];

    new[i] = NULL;
            

    free(a->arr);
    a->arr = new;
    a->idx++;
    return 1;
}

long __AppendElement(Arr *a, char *data) {
    if(a->arr == NULL)
        return 0;

    a->arr = (char **)realloc(a->arr, sizeof(char *) * (a->idx + 1));
    a->arr[a->idx] = strdup(data);
    a->idx++;
    return 1;
}

long __RemoveElement(Arr *a, int idx) {
    if(idx >= a->idx) 
        return 0;

    char **newArr = (char **)alloc2(a->idx - 1);
    for(int i = 0, j = 0; i < a->idx; i++) {
        if (i == idx) {
            free(a->arr[i]);
            continue;
        }
        newArr[j++] = a->arr[i];
    }

    free(a->arr);
    a->arr = newArr;
    a->idx--;

    return 1;
}

void *__Merge(Arr *a, char **arr) {
    if(arr == NULL)
        return NULL;

    int new_arr_count = count_arr(arr) + (int)a->idx - 1;
    
    char **new = (char **)alloc2(new_arr_count);
    for(int i = 0; i < a->idx; i++)
        new[i] = a->arr[i];

    for(int i = 0; i < new_arr_count; i++)
        new[a->idx++] = arr[i];

    new[a->idx] = NULL;
    free(a->arr);
    a->arr = new;

    return NULL;
}

char *__get(Arr *a, int idx) {
    for(int i = 0; i < a->idx; i++)
        if(i == idx)
            return a->arr[i];
            
    return NULL;
}

long __in_array(Arr *a, char *data) {
    for(int i = 0; i < a->idx; i++)
        if(!strcmp(a->arr[i], data))
            return 1;

    return 0;
}

void _killArray(Arr *a) {
    for(int i = 0; i < a->idx; i++) {
        if(a->arr[i] == NULL)
            break;

        a->arr[i] = NULL;
    }
    free(a->arr);
}

int count_arr(char **data) {
    int i = 0;
    while((data[i] != NULL))
        i++;
    
    return i;
}