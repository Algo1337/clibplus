#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Utils.h"

str *ExecuteCmd(const char *cmd) {
    str *s = string(NULL);
    char buffer[1024];
    if(!strlen(cmd))
        return (char *)"";

    FILE *resp = popen(cmd, "r");
    if(!resp)
        return (char *)"";

    while(fgets(buffer, sizeof(buffer), resp) != NULL) {
        s->AppendString(s, buffer);
    }

    fclose(resp);

    return s;
}