#include <stdlib.h>

struct intrusive_node {
    struct intrusive_node* next;
    struct intrusive_node* prev;
};

struct intrusive_list {
    struct intrusive_node* head;
    int length;
};

void init_list(struct intrusive_list * list) {
    
    struct intrusive_node * new_head = (struct intrusive_node*)malloc(sizeof(struct intrusive_node));
    
    list->head = new_head;
    list->head->next = list->head;
    list->head->prev = list->head;
    
    list->length = 0;
}

void add_node(struct intrusive_list * list, struct intrusive_node * node) {
    node->next = list->head;
    node->prev = (list->head)->prev;
    list->head->prev->next = node;
    list->head->prev = node;
    
    list->length += 1;
}

void remove_node(struct intrusive_list * list, struct intrusive_node * node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    list->length -= 1;
}

int get_length(struct intrusive_list * list) {
    return list->length;
}
