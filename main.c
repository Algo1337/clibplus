#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the entire package
#include <C_TYPES/c_types.h>
// #include <C_TYPES/Net/request.h>
#include "Libraries/Net/request.h"

int main() {
    str *s = string(NULL);
    s->Utils(s, _APPEND, "TEST");
    printf("%s\n", s->data);

    HTTPClientResponse *r = RequestURL("www.google.com", "");
    printf("%s", r->body->data);

    free(s);
    return 0;
}