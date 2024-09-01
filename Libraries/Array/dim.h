#pragma once

#ifndef DIM_H
#define DIM_H

//
// DimArrayElement
//

typedef struct DimArrayElement {
    char                **arr;      // Current Array
    long                columns;    // Array Length

    // Append A Value
    struct DimArrayElement *   (*Append) (struct DimArrayElement *e, char *data);
} DimArrayElement;

//
// DimArray
//

typedef struct DimArray {
    DimArrayElement     **arr;
    long                rows;

    // Append A Value In The Array @ Row Provided
    DimArrayElement *   (*Append)   (struct DimArray *a, int row, char *data);

    // Get the element @ idx provided in the array
    char *              (*Get)      (struct DimArray *a, int row, int column);

    // Clean Up The Struct
    void                (*Kill)     (struct DimArray *a);
} DimArray;

// == [ DimArray ] ==

//
//  Used for function chaining
//
extern DimArrayElement *CURRENT_DIM_ARR;

//
//                  Create an Instance Of Map
//
DimArrayElement     *create_dim_arr_element();

//
//                  Returns the entire row array
//
DimArrayElement     *append2arr(DimArray *a, int row, char *data);


//
//                  Get the Element @ IDX provided in the array
//
char                *__getElementAt(DimArray *a, int row, int column);

//
//                  Clean up the Struct
//
void                __KillMap(DimArray *a);

// == [ DimArrayElement ] ==

//
//                  Create an Instance of DimArray
//
DimArray            *create_arr(int dimensions);

//
//                  Append a value to the array in row provided
//
DimArrayElement     *__Append(DimArrayElement *e, char *data);

#endif