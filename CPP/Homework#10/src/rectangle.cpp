//
// Created by Александр on 09.12.16.
//

#include <stdio.h>

#include "../include/rectangle.h"

Rectangle::Rectangle(int init_id, int init_x, int init_y, int init_width, int init_height)
          :Figure(init_id, init_x, init_y)
{
    width = init_width;
    height = init_height;
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", get_id(), get_center_x(), get_center_y(), width, height);
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}

bool Rectangle::is_inside(int x, int y) const {
    int xc = get_center_x();
    int yc = get_center_y();

    return xc - width / 2 <= x && x <= xc + width / 2 &&
           yc - height / 2 <= y && y <= yc + height / 2;
}

Rectangle::~Rectangle() {
}
