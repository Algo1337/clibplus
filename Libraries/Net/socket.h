#pragma once

#ifndef SOCKET_H
#define SOCKET_H

#include <clib/String/str.h>

typedef enum SocketHostname_T {
    IPv4    = 8429930,
    IPv6    = 8429931
} SocketHostname_T;

typedef struct Socket {
    str                     *IP;
    int                     *Port;
    int                     SockFD;
    struct sockaddr_in      SockAddr;
} Socket;

Socket CreateSocket(SocketHostname_T *host_t, int type, str *host, str *port);
int Listen(Socket *s, int concurrent);
Socket *Accept(Socket *s);
str *Read(Socket *s);
int Write(Socket *s, str *data);
int Close(Socket *s);

#endif