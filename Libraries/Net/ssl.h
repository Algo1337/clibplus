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
void    cleanup_openssl();

//
SSL_CTX *create_ssl_context();

//
//      SSL Handshake
//
void verify_certificate(SSL *ssl);

#endif