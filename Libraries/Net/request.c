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

HTTPClientResponse *RequestURL(const char *hostname, const char *path) {
    HTTPClient *http = (HTTPClient *)malloc(sizeof(HTTPClient));
    http->hostname = strdup(hostname);
    http->url_route = strdup(path);

    init_openssl();
    http->ctx = create_context();

    int sockfd = Create_HTTP_Socket(http, "443");
    if(sockfd < 0)
        err_n_exit("[ HTTPClient ] Failed to create http request!");

    http->ssl = ssl_handshake(http->ctx, sockfd);

    __Send_HTTP_Request(http, hostname, path);
    HTTPClientResponse *r = __Parse_HTTP_Response(http);

    SSL_shutdown(http->ssl);
    SSL_free(http->ssl);
    close(sockfd);
    SSL_CTX_free(http->ctx);
    cleanup_openssl();

    return r;
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
