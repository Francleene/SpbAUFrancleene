#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "thread_pool.h"

typedef struct WaitingTaskNode {
    struct WaitingTaskNode * next;
    Task * task;
} WaitingTaskNode;

typedef struct WaitingTaskQueue {
    pthread_mutex_t mutex;
    WaitingTaskNode * begin, * end;
} WaitingTaskQueue;

void init_waiting_queue(WaitingTaskQueue * tq, Task * task) {
    pthread_mutex_init(&tq->mutex, NULL);

    WaitingTaskNode * last_node = malloc(sizeof(WaitingTaskNode));
    last_node->next = NULL;
    last_node->task = task;

    tq->begin = last_node;
    tq->end = last_node;
}

void add_waiting_task(WaitingTaskQueue * tq, Task * task) {
    pthread_mutex_lock(&tq->mutex);

    WaitingTaskNode * new_node = malloc(sizeof(WaitingTaskNode));

    new_node->next = NULL;
    new_node->task = task;

    tq->begin->next = new_node;
    tq->begin = new_node;

    pthread_mutex_unlock(&tq->mutex);
}

Task * pop_waiting_task(WaitingTaskQueue * tq) {
    pthread_mutex_lock(&tq->mutex);

    if (tq->end == NULL) {
        pthread_mutex_unlock(&tq->mutex);
        return NULL;
    }

    WaitingTaskNode * last_node = tq->end;
    Task *task = last_node->task;
    tq->end = tq->end->next;
    free(last_node);

    pthread_mutex_unlock(&tq->mutex);

    return task;
}

typedef struct {
    int * arr;
    size_t left, right, recur_depth;
    ThreadPool * thpool;
    WaitingTaskQueue * waiting_tasks;
} Data;

void swap(int * first, int * second) {
    int tmp = *first;
    *first = *second;
    *second = tmp;
}

int compar(const void * first, const void * second) {
    return *(int *)first - *(int *)second;
}

Data * pack_data(int * arr, size_t left, size_t right, size_t recur_depth, ThreadPool * thpool, WaitingTaskQueue * tq) {
    Data * data = malloc(sizeof(Data));

    data->arr = arr;
    data->left = left;
    data->right = right;
    data->recur_depth = recur_depth;
    data->thpool = thpool;
    data->waiting_tasks = tq;

    return data;
}

void partition(int * arr, size_t left, size_t right, size_t * i, size_t * j, int pivot) {
    *i = left, *j = right - 1;
    printf("p: %d %d %d\n", *i, *j, pivot);
    for (size_t k = left; k < right; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");
    while (*i <= *j) {
        while (arr[*i] < pivot) (*i)++;
        while (arr[*j] > pivot) (*j)--;
        if (*i <= *j) swap(&arr[(*i)++], &arr[(*j)--]);
    }
    for (size_t k = left; k < right; k++) {
        printf("%d ", arr[k]);
    }
    printf("\n");
}

// [left, right)
void quick_sort_t(void * ptr) {
    Data * data = (Data *)ptr;

    printf("%d %d %d\n", data->left, data->right, data->recur_depth);

    if (data->right - data->left < 2) {
        return;
    }

    if (data->recur_depth == 0) {
        qsort(data->arr + data->left, data->right - data->left, sizeof(int), &compar);
        for (size_t i = data->left; i < data->right; i++) {
            printf("%d ", data->arr[i]);
        }
        printf("\n");
        return;
    }

    int value = data->arr[ data->left + rand() % (data->right - data->left) ];
    size_t first_begin, second_end;
    partition(data->arr, data->left, data->right, &second_end, &first_begin, value);

    Task * first_task = malloc(sizeof(Task));
    Task * second_task = malloc(sizeof(Task));

    add_waiting_task(data->waiting_tasks, first_task);
    add_waiting_task(data->waiting_tasks, second_task);

    size_t middle = data->left + (data->right - data->left) / 2;
    void * first_ptr = (void *)pack_data(data->arr, data->left, first_begin + 1, data->recur_depth - 1, data->thpool, data->waiting_tasks);
    void * second_ptr = (void *)pack_data(data->arr, second_end, data->right, data->recur_depth - 1, data->thpool, data->waiting_tasks);

    init_task(first_task, quick_sort_t, first_ptr);
    init_task(second_task, quick_sort_t, second_ptr);

    thpool_submit(data->thpool, first_task);
    thpool_submit(data->thpool, second_task);
}

void start_quick_sort(int * arr, size_t size, size_t threads_num, size_t recur_depth) {
    ThreadPool * thpool = malloc(sizeof(ThreadPool));
    thpool_init(thpool, threads_num);

    Task * main_task = malloc(sizeof(Task));

    WaitingTaskQueue * waiting_tasks = (WaitingTaskQueue *)malloc(sizeof(WaitingTaskQueue));
    init_waiting_queue(waiting_tasks, main_task);

    void * ptr = pack_data(arr, 0, size, recur_depth, thpool, waiting_tasks);

    init_task(main_task, quick_sort_t, ptr);

    thpool_submit(thpool, main_task);

    thpool_wait(main_task);

    Task * waiting_task = pop_waiting_task(waiting_tasks);
    while (waiting_task != NULL) {
        thpool_wait(waiting_task);
        free(waiting_task);
        waiting_task = pop_waiting_task(waiting_tasks);
    }

    free(waiting_tasks);

    thpool_finit(thpool);
}

int main() {
    //srand(time(NULL));
    int * arr = (int *)malloc(20 * sizeof(int));
    for (int i = 0; i < 20; i++) {
        arr[i] = 1 + rand() % 20;
        printf("%d ", arr[i]);
    }

    printf("\n");

    start_quick_sort(arr, 20, 100, 100);

    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
