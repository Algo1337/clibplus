#pragma once

#ifndef MAIN_H
#define MAIN_H

//
// DimArrayElement
//

typedef struct DimArrayElement {
    char                **arr; // [ "", "" ]
    long                columns;

    struct DimArrayElement *   (*Append) (struct DimArrayElement *e, char *data);
} DimArrayElement;

//
// DimArray
//

typedef struct DimArray {
    DimArrayElement     **arr; // [ ["", ""], ["", ""] ]
    long                rows;

    DimArrayElement *   (*Append)   (struct DimArray *a, int row, char *data);
    char *              (*Get)      (struct DimArray *a, int row, int column);
} DimArray;

//
//  Used for function chaining
//
extern DimArrayElement *CURRENT_DIM_ARR;

//
//                  Create an Instance Of Map
//
DimArrayElement     *create_dim_arr_element();

//
//                  Append a value to the array in row provided
//
DimArrayElement     *__Append(DimArrayElement *e, char *data);

//
//                  Returns the entire row array
//
DimArrayElement     *append2arr(DimArray *a, int row, char *data);


DimArray *create_arr(int dimensions);
char *__getElementAt(DimArray *a, int row, int column);
#endif