#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mail.h"
#include "map.h"

#define BUF_SIZE 1024
#define BUF_EXTEND 2

static void end_line(char * str, int len, char off_ch){
    for(int i = 0; i < len; i++){
        if(str[i] == off_ch || str[i] == '\n'){
            str[i] = '\0';
        }
    }
}

static char* append(char * src, char * dest){
    char * tmp;
    if(dest == NULL){
        tmp = malloc(sizeof(char) * (BUF_SIZE * BUF_EXTEND));
        memset(tmp, 0, BUF_SIZE * BUF_EXTEND);
        strncpy(tmp, src, strlen(src));
    }else{
        tmp = malloc(sizeof(char) * (strlen(dest) + BUF_SIZE * BUF_EXTEND));
        memset(tmp, 0, strlen(dest) + BUF_SIZE * BUF_EXTEND);
        strncpy(tmp, dest, strlen(dest));
        strncpy(tmp + strlen(dest), src, strlen(src));
        free(dest);
    }
    return tmp;
}

static char* read_line(FILE * fp, char off_ch){
    char *buf = malloc(sizeof(char) * BUF_SIZE);
    char *line = NULL;
    while(fgets(buf, BUF_SIZE, fp) != 0){
        if(line == NULL){
            line = buf;
            if(strlen(buf) < BUF_SIZE - 1){
                break;
            }
            line = NULL;
            line = append(buf, line);
        }else{
            line = append(buf, line);
            if(strlen(buf) < BUF_SIZE - 1){
                break;
            }
        }
    }
    if(line != NULL){
        end_line(line, strlen(line), off_ch);
    }
    if(buf != line){
        free(buf);
    }
    return line;
}

static char * read_all(FILE * fp, char off_ch){
    char *buf = malloc(sizeof(char) * BUF_SIZE);
    char *tmp = NULL;
    int len;
    while((len = fread(buf, sizeof(char), BUF_SIZE - 1, fp)) != 0){
        buf[len] = '\0';
        tmp = append(buf, tmp);
    }
    return tmp;
}

static char * read_template(char * file_name){
    FILE *fp = fopen(file_name, "r");
    if(fp == NULL){
        printf("Read config file %s error!", file_name);
        exit(-1);
    }
    char *tpl = read_all(fp, '#');
    fclose(fp);
    return tpl;
}

void read_mail_config(char * cfg_file, char * tpl_file, MAIL_CONFIG *cfg){
    memset(cfg, 0, sizeof(MAIL_CONFIG));
    FILE * fp = fopen(cfg_file, "r");
    if(fp == NULL){
        printf("Read config file %s error!", cfg_file);
        exit(-1);
    }
    char *line;
    char *ch;
    MAP_NODE *head = NULL;
    while((line = read_line(fp, '#')) != NULL){
        if((ch = strchr(line, '=')) != NULL){
            *ch = '\0';
            head = put_(head, line, ch + 1);
            free(line);
        }
    }
    cfg->mail_account = get_(head, "mail_account");
    cfg->mail_cc = get_(head, "mail_cc");
    cfg->mail_to = get_(head, "mail_to");
    cfg->password = get_(head, "password");
    cfg->smtp_host = get_(head, "smtp_host");
    cfg->smtp_port = atoi(get_(head, "smtp_port"));
    cfg->ssl_open = atoi(get_(head, "ssl_open"));
    cfg->subject = get_(head, "subject");
    clear_(head);
    fclose(fp);
    cfg->body = read_template(tpl_file);
}
