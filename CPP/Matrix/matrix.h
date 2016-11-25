//
// Created by Александр on 18.11.16.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>

class Matrix {
private:
    int ** arr;
    size_t height, width;
public:
    Matrix(size_t height, size_t width);
    Matrix(const Matrix & obj);

    Matrix & operator=(const Matrix & obj);

    const Matrix & operator+=(const Matrix & obj);
    const Matrix & operator-=(const Matrix & obj);
    const Matrix & operator*=(const Matrix & obj);

    const Matrix operator+(const Matrix & obj) const;
    const Matrix operator-(const Matrix & obj) const;
    const Matrix operator*(const Matrix & obj) const;

    bool operator==(const Matrix & obj) const;
    bool operator!=(const Matrix & obj) const;

    void set(size_t row, size_t column, int value);
    int get(size_t row, size_t column) const;

    size_t get_rows() const;
    size_t get_cols() const;

    void print(FILE * file) const;

    ~Matrix();
};


#endif //MATRIX_MATRIX_H
