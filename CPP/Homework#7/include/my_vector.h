#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#define type int

#include <cstddef>

class MyVector {
public: // methods
    MyVector();
    MyVector(std::size_t init_capacity);
    ~MyVector();
    
    void set(std::size_t index, type value);
    type get(std::size_t index);
    
    std::size_t size();
    std::size_t capacity();
    
    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);
    
    void push_back(type value);
    void insert(std::size_t index, type value);
    void erase(std::size_t index);
private: // fields
    std::size_t _sz, _cp;
    type *_data;
};

#endif