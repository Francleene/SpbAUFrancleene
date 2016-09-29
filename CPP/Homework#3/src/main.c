#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/clist.h"

struct position_node {
    int x, y;
    struct intrusive_node node;
};

void remove_position(struct intrusive_list * list, int x, int y) { // removes all (x, y) pairs
    struct intrusive_node * ptr = (list->head)->next;
    while (ptr != list->head) {
        if (*((int *)ptr - 2) == x && *((int *)ptr - 1) == y) {
            remove_node(list, ptr);
            
            struct position_node * pos_node_address = (char *)ptr - 2 * sizeof(int);
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
    while (ptr != list->head) {
        printf("(%d %d) ", *((int *)ptr - 2), *((int *)ptr - 1));
        ptr = ptr->next;
    }
    printf("\n");
}

void remove_all_positions(struct intrusive_list * list) {
    struct intrusive_node * ptr = list->head->next;
    struct position_node * pos_ptr;
    
    while (ptr != list->head) {
        pos_ptr = (struct position_node*)((int *)ptr - 2);
        remove_node(list, ptr);
        free(pos_ptr);
        ptr = ptr->next;
    }
}

int main(int argc, const char * argv[]) {
    struct intrusive_list my_list;
    init_list(&my_list);
    
    char command[256];
    int x, y;
    while (1) {
        scanf("%s", &command);
        
        if (strcmp(command, "exit") == 0) {
            remove_all_positions(&my_list);
            free(my_list.head);
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