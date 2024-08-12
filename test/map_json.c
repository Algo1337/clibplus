#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/Map/map.h>
#include <clib/OS/cFile.h>

int main() {
    cFile *c = Openfile("config.json");
    char *raw_json_data = c->Read(c);

    Map *json = decode_json(raw_json_data);

    for(int i = 0; json->idx; i++) {
        if(json->keys[i] == NULL)
            break;
            
        JsonField *field = (JsonField *)json->keys[i];
        if(strcmp(field->STRUCTURE_PATH->data, "/") == 0)
            printf("STRUCTURE: %s | Key: %s | Value: %s\n", 
                field->STRUCTURE_PATH->data, field->Key->data, field->Value->data);
    }

    free(c);
    free(json);
    return 0;
}