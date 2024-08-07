#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/String/str.h"
#include "Libraries/Array/arr.h"

int main() {
    char *arr[] = {"TEST", "FAG", NULL};
    
    int c = count_arr(arr);
    Arr *a = Array(arr);
    printf("Elements: %d\n", c);

    a->Utils(a, __APPEND, "GAY");
    a->Utils(a, __APPEND, "Com");
    a->Utils(a, __APPEND, "Is");
    a->Utils(a, __APPEND, "Gay");

    a->Utils(a, __REMOVE_BY_IDX, 2);

    c = count_arr(a->arr);
    printf("Elements: %d\n", c);

    a->Utils(a, __APPEND_AT, 1, "NIGGER");

    c = count_arr(a->arr);
    printf("Elements: %d\n", c);

    for(int i = 0; i < a->idx; i++) {
        printf("%d: %s\n", i, a->arr[i]);
    }

    int n = (int)a->Utils(a, __IN_ARRAY, "Is");
    if(n)
        printf("InArray: %d | Elements: %d\n", n, c-1);

    return 0;
}