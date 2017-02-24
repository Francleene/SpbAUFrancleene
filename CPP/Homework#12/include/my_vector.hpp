#ifndef _MY_VECTOR_HPP_
#define _MY_VECTOR_HPP_

#include <cstddef>
#include <iostream>
#include <fstream>

template <class T>
class my_vector {
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(const my_vector& other);
    ~my_vector();

    size_t size() const; // I
    size_t capacity() const; // I
    bool empty() const; // I

    void resize(size_t n); // I
    void reserve(size_t n); // I

    T &operator[](size_t index); // I
    const T &operator[](size_t index) const; // I

    void push_back(T &obj); // I
    void pop_back(); // I
    void clear(); // I

	template <class U>
	friend std::ostream &operator<<(std::ostream &os, const my_vector<U> &obj);
	template <class U>
	friend std::ofstream &operator<<(std::ofstream &os, const my_vector<U> &obj);

private:
    void smaller_resize(size_t n); // I
    void greater_resize(size_t n); // I

    size_t nearest_pow2(size_t n) const; // I

    void new_obj(T *array, size_t pos); // I
    void new_obj(T *array, size_t pos, T &obj); // I
    void del_obj(T *array, size_t pos); // I

private:
    size_t capacity_;
    size_t size_;
    T *array_;
};

#include "../src/my_vector.tpp"

#endif  // _MY_VECTOR_HPP_
