#pragma once

#ifndef SOCKET_H
#define SOCKET_H

#include <clib/String/str.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef enum SocketHostname_T {
    IPv4    = 8429930,
    IPv6    = 8429931
} SocketHostname_T;

typedef struct Socket {
    str                     *IP;
    int                     Port;
    int                     SockFD;
    struct sockaddr_in      SockAddr;
} Socket;

static int READ_MAX_BUFFER = 1024;

Socket *CreateSocket(SocketHostname_T host_t, int type, str *host, int port);
int Listen(Socket *s, int concurrent);
Socket *Accept(Socket *s);
void set_read_max_buffer_sz(int sz);
str *Read(Socket *s);
int Write(Socket *s, str *data);
int Close(Socket *s);

#endif