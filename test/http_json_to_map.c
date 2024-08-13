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

    str *ip = string("/?q=");
    ip->AppendString(ip, argv[1]);

    str *gg = string(argv[1]);
    int t = validate_ipv4(gg);
    if(!t)
        err_n_exit("[ + ] Error, Invalid IP Provided...!");

    HTTPClientResponse *r = RequestURL("api.ipapi.is", ip->data);
    char **lines = r->body->Split(r->body, "\n");
    int line_count = count_arr(lines);
    
    str *new = string(NULL);
    Map *json;
    if(line_count > 1) {
        for(int i = 10; i < line_count; i++) {
            new->AppendString(new, lines[i]);
            if(i != line_count-1)
                new->AppendString(new, "\n");
        }
        json = decode_json(new->data);
    } else {
        json = decode_oneline_json(lines[10]);
    }

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