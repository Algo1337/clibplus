#pragma once

#ifndef STR_H
#define STR_H

#include "../global.h"
#include "../global_memory.h"

typedef enum strTools {
    _NONE,

    // Checking Tools
    _COUNTCHAR,
    _COUNTSTR,
    _STARTSWITH,
    _ENDSWITH,
    _ISLOWERCASE,
    _ISUPPERCASE,

    // Modifying Tools
    _NEW,
    _APPEND,
    _REMOVE,
    _REPLACE,
    _STRIP,
    _TRIM,
    _SPLIT,
    _SPLITCHAR,
    _TOLOWERCASE,
    _TOUPPERCASE,
    _JOIN
} strTools;

typedef struct str {
    char    *data;
    long    _idx;

    void *  (*Utils) (struct str *s, strTools mode, ...);
    void *  (*Kill)  (struct str *s);
} str;

//
//      Create an Instace of str
//
str     *string(const char *data);

//
//      Set of String Utilities Using ArrTools
//
void    *__StrUtils(str *s, strTools mode, ...);

//
//      Strip whitespaces from front and end of a string
// 
long     __Strip(str *s);

//
//      Trim a char from string.
//
long    __Trim(str *s, const char delim);

//
//      Count the amount of matches comparing a char
//
long    __CountChar(str *s, const char ch);

//
//      Count the amount of matches comparing a sub string
//
long    __CountSubstr(str *s, const char *substr);

// 
//      Check if a string starts with a sub string
//
long    __StartsWith(str *s, const char *str);

//
//      Check if a string ends with a sub string
//
long    __EndsWith(str *s, const char *str);

//
//      Check if a string contains all uppercase character
//
long    __IsUppercase(str *s);

//
//      Check if a string contains all lowercase charaters
//
long    __IsLowercase(str *s);

//
//      Convert all lowercase characters to uppercase
//
long    __ToUppercase(str *s);

//
//      Convert all uppercase characters to lowercase
//
long    __ToLowercase(str *s);

//
//      Replace a Substring
//
long    __Replace(str *s, const char *find, const char *replace);

//
//      Split a string
//
char    **__SplitChar(str *s, const char delim);


//
//      Append all element in the array provided to string with the delim between each
//
void    *__Join(str *s, const char **arr, const char delim);

#endif