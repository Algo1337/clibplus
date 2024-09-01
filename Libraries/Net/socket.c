#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "socket.h"

Socket CreateSocket(SocketHostname_T *host_t, int type, str *host, str *port) {
    Socket *s = (Socket *)malloc(sizeof(Socket));
    s->SockFD = socket(AF_INET, SOCK_STREAM, 0); 
    if (s->SockFD == -1)
        return NULL;

    bzero(&s->SockAddr, sizeof(s->SockAddr)); 
    s->SockAddr.sin_family = AF_INET; 
    /* Check if an IP is provided else use default */
    if(ip == NULL) {
        s->SockAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    } else {
        inet_aton(host->data, &s->SockAddr.sin_addr);
    }
    s->SockAddr.sin_port = htons(port->data); 
   
    if ((bind(s->SockFD, (struct sockaddr *)&s->SockAddr, sizeof(s->SockAddr))) != 0)
        return NULL;
   
    return s;
}

int Listen(Socket *s, int concurrent) {
    if(s == NULL)
        return -1;

    if(s->SockFD == < 1)
        return -1;

    if((listen(s->SockFD, concurrent)) != 0)
        return 0;

    return 1;
}

Socket *Accept(Socket *s) {
    if(s == NULL)
        return -1;

    if(s->SockFD == < 1)
        return -1;

    Socket *client_socket = (Socket *)malloc(sizeof(Socket));

    int len = sizeof(client_socket->SockAddr);
    client_socket->SockFD = accept(sockfd, (SA*)&client_socket->SockAddr, &len);

    return client_socket;
}

str *Read(Socket *s) {
    if(s == NULL)
        return NULL;

    if(s->SockFD == < 1)
        return NULL;

    str *resp = string(NULL);

    char buffer[65500];
    read(s->SockFD, buff, sizeof(buff));
    resp->AppendString(resp, buffer);

    return resp;
}

int Write(Socket *s, str *data) {
    if(s == NULL)
        return -1;

    if(s->SockFD == < 1)
        return -1;

    write(s->SockFD, data->data, strlen(data->data)); 
}

int Close(Socket *s) {
    if(s->SockFD > 0)
        close(s->SockFD);

    if(s->IP != NULL)
        free(ip);

    if(s->Port != NULL)
        free(port);
}