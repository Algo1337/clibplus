#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "global.h"

void err_n_exit(const char *data) {
    printf("%s\n", data);
    exit(0);
}

char **get_va_args_dptr_str(va_list a) {
    char **arg = (char **)va_arg(a, char**);
    return arg;
}

char *get_va_arg_str(va_list a) {
	char *arg = (char *)va_arg(a, char*);
	return  arg;
}

int get_va_arg_char(va_list a) {
	int arg = (int)va_arg(a, int);
	return arg;
}