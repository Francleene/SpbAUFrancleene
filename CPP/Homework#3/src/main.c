#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "../include/clist.h"

struct position_node {
    int x, y;
    struct intrusive_node node;
};

void remove_position(struct intrusive_list * list, int x, int y) { // removes all (x, y) pairs
    struct intrusive_node * ptr = (list->head)->next;
    struct position_node * container;
    while (ptr != list->head) {
        container = container_of(ptr, struct position_node, node);
        if (container->x == x && container->y == y) {
            remove_node(list, ptr);
            
            struct position_node * pos_node_address = container_of(ptr, struct position_node, node);
            free(pos_node_address);
        }
        
        ptr = ptr->next;
    }
    
}

void add_position(struct intrusive_list * list, int x, int y) {
    struct position_node * new_pos_node = (struct position_node*)malloc(sizeof(struct position_node));
    new_pos_node->x = x;
    new_pos_node->y = y;
    
    add_node(list, &new_pos_node->node);
}

void show_all_positions(struct intrusive_list * list) {
    struct intrusive_node * ptr = (list->head)->next;
    struct position_node * container;
    while (ptr != list->head) {
        container = container_of(ptr, struct position_node, node);
        printf("(%d %d) ", container->x, container->y);
        ptr = ptr->next;
    }
    printf("\n");
}

void remove_all_positions(struct intrusive_list * list) {
    struct intrusive_node * ptr = list->head->next;
    struct position_node * pos_ptr;
    
    while (ptr != list->head) {
        pos_ptr = container_of(ptr, struct position_node, node);
        remove_node(list, ptr);
        free(pos_ptr);
        ptr = ptr->next;
    }
}

int main(int argc, const char * argv[]) {
    struct intrusive_list my_list;
    init_list(&my_list);
    
    char * command = (char *)malloc(256);
    int x, y;
    while (1) {
        scanf("%s", command);
        
        if (strcmp(command, "exit") == 0) {
            remove_all_positions(&my_list);
            free(my_list.head);
            free(command);
            break;
        } else if (!strcmp(command, "add")) {
            scanf("%d%d", &x, &y);
            add_position(&my_list, x, y);
        } else if (!strcmp(command, "rm")) {
            scanf("%d%d", &x, &y);
            remove_position(&my_list, x, y);
        } else if (!strcmp(command, "rma")) {
            remove_all_positions(&my_list);
        } else if (!strcmp(command, "len")) {
            printf("%d\n", get_length(&my_list));
        } else if (!strcmp(command, "print")) {
            show_all_positions(&my_list);
        } else {
            printf("Unknown command\n");
        }
    }
    
    return 0;
}