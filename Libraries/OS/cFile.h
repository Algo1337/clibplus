#pragma once

#ifndef CFILE_H
#define CFILE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cFile {
    char    *path;
    FILE    *fd;
    char    *data;
    long    data_length;

    char *  (*Read)     (struct cFile *f);
    int     (*Write)    (struct cFile *f, const char *data);
    void *  (*Close)    (struct cFile *f);
} cFile;

//
//      Open a file
//
cFile   *Openfile(const char *filepath);

//
//      Get file content
//
char    *__readContext(cFile *f);

//
//      Get content length
//
static size_t  __get_content_length(cFile *f);

//
//      Write To File
//
int     __write2file(cFile *f, const char *data);

//
//      Clean up the structure
//
void    __Closefile(cFile *f);

#endif