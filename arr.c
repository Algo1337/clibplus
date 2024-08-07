#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Arr {
    char        **arr;
    long        idx;

    // void *      (*Utils) (struct Arr *a);
} Arr;

Arr *Array(const char **data) {
    Arr *a = (Arr *)malloc(sizeof(Arr));
    a->arr = (char **)malloc(sizeof(char *) * 1);
    a->idx = 1;

    memset(a->arr, '\0', 1);
    return a;
}

int Append(Arr *a, const char *v) {
    // a->arr[a->idx] = (char *)malloc(strlen(v) + 1);
    // memset(a->arr[a->idx], '\0', strlen(v) + 1);
    // strcpy(a->arr[a->idx], v);

    a->arr[a->idx] = strdup(v);
    a->idx++;
}

int main() {
    char *t[] = {NULL};
    Arr *a = Array((const char **)t);
    Append(a, "TEST");
    Append(a, "trtr");
    Append(a, "gergreg");
    Append(a, "gerg");
    Append(a, "gergre");
    for(int i = 0; i < a->idx; i++)
        if(a->arr[i] != NULL)
            printf("%s\n", a->arr[i]);
}