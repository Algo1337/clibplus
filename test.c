#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>
#include <clib/global_memory.h>
#include <clib/Net/request.h>

int main() {
    str *n = string("/");
    n->AppendString(n, "parent");
    n->AppendString(n, "BEEP\n");
    n->AppendString(n, "GEE\n");
    return 0;
}