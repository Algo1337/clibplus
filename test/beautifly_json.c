#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/global_memory.h>
#include <clib/Array/arr.h>
#include <clib/String/str.h>
#include <clib/Map/map.h>
#include <clib/OS/cFile.h>
#include <clib/Net/request.h>

int main() {
    cFile *c = Openfile("config.json");
    char *raw_json_data = c->Read(c);

    Map *json = decode_oneline_json(raw_json_data);

    for(int i = 0; json->idx; i++) {
        if(json->keys[i] == NULL)
            break;
            
        JsonField *field = (JsonField *)json->keys[i];
        printf("STRUCTURE: %s | Key: %s | Value: %s\n", 
            field->STRUCTURE_PATH->data, field->Key->data, field->Value->data);
    }
    return 0;
}