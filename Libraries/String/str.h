#pragma once

#ifndef STR_H
#define STR_H

#include "../global.h"
#include "../global_memory.h"

typedef enum strTools {
    _NONE,

    // Checking Tools
    _FINDCHAR,      // Find a char in string 
    _FINDSUBSTR,    // Find a sub string provided in string
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
    _REPLACECHAR,   // Replace a char in the string
    _STRIP,         // Strips whitespaces from the string
    _STRIPCHAR2END, // Strip a string from a char to the end of the strip
    _TRIM,          // Trim a char from the string
    _TRIM_AT_IDX,   // Trim a char from the string at idx
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
//      Start/Reset the current string
//
long     __newString(str *s, const char *data);

//
//      Append data to the current string
//
str    *__add2str(str *s, const char *data);

//////////////////////////////////////
//     == [ CHAR FUNCTIONS ] ==     //
//////////////////////////////////////

//
//      Count the amount of matches comparing a char
//
long    __CountChar(str *s, const char ch);

//
//      Find a first matching char in string
//
long    findchar(str *s, const char ch);

//
//      Find a char @ the matched count
//
long    findchar_at_count(str *s, const char ch, int count);

//
//      Remove whitespaces
//
long    __Strip(str *s);

//
//      Remove data from char to end of string
//
long    __StripCh2End(str *s, const char start);

//
//      Remove a char from string
//
long    __Trim(str *s, const char delim);

//
//      Remove a char at idx in the current string
//
long    __Trim_By_Idx(str *s, int idx);

//////////////////////////////////////
//    == [ STRING FUNCTIONS ] ==    //
//////////////////////////////////////

//
//      Find a substring in the current string
//
long    __findSubstr(str *s, const char *substr);

//
//      Count the amount of comparison matching the substring provided
//
long    __CountSubstr(str *s, const char *substr);

//
//      Get a substring from start to end position of the string
//
char    *get_substr(str *s, int start, int end);

//
//      Check if the string starts with a substring provided
//
long    __StartsWith(str *s, const char *str);

//
//      Check if the string ends with a substring provided
//
long    __EndsWith(str *s, const char *str);

//
//      Check if a string is all uppercase
//
long    __IsUppercase(str *s);

//
//      Check if a string is all lowercase
//
long    __IsLowercase(str *s);

//
//      Convert the string to all uppercase characters
//
long    __ToUppercase(str *s);

//
//      Convert the string to all lowercase characters
//
long    __ToLowercase(str *s);

//
//      Replace a char
//
long    __ReplaceChar(str *s, const char ch, const char r);

//
//      Convert a char with a string
//
long    __ReplaceCharWithStr(str *s, const char ch, const char *r);

//
//      Replace a string
//
char    *replace_string(str *s, const char *find, const char *replace);

//
//      Split a string using a string delim
//
char    **__Split(str *s, const char *delim);

//
//      Split a string using a char delim
//
char    **split_string_w_char(str *s, const char delim);

//
//      Append all element in the array provided to string with the delim between each
//
void    *__Join(str *s, const char **arr, const char delim);

//
//      Clean up the struct
//
void    CleanString(str *s);

#endif