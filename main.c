#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sock.h"
#include "mail.h"

void read_mail_config(char *, char *, MAIL_CONFIG*);
void sendemail(MAIL_CONFIG * mail_c, int(*recv)(char *, int), int(*send)(char *, int));

void free_mail_config(MAIL_CONFIG* cfg){
    free(cfg->mail_account);
    free(cfg->mail_cc);
    free(cfg->mail_to);
    free(cfg->password);
    free(cfg->smtp_host);
    free(cfg->body);
    free(cfg->subject);
    free(cfg);
}
void config_checker(MAIL_CONFIG* cfg){
    if(cfg->body == NULL || strlen(cfg->body) == 0){
        printf("Mail content can not be null!");
        exit(-1);
    }
    if(cfg->mail_to == NULL || strlen(cfg->mail_to)){
        printf("The reciver can not be null!");
        exit(-1);
    }
    if(cfg->mail_account == NULL || strlen(cfg->mail_account)){
        printf("The sender can not be null!");
        exit(-1);
    }
    if(cfg->smtp_host == NULL || strlen(cfg->smtp_host)){
        printf("The smtp host can not be null!");
        exit(-1);
    }
    if(cfg->smtp_port == 0){
        printf("The smtp port can not be null!");
        exit(-1);
    }
}
int main(int argc, char* argv[])
{
    MAIL_CONFIG* cfg = malloc(sizeof(MAIL_CONFIG));
    if(argc == 3){
        read_mail_config(*argv, *(argv + 1), cfg);
    }else{
        read_mail_config("mail_config.ini", "tpl.txt", cfg);
    }
    sock_connect(cfg);
    sendemail(cfg, sock_read, sock_write);
    free_mail_config(cfg);
    sock_close();
    return 0;
}
