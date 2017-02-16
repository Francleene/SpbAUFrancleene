//
// Created by Александр on 13.02.17.
//

#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>

class Employee {
public:
    Employee() = default;
    Employee(const Employee &other) = default;
    virtual Employee& operator=(const Employee &other) = default;
    virtual ~Employee() = default;

    virtual int salary() const = 0;

    friend std::istream& operator>>(std::istream &is, Employee &obj);
    friend std::ostream& operator<<(std::ostream &os, Employee &obj);

    friend std::ifstream& operator>>(std::ifstream &ifs, Employee &obj);
    friend std::ofstream& operator<<(std::ofstream &ofs, Employee &obj);
protected:
    virtual void read_binary(std::ifstream &is) = 0;
    virtual void write_binary(std::ofstream &os) const = 0;

    virtual void read_terminal(std::istream &is) = 0;
    virtual void write_terminal(std::ostream &os) const = 0;
};

class Developer : public Employee {
public:
    Developer();
    Developer(const Developer &other);
    Developer& operator=(const Developer &other);
    ~Developer();

    int salary() const;
protected:
    void read_binary(std::ifstream &is);
    void write_binary(std::ofstream &of) const;

    void read_terminal(std::istream &is);
    void write_terminal(std::ostream &os) const;
private:
    char *_name;
    int32_t _base_salary;
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    SalesManager();
    SalesManager(const SalesManager &other);
    SalesManager &operator=(const SalesManager &other);
    ~SalesManager();

    int salary() const;
protected:
    void read_binary(std::ifstream &is);
    void write_binary(std::ofstream &os) const;

    void read_terminal(std::istream &is);
    void write_terminal(std::ostream &os) const;
private:
    char *_name;
    int32_t _base_salary;
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    EmployeesArray();
    EmployeesArray(const EmployeesArray &other);
    EmployeesArray &operator=(const EmployeesArray &other);
    ~EmployeesArray();

    int total_salary() const;

    friend std::istream& operator>>(std::istream &is, EmployeesArray &obj);
    friend std::ostream& operator<<(std::ostream &os, EmployeesArray &obj);

    friend std::ifstream& operator>>(std::ifstream &is, EmployeesArray &obj);
    friend std::ofstream& operator<<(std::ofstream &os, EmployeesArray &obj);
private:
    void add(Employee *e);
    void copy_employees(const EmployeesArray &other);
    void double_capacity();
private:
    int32_t _size, _capacity;
    Employee **_employees;
};

#endif