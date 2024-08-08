#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/String/str.h"
#include "Libraries/Array/arr.h"

int main() {
    char *arr[] = {"TEST", "FAG"};

    Arr *a = Array(arr);
    printf("Array(): Elements: %d\n", count_arr(arr));

    a->Utils(a, __APPEND, "GAY");
    a->Utils(a, __APPEND, "Com");
    a->Utils(a, __APPEND, "Is");
    a->Utils(a, __APPEND, "Gay");
    a->Utils(a, __APPEND, "Gay");
    a->Utils(a, __APPEND, "Gay");
    a->Utils(a, __APPEND, "Gay");

    a->Utils(a, __REMOVE_BY_IDX, 2);
    printf("__REMOVE_BY_IDX: Elements: %d\n", count_arr(a->arr));

    __AppendElementAt(a, 2, "NIGGER");
    printf("__APPEND_AT: Elements: %d\n", count_arr(a->arr));

    // Display all elements
    for(int i = 0; i < a->idx; i++)
        printf("%d: %s\n", i, a->arr[i]);

    printf("InArray: %d | Elements: %d\n", (int)a->Utils(a, __IN_ARRAY, "Is"), count_arr(a->arr));

    return 0;
}