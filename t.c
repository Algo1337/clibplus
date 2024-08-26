#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/Net/web.h>
#include <clib/String/str.h>
#include <clib/OS/cFile.h>

int main() {
    cFile *g = Openfile("pages/index.html");
    g->Read(g);

    str *file = string(g->data);
    char **lines = file->Split(file, "\n");
    for(int i = 0; i < count_arr(lines); i++) {
        str *line = string(lines[i]);

        if(strstr(line->data, "include_css(") || strstr(line->data, "include_html(")) {
            printf("HERE\n");
            char *test = parse_include_line(line, i);
            printf("%s\n", test);
        }
    }
}