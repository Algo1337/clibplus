#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>
#include <clib/global_memory.h>
#include <clib/Net/request.h>

int main() {
    HTTPClientResponse *r = RequestURL("ipwho.is", "/8.8.4.4");
    char **lines = r->body->Utils(r->body, _SPLIT, "\n");
    int c = count_arr(lines);

    str *raw_json = string(lines[10]);
    __ReplaceCharWithStr(raw_json, ',', ",\n");
    __ReplaceCharWithStr(raw_json, '{', "{\n");
    __ReplaceCharWithStr(raw_json, '}', ",\n}");

    printf("%s\n", raw_json->data);

    free(r);
    return 0;
}