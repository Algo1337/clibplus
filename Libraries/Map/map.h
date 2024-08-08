#pragma once

#ifndef MAP_H
#define MAP_H

typedef enum MapTools {

} MapTools;

typedef struct Key {
    char    *name;
    char    *value;
} Key;

typedef struct Map {
    Key     **keys;     // Map->Keys[i]->Name
    long    idx;
} Map;

Map *create_map();

#endif