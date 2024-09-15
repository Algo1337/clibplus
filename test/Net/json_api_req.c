#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Include the entire package
#include <clib/String/str.h>
#include <clib/Map/map.h>
#include <clib/Net/request.h>

/*
*
*
*   == [ Web Request With One-line JSON Detection ] ==
*
*/
int main(int argc, char *argv[]) {
    HTTPClientResponse *r = RequestURL("ipwho.is/70.70.70.72", NULL, __GET);

    // Check Status Code && Display Headers If Valid Or Print Status Code Error
    if(r->status_code == OK) {
        for(int i = 0; i < r->headers->idx - 1; i++) {
            if(r->headers->keys[i] == NULL)
                break;
                
            Key *field = (Key *)r->headers->keys[i];
            if(field->name == NULL || field->value == NULL)
                break;
            
            printf("[ HEADER/%d ]: %s => %s\n", i, field->name, field->value);
        }

        // Oneline Raw JSON Detection Or Print Body 
        if(r->body->CountChar(r->body, '\n') == 0) {
            Map *json = decode_oneline_json(r->body->data);

            for(int i = 0; json->idx; i++) {
                if(json->keys[i] == NULL)
                    break;
                    
                JsonField *field = (JsonField *)json->keys[i];
                field->Key->data[0] = toupper(field->Key->data[0]);
                if(!strcmp(field->STRUCTURE_PATH->data, "/") || !strcmp(field->STRUCTURE_PATH->data, "/location"))
                    printf("%s: %s\n", field->Key->data, field->Value->data);
            }
        } else {
            printf("%s\n", r->body->data);
        }
    } else {
        printf("[ X ] Error, Status Code: %d\n", r->status_code);
    }
    return 0;
}