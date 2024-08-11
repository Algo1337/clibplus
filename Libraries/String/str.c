#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "str.h"

str *string(const char *data) {
    str *s = (str *)malloc(sizeof(str));
    
    s->Utils = __StrUtils;
    s->SplitCh = __SplitChar;
    s->Kill = CleanString;

    // Accepting NULL as a parameter
    if(data == NULL)
        return s;

    // Validate String
    if(strlen(data) > 0) {
        s->data = strdup((char *)*&data);
        s->idx = strlen(data);
    }

    return s;
}


void *__StrUtils(str *s, strTools mode, ...) {
    int first = 1, sec = 2;
	va_list args;
    va_start(args, sec);

	switch(mode) {
        case _NEW:              { return (void *)__newString(s, get_va_arg_str(args)); }
        case _APPEND:           { return (void *)__add2str(s, get_va_arg_str(args)); }
        case _FINDCHAR:         { return (void *)__findChar(s, get_va_arg_char(args)); }
		case _STRIP:            { return (void *)__Strip(s); }
        case _STRIPCHAR2END:    { return (void *)__StripCh2End(s, get_va_arg_char(args)); }
		case _TRIM:             { return (void *)__Trim(s, get_va_arg_char(args)); }
        case _TRIM_AT_IDX:      { return (void *)__Trim_By_Idx(s, get_va_arg_char(args)); }
		case _COUNTCHAR:        { return (void *)__CountChar(s, get_va_arg_char(args)); }
		case _COUNTSTR:         { return (void *)__CountSubstr(s, get_va_arg_str(args)); }
		case _STARTSWITH:       { return (void *)__StartsWith(s, get_va_arg_str(args)); }
		case _ENDSWITH:         { return (void *)__EndsWith(s, get_va_arg_str(args)); }
        case _ISUPPERCASE:      { return (void *)__IsUppercase(s); }
		case _ISLOWERCASE:      { return (void *)__IsLowercase(s); }
        case _TOUPPERCASE:      { return (void *)__ToUppercase(s); }
        case _TOLOWERCASE:      { return (void *)__ToLowercase(s); }
        case _SPLIT:            { return (void *)__Split(s, get_va_arg_str(args)); }
        case _SPLITCHAR:        { return (void *)__SplitChar(s, get_va_arg_char(args)); }
        case _REPLACE:          { 
            char *find = get_va_arg_str(args);
            char *replace = get_va_arg_str(args);
            return (void *)__Replace(s, find, replace); 
        }
        case _JOIN:             { 
            const char **arr = (const char **)get_va_args_dptr_arr(args);
            char delim = get_va_arg_char(args);
            return (void *)__Join(s, arr, delim); 
        }
	}

    va_end(args);
	return 0;
}

long __findChar(str *s, const char ch) {
    for(int i = 0; i < s->idx; i++)
        if(s->data[i] == ch)
            return i;

    return 0;
}

long __newString(str *s, const char *data) {
    if(strlen(data) == 0)
        return 0;

    s->data = strdup(data);
    s->idx = strlen(data) + 1;
    return 1;
}

long __add2str(str *s, const char *data) {
    if(strlen(data) == 0)
        return 0;

    if(s->data == NULL)
        return __newString(s, data);

    int new_sz = strlen(s->data) + strlen(data) + 1;
    char *new = (char *)realloc(s->data, new_sz);
    strcat(new, s->data);
    strcat(new, data);
    
    free(s->data);
    s->data = strdup(new);
    s->idx = new_sz;
    free(new);
    return 1;
}

long __Strip(str *s) {
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

long __StripCh2End(str *s, const char start) {
    char *new = (char *)alloc(1);
    
    int i = 0;
    while(i < s->idx) {
        if(s->data[i] == start)
            break;

        
        strncat(new, &s->data[i], sizeof(char));
        i++;
        new = (char *)realloc(new, i + 1);
        new[i] = '\0';
    }

    free(s->data);
    s->data = strdup(new);
    s->idx = strlen(new);

    return 1;
}

long __Trim(str *s, const char delim) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    memset(buffer, '\0', strlen(s->data) + 1);
    
    int start = 0;
    for(int i = 0; i < strlen(s->data); i++) {
        if(s->data[i] != delim) {
            strncat(buffer, &s->data[start], sizeof(char));
            start++;
        }
    }

    int modify_chk = strlen(buffer) < strlen(s->data) ? 1 : 0;
    s->data = strdup(buffer);
    free(buffer);

    return modify_chk;
}

long __Trim_By_Idx(str *s, int idx) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    char *buffer = (char *)alloc(strlen(s->data) + 1);
    memset(buffer, '\0', strlen(s->data) + 1);
    
    int start = 0;
    for(int i = 0; i < strlen(s->data); i++) {
        if(i != idx) {
            strncat(buffer, &s->data[i], sizeof(char));
        }
    }

    int modify_chk = strlen(buffer) < strlen(s->data) ? 1 : 0;
    s->data = strdup(buffer);
    free(buffer);

    return modify_chk;
}

long __CountChar(str *s, const char ch) {
    // if(s->data == NULL || ch == '\0')
    //     return 0;

    long count = 0;
    for(int i = 0; i < s->idx; i++) {
        if(s->data[i] == ch)
            count++;
    }

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

char **__Split(str *s, const char *delim) {
    char **arr = (char **)alloc2(1);

    int i = 0, idx = 0;
    char *token = strtok(s->data, delim);
    while(token != NULL) {
        arr[i] = (char *)alloc(strlen(token) + 1);
        strcpy(arr[i], token);
        token = strtok(NULL, delim);
        i++;
        arr = (char **)realloc(arr, (sizeof(char *) * i) + 1);
    }
    arr[i] = NULL;

    return arr;
}

char **__SplitChar(str *s, const char delim) {
    if(s->data == NULL || strlen(s->data) == 0)
        return 0;

    long args_count = __CountChar(s, delim);
    char **arr = (char **)alloc2(args_count + 1);
    memset(arr, '\0', (sizeof(char *) * args_count) + 1);
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
        arr[idx] = (char *)realloc(arr[idx], (sizeof(char *) * ch_count) + 1);
        arr[idx][ch_count] = '\0';
        arr[idx + 1] = NULL;
        ch_count++;
    }
    arr[idx + 1] = NULL;

    return arr;
}

void *__Join(str *s, const char **arr, const char delim) {
    int i = 0;
    while(arr[i] != NULL)
    {
        if(arr[i] == NULL)
            break;
            
        s->data = (char *)realloc(s->data, s->idx + strlen(arr[i]) + 1);
        strncat(s->data, arr[i], strlen(arr[i]));
        if(arr[ i + 1] != NULL)
            strncat(s->data, &delim, sizeof(char));
        i++;
        s->idx += strlen((const char *)&arr[i]) + 1;
    }
}

void CleanString(str *s) {
    if(s->data == NULL)
        return;

    s->idx = 0;
    free(s);
}