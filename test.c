#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// OOP

typedef struct NEW_STRUCT {
    char *name;
    int age;
} NEW_STRUCT;

typedef struct STRUCT {
    NEW_STRUCT *base;
    char *name;
    int age;

    void *  (*Kill) (struct STRUCT *s);
} STRUCT;

NEW_STRUCT *NEW_STRUCT_INIT() {
    NEW_STRUCT *n = (NEW_STRUCT *)malloc(sizeof(NEW_STRUCT));
    return n;
}

void *__KillNEW_STRUCT(NEW_STRUCT *n) {
    if(n->name == NULL)
        return NULL;

    free(n->name);
}

void *__KillSTRUCT(STRUCT *s) {

    if(s->base == NULL)
        return NULL;

    __KillNEW_STRUCT(s->base);
    free(s);
}

STRUCT *STRUCT_INIT(NEW_STRUCT *n, char *name) {
    STRUCT *s = (STRUCT *)malloc(sizeof(STRUCT));
    s->base = n;
    s->Kill = __KillSTRUCT;
    s->base->name = strdup(name);
    return s;
}

int main() {
    STRUCT *s = STRUCT_INIT(NEW_STRUCT_INIT(), "github.com/AdvancedAlgorithm");
    printf("%s\n", s->base->name);
    s->Kill(s);
    return 0;
}