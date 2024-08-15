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

//
//      Initial OpenSSL
//
void    init_openssl();

//
//      Create OpenSSL
//
SSL_CTX *create_context();

//
SSL_CTX *create_context_alt();

//
//      SSL Handshake
//
SSL     *ssl_handshake(SSL_CTX *ctx, int sockfd, const char *hostname);

//
//      Clean Up the OpenSSL Structure
//
void    cleanup_openssl();

#endif