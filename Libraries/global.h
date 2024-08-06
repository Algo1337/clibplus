#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

void err_n_exit(const char *data);


char        **get_va_args_dptr_str(va_list a);
char        *get_va_arg_str(va_list a);
char        get_va_arg_char(va_list a);


#endif