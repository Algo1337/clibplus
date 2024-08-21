#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DECLARE(name) \
    typedef const char *name;

DECLARE(String);

typedef struct Arr {
    void **arr;
    int idx;
} Arr;

int main() {
    Arr *a = (Arr *)malloc(sizeof(Arr));
    a->arr = (void **)malloc(sizeof(void *) * 3);
    memset(a->arr, '\0', sizeof(a->arr));

    String name = "algo";
    int age = 20;

    a->arr[0] = (void *)name;
    a->arr[1] = (void *)age;


    printf("%s\n", (char *)a->arr[0]);
    printf("%d\n", (int)a->arr[1]);
    return 0;
}