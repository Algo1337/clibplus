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
#include "../Array/arr.h"

typedef enum Request_T {
    __NULL__    =    -1,
    __GET       =    0x324,
    __POST      =    0x724
} Request_T;

typedef enum StatusCode_T {
    __NULL                          = -1,
    CONTINUEE                       = 100,
    SWITCH_PROTOCOL                 = 101,
    PROCESSING                      = 102,
    EARLY_HINT                      = 103,

    OK                              = 200,
    CREATED                         = 201,
    ACCEPTED                        = 202,
    NON_AUTHORIZED_INFO             = 203,
    NO_CONTENT                      = 204,
    RESET_CONTENT                   = 205,
    PARTIAL_CONTENT                 = 206,
    MULTI_STATUS                    = 207,
    ALREADY_REPRORTED               = 208,
    IM_USED                         = 226,

    MULTIPLE_CHOICES                = 300,
    MOVED_PERMANENTLY               = 301,
    FOUND                           = 302,
    SEE_OTHER                       = 303,
    NOT_MODIFIED                    = 304,
    USE_PROXY                       = 305,
    SWITCH_PROXY                    = 306,
    TEMP_REDIRECT                   = 307,
    PERM_REDIRECT                   = 308,

    BAD_REQUEST                     = 400,
    UNAUTHORIZED                    = 401,
    PAYMENT_REQUIRED                = 402,
    FORBIDDEN                       = 403,
    NOT_FOUND                       = 404,
    METHOD_NOT_ALLOWED              = 405,
    NOT_ACCEPTABLE                  = 406,
    PROXY_AUTH_REQUIRED             = 407,
    REQUIRE_TIMEOUT                 = 408,
    CONFLICT                        = 409,
    GONE                            = 410,
    LENGTH_REQUIRED                 = 411,
    PRECONDITION_FAILED             = 412,
    PAYLOAD_TOO_LARGE               = 413,
    URI_TOO_LONG                    = 414,
    UNSUPPORTED_MEDIA_TYPE          = 415,
    RANGE_NOT_SATISFIABLE           = 416,
    EXPECTATION_FAILED              = 417,
    IM_A_TEAPOT                     = 418,
    MISDIRECTED_REQUEST             = 421,
    UNPROCESSABLE_ENTITY            = 422,
    LOCKED                          = 423,
    FAILED_DEPENDENCY               = 424,
    TOO_EARLY                       = 425,
    UPGRADE_REQUIRED                = 426,
    PROCONDITION_REQUIRED           = 428,
    TOO_MANY_REQUEST                = 429,
    REQ_HEADER_FIELD_TOO_LARGE      = 431,
    UNAVAILABLE_FOR_LEGAL_REASON    = 451,
    
    INTERNAL_SERVER_ERR             = 500,
    NOT_IMPLEMENTED                 = 501,
    BAD_GATEWAY                     = 502,
    SERVER_UNAVAILABLE              = 503,
    GATEWAY_TIMEOUT                 = 504,
    HTTP_VERSION_NOT_SUPPORTED      = 505,
    VARIANT_ALSO_NEGOTIATES         = 506,
    INSUFFICIENT_STORAGE            = 507,
    LOOP_DETECTED                   = 508,
    NOT_EXTENDED                    = 510,
    NETWORK_AUTHENTICATION_REQUIRED = 511
} StatusCode_T;

typedef struct HTTPClient {
    char        *hostname;
    char        *url_route;
    Map         *headers;

    SSL         *ssl;
    SSL_CTX     *ctx;
    int         serverfd;
} HTTPClient;

//
// Request Information
//
typedef struct HTTPClientResponse {
    str             *route;         // Page Route
    str             *full_route;    // Full Route Path
    StatusCode_T    status_code;
    Map             *headers;       // Headers
    Map             *query;         // Data
    str             *body;          // Response Body Of the Request
} HTTPClientResponse;

// == [ HTTP Client ] == 

//
//                      Send a WebRequest
//
HTTPClientResponse      *RequestURL(const char *url, Map *headers, Request_T type);

//
//
//
Arr                     *parse_url(const char *data);

//
//                      Create a HTTP Socket
//
int                     Create_HTTP_Socket(HTTPClient *http, const char *port);

//
//                      Construct an HTTP Request Syntax to Send
//
void                    __Send_HTTP_GET_Request(HTTPClient *http);

//
//                      Parse the request's response
//
HTTPClientResponse      *__Parse_HTTP_Response(HTTPClient *http);

//
//
//
HTTPClientResponse      *parse_raw_traffic(const char *data);

#endif