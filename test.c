#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/Array/multi_type.h>

typedef struct NIGGER_BOB {
    char *name;
} NIGGER_BOB;

int main() {
    NIGGER_BOB *test = (NIGGER_BOB *)malloc(sizeof(NIGGER_BOB));
    test->name = strdup("FEDS_VC_IS_FILLED_WITH_SKIDS");
    uArray *n = new_array()->Append(NULL, sizeof(char *), "TEST")->Append(NULL, 1, (void *)2)->Append(NULL, sizeof(NIGGER_BOB), test);

    // or 

    n = new_array();
    uArray *second_arr = new_array();
    // if u create or append to a different array like above, you must provide the instance @ first append call
    n->Append(n, sizeof(char *), "GAY")->Append(NULL, 1, (void *)2);

    printf("%s\n", (char *)n->arr[0]);
    return 0;
}