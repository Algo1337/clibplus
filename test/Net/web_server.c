#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/Map/map.h>
#include <clib/Net/web.h>
#include <clib/Net/request.h>

void *index_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    printf("PATH: %s\n", r->route->data);
    
    Map *headers = create_map();
    headers->Utils(headers, __ADD_KEY, "Content-type", "application/json");
    headers->Utils(headers, __ADD_KEY, "DeZ_NuTz", "GAYYYY");

    SendResponse(s, request_socket, OK, headers, "test.html", NULL);
}

int main() {
    HTTPServer *s = StartWebServer(NULL, 80, 0);
    AddRoute(s, "/", index_page);

    StartListener(s);
    return 0;
}