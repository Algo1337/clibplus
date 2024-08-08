#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "map.h"

Map *create_map() {
    Map *m = (Map *)malloc(sizeof(Map));
    m->keys = (Key **)malloc(sizeof(Key *) * 1);
    memset(m->keys, '\0', sizeof(Key *) * 1);
    return m;
}

void *__MapUtils(Map *m, MapTools mode, ...) {

}

char *encode_json() {

}

char *decode_json() {

}