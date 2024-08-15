#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Include the entire package
#include <clib/global.h>
#include <clib/String/str.h>
#include <clib/Array/arr.h>
#include <clib/Map/map.h>
#include <clib/Net/request.h>
#include <clib/Net/netutils.h>
#include <clib/OS/cFile.h>


char **parse_url(const char *data) {
    str *s = string(data);
    printf("%s\n", s->data);

    if(strstr(s->data, "https://") != NULL) {
        s->ReplaceString(s, "https://", "");
    } else if(strstr(s->data, "http://") != NULL) {
        s->ReplaceString(s, "http://", "");
    } else if(strstr(s->data, "www.") != NULL) {
        s->ReplaceString(s, "www.", "");
    }

    if(strstr(s->data, "/") != NULL) {
        char **args = s->Split(s, "/");

        free(s);
        return args;
    }

    return NULL;
}

HTTPClientResponse *parse_raw_traffic(const char *data) {
    str *raw_data = string(data);
    char **lines = raw_data->Split(raw_data, "\n");
    int line_count = count_arr(lines);

    Map *headers = create_map();
    str *body = string(NULL);
    HTTPClientResponse *r = (HTTPClientResponse *)malloc(sizeof(HTTPClientResponse));

    if(line_count == 0)
        return r;

    int stop = 0;
    // skipping http version && status code
    for(int i = 1; i < line_count; i++)
    {
        if(!strcmp(lines[i], "") || !strcmp(lines[i], "2be")) {
            stop = 1;
            continue;
        } else if(!strcmp(lines[i], "0")) {
            break;
        }

        str *line = string(lines[i]);
        char **args = line->Split(line, ":");
        int arg_count = count_arr(args);

        if(arg_count >= 2 && !stop) {
            str *value = string(lines[i]);
            value->ReplaceString(value, args[0], "");
            
            headers->Utils(headers, __ADD_KEY, args[0], value->data);
        } else {
            body->AppendString(body, lines[i]);
        }

        free(line);
        free(args);
    }

    free(raw_data);
    free(lines);
    r->body = body;
    r->headers = headers;
    return r;
}

int main(int argc, char *argv[]) {
    char **url = parse_url(argv[1]);

    HTTPClientResponse *r;
    if(url == NULL) {
        r = RequestURL(argv[1], "/");
    } else {
        r = RequestURL(url[0], url[1]);
    }
    r = parse_raw_traffic(r->body->data);

    for(int i = 0; r->headers->idx; i++) {
        if(r->headers->keys[i] == NULL)
            break;
            
        Key *field = (Key *)r->headers->keys[i];
        printf("[ HEADER ]: %s => %s\n", field->name, field->value);
    }

    printf("[ BODY ]: %s\n", r->body->data);
    return 0;
}