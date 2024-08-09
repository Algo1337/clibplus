#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "str.h"

str *string(const char *data) {
    str *s = (str *)malloc(sizeof(str));
    if(data)
        s->data = strdup((char *)*&data);
        
    s->Utils = __StrUtils;
    s->Kill = CleanString;

    return s;
}


void *__StrUtils(str *s, strTools mode, ...) {
    int first = 1, sec = 2;
	va_list args;
    va_start(args, sec);

	switch(mode) {
		case _STRIP:            { return (void *)__Strip(s); }
		case _TRIM:             { return (void *)__Trim(s, get_va_arg_char(args)); }
		case _COUNTCHAR:        { return (void *)__CountChar(s, get_va_arg_char(args)); }
		case _COUNTSTR:         { return (void *)__CountSubstr(s, get_va_arg_str(args)); }
		case _STARTSWITH:       { return (void *)__StartsWith(s, get_va_arg_str(args)); }
		case _ENDSWITH:         { return (void *)__EndsWith(s, get_va_arg_str(args)); }
        case _ISUPPERCASE:      { return (void *)__IsUppercase(s); }
		case _ISLOWERCASE:      { return (void *)__IsLowercase(s); }
        case _TOUPPERCASE:      { return (void *)__ToUppercase(s); }
        case _TOLOWERCASE:      { return (void *)__ToLowercase(s); }
        // case _SPLIT:            { return (void *)__SplitChar(s, get_va_arg_char(args)); }
        case _SPLITCHAR:        { return (void *)__SplitChar(s, get_va_arg_char(args)); }
        case _REPLACE:          { 
            char *find = get_va_arg_str(args);
            char *replace = get_va_arg_str(args);
            return (void *)__Replace(s, find, replace); 
        }
        case _JOIN:             { 
            char **arr = get_va_args_dptr_arr(args);
            char delim = get_va_arg_char(args);
            return (void *)__Join(s, (const char **)arr, delim); 
        }
	}

    va_end(args);
	return 0;
}

long __Strip(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    
    int start = 0;
    while(s->data[start] != '\0')
        if(isspace(s->data[start]))
            start++;
        else
            break;

    int end = strlen(s->data) - 1;
    while(s->data[end] != '\0')
        if(isspace(s->data[end]))
            end--;
        else
            break;

    for(int i = start; i < end + 1; i++)
        strncat(buffer, &s->data[i], sizeof(char));

    s->data = strdup(buffer);
    free(buffer);

    return (start > 0 && end < strlen(s->data) ? 1 : 0);
}

long __Trim(str *s, const char delim) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    
    for(int i = 0; i < strlen(s->data); i++)
        if(s->data[i] != delim)
            strncat(buffer, &s->data[i], sizeof(char));

    int modify_chk = strlen(buffer) < strlen(s->data) ? 1 : 0;
    s->data = strdup(buffer);
    free(buffer);

    return modify_chk;
}

long __CountChar(str *s, const char ch) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    long count = 0;
    for(int i = 0; i < strlen(s->data); i++)
        if(s->data[i] == ch)
            count++;

    return count;
}

long __CountSubstr(str *s, const char *substr) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    long count = 0;
    if(strlen(substr) < 2) 
        return 0;

    for(int i = 0; i < strlen(s->data); i++)
        if(s->data[i] == substr[0] && s->data[ i + strlen(substr)-1 ] == substr[strlen(substr) - 1])
            count++;

    return count;
}

long __StartsWith(str *s, const char *str) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    if(strlen(str) < 2) 
        return 0;

    long count = 0;
    for(int i = 0; i < strlen(str); i++)
        if(s->data[i] == str[i])
            count++;
    
    return (count == strlen(str) ? 1 : 0);
}

long __EndsWith(str *s, const char *str) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    if(strlen(str) < 1)
        return 0;

    long count = 0;
    for(int i = strlen(s->data) - strlen(str); i < strlen(s->data); i++)
        if(s->data[i] == str[count])
            count++;

    return (count == strlen(str) ? 1 : 0);
}

long __IsUppercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    for(int i = 0; i < strlen(s->data) - 1; i++)
        if(!isupper(s->data[i]))
            return 0;

    return 1;
}

long __IsLowercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    for(int i = 0; i < strlen(s->data) - 1; i++)
        if(!islower(s->data[i]))
            return 0;

    return 1;
}

long __ToUppercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    long chk = 0;

    for(int i = 0; i < strlen(s->data); i++) {
        if(isalpha(s->data[i]) && !isupper(s->data[i])) {
            chk++;
            char byte = toupper(s->data[i]);
            strncat(buffer, &byte, sizeof(char));
            continue;
        }

        strncat(buffer, &s->data[i], sizeof(char));
    }

    s->data = strdup(buffer);
    free(buffer);

    return chk;
}

long __ToLowercase(str *s) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    long chk = 0;

    for(int i = 0; i < strlen(s->data); i++) {
        if(isalpha(s->data[i]) && !islower(s->data[i])) {
            chk++;
            char byte = tolower(s->data[i]);
            strncat(buffer, &byte, sizeof(char));
            continue;
        }

        strncat(buffer, &s->data[i], sizeof(char));
    }

    s->data = strdup(buffer);
    free(buffer);

    return chk;
}

long __Replace(str *s, const char *find, const char *replacement) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    printf("%s | %s | %s\n", s->data, find, replacement);
    long sz = strlen(s->data);
    if(strlen(replacement) > strlen(find))
        sz = strlen(s->data) + (strlen(replacement) - strlen(find));

    char *buffer = (char *)alloc(sz);

    for(int i = 0; i < strlen(s->data); i++) {
        if(s->data[i] == find[0]) {
            int ch_count = 0;
            for(int start = i; start < strlen(find) + 1; start++) {
                // Match all Characters
                if(s->data[start] == find[ch_count])
                    ch_count++;

                // Append replacement and adjust i
                if(ch_count == strlen(find)) {
                    strncat(buffer, replacement, strlen(replacement));
                    i += strlen(find);
                }
            }
        }
        strncat(buffer, &s->data[i], sizeof(char));
    }

    s->data = strdup(buffer);
    free(buffer);

    return 1;
}

char **__SplitChar(str *s, const char delim) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    long args_count = __CountChar(s, delim);
    char **arr = (char **)alloc2(args_count + 1);
    int idx = 0;
    int ch_count = 0;

    arr[0] = (char *)alloc(1);
    for(int i = 0; i < strlen(s->data); i++) 
    {
        if(s->data[i] == '\0')
            break;

        if(s->data[i] == delim) {
            idx++;
            arr[idx] = (char *)alloc(1);
            ch_count = 1;
            continue;
        }

        strncat(arr[idx], &s->data[i], sizeof(char));
        arr[idx] = (char *)realloc(arr[idx], ch_count + 1);
        ch_count++;
    }

    return arr;
}

void *__Join(str *s, const char **arr, const char delim) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    int i = 0;
    while(arr[i] != NULL)
    {
        strncat(s->data, arr[i], strlen(arr[i]));
        if(arr[ i + 1] != NULL)
            strncat(s->data, &delim, sizeof(char));
        i++;
    }
}

void CleanString(str *s) {
    if(s->data == NULL)
        return;

    s->idx = 0;
    free(s->data);
}