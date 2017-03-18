#ifndef _TEST_FUNCTION_TPP_
#define _TEST_FUNCTION_TPP_

#include <iostream>

#include "../include/my_vector.hpp"
#include "../include/test_function.hpp"

#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__);

void check(bool expr, const char *func, const char *filename, size_t line) {
	if (!expr) {	
		std::cout << "This is an error in function: " << func 
			 	  << "in file: " << filename 
			  	  << "on line: " << line
			      << std::endl;
	}
}

template <class T>
void test_my_vector_constructors_operators() {
	my_vector<T> *ptr = new my_vector<T>;

	DO_CHECK(ptr->size() == 0);
	DO_CHECK(ptr->capacity() == 0);

	delete ptr;

	my_vector<T> parent(5);
	DO_CHECK(parent.size() == 5);
	DO_CHECK(parent.capacity() == 8);
	
	my_vector<T> child(parent);
	DO_CHECK(child.size() == 5);
	DO_CHECK(child.capacity() == 8);
	
	my_vector<T> lover(4);
	DO_CHECK(lover.size() == 4);
	DO_CHECK(lover.capacity() == 4);

	lover = parent;
	DO_CHECK(lover.size() == 5);
	DO_CHECK(lover.capacity() == 8);
}

template <class T>
void test_my_vector_size(T x1, T x2) {
	my_vector<T> vector;
	T x3, x4, x5;

	vector.push_back(x1);
	DO_CHECK(vector.size() == 1);

	vector.push_back(x2);
	vector.push_back(x3);
	vector.push_back(x4);
	vector.push_back(x5);
	DO_CHECK(vector.size() == 5);

	vector.pop_back();
	vector.pop_back();
	DO_CHECK(vector.size() == 3);

	vector.clear();
	DO_CHECK(vector.size() == 0);

	vector.resize(6);
	DO_CHECK(vector.size() == 6);

	vector.reserve(9);
	DO_CHECK(vector.size() == 6);
}

template <class T>
void test_my_vector_capacity(T x1, T x2) {
	my_vector<T> vector;
	T x3, x4, x5;

	DO_CHECK(vector.capacity() == 0);

	vector.push_back(x1);
	DO_CHECK(vector.capacity() == 1);

	vector.push_back(x2);
	DO_CHECK(vector.capacity() == 2);

	vector.push_back(x3);
	vector.push_back(x4);
	vector.push_back(x5);
	DO_CHECK(vector.capacity() == 8);

	vector.pop_back();
	DO_CHECK(vector.capacity() == 8);

	vector.pop_back();
	DO_CHECK(vector.capacity() == 8);

	vector.resize(6);
	DO_CHECK(vector.capacity() == 8);

	vector.resize(9);
	DO_CHECK(vector.capacity() == 16);

	vector.reserve(14);
	DO_CHECK(vector.capacity() == 16);

	vector.reserve(33);
	DO_CHECK(vector.capacity() == 64);

	vector.clear();
	DO_CHECK(vector.capacity() == 64);
}

template <class T>
void test_my_vector_empty(T x1, T x2) {
	my_vector<T> vector;
	T x3;

	DO_CHECK(vector.empty() == true);

	vector.push_back(x1);
	DO_CHECK(vector.empty() == false);

	vector.pop_back();
	DO_CHECK(vector.empty() == true);

	vector.push_back(x1);
	vector.push_back(x2);
	vector.push_back(x3);
	DO_CHECK(vector.empty() == false);

	vector.clear();
	DO_CHECK(vector.empty() == true);

	vector.reserve(5);
	DO_CHECK(vector.empty() == true);

	vector.resize(5);
	DO_CHECK(vector.empty() == false);
}

template <class T>
void test_my_vector_resize(T x1, T x2) {
	my_vector<T> vector;

	vector.resize(1);
	DO_CHECK(vector.size() == 1);
	DO_CHECK(vector.capacity() == 1);

	vector.resize(2);
	DO_CHECK(vector.size() == 2);
	DO_CHECK(vector.capacity() == 2);

	vector.resize(3);
	DO_CHECK(vector.size() == 3);
	DO_CHECK(vector.capacity() == 4);

	vector.resize(3);
	DO_CHECK(vector.size() == 3);
	DO_CHECK(vector.capacity() == 4);

	vector.push_back(x1);
	vector.resize(4);
	DO_CHECK(vector.size() == 4);
	DO_CHECK(vector.capacity() == 4);

	vector.push_back(x2);
	vector.resize(5);
	DO_CHECK(vector.size() == 5);
	DO_CHECK(vector.capacity() == 8);

	vector.pop_back();
	vector.resize(4);
	DO_CHECK(vector.size() == 4);
	DO_CHECK(vector.capacity() == 8);

	vector.resize(9);
	DO_CHECK(vector.size() == 9);
	DO_CHECK(vector.capacity() == 16);

	vector.resize(4);
	DO_CHECK(vector.size() == 4);
	DO_CHECK(vector.capacity() == 16);

	vector.resize(3);
	DO_CHECK(vector.size() == 3);
	DO_CHECK(vector.capacity() == 16);

	vector.resize(0);
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 16);
}

template <class T>
void test_my_vector_reserve(T x1, T x2) {
	my_vector<T> vector;
	T x3;

	vector.reserve(0);
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 0);

	vector.reserve(1);
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 1);

	vector.push_back(x1);
	vector.push_back(x2);
	vector.push_back(x3);
	vector.reserve(3);
	DO_CHECK(vector.size() == 3);
	DO_CHECK(vector.capacity() == 4);

	vector.pop_back();
	vector.reserve(2);
	DO_CHECK(vector.size() == 2);
	DO_CHECK(vector.capacity() == 4);

	vector.reserve(5);
	DO_CHECK(vector.size() == 2);
	DO_CHECK(vector.capacity() == 8);

	vector.reserve(8);
	DO_CHECK(vector.size() == 2);
	DO_CHECK(vector.capacity() == 8);
	
	vector.reserve(3);
	DO_CHECK(vector.size() == 2);
	DO_CHECK(vector.capacity() == 8);
}

template <class T>
void test_my_vector_push_pop_back(T x1, T x2) {
	my_vector<T> vector;
	T x3, x4, x5;
	
	vector.push_back(x1);
	DO_CHECK(vector.size() == 1);
	DO_CHECK(vector.capacity() == 1);

	vector.pop_back();
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 1);

	vector.push_back(x1);
	vector.push_back(x2);
	vector.push_back(x3);
	DO_CHECK(vector.size() == 3);
	DO_CHECK(vector.capacity() == 4);

	vector.push_back(x4);
	DO_CHECK(vector.size() == 4);
	DO_CHECK(vector.capacity() == 4);
	
	vector.push_back(x5);
	DO_CHECK(vector.size() == 5);
	DO_CHECK(vector.capacity() == 8);

	vector.pop_back();
	DO_CHECK(vector.size() == 4);
	DO_CHECK(vector.capacity() == 8);

	vector.pop_back();
	DO_CHECK(vector.size() == 3);
	DO_CHECK(vector.capacity() == 8);
}

template <class T>
void test_my_vector_clear(T x1, T x2) {
	my_vector<T> vector;

	vector.clear();
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 0);
	
	vector.push_back(x1);
	vector.push_back(x2);
	vector.clear();
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 2);

	vector.push_back(x1);
	vector.pop_back();
	vector.clear();
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 2);

	vector.resize(5);
	vector.clear();
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 8);

	vector.reserve(17);
	vector.clear();
	DO_CHECK(vector.size() == 0);
	DO_CHECK(vector.capacity() == 32);
}

template<class T>
void test_my_vector(T x1, T x2) {
	test_my_vector_constructors_operators<T>();
	test_my_vector_size<T>(x1, x2);
	test_my_vector_capacity<T>(x1, x2);
	//test_my_vector_empty<T>(x1, x2);
	//test_my_vector_resize<T>(x1, x2);
	//test_my_vector_reserve<T>(x1, x2);
	//test_my_vector_push_pop_back<T>(x1, x2);
	//test_my_vector_clear<T>(x1, x2);
}

#endif // _TEST_FUNCTION_TPP
