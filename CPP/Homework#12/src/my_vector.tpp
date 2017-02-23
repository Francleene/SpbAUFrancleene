#ifndef _MY_VECTOR_TPP_
#define _MY_VECTOR_TPP_

#include "../include/my_vector.hpp"

template <class T>
my_vector<T>::my_vector() {
    size_     = 0;
    capacity_ = 0;
    array_    = nullptr;
}

template <class T>
my_vector<T>::my_vector(size_t n) {
    size_     = n;
    capacity_ = nearest_pow2(n);
    array_    = ::operator new(capacity_ * sizeof(T));
}

template <class T>
my_vector<T>::my_vector(const my_vector &other) {
    this->size_     = other.size_;
    this->capacity_ = nearest_pow2(size_);
    this->array     = ::operator new(capacity_ * sizeof(T));

    for (size_t i = 0; i < size_; i++) {
        new_obj(this->array_, i, other.array_[i]);
    }
}

template <class T>
my_vector<T> &my_vector<T>::operator=(const my_vector &other) {
    my_vector tmp(other);

    std::swap(this->size_,     tmp.size_);
    std::swap(this->capacity_, tmp.capacity_);
    std::swap(this->array_,    tmp.array_);

    return *this;
}

template <class T>
my_vector<T>::~my_vector() {
    clear();
    if (array_) { delete[] (char *)array_; }
}

template <class T>
size_t my_vector<T>::size() const {
    return size_;
}

template <class T>
size_t my_vector<T>::capacity() const {
    return capacity_;
}

template <class T>
bool my_vector<T>::empty() const {
    return size_ == 0;
}

template <class T>
void my_vector<T>::resize(size_t n) {
    if (n < size_)  { smaller_resize(n); }
    if (n == size_) {            return; }
    if (size_ < n)  { greater_resize(n); }
}

template <class T>
void my_vector<T>::reserve(size_t n) {
    if (n <= capacity_) { return; }

    size_t new_capacity = nearest_pow2(n);
    T *new_array        = (T *)new char[n * sizeof(T)];
    capacity_           = new_capacity;

    for (size_t i = 0; i < size_; i++) {
        new_obj(new_array, i, array_[i]);
        del_obj(array_, i);
    }

    if (array_) { delete[] (char *)array_; }
    array_ = new_array;
}

template <class T>
T &my_vector<T>::operator[](size_t index) {
    return array_[index];
}

template <class T>
const T &my_vector<T>::operator[](size_t index) const {
    return array_[index];
}

template <class T>
void my_vector<T>::push_back(T &obj) {
    if (size_ == capacity_) { reserve(size_ + 1); }

    new_obj(array_, size_, obj);
    size_++;
}

template <class T>
void my_vector<T>::pop_back() {
    if (size_ == 0) { return; }

    del_obj(array_, size_ - 1);
    size_--;
}

template <class T>
void my_vector<T>::clear() {
    resize(0);
}

template <class T>
void my_vector<T>::smaller_resize(size_t n) {
    for (; n < size_; size_--) {
        array_[size_ - 1].~T();
    }
}

template <class T>
void my_vector<T>::greater_resize(size_t n) {
    for (; size_ < n; size_++) {
        new (array_ + size_) T();
    }
}

template <class T>
size_t my_vector<T>::nearest_pow2(size_t n) const {
    size_t ans = 1;
    while (ans < capacity_) {
        ans <<= 1;
    }

    return ans;
}

template <class T>
void my_vector<T>::new_obj(T *array, size_t pos) {
    new (array + pos) T();
}

template <class T>
void my_vector<T>::new_obj(T *array, size_t pos, T &obj) {
    new (array + pos) T(obj);
}

template <class T>
void my_vector<T>::del_obj(T *array, size_t pos) {
    array[pos].~T();
}

#endif // _MY_VECTOR_TPP_