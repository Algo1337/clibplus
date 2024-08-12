#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>

int main() {
    str *n = string(NULL);
    n->AppendString(n, "NEW\n");
    n->AppendString(n, "BEEP\n");
    n->AppendString(n, "GEE\n");

    long t = n->FindSubstr(n, "BEEP");
    printf("%ld\n", t);

    n->ReplaceString(n, "BEEP", "LUL");

    n->AppendString(n, "GAY");
    n->TrimAtIdx(n, n->idx - 1);
    printf("%s\n", n->data);
    printf("%ld", n->idx);
    return 0;
}