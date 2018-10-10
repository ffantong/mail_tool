#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

static char *strcopy(char *str){
    char *t = malloc(sizeof(char) * (strlen(str) + 1));
    strncpy(t, str, strlen(str) + 1);
    return t;
}

MAP_NODE* put_(MAP_NODE *head, char *key, char *value){
    MAP_NODE *t = head;
    head = malloc(sizeof(MAP_NODE));
    head->key = strcopy(key);
    head->value = strcopy(value);
    head->next = t;
    return head;
}

char *get_(MAP_NODE *head, char *key){
    MAP_NODE *t = head;
    while(t != NULL){
        if(!strncmp(t->key, key, strlen(key))){
            return strcopy(t->value);
        }
        t = t->next;
    }
    return NULL;
}

void remove_(MAP_NODE *head, char *key){
    MAP_NODE *t = head->next, *p = head;
    if(!strncmp(t->key, key, strlen(key))){
        free(head->key);
        free(head->value);
        head = head->next;
        free(p);
        return;
    }
    while(t != NULL){
        if(!strncmp(t->key, key, strlen(key))){
            free(t->key);
            free(t->value);
            p->next = t->next;
            free(t);
            break;
        }
        p = t;
        t = t->next;
    }
}

void clear_(MAP_NODE *head){
    MAP_NODE *p = head;
    while(p != NULL){
        head = p;
        p = p->next;
        free(head->key);
        free(head->value);
        free(head);
    }
}
