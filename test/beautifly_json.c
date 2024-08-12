#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/global_memory.h>
#include <clib/Array/arr.h>
#include <clib/String/str.h>
#include <clib/Map/map.h>
#include <clib/OS/cFile.h>
#include <clib/Net/request.h>

void make_json_pretty(str *s) {
    str *new_string = string("-");

    int depths = 0, j = 0;
    for(int i = 0; i < strlen(s->data); i++) {
        if(s->data[i] == '{') {
            depths++;
            printf("{\n");
            j = 0;
            while(j < depths) { 
                printf("\t"); 
                j++;
            }
            continue;
        }

        if(s->data[i] == '}') {
            printf("\n");
            depths--;
            j = 0;
            while(j < depths) { printf("\t"); j++; }
            printf("}");
            continue;
        }

        if(s->data[i] == ',' && (s->data[i + 1] == '"' || s->data[i - 1] == '"')) {
            j = 0;
            printf(",\n");
            while(j < depths) { printf("\t"); j++; }
            continue;
        }

        printf("%c", s->data[i]);
    }
}

int main() {
    cFile *c = Openfile("config.json");
    char *raw_json_data = c->Read(c);

    str *raw_json = string(raw_json_data);
    make_json_pretty(raw_json);

    free(c);
    free(raw_json);
    return 0;
}