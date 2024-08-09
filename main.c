#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the entire package
#include <C_TYPES/c_types.h>

int main() {
    str *s = string("test");
    printf("%s\n", s->data);

    return 0;
}