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
    HTTPClientResponse *r = RequestURL("ipwho.is", "/70.70.70.72");
    
    if(r->status_code == OK) {
        printf("%s", r->body->data);
    } else {
        printf("Error, Status Code %d", r->status_code)
    }

    return 0;
}