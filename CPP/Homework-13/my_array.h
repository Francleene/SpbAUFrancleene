//
// Created by Александр on 08.03.17.
//

#ifndef MY_ARRAY_MY_ARRAY_H
#define MY_ARRAY_MY_ARRAY_H

#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define ASSERT(condition, message) \
if (!(condition)) {        \
std::cerr << message;  \
std::exit(1);               \
}

#define GET_CHAR_INDEX(number) (number >> 3)
#define GET_CHAR_SIZE(number) (((number - 1) >> 3) + 1)
#define MAX_CHAR (255)
#define MIN_CHAR (0)

template<typename T, size_t N>
class my_array_base {
public:
    bool empty() const;
    size_t size() const;
};

template<typename T, size_t N>
bool my_array_base<T, N>::empty() const {
    return false;
}

template<typename T, size_t N>
size_t my_array_base<T, N>::size() const {
    return N;
}

template<typename T, size_t N>
class my_array : public my_array_base<T, N> {
public:
    my_array();
    my_array(const my_array<T, N> &other);
    my_array<T, N> &operator=(const my_array<T, N> &other);
    ~my_array();
    
    T &at(size_t index);
    const T &at(size_t index) const;
    
    T &operator [] (size_t index);
    const T &operator [] (size_t index) const;
    
    void fill(const T &value);
private:
    T array_[N];
};

template<typename T, size_t N>
my_array<T, N>::my_array() { }

template<typename T, size_t N>
my_array<T, N>::my_array(const my_array<T, N> &other) {
    for (size_t i = 0; i < N; i++) {
        this->array_[i] = other.array_[i];
    }
}

template<typename T, size_t N>
my_array<T, N> &my_array<T, N>::operator=(const my_array<T, N> &other) {
    for (size_t i = 0; i < N; i++) {
        this->array_[i] = other.array_[i];
    }
    return *this;
}

template<typename T, size_t N>
my_array<T, N>::~my_array() { }

template<typename T, size_t N>
T &my_array<T, N>::at(size_t index) {
    ASSERT(index < N, "Index's out of range\n");
    return array_[index];
}

template<typename T, size_t N>
const T &my_array<T, N>::at(size_t index) const {
    ASSERT(index < N, "Index's out of range\n");
    return array_[index];
}

template<typename T, size_t N>
T &my_array<T, N>::operator [] (size_t index) {
    return array_[index];
}

template<typename T, size_t N>
const T &my_array<T, N>::operator [] (size_t index) const {
    return array_[index];
}

template<typename T, size_t N>
void my_array<T, N>::fill(const T &value) {
    for (size_t i = 0; i < N; i++) {
        array_[i] = value;
    }
}

template<size_t N>
class my_array<bool, N> : public my_array_base<bool, N> {
private:
    class blob {
    public:
        blob(char *block, size_t pos);
        
        blob &operator = (const blob &other);
        blob &operator = (const bool &other);
        
        operator bool() const;
    private:
        void set_zero();
        void set_one();
    private:
        char *block_;
        size_t pos_;
    };
public:
    my_array();
    my_array(const my_array<bool, N> &other);
    my_array<bool, N> &operator = (const my_array<bool, N> &other);
    ~my_array();
    
    blob at(size_t index);
    bool at(size_t index) const;
    
    blob operator [] (size_t index);
    bool operator [] (size_t index) const;
    
    void fill(bool is_true);
private:
    bool get_value(size_t index) const;
private:
    char array_[GET_CHAR_SIZE(N)];
};

template<size_t N>
my_array<bool, N>::my_array() {
    fill(false);
}

template<size_t N>
my_array<bool, N>::my_array(const my_array<bool, N> &other) {
    for (size_t i = 0; i < GET_CHAR_SIZE(N); i++) {
        this->array_[i] = other.array_[i];
    }
}

template<size_t N>
my_array<bool, N> &my_array<bool, N>::operator=(const my_array<bool, N> &other) {
    for (size_t i = 0; i < GET_CHAR_SIZE(N); i++) {
        this->array_[i] = other.array_[i];
    }
}

template<size_t N>
my_array<bool, N>::~my_array() {}

template<size_t N>
typename my_array<bool, N>::blob my_array<bool, N>::at(size_t index) {
    ASSERT(index < N, "Index's out of range\n");
    
    return blob(array_ + GET_CHAR_INDEX(index), index % 8);
}

template<size_t N>
bool my_array<bool, N>::at(size_t index) const {
    ASSERT(index < N, "Index's out of range\n");
    
    return get_value(index);
}

template<size_t N>
typename my_array<bool, N>::blob my_array<bool, N>::operator [] (size_t index) {
    return blob(array_ + GET_CHAR_INDEX(index), index % 8);
}

template<size_t N>
bool my_array<bool, N>::operator [] (size_t index) const {
    return get_value(index);
}

template<size_t N>
void my_array<bool, N>::fill(bool is_true) {
    char filling = is_true ? MAX_CHAR : MIN_CHAR;
    
    for (size_t i = 0; i < GET_CHAR_SIZE(N); i++) {
        array_[i] = filling;
    }
}

template<size_t N>
bool my_array<bool, N>::get_value(size_t index) const {
    size_t block_index = index % 8;
    return array_[GET_CHAR_INDEX(index)] & (1 << block_index);
}

template<size_t N>
my_array<bool, N>::blob::blob(char *block, size_t pos)
: block_(block),
pos_(pos) {}

template<size_t N>
typename my_array<bool, N>::blob &my_array<bool, N>::blob::operator = (const blob &other) {
    bool(other) ? set_one() : set_zero();
    return *this;
}

template<size_t N>
typename my_array<bool, N>::blob &my_array<bool, N>::blob::operator = (const bool &other) {
    other ? set_one() : set_zero();
    return *this;
}

template<size_t N>
my_array<bool, N>::blob::operator bool() const {
    return *block_ & (1 << pos_);
}

template<size_t N>
void my_array<bool, N>::blob::set_zero() {
    *block_ &= ~(1 << pos_);
}

template<size_t N>
void my_array<bool, N>::blob::set_one() {
    *block_ |= (1 << pos_);
}

#endif //MY_ARRAY_MY_ARRAY_H
