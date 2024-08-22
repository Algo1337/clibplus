#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <clib/Map/map.h>
#include <clib/Net/web.h>
#include <clib/Net/request.h>

void *index_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/\x1b[0m ] Page Visited\n");
    printf("Body: %s\n", r->body->data);

    if(!strcmp(r->request_type->data, "POST"))
        if(r->queries->Utils(r->queries, __IN_KEYS, "NIGGER"))
            if(r->queries->Utils(r->queries, __IN_KEYS, "name_input"))
                printf("Name Submitted: %s\n", (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "name_input"));

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    SendResponse(s, request_socket, OK, headers, "pages/index.html", NULL);
}

void *doc_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/doc\x1b[0m ] Page Visited\n");

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");

    SendResponse(s, request_socket, OK, headers, "pages/doc.html", NULL);
}

void *source_code_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("[ \x1b[32m/source_code\x1b[0m ] Page Visited\n");

    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-Type", "text/html; charset=UTF-8");
    headers->Utils(headers, __ADD_KEY, "Connection", "close");
    
    SendResponse(s, request_socket, OK, headers, "pages/source_code.html", NULL);
}

int main() {
    HTTPServer *s = StartWebServer(NULL, 80, 0);
    AddRoute(s, "/index", index_page);
    AddRoute(s, "/doc", doc_page);
    AddRoute(s, "/source_code", source_code_page);

    StartListener(s);
    return 0;
}
