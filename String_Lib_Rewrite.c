#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>
#include <clib/Array/arr.h>

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
    printf("%s | %ld\n", n->data, n->idx);

    char **arr = n->SplitStringWithChar(n, '\n');
    int count = count_arr(arr);
    for(int i = 0; i < count; i++) {
        if(arr[i] == NULL)
            break;
        printf("[%d]: %s\n", i, arr[i]);
    }
    return 0;
}