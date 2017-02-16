//
// Created by Александр on 08.11.16.
//

#ifndef PTHREADS_THREAD_POOL_H
#define PTHREADS_THREAD_POOL_H

#include <stdlib.h>
#include <pthread.h>

typedef struct Task {
    void (* func)(void *);
    void * arg;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int solved;
} Task;

typedef struct TaskNode {
    Task * task;
    struct TaskNode * next;
} TaskNode;

typedef struct TaskQueue {
    TaskNode * task_head;
    int finished;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
} TaskQueue;

typedef struct ThreadPool {
    pthread_t * threads;
    TaskQueue tasks;

    size_t threads_num;
} ThreadPool;

void task_queue_init(struct TaskQueue * tq);
void add_task(TaskQueue * tq, Task * task);
TaskNode * pop_task(struct TaskQueue * tq);

void init_task(Task * task, void (* init_func)(void *), void * init_arg);

void thpool_init(ThreadPool * pool, size_t threads_nm);
void thpool_submit(ThreadPool * pool, Task * task);
void thpool_wait(Task * task);
void thpool_finit(ThreadPool * thpool);

#endif //PTHREADS_THREAD_POOL_H
