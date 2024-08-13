#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <clib/Array/arr.h>
#include <clib/Net/netutils.h>
#include <clib/OS/Utils.h>

Arr *get_interface() {
    str *resp = ExecuteCmd("ifconfig");
    Arr *a = Array(NULL);

    char **lines = resp->Split(resp, "\n");
    int line_count = count_arr(lines);

    if(line_count < 1)
        return a;

    for(int i = 0; i < line_count; i++)
    {
        str *line = string(lines[i]);
        line->Strip(line);
        char **args = line->Split(line, " ");
        int count = count_arr(args);

        if(count > 1 && strstr(args[0], ":")) {
            a->Utils(a, __APPEND, args[0]);
        }

        free(line);
        free(args);
    }
    return a;
}

int main() {
    Arr *a = get_interface();
    for(int i = 0; i < a->idx; i++)
        printf("%s\n", a->arr[i]);
        
    return 0;
}