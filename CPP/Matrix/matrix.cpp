//
// Created by Александр on 18.11.16.
//

#include "matrix.h"

Matrix::Matrix(size_t new_height, size_t new_width): height(new_height), width(new_width) {
    arr = new int*[height];
    for (size_t i = 0; i < height; i++) {
        arr[i] = new int[width]();
    }
}

Matrix::Matrix(const Matrix & obj): height(obj.height), width(obj.width) {
    arr = new int*[height];
    for (size_t i = 0; i < height; i++) {
        arr[i] = new int[width];
    }

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            arr[i][j] = obj.arr[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (size_t i = 0; i < height; i++) {
        delete [] arr[i];
    }
    delete [] arr;
}

Matrix & Matrix::operator=(const Matrix & obj) {
    if (this == &obj) return * this;

    Matrix tmp(obj);

    std::swap(this->width, tmp.width);
    std::swap(this->height, tmp.height);
    std::swap(this->arr, tmp.arr);

    return *this;
}

const Matrix Matrix::operator+(const Matrix &obj) const {
    Matrix add_matrix(*this);

    add_matrix += obj;

    return add_matrix;
}

const Matrix & Matrix::operator+=(const Matrix &obj) {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            this->arr[i][j] += obj.arr[i][j];
        }
    }
    return *this;
}

void Matrix::print(FILE * file) const {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            fprintf(file, "%d ", arr[i][j]);
        }
        fprintf(file, "\n");
    }
}

const Matrix Matrix::operator-(const Matrix &obj) const {
    Matrix sub_matrix(obj);

    sub_matrix -= *this;

    return sub_matrix;
}

const Matrix Matrix::operator*(const Matrix &obj) const {
    Matrix mul_matrix(*this);

    mul_matrix *= obj;

    return mul_matrix;
}

const Matrix & Matrix::operator-=(const Matrix & obj) {
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            this->arr[i][j] -= obj.arr[i][j];
        }
    }
    return *this;
}

const Matrix &Matrix::operator*=(const Matrix &obj) {
    Matrix mul_matrix(this->height, obj.width);

    for (size_t i = 0; i < this->height; i++) {
        for (size_t j = 0; j < obj.width; j++) {
            for (size_t t = 0; t < this->width; t++) {
                mul_matrix.arr[i][j] += this->arr[i][t] * obj.arr[t][j];
            }
        }
    }

    std::swap(this->arr, mul_matrix.arr);
    std::swap(this->height, mul_matrix.height);
    std::swap(this->width, mul_matrix.width);

    return *this;
}

bool Matrix::operator==(const Matrix & obj) const {
    if (this->height != obj.height) return false;
    if (this->width != obj.width) return false;

    for (size_t i = 0; i < this->height; i++) {
        for (size_t j = 0; j < this->width; j++) {
            if (this->arr[i][j] != obj.arr[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix & obj) const {
    return !(*this == obj);
}

size_t Matrix::get_rows() const {
    return height;
}

size_t Matrix::get_cols() const {
    return width;
}

void Matrix::set(size_t row, size_t column, int value) {
    if (row < height && column < width) {
        arr[row][column] = value;
    }
}

int Matrix::get(size_t row, size_t column) const {
    if (row < height && column < width) {
        return arr[row][column];
    }
    return 0;
}
