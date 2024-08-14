#pragma once

#ifndef MULTI_TYPE_H
#define MULTI_TYPE_H

typedef struct uArray {
    void            **arr;
    long            idx;
    struct uArray * (*Append) (int sz, void *data);
} uArray;

static uArray *CARRAY;

uArray *new_array();
uArray *__appendelement(int sz, void *data);


#endif