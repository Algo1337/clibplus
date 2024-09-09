#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cFile.h"

cFile *Openfile(const char *filepath) {
    cFile *f = (cFile *)malloc(sizeof(cFile));

    f->Read = __readContext;
    f->Write = __write2file;


    if(strlen(filepath) == 0)
        return f;

    f->fd = fopen(filepath, "a+");
    if(f->fd == NULL)
        return f;

    f->path = strdup(filepath);

    return f;
}

cFile *CreateFile(const str *filename, const str *output) {
    FILE *fd = fopen(filename->data, "w");
    if(!fd)
        return NULL;

    fwrite(output->data, sizeof(char), strlen(output->data), fd);
    fclose(fd);

    return Openfile(filename->data);
}

char *__readContext(cFile *f) {
    f->data_length = (long)__get_content_length(f) + 1;
    f->data = (char *)malloc(f->data_length);
    memset(f->data, '\0', f->data_length);

    fread(f->data, 1, f->data_length, f->fd);
    return f->data;
}

static size_t __get_content_length(cFile *f) {
    fseek(f->fd, 0L, SEEK_END);
    size_t sz = ftell(f->fd);
    fseek(f->fd, 0L, SEEK_SET);

    return sz;
}

int __write2file(cFile *f, const char *data) {
    if(f == NULL || f->fd == NULL)
        return 0;

    fwrite(data, sizeof(char), strlen(data), f->fd);
    return 1;
}

void __Closefile(cFile *f) {
    if(f->path == NULL)
        f->path = NULL;

    fclose(f->fd);
}