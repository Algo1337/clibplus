#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "String/str.h"
#include "Array/arr.h"
#include "Array/dim.h"
#include "Map/map.h"

//
//          Output an error message and exit
//
void        err_n_exit(const char *data);

//
//          Get a double pointer array
//
char        **get_va_args_dptr_arr(va_list a);

//
//          Get a string (char *)
//
char        *get_va_arg_str(va_list a);

//
//          Get a char or int
//
int         get_va_arg_char(va_list a);


#endif