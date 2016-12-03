#include <stdio.h>
#include "thread_pool.h"


void do_task(Task * task) {
    // if task already solve then exit
    if (task->solved) {
        pthread_mutex_unlock(&task->mutex);
        return;
    }

    // if task ain't solved and we SHOULD NOT solve it then just wait
    if (!task->should_solve) {
        pthread_cond_wait(&task->cond, &task->mutex);
        pthread_mutex_unlock(&task->mutex);
        return;
    }

    task->func(task->arg);
    task->solved = 1;

    pthread_cond_signal(&task->cond);

    pthread_mutex_unlock(&task->mutex);
}

int is_finished(TaskQueue * tq) {
	pthread_mutex_lock(&tq->finished_mutex);
	int finished = tq->finished;
	pthread_mutex_unlock(&tq->finished_mutex);
	return finished;
}

void * do_tasks(void * ptr) {
    struct TaskQueue * tq = (struct TaskQueue *)ptr;

    for(;;) {
        pthread_mutex_lock(&tq->mutex);

        while (tq->task_head == NULL && !is_finished(tq)) {
            pthread_cond_wait(&tq->cond, &tq->mutex);
        }

        if (tq->task_head != NULL) {
            TaskNode * task_node = pop_task(tq);
            pthread_mutex_unlock(&tq->mutex);

            pthread_mutex_lock(&task_node->task->mutex);
            task_node->task->should_solve = 1;
            do_task(task_node->task);
			free(task_node);
        } else {
            pthread_mutex_unlock(&tq->mutex);
            break;
        }
    }
}

void add_task(TaskQueue * tq, Task * task) {
    TaskNode * tn = (TaskNode *)malloc(sizeof(TaskNode));

    tn->task = task;
    tn->next = tq->task_head;
    tq->task_head = tn;
}

struct TaskNode * pop_task(struct TaskQueue * tq) {
    struct TaskNode * task = tq->task_head;
    tq->task_head = tq->task_head->next;
    return task;
}

void task_queue_init(struct TaskQueue * tq)
{
	pthread_mutex_init(&tq->finished_mutex, NULL);
    pthread_mutex_init(&tq->mutex, NULL);
    pthread_cond_init(&tq->cond, NULL);

    tq->task_head = NULL;
    tq->finished = 0;
}

void thpool_init(struct ThreadPool * pool, size_t threads_nm)
{
    pool->threads = (pthread_t *)malloc(threads_nm * sizeof(pthread_t));

    task_queue_init(&pool->tasks);
    pool->threads_num = threads_nm;

    for (size_t i = 0; i < threads_nm; i++) {
        pthread_create(pool->threads + i, NULL, do_tasks, (void *)&pool->tasks);
    }

    //pthread_join(*pool->threads, NULL);
}

void thpool_submit(struct ThreadPool* pool, Task * task) {
    pthread_mutex_lock(&pool->tasks.mutex);
    add_task(&pool->tasks, task);
    pthread_cond_signal(&pool->tasks.cond);
    pthread_mutex_unlock(&pool->tasks.mutex);
}

void thpool_wait(Task * task) {
    pthread_mutex_lock(&task->mutex);
    do_task(task);
}

void set_finished(TaskQueue * tq) {
	pthread_mutex_lock(&tq->finished_mutex);
	tq->finished = 1;
	pthread_mutex_unlock(&tq->finished_mutex);	
}

void thpool_finit(ThreadPool* thpool) {
    set_finished(&thpool->tasks);
    pthread_cond_broadcast(&thpool->tasks.cond);

    for (size_t i = 0; i < thpool->threads_num; i++) {
		pthread_cond_signal(&thpool->tasks.cond);
        pthread_join(thpool->threads[i], NULL);
    }
    free(thpool->threads);
}

void init_task(Task * task, void (* init_func)(void *), void * init_arg)
{
    task->func = init_func;
    task->arg = init_arg;

    task->solved = 0;
    task->should_solve = 0;

    pthread_mutex_init(&task->mutex, NULL);
    pthread_cond_init(&task->cond, NULL);
}
