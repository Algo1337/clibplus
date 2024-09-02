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

//
//          Create an instance Socket
//
Socket      *CreateSocket(SocketHostname_T host_t, int type, str *host, int port);

//
//          Listening Concurrent 
//
int         Listen(Socket *s, int concurrent);

//
//          Accpet Question, returning socket info
//
Socket      *Accept(Socket *s);

//
//          
//
void        set_read_max_buffer_sz(int sz);

//
//
//
str         *Read(Socket *s);

//
//
//
int         Write(Socket *s, str *data);

//
//
//
int         Close(Socket *s);

#endif