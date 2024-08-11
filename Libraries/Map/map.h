#pragma once

#ifndef MAP_H
#define MAP_H

#include "../global.h"
#include "../String/str.h"
#include "../Array/arr.h"

// Map Tools
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

// DataTypes from JSON
typedef enum JsonData_T {
    ___NONE_T   = -1000001, // NONE
    ___STRING   = -1000002, // String
    ___INT      = -1000003, // Int
    ___FLOAT    = -1000004, // Float
    ___ARRAY    = -1000005, // Array
    ___JSON     = -1000006  // Json
} JsonData_T;

// JsonField Structure Containing JSON Field Info
typedef struct JsonField {
    str        *STRUCTURE_PATH; // "parent/stresser_plan" as default/start of a JSON ( parent/stresser_plan )
    str        *STRUCTURE;      // "stresser_plan"
    str        *Key;            // attack_time
    str        *Value;          // 1200
    JsonData_T *type;
} JsonField;

// Key Structure Containing Information of the key
typedef struct Key {
    char        *name;      // Key Name
    char        *value;     // Key Value
} Key;

// Map Structure for Keys
typedef struct Map {
    void        **keys;     // Keys
    long        idx;        // Key Length

    //      Map Utilities
    void *  (*Utils) (struct Map *m, MapTools mode, ...);
} Map;

//
//      Create an instance of Map
//
Map     *create_map();

Map *create_json_map();

//
//      Map Utilities
//
void    *__MapUtils(Map *m, MapTools mode, ...);

//
//      Append a new key
//
void    *__AppendField(Map *m, const char *key, const char *value);

void *__AppendJSONField(Map *m, const char *structure, const char *key, const char *value);

//
//      Get an exiting Key instance with the key provided
//
Key     *__getKey(Map *m, const char *key);

//
//      Get a value to a key
//
char    *__getKeyValue(Map *m, const char *key);

//
//      Check if a key exists in the map
//
long    __InKeys(Map *m, const char *key);

//
//      Convert Map to JSON String
//
char    *encode_json(Map *m);

//
//      Convert a raw json string to a Map
//
Map     *decode_json(const char *data);

#endif