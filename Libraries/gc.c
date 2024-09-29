#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "gc.h"

GarbageCollector *start_gc(int d) {
    GarbageCollector *gc = (GarbageCollector *)malloc(sizeof(GarbageCollector));

    *gc = (GarbageCollector){
        .Bins               = (Garbage **)malloc(sizeof(Garbage *) * 1),
        .debug              = d,

        .CreateBin          = start_new_bin,
        .AddToBin           = add_ptr_to_bin,
        .AddToBinArgs       = add_ptrs_to_bin,

        .DestroyBin         = DestroyGCBin,
        .DestroyGC          = DestroyGC
    };

    return gc;
}

static int start_new_bin(GarbageCollector *gc) {
    // Ensure the ID isn't already taken
    int bin_id = (rand() % (1000000 - 0 + 1) + 0);

    // 5 Trys before giving up on a new unique ID
    for(int i = 0; i < 5; i++) {
        if(IsValidBin(gc, bin_id) < 0)
            break;

        if(i == 4) {
            printf("[ x ] Error, Something went wrong trying to get a GC Bin ID for a new bin....!\n");
            return -1;
        }
    }

    Garbage *g = (Garbage *)malloc(sizeof(Garbage));
    *g = (Garbage){
        .BinID      = bin_id,
        .Objects    = (Object **)malloc(sizeof(Object *) * 1)
    };

    gc->Bins[gc->idx] = g;
    gc->idx++;
    gc->Bins = (Garbage **)realloc(gc->Bins, sizeof(Garbage *) * (gc->idx + 1));

    return g->BinID;
}

// Returns -1 on fail or The Bin Index Position From The GC Bins Array
static int IsValidBin(GarbageCollector *gc, int binID) {
    for(int i = 0; i < gc->idx; i++) {
        if(!gc->Bins[i])
            break;

        if(gc->Bins[i]->BinID == binID)
            return i;
    }

    return -1;
}

// Returns 0 on fail and 1 on success
static int add_ptr_to_bin(GarbageCollector *gc, int BID, Garbage_T type, void *obj) {
    if(!gc || !BID || !obj)
        return 0;

    for(int bidx = 0; bidx < gc->idx; bidx++) {
        if(gc->Bins[bidx] == NULL)
            break;

        if(!gc->Bins[bidx]->Objects)
            break;

        if(gc->Bins[bidx]->BinID == BID) {
            Object *o = (Object *)malloc(sizeof(Object));
            o->Object = obj;
            o->Type = type;
            gc->Bins[bidx]->Objects[gc->Bins[bidx]->idx] = o;
            gc->Bins[bidx]->idx++;
            gc->Bins[bidx]->Objects = (Object **)realloc(gc->Bins[bidx]->Objects, sizeof(Object) * (gc->Bins[bidx]->idx + 1));
        }
    }

    return 1;
}

static int add_ptrs_to_bin(GarbageCollector *gc, int BID, Garbage_T type, void **objs) {
    if(!gc || !BID || !objs)
        return 0;

    for(int bidx = 0; bidx < gc->idx; bidx++) {
        if(!gc->Bins[bidx])
            break;


        for(int i = 0; i < count_array(objs); i++) {
            Object *new_obj = (Object *)malloc(sizeof(Object));
            new_obj->Object = objs[i];
            new_obj->Type = type;
            gc->Bins[bidx]->Objects[gc->Bins[bidx]->idx] = new_obj;
            gc->Bins[bidx]->idx++;
            gc->Bins[bidx]->Objects = (Object **)realloc(gc->Bins[bidx]->Objects, sizeof(Object *) * (gc->Bins[bidx]->idx + 1));
        }
    }

    return 1;
}

static void DestroyGCBin(GarbageCollector *gc, int BID) {
    for(int i = 0; i < gc->idx; i++) {
        if(!gc->Bins[i]) {
            // Indication of an issue not reaching the last of the array ( Shouldn't get this if everything goes right )
            if(i != (gc->idx - 1) && gc->debug)
                printf("[ x ] Error, Something is wrong....!\n");
            break;
        }

        if(gc->Bins[i]->BinID != BID)
            continue;

        for(int obj_idx = 0; obj_idx < gc->Bins[i]->idx; obj_idx++) {
            if(!gc->Bins[i]->Objects[obj_idx]->Object) {
                if(gc->Bins[i]->idx != (gc->Bins[i]->idx - 1) && gc->debug)
                    printf("[ x ] Error, Something is wrong....!\n");
                break;
            }
            free(gc->Bins[i]->Objects[obj_idx]->Object);
            gc->Bins[i]->Objects[obj_idx]->Object = NULL;
            (void)(gc->debug ? printf("[ + ] Destroyed Obj In Bin: %d @ Pos: %d\n", gc->Bins[i]->BinID, obj_idx) : 0);
        }

        (void)(gc->debug ? printf("[ + ] Destroying Bin: %d\n", gc->Bins[i]->BinID) : 0);
        free(gc->Bins[i]->Objects);
        gc->Bins[i]->Objects = NULL; // remove the dangling pointing address
        free(gc->Bins[i]);
        gc->Bins[i] = NULL; // remove the dangling pointing address
    }
}

static void DestroyGC(GarbageCollector *gc) {
    for(int i = 0; i < gc->idx; i++) {
        if(!gc->Bins[i])
            break;

        if(!gc->Bins[i]->Objects) // Bin Declared and added but never used
            continue;

        for(int bidx = 0; bidx < gc->Bins[i]->idx; bidx++) {
            if(!gc->Bins[i]->Objects[bidx])
                break;

            if(gc->Bins[i]->Objects[bidx]->Object) {
                free(gc->Bins[i]->Objects[bidx]->Object);
                gc->Bins[i]->Objects[bidx]->Object = NULL;
            }
        }

        free(gc->Bins[i]);
        gc->Bins[i] = NULL;
    }
}

static int count_array(void **args) {
    int i = 0;
    while(args[i] != NULL)
        i++;

    return i;
}