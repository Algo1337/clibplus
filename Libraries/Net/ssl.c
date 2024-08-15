#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

void init_openssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl() {
    EVP_cleanup();
}

SSL_CTX *create_context() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_client_method();

    ctx = SSL_CTX_new(method);
    if(!ctx)
        return NULL;

    return ctx;
}

SSL_CTX *create_context_alt() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_client_method();  // Use the latest method supporting TLS 1.2 and 1.3

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("ERROR");
        return NULL;
    }

    // Optional: Disable older, insecure versions of SSL/TLS
    SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);

    return ctx;
}

SSL *ssl_handshake(SSL_CTX *ctx, int sockfd, const char *hostname) {
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);

    // Set the hostname for SNI (Server Name Indication)
    SSL_set_tlsext_host_name(ssl, hostname);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return ssl;
}