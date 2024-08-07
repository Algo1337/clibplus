#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/global.h"
#include "Libraries/String/str.h"
#include "Libraries/Array/arr.h"

int main() {
    char *arr[] = {"TEST", "FAG", NULL};
    
    int c = count_arr(arr);
    Arr *a = Array(arr);
    printf("Elements: %d\n", c);

    a->Append(a, "GAY");
    a->Append(a, "Com");
    a->Append(a, "Is");
    a->Append(a, "Gay");

    c = count_arr(a->arr);
    printf("Elements: %d\n", c);
    for(int i = 0; i < a->idx; i++) {
        printf("%d: %s\n", i, a->arr[i]);
    }


    return 0;
}