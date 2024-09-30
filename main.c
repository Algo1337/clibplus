#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Libraries/gc.h"
// #include <clib/gc.h>

GarbageCollector *gc = NULL;
int global_var_bin = -1;

char *GLOBAL_VAR_APP_NAME = NULL;
int main(void) {
    gc = start_gc(1);

    // setting a pointer for the example 
    GLOBAL_VAR_APP_NAME = strdup("APP V1.0.0");

    // Create a global variable bin
    // Append global variable to the GLOBAL VARIABLE PATH, This will be free'd when the 
    // entire GarbageCollector is destrusted & free'd
    global_var_bin = gc->CreateBin(gc);
    gc->AddToBin(gc, global_var_bin, GARBAGE_STRING, GLOBAL_VAR_APP_NAME);

    // Create a new bin for the specific current function and append your pointers
    int bin_id = gc->CreateBin(gc);
    char *foo = strdup("bar");
    gc->AddToBin(gc, bin_id, GARBAGE_STRING, foo);


    gc->DestroyBin(gc, bin_id);
    gc->DestroyBin(gc, global_var_bin);
    gc->DestroyGC(gc);
    free(gc);
    return 0;
}