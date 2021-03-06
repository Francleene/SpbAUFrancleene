#include <cstdlib>
#include <cstdio>

#include "../include/my_vector.h"

MyVector::MyVector() : MyVector::MyVector(2) { }
MyVector::MyVector(std::size_t init_capacity) {
    _sz = 0;
    _cp = init_capacity > 0 ? init_capacity : 2;
    _data = (type *)malloc(_cp * sizeof(type));
}
MyVector::~MyVector() {
    free(_data);
}
    
void MyVector::set(std::size_t index, type value) {
    if (index < _sz) {
        _data[index] = value;
    }
}

type MyVector::get(std::size_t index) {
    if (index < _sz) {
        return _data[index];
    } else {
        return -1;
    }
}
    
std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}
    
void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity > _cp) {
        _data = (type *)realloc(_data, new_capacity * sizeof(type));
        _cp = new_capacity;
    }
}

void MyVector::resize(std::size_t new_size) {
    if (new_size > _cp) {
        std::size_t new_cap = _cp;
        while (new_cap < new_size) {
            new_cap *= 2;
        }
        reserve(new_cap);
    }
    
    for (std::size_t i = _sz; i < new_size; i++) {
        _data[i] = 0;
    }
    
    _sz = new_size;
}
    
void MyVector::push_back(type value) {
    if (_sz == _cp) {
        reserve(2 * _sz);
    }
    _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, type value) {
    if (index > _sz) {
        resize(index + 1);
        _data[index] = value;
        return;
    }
    
    if (index == _sz) {
        push_back(value);
        return;
    }
    
    if (_sz >= _cp) {
        reserve(2 * _sz);
    }
    
    for (std::size_t i = _sz; i > index; i--) {
        _data[i] = _data[i - 1];
    }
    _sz++;
    _data[index] = value;
}

void MyVector::erase(std::size_t index) {
    if (index >= _sz) return;
    if (_sz == 0) return;
    
    _sz--;
    for (std::size_t i = index; i < _sz; i++) {
        _data[i] = _data[i + 1];
    }
}
