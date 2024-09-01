#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include <clib/Net/socket.h>

void handle_conn(void *c) {
    Socket *client = (Socket *)c;
    while(1) { 
        str *r = Read(client);

        if(strstr(r->data, "test")) {
            printf("WORKING\n");
            Write(client, string("WORKING\n"));
        }

        free(r);
    }
}

int main() {
    Socket *cnc = CreateSocket(IPv4, SOCK_STREAM, NULL, 69);
    if(cnc == NULL) {
        printf("Error, Unable to make socket\n");
        return -1;
    }

    if(Listen(cnc, 999) < 1) {
        printf("Error, Unable to listen\n");
        return -1;
    }

    while(1) {
        printf("Listening for connections\n");
        Socket *client = Accept(cnc);
        if(client == NULL) {
            printf("Error, Unable to accept!");
            continue;
        }
        
        pthread_t client_thrd;
        pthread_create(&client_thrd, NULL, (void *)handle_conn, (void *)client);
    }

    Close(cnc);
    return 0;
}