#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the entire package
#include <clib/c_types.h>
#include <clib/Net/request.h>

/*
    Basic Web Request
*/
int main() {
    HTTPClientResponse *r = RequestURL("ipwho.is", "/8.8.4.4");
    printf("%s", r->body->data);

    return 0;
}