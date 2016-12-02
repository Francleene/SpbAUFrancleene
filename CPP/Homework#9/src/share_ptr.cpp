#include <algorithm>

#include <algorithm>

#include "shared_ptr.h"

shared_ptr::shared_ptr(Matrix *obj) {
    storage_ = new Storage(obj);
}

shared_ptr::shared_ptr(const shared_ptr &other) {
    storage_ = other.storage_;
    storage_->incr();
}

shared_ptr::~shared_ptr() {
    storage_->decr();
    if (storage_->getCounter() == 0) {
        delete storage_;
    }
}

shared_ptr &shared_ptr::operator=(const shared_ptr &other) {
    shared_ptr tmp(other);
    std::swap(storage_, tmp.storage_);
    return *this;
}

Matrix *shared_ptr::ptr() const {
    return storage_->getObject();
}

bool shared_ptr::isNull() const {
    return storage_->getObject() == NULL;
}

Matrix *shared_ptr::operator->() const {
    return storage_->getObject();
}

Matrix &shared_ptr::operator*() const {
    return *(storage_->getObject());
}

void shared_ptr::reset(Matrix *obj) {
    shared_ptr tmp(obj);
    std::swap(storage_, tmp.storage_);
}

shared_ptr::Storage::Storage(Matrix * mtx) {
    data_ = mtx;
    ref_count_ = 1;
}

shared_ptr::Storage::~Storage() {
    if (data_) {
        delete data_;
    }
}

void shared_ptr::Storage::incr() {
    ref_count_ += 1;
}

void shared_ptr::Storage::decr() {
    ref_count_ -= 1;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

Matrix *shared_ptr::Storage::getObject() const {
    return data_;
}
