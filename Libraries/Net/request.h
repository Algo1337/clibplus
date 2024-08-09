#pragma once

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "../c_types.h"
#include "ssl.h"

typedef struct HTTPClient {
    char        *hostname;
    char        *url_route;

    SSL         *ssl;
    SSL_CTX     *ctx;
    int         serverfd;
} HTTPClient;

typedef struct HTTPClientResponse {
    str         *route;
    str         *full_route;
    Map         *headers;
    Map         *query;
    str         *body;
} HTTPClientResponse;

// == [ HTTP Client ] == 

//
//                      Send a WebRequest
//
HTTPClientResponse      *RequestURL(const char *hostname, const char *path);

//
//                      Create a HTTP Socket
//
int                     Create_HTTP_Socket(HTTPClient *http, const char *port);

//
//                      Construct an HTTP Request Syntax to Send
//
void                    __Send_HTTP_Request(HTTPClient *http, const char *hostname, const char *path);

//
//
//
HTTPClientResponse      *__Parse_HTTP_Response(HTTPClient *http);

#endif