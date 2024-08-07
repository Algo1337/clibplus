#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
*   [ Calloc-Like Functions ]
*/

char *alloc(long mem_sz) {
    char *data = (char *)malloc(mem_sz);
    memset(data, '\0', mem_sz);
    
    return data;
}

char **alloc2(long mem_sz) {
    char **data = (char **)malloc(sizeof(char *) * mem_sz);
    memset(data, '\0', mem_sz);

    return data;
}

/*
*   [@DOC]
*       int FreeDChar(char **data)
*
*       0 means no memory was free'd
*/
int FreeDChar(char **data) {
    if(data == NULL)
        return 0;

    int i = 0;
    while(data[i] != NULL) {
        free(data[i]);
        i++;
    }

    return i;
}