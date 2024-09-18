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
    if(m == NULL || strlen(key) == 0)
        return 0;

    for(int i = 0; i < m->idx; i++) {
        if((Key *)m->keys[i] == NULL)
            break;
            
        if(strcmp((char *)((Key *)m->keys[i])->name, key) == 0)
            return 1;
    }

    return 0;
}

char *encode_json(Map *m) {

}

Map *decode_oneline_json(const char *data) {
    str *raw_json = string(data);
    long ch_count = raw_json->CountChar(raw_json, ',');
    raw_json->ReplaceCharWithStr(raw_json, ',', ",\n");
        
    raw_json->ReplaceCharWithStr(raw_json, '{', "{\n");
    raw_json->ReplaceCharWithStr(raw_json, '}', "\n}");

    Map *json = decode_json(raw_json->data);

    free(raw_json);
    return json;
}

//brb
Map *decode_json(const char *data) {
    Map *json = create_json_map();

    str *rjson = string(data);
    char **lines = rjson->Split(rjson, "\n");
    int line_count = count_arr(lines);

    str *structure_path = string("parent");
    str *structure = string("/");

    if(line_count < 1)
        return NULL;

    for(int i = 0; i < line_count; i++)
    {
        str *line = string(lines[i]);
        line->Strip(line);

        if(strstr(line->data, "}") || !strcmp(line->data, "}")) {
            structure_path->ReplaceString(structure_path, structure->data, "/");
            structure = string("/");
        }

        char **args = (char **)line->Split(line, ":");
        if(count_arr(args) < 2)
            continue;

        Arr *a = Array(args);

        if(a->idx == 2)
        {
            str *key = string(args[0]);
            key->TrimAtIdx(key, 0);
            key->TrimAtIdx(key, strlen(key->data) - 1);
            key->Strip(key);

            str *value = string(args[1]);
            value->Trim(value, ',');
            value->Strip(value);

            // Value Datatype Checking
            if(strcmp(value->data, "{") == 0) {
                structure_path->AppendString(structure_path, "/");
                structure_path->AppendString(structure_path, key->data);
                structure = string("/");
                structure->AppendString(structure, key->data);
                continue;
            } else if (value->data[value->idx - 2] == '{') {
                structure_path->AppendString(structure_path, "/");
                structure_path->AppendString(structure_path, key->data);
                structure = string("/");
                structure->AppendString(structure, key->data);
                continue;
            }
            
            if(strstr(value->data, "\"") > 0) {
                value->TrimAtIdx(value, 0);
                value->TrimAtIdx(value, strlen(value->data) - 1);
            } else if(value->data[0] == '[' && value->data[strlen(value->data) - 1] == ']') {
                value->TrimAtIdx(value, 0);
                value->TrimAtIdx(value, strlen(value->data) - 1);
            }

            __AppendJSONField(json, structure->data, key->data, value->data);
            free(key);
            free(value);
        }
        
        free(a);
        free(args);
        free(line);
    }

    return json;
}