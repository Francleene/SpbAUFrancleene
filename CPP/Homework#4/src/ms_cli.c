#include <stdlib.h>
#include <stdio.h>
#include "../include/mergesort.h"

// Compare functions
int is_less_int(const void * first, const void  * second) {
    return *(int *)first - *(int *)second;
}

int is_less_char(const void * first, const void * second) {
    return *(char *)first - *(char *)second;
}

int is_less_str(const void * first, const void * second) {
    char * ptr1 = *(char **) first,
    * ptr2 = *(char **) second;
    
    while (*ptr1 != 0 && *ptr1 == *ptr2) {
        ptr1++;
        ptr2++;
    }
    
    return *ptr1 - *ptr2;
}

// Utils functions
int not_equals(const char *first, const char *second) {
    while (*first != 0 && *first == *second) {
        first++;
        second++;
    }
    return *first - *second;
}

size_t len_of(char * str) {
    size_t len = 1;
    while (*str) {
        len++;
        str++;
    }
    return len;
}

void str_cpy(char *str1, const char *str2) {
    while (*str2) *(str1++) = *(str2++);
    *str1 = 0;
}

// Init functions
void init_int(int argc, char ** argv, int *arr) {
    for (int i = 0; i < argc - 2; i++) {
        arr[i] = atoi(argv[i + 2]);
    }
}

void init_char(int argc, char ** argv, char * arr) {
    for (int i = 0; i < argc - 2; i++) {
        arr[i] = argv[i + 2][0];
    }
}

void init_str(int argc, char ** argv, char ** arr) {
    size_t tmp_len = 0;
    for (int i = 0; i < argc - 2; i++) {
        tmp_len = len_of(argv[i + 2]);
        arr[i] = (char *)malloc(tmp_len * sizeof(char));
        str_cpy(arr[i], argv[i + 2]);
    }
}

// Print functions
void print_int(int * arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_char(char * arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

void print_str(char ** arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}



int main(int argc, char ** argv) {
    
    if (!not_equals(argv[1], "int")) {
        int *arr = (int *)malloc((argc - 2) * sizeof(int));
        
        init_int(argc, argv, arr);
        merge_sort(arr, argc - 2, sizeof(int), &is_less_int);
        print_int(arr, argc - 2);
        
        free(arr);
    } else if (!not_equals(argv[1], "char")) {
        char *arr = (char *)malloc((argc - 2) * sizeof(char));
        
        init_char(argc, argv, arr);
        merge_sort(arr, argc - 2, sizeof(char), &is_less_char);
        print_char(arr, argc - 2);
        
        free(arr);
    } else {
        char ** arr = (char **)malloc((argc - 2) * sizeof(char *));
        
        init_str(argc, argv, arr);
        merge_sort(arr, argc - 2, sizeof(char *), &is_less_str);
        print_str(arr, argc - 2);
        
        for (int i = 0; i < argc - 2; i++) {
            free(arr[i]);
        }
        free(arr);
    }
    
    return 0;
}