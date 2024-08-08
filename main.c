#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// This Lib Currently Cannot Be Threaded
#include "Libraries/Array/dim.h"

int main() {
    // Create an Instance of Map
    DimArray *a = create_arr(2);

    // Append Values to Array In Row Provided
    //
    // DimArrayElement * (*Append) (DimArray *a, int row, char *data);
    // ex: a->Append(a, 0, "NEW");
    //
    // Both DimArray and DimArrayElement have an Append method that will allow you 
    // to chain the method after pending once to append multiple values.
    //
    a->Append(a, 0, "TEST")->Append(CURRENT_DIM_ARR, "BEEP");
    a->Append(a, 1, "NEW")->Append(CURRENT_DIM_ARR, "BRUH");

    char *e = a->Get(a, 0, 1);
    printf("a->Get(): %s\n", e);
    
    e = a->Get(a, 1, 0);
    printf("a->Get(): %s\n", e);

    // How use append multiple values using a forloop
    char *t[] = {"TESTING", "THIS"};
    DimArrayElement *em;
    for(int i = 0; i < 2; i++)
        em = a->Append(a, 1, t[i]);

    // Debugging Purposes
    for(int i = 0; i < a->rows; i++) {
        if(a->arr[i] == NULL)
            break;

        if(a->arr[i]->arr == NULL)
            break;

        for(int j = 0; j < a->arr[i]->columns; j++)
            printf("[%d][%d] %s\n", i, j, a->arr[i]->arr[j]);
    }

    a->Kill(a);
    free(a);
    return 0;
}