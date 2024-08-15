#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "request.h"
#include "../c_types.h"

HTTPClientResponse *RequestURL(const char *url) {
    char **hostname_info = parse_url(url);
    const char *hostname = (hostname_info == NULL ? url : hostname_info[0]);

    str *p = string("/");
    p->AppendString(p, hostname_info[1]);
    const char *path = strdup(p->data);
    free(p);

    printf("%s %s\n", hostname, path);
    HTTPClient *http = (HTTPClient *)malloc(sizeof(HTTPClient));
    http->hostname = strdup(hostname);
    http->url_route = strdup(path);

    init_openssl();
    http->ctx = create_context();
    if(http->ctx == NULL)
        http->ctx = create_context_alt();

    int sockfd = Create_HTTP_Socket(http, "443");
    if(sockfd < 0)
        err_n_exit("[ HTTPClient ] Failed to create http request!");

    http->ssl = ssl_handshake(http->ctx, sockfd, hostname);

    __Send_HTTP_Request(http, hostname, path);
    HTTPClientResponse *r = __Parse_HTTP_Response(http);
    r = parse_raw_traffic(r->body->data);

    SSL_shutdown(http->ssl);
    SSL_free(http->ssl);
    close(sockfd);
    SSL_CTX_free(http->ctx);
    cleanup_openssl();

    return r;
}

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

int Create_HTTP_Socket(HTTPClient *http, const char *port) {
    struct addrinfo hints, *res;
    int sockfd;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(http->hostname, port, &hints, &res) != 0)
        return 0;

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
        return 0;

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0)
        return 0;

    freeaddrinfo(res);
    http->serverfd = sockfd;

    return sockfd;
}

void __Send_HTTP_Request(HTTPClient *http, const char *hostname, const char *path) {
    char request[1024];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n"
             "\r\n",
             path, hostname);

    SSL_write(http->ssl, request, strlen(request));
}

HTTPClientResponse *__Parse_HTTP_Response(HTTPClient *http) {
    HTTPClientResponse *r = (HTTPClientResponse *)malloc(sizeof(HTTPClientResponse));
    char buffer[4096];
    int bytes;

    r->body = string(NULL);

    while ((bytes = SSL_read(http->ssl, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = '\0';
        r->body->AppendString(r->body, (const char *)&buffer);
        memset(buffer, '\0', 4096);
    }

    r->full_route = string(http->url_route); // TODO: Parse to get the last element splitting delim: /
    return r;
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

    // Grab status code and http version
    str *version = string(lines[0]);
    char **code_args = version->Split(version, " ");
    version->ReplaceString(version, code_args[0], "");
    
    version = string(NULL);
    int i = 1;
    while(code_args[i] != NULL)
    {
        version->AppendString(version, code_args[i]);
        version->AppendString(version, " ");
        i++;
    }

    r->status_code = atoi(code_args[1]);
    headers->Utils(headers, __ADD_KEY, code_args[0], version->data);
    free(version);
    free(code_args);

    int stop = 0;
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

        line->Strip(line);
        if(strcmp(line->data, "") == 0) {
            stop = 1;
            continue;
        }

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