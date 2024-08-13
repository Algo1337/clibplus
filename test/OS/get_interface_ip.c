#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <clib/String/str.h>
#include <clib/Net/netutils.h>
#include <clib/OS/Utils.h>

str *get_interface_ip(const char *iface) {
    str *resp = ExecuteCmd("ifconfig");

    char **lines = resp->Split(resp, "\n");
    int line_count = count_arr(lines);

    if(line_count < 1)
        return resp;

    for(int i = 0; i < line_count; i++)
    {
        str *line = string(lines[i]);
        str *next = string(lines[i + 1]);
        next->Strip(next);

        char **args = next->Split(next, " ");
        int count = count_arr(args);

        if(count > 1 && strstr(line->data, iface)) {
            str *rep = string(args[1]);
            free(resp);
            free(line);
            free(next);
            free(args);
            free(lines);
            return rep;
        }

        free(line);
        free(args);
    }

    free(resp);
    free(lines);
    return NULL;
}

int main() {
    str *a = get_interface_ip("enp0s3");
    printf("%s\n", a->data);

    return 0;
}