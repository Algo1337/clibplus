#pragma once

#ifndef CFILE_H
#define CFILE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>

typedef struct cFile {
    char            *path;
    FILE            *fd;
    char            *data;
    long            data_length;
    
    struct cFile    (*Createfile)   (const str *filename, const str *output);
    char *          (*Read)         (struct cFile *f);                      // Get file content
    int             (*Write)        (struct cFile *f, const char *data);    // Write To File
    void *          (*Close)        (struct cFile *f);
} cFile;

//
//      Open a file
//
cFile   *Openfile(const char *filepath);

//
//      Create a new file and return a new instance of cFile
//
cFile   *CreateFile(const str *filename, const str *output);

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