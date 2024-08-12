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

Map *create_json_map() {
    Map *m = (Map *)malloc(sizeof(Map));
    m->idx = 0;

    m->keys = (void **)malloc(sizeof(JsonField *) * 1);
    memset(m->keys, '\0', sizeof(JsonField *) * 1);

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

void *__AppendJSONField(Map *m, const char *structure, const char *key, const char *value) {
    if(m == NULL || key == NULL || value == NULL)
        return NULL;
        
    JsonField *field = (JsonField *)malloc(sizeof(JsonField));
    field->STRUCTURE_PATH = string(structure);
    field->Key = string(key);
    field->Value = string(value);
    
    m->keys[m->idx] = field;
    m->idx++;
    m->keys = (void **)realloc(m->keys, sizeof(JsonField *) * m->idx + 1);
}

void *__AppendField(Map *m, const char *key, const char *value) {
    if(m == NULL || key == NULL || value == NULL)
        return NULL;
        
    Key *k = (Key *)malloc(sizeof(Key));
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


//brb
Map *decode_json(const char *data) {
    Map *json = create_json_map();
    str *raw_json = string(data);

    char **lines = (char **)raw_json->SplitStringWithChar(raw_json, '\n');
    int line_count = count_arr(lines);

    char *start[] = {"parent", NULL};
    Arr *structure_path = Array(start);
    str *full_path = string("/");

    for(int i = 0; i < line_count; i++) {
        str *line = string(lines[i]);
        line->Strip(line);

        if(strstr(line->data, "}")) {
            structure_path->Utils(structure_path, __REMOVE_BY_IDX, structure_path->idx - 1);
            full_path = string("/");
        }

        char **args = (char **)line->SplitStringWithChar(line, ':');
        Arr *a = Array(args);

        // Key/Value Found
        if(a->idx == 2) {
            str *key = string(args[0]);
            key->TrimAtIdx(key, 0);
            key->TrimAtIdx(key, strlen(key->data) - 1);
            key->Strip(key);

            str *value = string(args[1]);
            value->Trim(value, ',');
            value->Strip(value);

            // Value Datatype Checking
            if(strcmp(value->data, "{") == 0) {
                structure_path->Utils(structure_path, __APPEND, key->data);
                full_path->data = __arr2str(structure_path, '/');
                continue;
            } else if (value->data[value->idx - 2] == '{') {
                structure_path->Utils(structure_path, __APPEND, key->data);
                full_path->data = __arr2str(structure_path, '/');
                continue;
            }
            
            if(strstr(value->data, "\"") > 0) {
                value->TrimAtIdx(value, 0);
                value->TrimAtIdx(value, strlen(value->data) - 1);
            } else if(value->data[0] == '[' && value->data[strlen(value->data) - 1] == ']') {
                value->TrimAtIdx(value, 0);
                value->TrimAtIdx(value, strlen(value->data) - 1);
            }

            __AppendJSONField(json, full_path->data, key->data, value->data);
            free(key);
            free(value);
        }
        free(a);
        free(args);
        free(line);
    }

    return json;
}