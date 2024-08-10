#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/OS/cFile.h>

int main() {
    cFile *c = Openfile("config.json");
    c->Read(c);
    printf("%s\n", c->data);
    return 0;
}