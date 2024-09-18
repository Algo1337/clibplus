#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Include the entire package
#include <clib/global.h>
#include <clib/String/str.h>
#include <clib/Net/request.h>
#include <clib/Net/netutils.h>

/*
    Basic Web Request
*/
int main(int argc, char *argv[]) {
    if(argc != 2)
        err_n_exit("[ + ] Error, Invalid argument..!");

    str *ip = string("https://api.ipapi.is/?q=");
    ip->AppendString(ip, argv[1]);

    HTTPClientResponse *r = RequestURL(ip->data, NULL, __GET);
    printf("%d\n", r->status_code);
    Map *json = decode_json(r->body->data);

    for(int i = 0; json->idx; i++) {
        if(json->keys[i] == NULL)
            break;
            
        JsonField *field = (JsonField *)json->keys[i];
        field->Key->data[0] = toupper(field->Key->data[0]);
        if(!strcmp(field->STRUCTURE_PATH->data, "/") || !strcmp(field->STRUCTURE_PATH->data, "/location"))
            printf("%s: %s\n", field->Key->data, field->Value->data);
    }

    return 0;
}