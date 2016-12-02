#include <stdio.h>

#include "thread_pool.h"

typedef struct TreeNode {
    Task * task;
    struct TreeNode *left, *right, *parent;
} TreeNode;

typedef struct Data {
    int *arr;
    int left, right, recur_depth;
    ThreadPool * thpool;
    TreeNode * root;
} Data;

TreeNode * make_tree_node(Task * task, TreeNode * parent) {
    TreeNode * new_node = malloc(sizeof(TreeNode));

    new_node->task = task;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = parent;

    return new_node;
}

void * pack_data(int * arr, int left, int right, int recur_depth, ThreadPool * thpool, TreeNode * root) {
    Data * data = malloc(sizeof(Data));

    data->arr = arr;
    data->left = left;
    data->right = right;
    data->recur_depth = recur_depth;
    data->thpool = thpool;
    data->root = root;

    return data;
}

int compar(const void * first, const void * second) {
    return *(int *)first - *(int *)second;
}

void swap(int * first, int * second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
}

void partition(int * arr, int left, int right, int * i, int * j, int pivot) {
    *i = left, *j = right - 1;
    while (*i <= *j) {
        while (arr[*i] < pivot) (*i)++;
        while (arr[*j] > pivot) (*j)--;
        if (*i <= *j) swap(&arr[(*i)++], &arr[(*j)--]);
    }
}

void quick_sort(void * ptr) {
    struct Data * data = (struct Data *)ptr;

    int * arr = data->arr;
    int left  = data->left,
        right = data->right;

    if (right - left < 2) {
        return;
    }

    if (data->recur_depth == 0) {
        qsort(arr + left, (size_t)(right - left), sizeof(int), &compar);
        return;
    }

    int value = arr[left + rand() % (right - left)];
    int first_begin, second_end;
    partition(arr, left, right, &second_end, &first_begin, value);

    Task * first_task = malloc(sizeof(Task));
    Task * second_task = malloc(sizeof(Task));

    data->root->left = make_tree_node(first_task, data->root);
    data->root->right = make_tree_node(second_task, data->root);

    void * first_ptr = pack_data(arr, left, first_begin + 1, data->recur_depth - 1, data->thpool, data->root->left);
    void * second_ptr = pack_data(arr, second_end, right, data->recur_depth - 1, data->thpool, data->root->right);

    init_task(first_task, quick_sort, first_ptr);
    init_task(second_task, quick_sort, second_ptr);

    thpool_submit(data->thpool, first_task);
    thpool_submit(data->thpool, second_task);
}

void free_task(Task * task) {
    free(task->arg);
    free(task);
}

void start_quick_sort(int * arr, int size, size_t threads_num, int recur_depth) {
    ThreadPool * thpool = malloc(sizeof(ThreadPool));
    thpool_init(thpool, threads_num);

    Task * main_task = malloc(sizeof(Task));
    TreeNode * root = make_tree_node(main_task, NULL);

    void * ptr = pack_data(arr, 0, size, recur_depth, thpool, root);
    init_task(main_task, quick_sort, ptr);

    thpool_submit(thpool, main_task);
    TreeNode * traveller = root;
    Task * waiting_task;
    while (traveller != NULL) {
        waiting_task = traveller->task;

        if (waiting_task != NULL) {
            thpool_wait(waiting_task);
            free_task(waiting_task);
            traveller->task = NULL;
        }

        if (traveller->left != NULL) {
            if (traveller->left->task != NULL) {
                // if task in left child isn't solved
                traveller = traveller->left;
            } else {
                // if task in left child is solved but left node isn't deleted
                free(traveller->left);
                traveller->left = NULL;
            }
            continue;
        }

        if (traveller->right != NULL) {
            if (traveller->right->task != NULL) {
                traveller = traveller->right;
            } else {
                free(traveller->right);
                traveller->right = NULL;
            }

            continue;
        }

        traveller = traveller->parent;
    }

    free(root);

    thpool_finit(thpool);
    free(thpool);
}

const int size = 100;

int main() {
    int * arr = malloc(size * sizeof(int));
    for (int k = 0; k < 200; k++) {
        printf("input array: ");
        for (int i = 0; i < size; i++) {
            arr[i] = 1 + rand() % size;
            printf("%d ", arr[i]);
        }
        printf("\n");

        start_quick_sort(arr, size, 4, 100);

        printf("sorted array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    free(arr);
}
