//
// Created by Александр on 17.03.17.
//

#ifndef LAB_14_MATRIX_H
#define LAB_14_MATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class MatrixException {
public:
    MatrixException(const std::string &message);
    MatrixException(const MatrixException &other) = default;
    MatrixException &operator =(const MatrixException &other) = default;
    ~MatrixException() = default;

    const std::string &what() const;
private:
    std::string message_;
};

class Matrix {
public:
    Matrix();
    Matrix(size_t num_rows, size_t num_cols);
    Matrix(const Matrix &other) = default; // FIX IT
    Matrix &operator =(const Matrix &other) = default; // FIX IT
    ~Matrix() = default;

    Matrix &operator +=(const Matrix &other);
    Matrix &operator *=(const Matrix &other);

    int at(size_t i, size_t j) const; // get mtx[i][j] with check
    int get(size_t i, size_t j) const; // without check

    size_t get_height() const;
    size_t get_width() const;

    void resize(size_t new_height, size_t new_width);
    void fill_from_file(std::ifstream &is);
private:
    std::vector<std::vector<int>> data_;
    size_t height_, width_;

};

std::ifstream &operator>>(std::ifstream &is, Matrix &mtx);
std::ostream &operator<<(std::ostream &os, const Matrix &mtx);

class MatrixInterpreter {
public:
    MatrixInterpreter();
    MatrixInterpreter(const MatrixInterpreter &other) = delete;
    MatrixInterpreter &operator =(const MatrixInterpreter &other) = delete;
    ~MatrixInterpreter() = default;

    void load();
    void print() const;

    void add();
    void mul();
    void elem() const;
private:
    size_t reg_str_to_num(const std::string &reg_num_str) const;
    size_t get_reg_num() const;
    void load_at(size_t reg_num, const std::string &file_name);
private:
    std::vector<Matrix> data_;
};

#endif //LAB_14_MATRIX_H
