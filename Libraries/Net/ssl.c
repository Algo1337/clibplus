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
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

SSL *ssl_handshake(SSL_CTX *ctx, int sockfd) {
    SSL *ssl = SSL_new(ctx);

    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return ssl;
}