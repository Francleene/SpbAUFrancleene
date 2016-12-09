//
// Created by Александр on 09.12.16.
//

#ifndef SCHEME_CIRCLE_H
#define SCHEME_CIRCLE_H

#include <memory>

#include "../include/figure.h"

class Circle: public Figure {
public:
    Circle(int init_id = 1, int init_x = 0, int init_y = 0, int init_radius = 1, const char * init_label = 0);
    Circle(const Circle &other) = delete;
    Circle & operator=(const Circle &other) = delete;
    ~Circle();

    void print() const;
    void zoom(int factor);
    bool is_inside(int x, int y) const;
private:
    int radius;
    char * label;
};

#endif //SCHEME_CIRCLE_H
