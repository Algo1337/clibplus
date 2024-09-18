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

HTTPClientResponse *RequestURL(const char *url, Map *headers, Request_T type) {
    Arr *hostname_info = parse_url(url);
    const char *hostname = hostname_info->arr[0];
    const char *path = hostname_info->arr[1];

    HTTPClient *http = (HTTPClient *)malloc(sizeof(HTTPClient));
    http->hostname = strdup(hostname);
    http->url_route = strdup(path);
    http->headers = headers;

    const char *port = (strstr(url, "https://") ? "443" : "80");
    http->serverfd = Create_HTTP_Socket(http, port);

    HTTPClientResponse *r;
    if(strstr(url, "https://")) {
        init_openssl();
        http->ctx = create_ssl_context();

        http->ssl = SSL_new(http->ctx);
        SSL_set_fd(http->ssl, http->serverfd);

        if (SSL_connect(http->ssl) <= 0)
            return NULL;
            
        switch(type) {
            case __GET: { 
                __Send_HTTP_GET_Request(http, 1); 
                r = __Parse_HTTP_Response(http, 1);
                r = parse_raw_traffic(r->body->data);
                break;
            }
            // case __POST: { }
            default: {
                printf("ERROR");
                return NULL;
            }
        }
    } else {
        __Send_HTTP_GET_Request(http, 0); 
        r = __Parse_HTTP_Response(http, 0);
        r = parse_raw_traffic(r->body->data);
    }

    if (strstr(url, "https://")) {
        SSL_free(http->ssl);
        SSL_CTX_free(http->ctx);
        cleanup_openssl();
    }

    close(http->serverfd);
    return r;
}

Arr *parse_url(const char *data) {
    str *hostname = string(data);
    str *path = string("/");
    Arr *args;

    if(hostname->StartsWith(hostname, "https://"))
        hostname->ReplaceString(hostname, "https://", "");
    
    if(hostname->StartsWith(hostname, "http://")) 
        hostname->ReplaceString(hostname, "http://", "");
    
    if(strstr(hostname->data, "www."))
        hostname->ReplaceString(hostname, "www.", "");

    str *url = string(hostname->data);
    if(hostname->EndsWith(hostname, "/")) {
        hostname->ReplaceString(hostname, "/", "");
    } else if(strstr(hostname->data, "/") != NULL) {
        int start = hostname->FindCharAt(hostname, '/', 1);
        hostname->RemoveSubstr(hostname, start, hostname->idx - 1);
    }
    
    if(url->CountChar(url, '/') > 0) {
        args = Array(url->Split(url, "/"));
        
        for(int i = 1; i < args->idx; i++) {
            path->AppendString(path, args->arr[i]);
            if(i != args->idx - 1)
                path->AppendString(path, "/");
        }

        args = Array(NULL);
        args->Utils(args, __APPEND, hostname->data);
        args->Utils(args, __APPEND, path->data);


        free(hostname);
        free(path);
        free(url);
        return args;
    }

    if(hostname->StartsWith(hostname, "https://"))
        hostname->ReplaceString(hostname, "https://", "");
    
    if(hostname->StartsWith(hostname, "http://")) 
        hostname->ReplaceString(hostname, "http://", "");
    
    if(strstr(hostname->data, "www."))
        hostname->ReplaceString(hostname, "www.", "");

    if(hostname->EndsWith(hostname, "/"))
        hostname->ReplaceString(hostname, "/", "");
    
    
    args = Array(NULL);
    args->Utils(args, __APPEND, hostname->data);
    args->Utils(args, __APPEND, "/");

    free(hostname);
    free(path);
    free(url);
    return args;
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

void __Send_HTTP_GET_Request(HTTPClient *http, int ssl) {
    char *start_of_req[] = {"GET ", http->url_route, " HTTP/1.1\r\n", "Host: ", http->hostname, "\r\n"};
    str *req_data = string(NULL);

    for(int i = 0; i < 6; i++)
        req_data->AppendString(req_data, start_of_req[i]);


    if(http->headers != NULL) {
        for(int i = 0; i < http->headers->idx; i++) {
            req_data->AppendString(req_data, (char *)((Key *)http->headers->keys[i])->name);
            req_data->AppendString(req_data, ": ");
            req_data->AppendString(req_data, (char *)((Key *)http->headers->keys[i])->value);
            req_data->AppendString(req_data, "\r\n");
        }
    }

    req_data->AppendString(req_data, "Connection: close\r\n\r\n");

    if(ssl == 1)
        SSL_write(http->ssl, req_data->data, strlen(req_data->data));
    else
        write(http->serverfd, req_data->data, strlen(req_data->data));

    free(req_data);
}

HTTPClientResponse *__Parse_HTTP_Response(HTTPClient *http, int ssl) {
    HTTPClientResponse *r = (HTTPClientResponse *)malloc(sizeof(HTTPClientResponse));
    char buffer[4096] = {0};
    int bytes;

    r->body = string(NULL);

    if(ssl == 1) {
        while ((bytes = SSL_read(http->ssl, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes] = '\0';
            r->body->AppendString(r->body, (const char *)&buffer);
            memset(buffer, '\0', 4096);
        }
    } else {
        memset(buffer, '\0', 4096);
        bytes = read(http->serverfd, buffer, 4095);
        r->body->AppendString(r->body, (const char *)&buffer);
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