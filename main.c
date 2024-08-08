#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the entire package
#include "Libraries/c_types.h"

int main() {
    str *s = string("TEST");
    printf("%s\n", s->data);

    return 0;
}