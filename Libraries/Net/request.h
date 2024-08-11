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

#include "ssl.h"
#include "../global.h"
#include "../c_types.h"

typedef struct HTTPClient {
    char        *hostname;
    char        *url_route;

    SSL         *ssl;
    SSL_CTX     *ctx;
    int         serverfd;
} HTTPClient;

//
// Request Information
//
typedef struct HTTPClientResponse {
    str         *route;         // Page Route
    str         *full_route;    // Full Route Path
    Map         *headers;       // Headers
    Map         *query;         // Data
    str         *body;          // Response Body Of the Request
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
//                      Parse the request's response
//
HTTPClientResponse      *__Parse_HTTP_Response(HTTPClient *http);

#endif