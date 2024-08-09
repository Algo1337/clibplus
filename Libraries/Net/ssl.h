#pragma once

#ifndef SSL_H
#define SSL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void init_openssl();
void cleanup_openssl();
SSL_CTX *create_context();
SSL *ssl_handshake(SSL_CTX *ctx, int sockfd);

#endif