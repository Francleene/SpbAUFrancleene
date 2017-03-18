//
// Created by Александр on 17.03.17.
//

#include "matrix.h"

MatrixException::MatrixException(const std::string &message)
        : message_(message) { }

const std::string &MatrixException::what() const {
    return message_;
}

Matrix::Matrix() : height_(0), width_(0) { }

size_t Matrix::get_height() const {
    return height_;
}

size_t Matrix::get_width() const {
    return width_;
}

void Matrix::resize(size_t new_height, size_t new_width) {
    height_ = new_height;
    width_  = new_width;

    data_.resize(new_height);
    for (size_t i = 0; i < new_height; ++i) {
        data_[i].resize(new_width);
    }
}

void Matrix::fill_from_file(std::ifstream &is) {
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            is >> data_[i][j];
        }
    }
}



int Matrix::at(size_t i, size_t j) const {
    if (height_ <= i || width_ <= j) {
        throw MatrixException("ACCESS: bad index.");
    }

    return data_[i][j];
}

int Matrix::get(size_t i, size_t j) const {
    return data_[i][j];
}

Matrix &Matrix::operator+=(const Matrix &other) {
    if (this->height_ != other.height_ ||
        this->width_  != other.width_) {
        throw MatrixException("ADD: dimensions do not match.");
    }

    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            data_[i][j] += other.get(i, j);
        }
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    if (this->width_ != other.height_) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }

    Matrix mul_matrix(this->height_, other.width_);
    for (size_t i = 0; i < mul_matrix.height_; ++i) {
        for (size_t j = 0; j < mul_matrix.width_; ++j) {
            mul_matrix.data_[i][j] = 0;
            for (size_t t = 0; t < this->width_; t++) {
                mul_matrix.data_[i][j] += this->data_[i][t] * other.data_[t][j];
            }
        }
    }

    std::swap(this->data_,   mul_matrix.data_);
    std::swap(this->height_, mul_matrix.height_);
    std::swap(this->width_,  mul_matrix.width_);

    return *this;
}

Matrix::Matrix(size_t num_rows, size_t num_cols)
        : height_(num_rows),
          width_(num_cols) {

    resize(height_, width_);
}

std::ifstream &operator>>(std::ifstream &is, Matrix &mtx) {
    size_t new_height, new_width;
    is >> new_height >> new_width;

    mtx.resize(new_height, new_width);
    mtx.fill_from_file(is);

    return is;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mtx) {
    for (size_t i = 0; i < mtx.get_height(); ++i) {
        for (size_t j = 0; j < mtx.get_width(); ++j) {
            os << mtx.get(i, j) << ' ';
        }
        os << std::endl;
    }

    return os;
}

MatrixInterpreter::MatrixInterpreter() {
    data_.resize(10);
}

void MatrixInterpreter::load() {
    size_t reg_num = get_reg_num();

    std::string file_name;
    std::cin >> file_name;

    load_at(reg_num, file_name);
}

size_t MatrixInterpreter::reg_str_to_num(const std::string &reg_num_str) const {
    return size_t(reg_num_str[1] - '0');
}

size_t MatrixInterpreter::get_reg_num() const {
    std::string reg_str;
    std::cin >> reg_str;

    return reg_str_to_num(reg_str);
}

void MatrixInterpreter::load_at(size_t reg_num, const std::string &file_name) {
    std::ifstream fin(file_name);

    fin >> data_[reg_num];

    fin.close();
}

void MatrixInterpreter::print() const {
    size_t reg_num = get_reg_num();

    std::cout << data_[reg_num];
}

void MatrixInterpreter::add() {
    try {
        size_t reg_num_1 = get_reg_num(),
               reg_num_2 = get_reg_num();

        data_[reg_num_1] += data_[reg_num_2];
    } catch (MatrixException &error) {
        std::cout << error.what() << std::endl;
    }
}

void MatrixInterpreter::mul() {
    try {
        size_t reg_num_1 = get_reg_num(),
               reg_num_2 = get_reg_num();

        data_[reg_num_1] *= data_[reg_num_2];
    } catch (MatrixException &error) {
        std::cout << error.what() << std::endl;
    }
}

void MatrixInterpreter::elem() const {
    try {
        size_t reg_num = get_reg_num();

        int i, j;
        std::cin >> i >> j;

        std::cout << data_[reg_num].at(size_t(i), size_t(j)) << std::endl;
    } catch (MatrixException &error) {
        std::cout << error.what() << std::endl;
    }
}