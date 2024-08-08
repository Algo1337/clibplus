#pragma once

#ifndef MAP_H
#define MAP_H

#include "../global.h"

typedef enum MapTools {
    ___NONE,

    // Checking Tools
    __IN_KEYS,

    // SET Tools
    __ADD_KEY,
    __REMOVE_KEY,

    // GET Tools
    __GET_KEY,
    __GET_KEY_VALUE
} MapTools;

/*

{
    "username": "",
    "password": "",
    "stesser_plan": {
        "attack_time": "1200"
    },
    "rank": ""
}

*/

typedef struct JsonField {
    char    *STRUCTURE_PATH; // "parent/stresser_plan" as default/start of a JSON ( parent/stresser_plan )
    char    *STRUCTURE;      // "stresser_plan"
    char    *Key;            // attack_time
    char    *Value;          // 1200
} JsonField;

typedef struct Key {
    char    *name;
    char    *value;
} Key;

typedef struct Map {
    void     **keys;     // Map->Keys[i]->Name
    long    idx;
    void *  (*Utils) (struct Map *m, MapTools mode, ...);
} Map;

Map *create_map();
void *__MapUtils(Map *m, MapTools mode, ...);
void *__AppendField(Map *m, const char *key, const char *value);
Key *__getKey(Map *m, const char *key);
char *__getKeyValue(Map *m, const char *key);
long __InKeys(Map *m, const char *key);
char *encode_json(const char *data);
char *decode_json(const char *data);

#endif