//
// Created by Александр on 16.02.17.
//

#ifndef LAB_11_INTERFACE_H
#define LAB_11_INTERFACE_H

#include "employees.hpp"

class Interface {
public:
    Interface() = default;
    Interface(const Interface &other) = delete;
    Interface &operator=(const Interface &other) = delete;
    ~Interface() = default;

    void load();
    void list();
    void add();
    void save();
private:
    EmployeesArray _data;
};

#endif //LAB_11_INTERFACE_H
