#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/Array/multi_type.h>
/*
*
*
*   [ MULTI-TYPE SUPPORTED ARRAY ]
*
*/

typedef struct NIGGER_BOB {
    char *name;
} NIGGER_BOB;

int main() {
    NIGGER_BOB *test = (NIGGER_BOB *)malloc(sizeof(NIGGER_BOB));
    test->name = strdup("FEDS_VC_IS_FILLED_WITH_SKIDS");
    uArray *n = new_array()->Append(sizeof(char *), "TEST")->Append(1, (void *)2)->Append(sizeof(NIGGER_BOB), test);

    printf("%s\n", (char *)n->arr[0]);
    printf("%d\n", (int)n->arr[1]);
    printf("%s\n", (char *)((NIGGER_BOB *)n->arr[2])->name);
    return 0;
}