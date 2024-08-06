#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/global.h"
#include "Libraries/String/str.h"
#include "Libraries/Array/arr.h"

int main() {
    Arr *a = Array(NULL);
    char *t[] = {"GAY", "LUL", "FAG", "NIGGER"};
    
    a->Utils(a, __APPEND, "TEST");
    a->Utils(a, __MERGE, &t);

    printf("%ld\n", a->idx);
    for(int i = 0; i < a->idx; i++) {
        printf("[%d] %s\n", i, a->arr[i]);
    }

    free(a->arr);
    free(a);
    return 0;
}