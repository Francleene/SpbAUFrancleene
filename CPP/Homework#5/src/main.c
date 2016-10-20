//
//  main.c
//  CPP
//
//  Created by Александр on 14.10.16.
//  Copyright © 2016 Alexander. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/position.h"
#include "../include/clist.h"

typedef void (* op)(intrusive_node * node, const void * input, void * output);
typedef void (* save_elem)(FILE * file, char * format, int x, int y);

void readint(FILE * file, int * x) {
    char * num = malloc(3 * sizeof(char));
    
    for (int i = 0; i < 3; i++) {
        num[i] = 0;
    }
    
    fread(num, sizeof(char), 3, file);
    
    *x = 0;
    *x |= num[0];
    *x |= num[1] << 8;
    *x |= num[2] << 16;
    
    if (*x >= 8388608) *x |= 255 << 24;
    
    free(num);
}

void readpoint(FILE * file, int * x, int * y) {
    readint(file, x);
    readint(file, y);
}

void writeint(FILE * file, int x) {
    static int first_part = 255;
    static int second_part = 255 << 8;
    static int third_part = 255 << 16;
    
    char * num = malloc(3 * sizeof(char));
    
    num[0] = x & 255;
    num[1] = (x & second_part) >> 8;
    num[2] = (x & third_part) >> 16;
    
    fwrite(num, sizeof(char), 3, file);
    
    free(num);
}



void loadtext(intrusive_list * list, const char * filename) {
    FILE * file = fopen(filename, "r");
    
    int x, y;
    fscanf(file, "%d%d\n", &x, &y);
    while (!feof(file)) {
        add_position(list, x, y);
        fscanf(file, "%d%d\n", &x, &y);
    }
    
    fclose(file);
}

void loadbin(intrusive_list * list, const char * filename) {
    FILE * file = fopen(filename, "rb");
    
    int x, y;
    readpoint(file, &x, &y);
    while (!feof(file)) {
        add_position(list, x, y);
        readpoint(file, &x, &y);
    }
    
    fclose(file);
}

void savetext_point(FILE * file, char * format, int x, int y) {
    fprintf(file, format, x, y);
}

void savebin_point(FILE * file, char * format, int x, int y) {
    writeint(file, x);
    writeint(file, y);
}

void count_elem(intrusive_node * node, const void * input, void * output) {
    *(int *)output += 1;
}

void print_elem(intrusive_node * node, const void * input, void * output) {
    print_position_formated(node, stdout, (char *)input, &savetext_point);
}

void savetext_elem(intrusive_node * node, const void * input, void * output) {
    print_position_formated(node, (FILE *)input, "%d %d\n", &savetext_point);
}

void savebin_elem(intrusive_node * node, const void * input, void * output) {
    print_position_formated(node, (FILE *)input, NULL, &savebin_point);
}

void apply(intrusive_list *list, op oper, const void * input, void * output) {
    intrusive_node *head = &list->head;
    intrusive_node *node = head->next;
    
    for (; node != head; node = node->next) {
        oper(node, input, output);
    }
}

void savetext(intrusive_list * list, const char * filename) {
    FILE * file = fopen(filename, "w");
    
    apply(list, &savetext_elem, file, NULL);
    
    fclose(file);
}

void savebin(intrusive_list * list, const char * filename) {
    FILE * file = fopen(filename, "wb");
    
    apply(list, &savebin_elem, file, NULL);
    
    fclose(file);
}

void print(intrusive_list * list, const char * format) {
    apply(list, &print_elem, format, NULL);
    printf("%c", '\n');
}

void count(intrusive_list * list) {
    int counter = 0;
    apply(list, &count_elem, NULL, &counter);
    printf("%d\n", counter);
}

int main(int argc, const char * argv[]) {
    
    intrusive_list * list = malloc(sizeof(intrusive_list));
    init_list(list);
    
    if (!strcmp(argv[1], "loadtext")) {
        loadtext(list, argv[2]);
    } else if (!strcmp(argv[1], "loadbin")){
        loadbin(list, argv[2]);
    } else {
        printf("Usage: {loadtext | loadbin}\n");
        
        free(list);
        return 0;
    }
    
    if (!strcmp(argv[3], "savetext")) {
        savetext(list, argv[4]);
    } else if (!strcmp(argv[3], "savebin")) {
        savebin(list, argv[4]);
    } else if (!strcmp(argv[3], "print")) {
        print(list, argv[4]);
    } else if (!strcmp(argv[3], "count")) {
        count(list);
    } else {
        printf("Unknown command =(\n");
    }
    
    remove_all(list);
    free(list);
    
    return 0;
}
