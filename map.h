#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

typedef struct map_node{
    char *key;
    char *value;
    struct map_node *next;
} MAP_NODE;

MAP_NODE* put_(MAP_NODE *head, char *key, char *value);
char *get_(MAP_NODE *head, char *key);
void remove_(MAP_NODE *head, char *key);
void clear_(MAP_NODE *head);

#endif // MAP_H_INCLUDED
