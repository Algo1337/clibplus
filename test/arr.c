#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <C_TYPES/c_types.h>

int run_arr() {
    char *arr[] = {"TEST", "FAG"};

    // Create an array instance providing a pre-made array
    Arr *a = Array(arr);
    printf("Array(): Elements: %d\n", count_arr(arr));

    // Append Element
    a->Utils(a, __APPEND, "GAY");
    a->Utils(a, __APPEND, "Com");
    a->Utils(a, __APPEND, "Is");
    a->Utils(a, __APPEND, "Gay");
    a->Utils(a, __APPEND, "fdgfw");
    a->Utils(a, __APPEND, "ewfwf");
    a->Utils(a, __APPEND, "efwfw");

    // Remove Element
    a->Utils(a, __REMOVE_BY_IDX, 2);
    printf("__REMOVE_BY_IDX: Elements: %d\n", count_arr(a->arr));

    // Append At
    a->Utils(a, __APPEND_AT, 2, "TEST");
    printf("__APPEND_AT Elements: %d\n", count_arr(a->arr));

    // Merge an existing array
    a->Utils(a, __MERGE_ARR, arr);
    printf("__MERGE_ARR Elements: %d\n", count_arr(a->arr));
    
    // Get an element @ idx (Do not free to avoid loosing data. Use a->Kill(a); when done )
    char *test = a->Utils(a, __GET_ELEMENT, 3);
    printf("__GET_ELEMENT: %s\n", test);

    printf("InArray: %d | Elements: %d\n", (int)a->Utils(a, __IN_ARRAY, "Is"), count_arr(a->arr));

    // Display all elements
    for(int i = 0; i < a->idx; i++) {
        if(a->arr[i] == NULL)
            break;
        
        printf("%d: %s\n", i, a->arr[i]);
    }

    // Arr to String ( Free separately )
    char *arr2str = __toStr(a);
    printf("%s\n", arr2str);

    a->Kill(a);
    free(arr2str);
    free(a);
    return 0;
}