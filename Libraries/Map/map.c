#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "map.h"

Map *create_map() {
    Map *m = (Map *)malloc(sizeof(Map));
    m->idx = 0;

    m->keys = (void **)malloc(sizeof(Key *) * 1);
    memset(m->keys, '\0', sizeof(Key *) * 1);

    m->Utils = __MapUtils;

    return m;
}

void *__MapUtils(Map *m, MapTools mode, ...) {
    int first = 1, sec = 2;
	va_list args;
    va_start(args, sec);

	switch(mode) {
        // Checks
        case __IN_KEYS:         { return (void *)__InKeys(m, get_va_arg_str(args)); }
        case __GET_KEY:         { return (void *)__getKey(m, get_va_arg_str(args)); }
        case __GET_KEY_VALUE:   { return (void *)__getKeyValue(m, get_va_arg_str(args)); }

        // Modifying
        case __ADD_KEY:         { 
            char *k = get_va_arg_str(args);
            char *v = get_va_arg_str(args);
            return (void *)__AppendField(m, k, v); }
	}

    va_end(args);
	return 0;
}

void *__AppendField(Map *m, const char *key, const char *value) {
    if(m == NULL || key == NULL || value == NULL)
        return NULL;
        
    Key *k = (Key *)malloc(sizeof(Key *));
    k->name = strdup(key);
    k->value = strdup(value);
    
    m->keys[m->idx] = k;
    m->idx++;
    m->keys = (void **)realloc(m->keys, sizeof(Key *) * m->idx + 1);
}

Key *__getKey(Map *m, const char *key) {
    if(m == NULL || key == NULL)
        return NULL;

    for(int i = 0; i < m->idx; i++) {
        if(m->keys[i] == NULL)
            break;

        if(strcmp((char *)((Key *)m->keys[i])->name, key) == 0)
            return m->keys[i];
    }

    return NULL;
}

char *__getKeyValue(Map *m, const char *key) {
    if(m == NULL || key == NULL)
        return NULL;

    for(int i = 0; i < m->idx; i++) {
        if(m->keys[i] == NULL)
            break;

        if(strcmp((char *)((Key *)m->keys[i])->name, key) == 0)
            return (char *)((Key *)m->keys[i])->value;
    }

    return NULL;
}

long __InKeys(Map *m, const char *key) {
    if(m == NULL || key == NULL)
        return 0;

    for(int i = 0; i < m->idx; i++)
        if(strcmp((char *)((Key *)m->keys[i])->name, key) == 0)
            return 1;

    return 1;
}

char *encode_json(Map *m) {

}

Map *decode_json(Map *m, const char *data) {

}