#pragma once

typedef enum Garbage_T {
    GARBAGE_STRING      = 0x0400001,
    GARBAGE_ARRAY       = 0x0400002,
    GARBAGE_STRUCT      = 0x0400003
} Garbage_T;

typedef struct Object {
    void                *Object;
    Garbage_T           Type;
} Object;

typedef struct Garbage {
    int                 BinID;
    Object              **Objects;
    long                idx;
} Garbage;

typedef struct GarbageCollector {
    Garbage             **Bins;
    long                idx;
    int                 debug;

    // Pointing to static Functions (Lib Functions)
    int                 (*CreateBin)            (struct GarbageCollector *gc);
    int                 (*AddToBin)             (struct GarbageCollector *gc, int BID, Garbage_T type, void *obj);
    int                 (*AddToBinArgs)         (struct GarbageCollector *gc, int BID, Garbage_T type, void **objs);
    void                (*DestroyBin)           (struct GarbageCollector *gc, int BID);

    void                (*DestroyGC)            (struct GarbageCollector *gc);
} GarbageCollector;

GarbageCollector        *start_gc();
static int              start_new_bin(GarbageCollector *gc);
static int              IsValidBin(GarbageCollector *gc, int binID);
static int              add_ptr_to_bin(GarbageCollector *gc, int BID, Garbage_T type, void *obj);
static int              add_ptrs_to_bin(GarbageCollector *gc, int BID, Garbage_T type, void **objs);
static void             DestroyGCBin(GarbageCollector *gc, int BID);
static void             DestroyGC(GarbageCollector *gc);
static int              count_array(void **args);