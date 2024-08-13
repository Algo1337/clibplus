#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>
#include <clib/global_memory.h>
#include <clib/Array/arr.h>
#include <clib/Net/request.h>

typedef struct Arrr {
    char **arr;
    long idx;
} Arrr;

Arrr *array(const char **data) {
    Arrr *a = (Arrr *)malloc(sizeof(Arrr));

    if(data == NULL)
        return a;

    long count = count_arr((char **)data);
    printf("%s\n", data[0]);

    printf("%ld\n", count);
    return a;
}

// void __arr2str(Arr *a, const char *delim) {
//     char *new = (char *)alloc2(1);
//     long idx = 0;
    
//     if(a->idx )
// }

int main() {
    Arrr *a = array(NULL);

    char *test[] = {"TESTING", "THIS", "SHIT"};
    a = array((const char **)test);

    return 0;
}