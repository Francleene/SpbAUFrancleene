#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

struct intrusive_node {
    struct intrusive_node* next;
    struct intrusive_node* prev;
};

struct intrusive_list {
    struct intrusive_node* head;
    int length;
};

void init_list(struct intrusive_list * list);
void add_node(struct intrusive_list * list, struct intrusive_node * node);
void remove_node(struct intrusive_list * list, struct intrusive_node * node);
int get_length(struct intrusive_list * list);

#endif CLIST_H