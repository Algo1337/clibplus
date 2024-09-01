#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "socket.h"

Socket *CreateSocket(SocketHostname_T host_t, int type, str *host, int port) {
    Socket *s = (Socket *)malloc(sizeof(Socket));
    s->SockFD = socket(AF_INET, SOCK_STREAM, 0); 
    if (s->SockFD == -1)
        return NULL;

    bzero(&s->SockAddr, sizeof(s->SockAddr)); 
    s->SockAddr.sin_family = AF_INET; 
    /* Check if an IP is provided else use default */
    if(host == NULL) {
        s->SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    } else {
        s->IP = host;
        inet_aton(host->data, &s->SockAddr.sin_addr);
    }

    s->SockAddr.sin_port = htons(port); 
    s->Port = port;
   
    if ((bind(s->SockFD, (struct sockaddr *)&s->SockAddr, sizeof(s->SockAddr))) != 0)
        return NULL;
   
    return s;
}

int Listen(Socket *s, int concurrent) {
    if(s == NULL)
        return -1;

    if(s->SockFD < 1)
        return -1;

    if((listen(s->SockFD, concurrent)) != 0)
        return 0;

    return 1;
}

Socket *Accept(Socket *s) {
    if(s == NULL)
        return NULL;

    if(s->SockFD < 1)
        return NULL;

    Socket *client_socket = (Socket *)malloc(sizeof(Socket));

    int len = sizeof(client_socket->SockAddr);
    client_socket->SockFD = accept(s->SockFD, (struct sockaddr *)&client_socket->SockAddr, &len);

    return client_socket;
}

void set_read_max_buffer_sz(int sz) {
    READ_MAX_BUFFER = sz;
}

str *Read(Socket *s) {
    if(s == NULL)
        return NULL;

    if(s->SockFD < 1)
        return NULL;

    str *resp = string(NULL);
    char buffer[1024];
    int bytesRead = 0;
    
    read(s->SockFD, buffer, sizeof(buffer) - 1);
    resp = string(buffer);
    // while((bytesRead = read(s->SockFD, buffer, sizeof(buffer) - 1)) > 0) {
    //     if(resp->idx >= READ_MAX_BUFFER)
    //         break;

    //     resp->AppendString(resp, buffer);
    //     memset(buffer, 0, sizeof(buffer));
    // }

    return resp;
}

int Write(Socket *s, str *data) {
    if(s == NULL)
        return -1;

    if(s->SockFD < 1)
        return -1;

    write(s->SockFD, data->data, strlen(data->data)); 
    return 1;
}

int Close(Socket *s) {
    if(s->SockFD > 0)
        close(s->SockFD);

    if(s->IP != NULL)
        free(s->IP);
}