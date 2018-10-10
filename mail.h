#ifndef MAIL_H_INCLUDED
#define MAIL_H_INCLUDED

typedef struct mail_config{
    char *smtp_host;
    int smtp_port;
    int ssl_open;
    char *mail_account;
    char *password;
    char *mail_to;
    char *mail_cc;
    char *subject;
    char *body;
} MAIL_CONFIG;
#endif // MAIL_H_INCLUDED
