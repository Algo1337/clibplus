#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Include the entire package
#include <clib/global.h>
#include <clib/String/str.h>
#include <clib/Array/arr.h>
#include <clib/Map/map.h>
#include <clib/Net/request.h>
#include <clib/Net/netutils.h>
#include <clib/OS/cFile.h>

int main(int argc, char *argv[]) {
    HTTPClientResponse *r = RequestURL(argv[1]);

    if(r->status_code == OK) {
        for(int i = 0; r->headers->idx - 1; i++) {
            if(r->headers->keys[i] == NULL)
                break;
                
            Key *field = (Key *)r->headers->keys[i];
            if(field->name && field->value)
                printf("[ HEADER ]: %s => %s\n", field->name, field->value);
        }

        printf("[ BODY ]: %s\n", r->body->data);

        if(r->body->CountChar(r->body, '\n') == 0 && r->body->StartsWith(r->body, " ") && r->body->EndsWith(r->body, " "));
            printf("JSON Detected\n");
    } else {
        printf("[ X ] Error, Status Code: %d\n", r->status_code);
    }
    return 0;
}