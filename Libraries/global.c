#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "global.h"

void err_n_exit(const char *data) {
    printf("%s\n", data);
    exit(0);
}