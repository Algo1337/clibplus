#pragma once

#ifndef WEB_H
#define WEB_H

#include "request.h"
#include "../global.h"
#include "../String/str.h"
#include "../Map/map.h"
#include "../OS/cFile.h"

#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "request.h"

typedef struct HTTPServer {
    char                *ip;
    int                 port;
    int                 socket;
    Map                 *routes;
    struct sockaddr_in  address;
    SSL_CTX             *ssl_ctx;
    char                *err_404_filepath;
} HTTPServer;

typedef struct HTTPRequest {
    str                 *route;         // Page Name
    str                 *full_route;    // Full Route Path
    str                 *request_type;  // Receiving GET/POST
    Map                 *headers;       // Headers
    Map                 *queries;       // Queries for POST request
    str                 *body;          // Response Body Of the Request
} HTTPRequest;

typedef Map Headers;

//
//                      Start a Web Server
//
HTTPServer              *StartWebServer(const char *ip, const int port, int auto_search_dir);

//
//                      Add a route to the web server
//
int                     AddRoute(HTTPServer *s, const char *route, void *fn);

//
//
//
int                     Add404Page(HTTPServer *s, const char *path);

//
//                      Listen for connections
//
void                    StartListener(HTTPServer *s);

//
//                      Check if route is valid
//
int                     isRouteValid(HTTPServer *s, char *data);

//
//                      Execute Parser & Check for Routes
//
void                    *ParseAndCheckForRoute(HTTPServer *s, int request_socket);

//
//
//
void thread_req(void **a);

//
//                      Get post queries
//
Map                    *get_post_queries(HTTPServer *s, HTTPRequest *r);

//
//                      Retrieve GET Parameters
// 
int                    retrieve_get_parameter(HTTPServer *s, HTTPRequest *r);

//
//                      Parse the incoming HTTP Server Request
//
HTTPRequest             *ParseHTTPTraffic(const char *data);

//
//                      Send a response to the request client
//
void                    SendResponse(HTTPServer *s, int request_socket,StatusCode_T code, Map *headers, const char *html_file, Map *vars);

//
//
//
void                    SendRawResponse(HTTPServer *s, int request_socket, StatusCode_T code, Map *headers, const char *raww, Map *vars);

//
//                      Close The Server and Clean the HTTPServer struct
//
int                     CloseServer(HTTPServer *s);

//
//  == [ WEB UTILS ] ==
//

//
//
//
str                     *construct_path(str *route, Map *parameters);

//
//
//
str                     *construct_js_var(Map *vars);

//
//
//
str                     *construct_js_input_var(str *route, Map *vars, Map *parameters);
#endif