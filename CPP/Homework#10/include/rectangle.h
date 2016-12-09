//
// Created by Александр on 09.12.16.
//

#ifndef SCHEME_RECTANGLE_H
#define SCHEME_RECTANGLE_H

#include "../include/figure.h"

class Rectangle: public Figure {
public:
    Rectangle(int init_id = 1, int init_x = 0, int init_y = 0, int init_width = 0, int init_height = 0);
    Rectangle(const Rectangle &other) = delete;
    Rectangle & operator=(const Rectangle &other) = delete;
    ~Rectangle();

    void print() const;
    void zoom(int factor);
    bool is_inside(int x, int y) const;
private:
    int width, height;
};

#endif //SCHEME_RECTANGLE_H
