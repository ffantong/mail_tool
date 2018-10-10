#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mail.h"

struct data6 {
    unsigned int d4:6;
    unsigned int d3:6;
    unsigned int d2:6;
    unsigned int d1:6;
};
static char con628(char c6) {
    char rtn = '\0';
    if (c6 < 26) rtn = c6 + 65;
    else if (c6 < 52) rtn = c6 + 71;
    else if (c6 < 62) rtn = c6 - 4;
    else if (c6 == 62) rtn = 43;
    else rtn = 47;
    return rtn;
}

static void base64(char *dbuf, char *buf128, int len) {
    struct data6 *ddd = NULL;
    int i = 0;
    char buf[256] = {0};
    char *tmp = NULL;
    char cc = '\0';
    memset(buf, 0, 256);
    strcpy(buf, buf128);
    for(i = 1; i <= len/3; i++) {
        tmp = buf+(i-1)*3;
        cc = tmp[2];
        tmp[2] = tmp[0];
        tmp[0] = cc;
        ddd = (struct data6 *)tmp;
        dbuf[(i-1)*4+0] = con628((unsigned int)ddd->d1);
        dbuf[(i-1)*4+1] = con628((unsigned int)ddd->d2);
        dbuf[(i-1)*4+2] = con628((unsigned int)ddd->d3);
        dbuf[(i-1)*4+3] = con628((unsigned int)ddd->d4);
    }
    if(len%3 == 1) {
        tmp = buf+(i-1)*3;
        cc = tmp[2];
        tmp[2] = tmp[0];
        tmp[0] = cc;
        ddd = (struct data6 *)tmp;
        dbuf[(i-1)*4+0] = con628((unsigned int)ddd->d1);
        dbuf[(i-1)*4+1] = con628((unsigned int)ddd->d2);
        dbuf[(i-1)*4+2] = '=';
        dbuf[(i-1)*4+3] = '=';
    }
    if(len%3 == 2) {
        tmp = buf+(i-1)*3;
        cc = tmp[2];
        tmp[2] = tmp[0];
        tmp[0] = cc;
        ddd = (struct data6 *)tmp;
        dbuf[(i-1)*4+0] = con628((unsigned int)ddd->d1);
        dbuf[(i-1)*4+1] = con628((unsigned int)ddd->d2);
        dbuf[(i-1)*4+2] = con628((unsigned int)ddd->d3);
        dbuf[(i-1)*4+3] = '=';
    }
    return;
}

static char * substring(const char *str, char start_ch, char end_ch){
    char *p = NULL;
    if(start_ch == '\0'){
        char *t = strchr(str, end_ch);
        if(t != NULL){
            p = malloc(t - str + 1);
            strncpy(p, str, t - str);
            p[t - str] = '\0';
            return p;
        }
    }else{
        char *t = strchr(str, end_ch);
        char *t1 = strchr(str, start_ch);
        if(t != NULL && t1 != NULL){
            p = malloc(t - t1 + 1);
            strncpy(p, t1, t - t1);
            p[t - t1] = '\0';
            return p;
        }
    }
    p = malloc(strlen(str) + 1);
    strncpy(p, str, strlen(str) + 1);
    return p;
}

static char * mail_to(char *header, char * mail_to){
    char *t = mail_to, *t1, *t2;
    char *p = malloc(strlen(header) + strlen(mail_to) * 2);
    memset(p, 0, strlen(header) + strlen(mail_to) * 2);
    strcat(p, header);
    t = mail_to;
    while(t < mail_to + strlen(mail_to)){
        t1 = substring(t, '\0', ',');
        t2 = substring(t1, '\0', '@');
        strcat(p, t2);
        strcat(p, " <");
        strcat(p, t1);
        strcat(p, ">;");
        t += strlen(t1) + 1;
        free(t2);
        free(t1);
    }
    strcat(p, "\r\n");
    return p;
}

void sendemail(MAIL_CONFIG * mail_c, int(*recv)(char *, int), int(*send)(char *, int)) {
    char buf[1500] = {0};
    char rbuf[1500] = {0};
    char login[128] = {0};
    char pass[128] = {0};
    while(recv(rbuf, 1500) == 0) {
        return;
    }
    printf("%s\n", rbuf);

    memset(buf, 0, 1500);
    sprintf(buf, "EHLO %s\r\n", mail_c->smtp_host);
    send(buf, strlen(buf));
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    memset(buf, 0, 1500);
    sprintf(buf, "AUTH LOGIN\r\n");
    send(buf, strlen(buf));
    printf("%s\n", buf);
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    base64(login, mail_c->mail_account, strlen(mail_c->mail_account));
    sprintf(buf, "%s\r\n", login);
    send(buf, strlen(buf));
    printf("%s\n", buf);
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    memset(pass, 0, 128);
    base64(pass, mail_c->password, strlen(mail_c->password));
    sprintf(buf, "%s\r\n", pass);
    send(buf, strlen(buf));
    printf("%s\n", buf);

    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    memset(buf, 0, 1500);
    sprintf(buf, "MAIL FROM: %s\r\n", mail_c->mail_account);
    send(buf, strlen(buf));
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    char *t = mail_c->mail_to, *t1;
    while(t < mail_c->mail_to + strlen(mail_c->mail_to)){
        t1 = substring(t, '\0', ',');
        memset(buf, 0, 1500);
        sprintf(buf, "RCPT TO:<%s>\r\n", t1);
        printf("%s", buf);
        send(buf, strlen(buf));
        memset(rbuf, 0, 1500);
        recv(rbuf, 1500);
        printf("%s\n", rbuf);
        t += strlen(t1) + 1;
        free(t1);
    }

    t = mail_c->mail_cc;
    while(mail_c->mail_cc != NULL && t < mail_c->mail_cc + strlen(mail_c->mail_cc)){
        t1 = substring(t, '\0', ',');
        memset(buf, 0, 1500);
        sprintf(buf, "RCPT TO:<%s>\r\n", t1);
        printf("%s", buf);
        send(buf, strlen(buf));
        memset(rbuf, 0, 1500);
        recv(rbuf, 1500);
        printf("%s\n", rbuf);
        t += strlen(t1) + 1;
        free(t1);
    }

    memset(buf, 0, 1500);
    sprintf(buf, "DATA\r\n");
    send(buf, strlen(buf));
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    char *name = substring(mail_c->mail_account, '\0', '@');
    char *from = malloc(15 + strlen(name) + strlen(mail_c->mail_account));
    sprintf(from, "From: %s <%s>\r\n", name, mail_c->mail_account);
    free(name);

    char *to = mail_to("To: ", mail_c->mail_to);

    char *cc = mail_to("Cc: ", mail_c->mail_cc);

    char *subject = malloc(11 + strlen(mail_c->subject));
    sprintf(subject, "Subject: %s\r\n", mail_c->subject);

    char *t_body = malloc(strlen(from) + strlen(to) + strlen(cc) + strlen(subject) + strlen(mail_c->body) + 6);
    sprintf(t_body, "%s%s%s%s%s\r\n.\r\n", from, to, cc, subject, mail_c->body);

    printf("%s", t_body);
    send(t_body, strlen(t_body));
    free(from);
    free(to);
    free(cc);
    free(subject);
    free(t_body);
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);

    memset(buf, 0, 1500);
    sprintf(buf, "QUIT\r\n");
    send(buf, strlen(buf));
    memset(rbuf, 0, 1500);
    recv(rbuf, 1500);
    printf("%s\n", rbuf);
}
