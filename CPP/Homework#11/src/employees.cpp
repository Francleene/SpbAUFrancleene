#include <iostream>
#include <fstream>
#include <cstring>
#include <utility>

#include "../include/employees.hpp"

// read-write operators
std::istream &operator>>(std::istream &is, Employee &obj);
std::ostream &operator<<(std::ostream &os, Employee &obj);
std::ifstream &operator>>(std::ifstream &is, Employee &obj);
std::ofstream &operator<<(std::ofstream &os, Employee &obj);

// static utilities
static int get_cstring_len_binary(std::ifstream &is);
static char *double_capacity(char *old_cstring, size_t old_capacity);
static bool can_be_in_name(char ch);

// static read function
static char *  read_cstring_binary(std::ifstream &is);
       char *  read_cstring_terminal(std::istream &is); // !! not static !!
static int32_t read_int32_t_binary(std::ifstream &is);
static bool    read_bool_binary(std::ifstream &is);

// static write function
static void write_cstring_binary(std::ofstream &os, const char *cstring);
static void write_int32_t_binary(std::ofstream &os, int32_t output);
static void write_bool_binary(std::ofstream &os, bool output);

std::istream &operator>>(std::istream &is, Employee &obj) {
    obj.read_terminal(is);
    return is;
}

std::ostream &operator<<(std::ostream &os, Employee &obj) {
    obj.write_terminal(os);
    return os;
}

std::ifstream &operator>>(std::ifstream &is, Employee &obj) {
    obj.read_binary(is);
    return is;
}

std::ofstream &operator<<(std::ofstream &os, Employee &obj) {
    obj.write_binary(os);
    return os;
}

// !! with 0 symbol !!
static int get_cstring_len_binary(std::ifstream &is) {
    int len = 0;
    char ch;

    do {
        len++;
        is.read(&ch, 1);
    } while (ch);

    is.seekg(-len, is.cur);
    return len;
}

static char *double_capacity(char *old_cstring, size_t old_capacity) {
    size_t new_capacity = old_capacity * 2;

    char *new_cstring = new char[new_capacity];
    memcpy(new_cstring, old_cstring, old_capacity * sizeof(char));

    delete[] old_cstring;
    return new_cstring;
}

static bool can_be_in_name(char ch) {
    return ('a' <= ch && ch <= 'z') ||
           ('A' <= ch && ch <= 'Z') ||
           ('0' <= ch && ch <= '9') ||
            ch == '.';
}

static char *read_cstring_binary(std::ifstream &is) {
    int len_name = get_cstring_len_binary(is);
    char *cstring= new char[len_name];

    is.read(cstring, len_name);
    return cstring;
}

char *read_cstring_terminal(std::istream &is) {
    size_t size = 0, capacity = 2;
    char *cstring = new char[capacity];



    char ch;
    do {
        is.get(ch);
    } while (!can_be_in_name(ch));

    while (can_be_in_name(ch)) {
        if (size == capacity) {
            cstring = double_capacity(cstring, capacity);
            capacity *= 2;
        }

        cstring[size++] = ch;
        is.get(ch);
    }

    return cstring;
}

static int32_t read_int32_t_binary(std::ifstream &is) {
    int32_t input;
    is.read((char *)&input, sizeof(int32_t));
    return input;
}

static bool read_bool_binary(std::ifstream &is) {
    bool input;
    is.read((char *)&input, sizeof(bool));
    return input;
}

static void write_cstring_binary(std::ofstream &os, const char *cstring) {
    size_t len_name = strlen(cstring) + 1;
    os.write(cstring, len_name);
}

static void write_int32_t_binary(std::ofstream &os, int32_t output) {
    os.write((char *)&output, sizeof(int32_t));
}

static void write_bool_binary(std::ofstream &os, bool output) {
    os.write((char *)&output, sizeof(bool));
}

Developer::Developer() {
    _name = nullptr;
}

Developer::Developer(const Developer &other) {
    this->_base_salary = other._base_salary;
    this->_has_bonus   = other._has_bonus;

    size_t name_len = strlen(other._name);

    this->_name = new char[name_len + 1];
    strcpy(this->_name, other._name);
}

Developer &Developer::operator=(const Developer &other) {
    Developer tmp_dev(other);

    std::swap(this->_base_salary, tmp_dev._base_salary);
    std::swap(this->_has_bonus,   tmp_dev._has_bonus);
    std::swap(this->_name,        tmp_dev._name);

    return *this;
}

Developer::~Developer() {
    if (this->_name) {
        delete[] this->_name;
    }
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

void Developer::read_binary(std::ifstream &is) {
    if (_name) { delete[] _name; }
    _name = read_cstring_binary(is);

    _base_salary = read_int32_t_binary(is);
    _has_bonus   = read_bool_binary(is);
}

void Developer::write_binary(std::ofstream &os) const {
    write_int32_t_binary(os, 1);
    write_cstring_binary(os, _name);
    write_int32_t_binary(os, _base_salary);
    write_bool_binary(os, _has_bonus);
}

void Developer::read_terminal(std::istream &is) {
    if (_name) { delete[] _name; }
    _name = read_cstring_terminal(is);

    is >> _base_salary >> _has_bonus;
}

void Developer::write_terminal(std::ostream &os) const {
    os << "Developer" << std::endl;
    os << "Name: " << _name << std::endl;
    os << "Base Salary: " << _base_salary << std::endl;
    os << "Has bonus: " << (_has_bonus ? '+' : '-') << std::endl;
}

SalesManager::SalesManager() {
    _name = nullptr;
}

SalesManager::SalesManager(const SalesManager &other) {
    this->_base_salary = other._base_salary;
    this->_sold_nm     = other._sold_nm;
    this->_price       = other._price;

    size_t name_len = strlen(other._name);

    this->_name = new char[name_len + 1];
    strcpy(this->_name, other._name);
}

SalesManager &SalesManager::operator=(const SalesManager &other) {
    SalesManager tmp(other);

    std::swap(this->_base_salary, tmp._base_salary);
    std::swap(this->_sold_nm,     tmp._sold_nm);
    std::swap(this->_price,       tmp._price);
    std::swap(this->_name,        tmp._name);

    return *this;
}

SalesManager::~SalesManager() {
    if (_name) {
        delete[] _name;
    }
}

int SalesManager::salary() const {
    return (int)(_base_salary + _sold_nm * _price * 0.01);
}

void SalesManager::read_binary(std::ifstream &is) {
    if (_name) { delete[] _name; }
    _name = read_cstring_binary(is);

    _base_salary = read_int32_t_binary(is);
    _sold_nm     = read_int32_t_binary(is);
    _price       = read_int32_t_binary(is);
}

void SalesManager::write_binary(std::ofstream &os) const {
    write_int32_t_binary(os, 2);
    write_cstring_binary(os, _name);
    write_int32_t_binary(os, _base_salary);
    write_int32_t_binary(os, _sold_nm);
    write_int32_t_binary(os, _price);
}

void SalesManager::read_terminal(std::istream &is) {
    if (_name) { delete[] _name; }
    _name = read_cstring_terminal(is);

    is >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::write_terminal(std::ostream &os) const {
    os << "Sales Manager" << std::endl;
    os << "Name: " << _name << std::endl;
    os << "Base Salary: " << _base_salary << std::endl;
    os << "Sold items: " << _sold_nm << std::endl;
    os << "Item price: " << _price << std::endl;
}

EmployeesArray::EmployeesArray() {
    _size = 0;
    _capacity = 2;

    _employees = new Employee*[_capacity];
}

EmployeesArray::EmployeesArray(const EmployeesArray &other) {
    this->_size     = other._size;
    this->_capacity = other._capacity;

    _employees = new Employee*[_capacity];
    copy_employees(other);
}

EmployeesArray &EmployeesArray::operator=(const EmployeesArray &other) {
    EmployeesArray tmp(other);

    std::swap(this->_size,      tmp._size);
    std::swap(this->_capacity,  tmp._capacity);
    std::swap(this->_employees, tmp._employees);

    return *this;
}

EmployeesArray::~EmployeesArray() {
    delete[] _employees;
}

int EmployeesArray::total_salary() const {
    int32_t summ = 0;
    for (size_t i = 0; i < _size; i++) {
        summ += _employees[i]->salary();
    }
    return summ;
}

void EmployeesArray::add(Employee *e) {
    if (_size == _capacity) { double_capacity(); }

    _employees[_size++] = e;
}

void EmployeesArray::copy_employees(const EmployeesArray &other) {
    memcpy(this->_employees, other._employees, _size * sizeof(Employee *));
}

void EmployeesArray::double_capacity() {
    _capacity *= 2;

    Employee ** doubled_employees = new Employee*[_capacity];
    memcpy(doubled_employees, _employees, _size * sizeof(Employee *));

    delete[] _employees;
    _employees = doubled_employees;
}

std::istream &operator>>(std::istream &is, EmployeesArray &obj) {
    int32_t type;
    is >> type;

    Employee *new_worker;
    if (type == 1) { new_worker = new Developer;    }
    else           { new_worker = new SalesManager; }

    is >> *new_worker;
    obj.add(new_worker);

    return is;
}

std::ostream &operator<<(std::ostream &os, EmployeesArray &obj) {
    for (size_t i = 0; i < obj._size; i++) {
        os << i + 1 << ". " << *obj._employees[i];
    }

    os << "== Total salary: " << obj.total_salary() << std::endl;

    return os;
}

std::ifstream &operator>>(std::ifstream &is, EmployeesArray &obj) {
    int32_t type, num_worker = read_int32_t_binary(is);
    Employee *new_worker;

    for (size_t i = 0; i < num_worker; i++) {
        type = read_int32_t_binary(is);

        if (type == 1) { new_worker = new Developer; }
        else           { new_worker = new SalesManager; }

        is >> *new_worker;
        obj.add(new_worker);
    }
    return is;
}

std::ofstream &operator<<(std::ofstream &os, EmployeesArray &obj) {
    write_int32_t_binary(os, obj._size);

    for (size_t i = 0; i < obj._size; i++) {
        os << *obj._employees[i];
    }

    return os;
}
