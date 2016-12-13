#include <stdio.h>

#include "../include/thread_pool.h"

typedef struct TreeNode {
	int need_waiting;
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
    TreeNode * new_node = (TreeNode *)malloc(sizeof(TreeNode));
	
	new_node->need_waiting = 1;
    new_node->task = task;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = parent;

    return new_node;
}

void * pack_data(int * arr, int left, int right, int recur_depth, ThreadPool * thpool, TreeNode * root) {
    Data * data = (Data *)malloc(sizeof(Data));

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
		free(data);
		return;
	}

	if (data->recur_depth == 0 || right - left < 100) {
		qsort(arr + left, (size_t)(right - left), sizeof(int), &compar);
		free(data);
		return;
	}

	int value = arr[left + arr[left] % (right - left)];
	int first_begin, second_end;
	partition(arr, left, right, &second_end, &first_begin, value);

	Task * left_task = (Task *)malloc(sizeof(Task));

	data->root->left = make_tree_node(left_task, data->root);
	data->root->right = make_tree_node(data->root->task, data->root);

	void * left_ptr = pack_data(arr, left, first_begin + 1, data->recur_depth - 1, data->thpool, data->root->left);
	void * right_ptr = pack_data(arr, second_end, right, data->recur_depth - 1, data->thpool, data->root->right);

	init_task(left_task, quick_sort, left_ptr);

	thpool_submit(data->thpool, left_task);
	free(data);
	quick_sort(right_ptr);
}

void free_tree_node(TreeNode * node) {
    free(node->task);
	free(node);
}

void start_quick_sort(int * arr, int size, size_t threads_num, int recur_depth) {
    ThreadPool * thpool = (ThreadPool *)malloc(sizeof(ThreadPool));
    thpool_init(thpool, threads_num);

    Task * main_task = (Task *)malloc(sizeof(Task));
    TreeNode * root = make_tree_node(main_task, NULL);

    void * ptr = pack_data(arr, 0, size, recur_depth, thpool, root);
    init_task(main_task, quick_sort, ptr);

    thpool_submit(thpool, main_task);
    TreeNode * traveller = root;
    Task * waiting_task;

    while (traveller != NULL) {
		thpool_wait(traveller->task);
		traveller->need_waiting = 0;

        if (traveller->left != NULL) {
			if (traveller->left->need_waiting) {
				traveller = traveller->left;
			} else {
				free_tree_node(traveller->left);
				traveller->left = NULL;
			}
			continue;
		}

		if (traveller->right != NULL) {
			if (traveller->right->need_waiting) {
				traveller = traveller->right;
			} else {
				free(traveller->right);
				traveller->right = NULL;
			}
			continue;
		}
		
		traveller = traveller->parent;
    }

    free_tree_node(root);

    thpool_finit(thpool);
    free(thpool);
}

void check_sort(int * arr, int size) {
	for (int i = 1; i < size; i++) {
		if (arr[i] < arr[i - 1]) {
			printf("It doesn't work!\n");
			exit(1);
		}
	}
	printf("A great piece of luck! It works!\n");
}

int main(int argc, char ** argv) {
	int num_threads = atoi(argv[1]),
		size = atoi(argv[2]),
		rec_depth = atoi(argv[3]);

	srand(42);

    int	* arr = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
    	arr[i] = rand();
    }

    start_quick_sort(arr, size, num_threads, rec_depth);

    check_sort(arr, size);
	
    free(arr);
}
