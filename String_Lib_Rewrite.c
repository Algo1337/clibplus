#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>

int main() {
    str *n = string(NULL);
    n = __add2str(n, "NEW\n");
    n = __add2str(n, "BEEP\n");
    n = __add2str(n, "GEE\n");

    long t = (long)__findSubstr(n, "BEEP");
    printf("%ld\n", t, n->data);

    n->data = replace_string(n, "BEEP", "LUL");

    n = __add2str(n, "GAY");
    printf("%s\n", n->data);
    printf("%ld", n->idx);
    return 0;
}