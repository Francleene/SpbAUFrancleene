//
// Created by Александр on 18.11.16.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

class Matrix {
private:
    int ** arr;
    size_t width, height;
public:
    Matrix(size_t height, size_t width);
    Matrix(const Matrix & obj);

    Matrix & operator=(const Matrix & obj);

    Matrix & operator+=(const Matrix & obj);
    Matrix & operator-=(const Matrix & obj);
    Matrix & operator*=(const Matrix & obj);

    Matrix operator+(const Matrix & obj);
    Matrix operator-(const Matrix & obj);
    Matrix operator*(const Matrix & obj);

    bool operator==(const Matrix & obj);
    bool operator!=(const Matrix & obj);

    void set(size_t row, size_t column, int value);
    int get(size_t row, size_t column);

    size_t get_rows();
    size_t get_cols();

    void print(FILE * file);

    ~Matrix();
};


#endif //MATRIX_MATRIX_H
