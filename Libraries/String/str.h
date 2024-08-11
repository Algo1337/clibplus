#pragma once

#ifndef STR_H
#define STR_H

#include "../global.h"

typedef enum strTools {
    _NONE,

    // Checking Tools
    _FINDCHAR,      // Find a char in string 
    _COUNTCHAR,     // Count a char in string
    _COUNTSTR,      // Count a substr in string
    _STARTSWITH,    // check if string starts with a string
    _ENDSWITH,      // check if a string ends with a string
    _ISLOWERCASE,   // check if a string is all lowercase
    _ISUPPERCASE,   // check if a string is all uppercase

    // Modifying Tools
    _NEW,           // Overwrite new data
    _APPEND,        // Append a string
    _REMOVE,        // Remove a substr
    _REPLACE,       // Replace a substr in the string
    _STRIP,         // Strips whitespaces from the string
    _STRIPCHAR2END, // Strip a string from a char to the end of the strip
    _TRIM,          // Trim a char from the string
    _SPLIT,         // Split a string into an array using a string delim
    _SPLITCHAR,     // Split a string into an array using a char delim
    _TOLOWERCASE,   // Convert an entire string to lowercase
    _TOUPPERCASE,   // Convert an entire string to uppercase
    _JOIN           // Merge an array into a string
} strTools;

typedef struct str {
    char    *data;      // String Data
    long    idx;        // Current String Length

    // String Utilities
    void *  (*Utils) (struct str *s, strTools mode, ...);

    char ** (*SplitCh) (struct str *s, const char ch);

    // Clean up the structure
    void    (*Kill)  (struct str *s);
} str;

#define DeclareT(typ, name) \
    typedef const typ name;

#define DeclarePtrT(typ, name) \
    typedef const typ *name;

#define DeclarePtrPtrT(typ, name) \
    typedef const typ **name;

DeclareT(char, Char);
DeclarePtrT(char, String);
DeclarePtrT(char, strArr);

//
//      Create an Instace of str
//
str     *string(const char *data);

//
//      Set of String Utilities Using ArrTools
//
void    *__StrUtils(str *s, strTools mode, ...);

//
//      Create a new string
//
long    __newString(str *s, const char *data);

//
//      Append To String
//
long    __add2str(str *s, const char *data);

long __findChar(str *s, const char ch);

//
//      Strip whitespaces from front and end of a string
// 
long     __Strip(str *s);

long     __StripCh2End(str *s, const char start);

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
//
//
char    **__Split(str *s, const char *delim);

//
//      Split a string
//
char    **__SplitChar(str *s, const char delim);


//
//      Append all element in the array provided to string with the delim between each
//
void    *__Join(str *s, const char **arr, const char delim);

//
//      Clean up the struct
//
void    CleanString(str *s);

#endif