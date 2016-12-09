//
// Created by Александр on 09.12.16.
//

#ifndef SCHEME_SCHEME_H
#define SCHEME_SCHEME_H

#include "../include/circle.h"
#include "../include/rectangle.h"

class Scheme {
public:
    Scheme(int int_capacity = 100);
    Scheme(const Scheme &other) = delete;
    Scheme & operator=(const Scheme &other) = delete;
    ~Scheme();

    void push_back_figure(Figure * fg);
    void remove_figure(int id);

    void print_all_figures();
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y);
    void move(int id, int new_x, int new_y);
private:
    int size;
    Figure ** data;
};

#endif //SCHEME_SCHEME_H
