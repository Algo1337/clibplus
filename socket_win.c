#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#include "socket.h"

Socket *CreateSocket(SocketHostname_T host_t, int type, str *host, int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return NULL;

    Socket *s = (Socket *)malloc(sizeof(Socket));
    s->SockFD = socket(AF_INET, type, 0);
    if (s->SockFD == INVALID_SOCKET) {
        return NULL;

    memset(&s->SockAddr, 0, sizeof(s->SockAddr));
    s->SockAddr.sin_family = AF_INET;
    s->SockAddr.sin_port = htons(port);
    s->Port = port;

    if (host == NULL) {
        s->SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
        if (host_t == IP_ADDRESS) {
            inet_pton(AF_INET, host->data, &s->SockAddr.sin_addr);
        } else if (host_t == HOSTNAME) {
            struct addrinfo *result = NULL, hints;
            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_INET; 
            hints.ai_socktype = type;

            if (getaddrinfo(host->data, NULL, &hints, &result) != 0) {
                return NULL;
            }

            s->SockAddr.sin_addr = ((struct sockaddr_in *)(result->ai_addr))->sin_addr;
            freeaddrinfo(result);
        }
        s->IP = host;
    }

    return s;
}

void cleanup_socket(Socket *s) {
    if (s != NULL) {
        closesocket(s->SockFD);  // Close the socket
        free(s);
        WSACleanup();  // Cleanup Winsock
    }
}