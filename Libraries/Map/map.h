#pragma once

#ifndef MAP_H
#define MAP_H

#include "../global.h"

typedef enum MapTools {
    ___NONE,

    // Checking Tools
    __IN_KEYS,

    // Modifying Tools
    __ADD_KEY,
    __REMOVE_KEY,
    __GET_KEY
} MapTools;

typedef struct Key {
    char    *name;
    char    *value;
} Key;

typedef struct Map {
    Key     **keys;     // Map->Keys[i]->Name
    long    idx;
    void *  (*Utils) (struct Map *m, MapTools mode, ...);
} Map;

Map *create_map();
void *__MapUtils(Map *m, MapTools mode, ...);
void *__AppendField(Map *m, const char *key, const char *value);
Key *__getKey(Map *m, const char *key);
long __InKeys(Map *m, const char *key);
char *encode_json(const char *data);
char *decode_json(const char *data);

#endif