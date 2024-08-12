#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the entire package
#include <clib/c_types.h>
#include <clib/Net/request.h>

/*
    Basic Web Request
*/
int main(int argc, char *argv[]) {
    HTTPClientResponse *r = RequestURL("ipwho.is", argv[1]);
    printf("%s", r->body->data);

    return 0;
}