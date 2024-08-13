#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include the entire package
#include <clib/c_types.h>
#include <clib/String/str.h>
#include <clib/Array/arr.h>
#include <clib/Net/request.h>

/*
    Basic Web Request
*/
int main(int argc, char *argv[]) {
    HTTPClientResponse *r = RequestURL("api.ipapi.is", argv[1]);
    printf("%s", r->body->data);

    char **lines = r->body->Split(r->body, "\n");
    int line_count = count_arr(lines);
    
    str *new = string(NULL);
    for(int i = 10; i < line_count; i++) {
        printf("[%d]: %s\n", i, lines[i]);
        new->AppendString(new, lines[i]);
        if(i != line_count-1)
            new->AppendString(new, "\n");
    }

    // if(lines == 0) {
    //     Arr *a = Array(NULL);
    //     for(int i = 10; i < line_count; i++)
    //         a->Utils(a, __APPEND, lines[i]);
            
    //     str *new = string(NULL);
    //     new->Join(new, (const char **)a->arr, '\n');
    //     json = decode_json(new->data);
    // } else {
    //     json = decode_oneline_json(lines[10]);
    // }

    Map *json = decode_json(new->data);

    for(int i = 0; json->idx; i++) {
        if(json->keys[i] == NULL)
            break;
            
        JsonField *field = (JsonField *)json->keys[i];
        printf("STRUCTURE: %s | Key: %s | Value: %s\n", 
            field->STRUCTURE_PATH->data, field->Key->data, field->Value->data);
    }

    return 0;
}