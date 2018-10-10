#ifndef SOCK_H_INCLUDED
#define SOCK_H_INCLUDED
#include <openssl/ssl.h>

typedef struct sock_config{
    int sockfd;
    int ssl_open;
    SSL_CTX *ctx;
    SSL *ssl;
} SOCK_CONFIG;

void sock_connect();
void sock_close();
int sock_read(char *, int);
int sock_write(char *, int);

SOCK_CONFIG* sock;

#endif // SOCK_H_INCLUDED
