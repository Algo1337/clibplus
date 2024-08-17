#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 443
#define CERT_FILE "server.crt"
#define KEY_FILE "server.key"
#define BUFFER_SIZE 1024

// Initialize OpenSSL and create a new SSL context
SSL_CTX* init_ssl_context(void) {
    SSL_CTX *ctx;

    SSL_load_error_strings();   
    OpenSSL_add_ssl_algorithms();

    ctx = SSL_CTX_new(TLS_server_method());
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    // Set the certificate and key
    if (SSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

// Clean up SSL context and free allocated resources
void cleanup_ssl(SSL_CTX *ctx) {
    SSL_CTX_free(ctx);
    EVP_cleanup();
}

// Create a socket, bind it to the specified port, and listen for connections
int create_socket(void) {
    int sockfd;
    struct sockaddr_in addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind to port");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

// Handle communication with a single client
void handle_client(SSL *ssl) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes;

    // Receive data from the client
    bytes = SSL_read(ssl, buffer, sizeof(buffer));
    if (bytes > 0) {
        printf("Received message: \"%s\"\n", buffer);

        // Send a response
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, SSL World!\n";
        SSL_write(ssl, response, strlen(response));
    } else {
        ERR_print_errors_fp(stderr);
    }
}

int main(int argc, char **argv) {
    SSL_CTX *ctx;
    int sockfd;
    struct sockaddr_in addr;
    uint len = sizeof(addr);

    // Initialize SSL and create context
    ctx = init_ssl_context();

    // Create and bind socket
    sockfd = create_socket();

    while (1) {
        int client;
        SSL *ssl;

        // Accept incoming connections
        client = accept(sockfd, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("Unable to accept connection");
            exit(EXIT_FAILURE);
        }
        
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        SSL_accept(ssl) <= 0 ? ERR_print_errors_fp(stderr) : handle_client(ssl);

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client);
    }

    // Clean up resources
    close(sockfd);
    cleanup_ssl(ctx);
    return 0;
}
