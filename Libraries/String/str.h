#pragma once

#ifndef STR_H
#define STR_H

#include "../global.h"
#include "../global_memory.h"

typedef struct str {
    char            *data;      // String Data
    long            idx;        // Current String Length

    // String Utilitiess
    int             (*NewString)            (struct str *s, const char *data);
    int             (*AppendString)         (struct str *s, const char *data);

    long            (*CountChar)            (struct str *s, const char ch);
    long            (*FindChar)             (struct str *s, const char ch);
    long            (*FindCharAt)           (struct str *s, const char ch, int count);
    long            (*Strip)                (struct str *s);
    long            (*StripCh2End)          (struct str *s, const char start);
    long            (*Trim)                 (struct str *s, const char delim);
    long            (*TrimAtIdx)            (struct str *s, int idx);
    long            (*CountSubstr)          (struct str *s, const char *substr);
    long            (*FindSubstr)           (struct str *s, const char *substr);
    char *          (*GetSubstr)            (struct str *s, int start, int end);
    long            (*StartsWith)           (struct str *s, const char *str);
    long            (*EndsWith)             (struct str *s, const char *str);
    long            (*IsUppercase)          (struct str *s);
    long            (*IsLowercase)          (struct str *s);
    long            (*ToUppercase)          (struct str *s);
    long            (*ToLowercase)          (struct str *s);
    long            (*ReplaceChar)          (struct str *s, const char ch, const char r);
    long            (*ReplaceCharWithStr)   (struct str *s, const char ch, const char *r);
    char *          (*ReplaceString)        (struct str *s, const char *find, const char *replace);
    char **         (*Split)                (struct str *s, const char *delim);
    char **         (*SplitStringWithChar)  (struct str *s, const char delim);
    void            (*Join)                 (struct str *s, const char **arr, const char delim);

    // Clean up the structure
    void            (*Kill)  (struct str *s);
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
//      Start/Reset the current string
//
int     __newString(str *s, const char *data);

//
//      Append data to the current string
//
int     __add2str(str *s, const char *data);

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