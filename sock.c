#ifdef WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/time.h>
#include <netdb.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "sock.h"
#include "mail.h"

void sock_connect(MAIL_CONFIG* mail) {
    sock = malloc(sizeof(SOCK_CONFIG));
    int sockfd = 0;
    struct sockaddr_in their_addr = {0};
#ifdef WIN32
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 2), &WSAData);
#endif
    memset(&their_addr, 0, sizeof(their_addr));
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(mail->smtp_port);
    struct hostent* phost = gethostbyname(mail->smtp_host);
    memcpy(&their_addr.sin_addr, phost->h_addr_list[0], phost->h_length);
    sockfd=socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        fprintf(stderr, "Open sockfd(TCP) error!\n");
        exit(-1);
    }
    if(connect(sockfd, (const struct sockaddr *)&their_addr, sizeof(struct sockaddr)) < 0) {
        fprintf(stderr, "Connect sockfd(TCP) error!\n");
        exit(-1);
    }
    sock->sockfd = sockfd;
    sock->ssl_open = mail->ssl_open;
    if(sock->ssl_open){
        SSL_CTX *ctx;
        SSL *ssl;
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        ctx = SSL_CTX_new(SSLv23_client_method());
        if (ctx == NULL)
        {
            ERR_print_errors_fp(stdout);
            exit(1);
        }
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, sockfd);
        if (SSL_connect(ssl) == -1){
            ERR_print_errors_fp(stderr);
        }
        sock->ssl = ssl;
        sock->ctx = ctx;
    }
}

void sock_close() {
#ifdef WIN32
    WSACleanup();
#endif
    if(sock->ssl_open){
        SSL_shutdown(sock->ssl);
        SSL_free(sock->ssl);
        SSL_CTX_free(sock->ctx);
    }
    close(sock->sockfd);
    free(sock);
}

int sock_read(char * buf, int len){
    if(sock->ssl_open){
        return SSL_read(sock->ssl, buf, len);
    }else{
        return recv(sock->sockfd, buf, len, 0);
    }
}

int sock_write(char * buf, int len){
    if(sock->ssl_open){
        return SSL_write(sock->ssl, buf, len);
    }else{
        return send(sock->sockfd, buf, len, 0);
    }
}
