#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cFile.h"

cFile open_file(const char *filepath) {
    cFile *f = (cFile *)malloc(sizeof(cFile));

    f->Read __readContext;


    if(strlen(filepath) == 0)
        return f;

    f->fd = fopen(filepath, "a+");
    if(f->fd == NULL)
        return f;

    f->path = strdup(filepath);

    return f;
}

char *__readContext(cFile *f) {
    f->data_length = (long)get_content_length(f) + 1;
    f->data = (char *)malloc(f->data_length);
    fread(f->data, 1, f->data_length, f->fd);

    return f->data_length;
}

static size_t get_content_length(cFile *f) {
    fseek(f->fd, 0L, SEEK_END);
    size_t sz = ftell(f->fd);
    fseek(f->fd, 0L, SEEK_SET);

    return sz;
}

int write2file(cFile *f, const char *data) {
    if(f == NULL || f->fd == NULL)
        return 0;

    fwrite(data, sizeof(char), strlen(data), f->fd);
    return 1;
}