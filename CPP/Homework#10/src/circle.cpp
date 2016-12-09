//
// Created by Александр on 09.12.16.
//

#include <string.h>
#include <stdio.h>

#include "../include/circle.h"

Circle::Circle(int init_id, int init_x, int init_y, int init_radius, const char *init_label)
       :Figure(init_id, init_x, init_y)
{
    radius = init_radius;
    if (!init_label) {
        label = new char[1];
        label[0] = 0;
    } else {
        label = new char[strlen(init_label)];
        strcpy(label, init_label);
    }
}

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", get_id(), get_center_x(), get_center_y(), radius, label);
}

void Circle::zoom(int factor) {
    radius *= factor;
}

bool Circle::is_inside(int x, int y) const {
    int xc = get_center_x();
    int yc = get_center_y();

    bool result = (x - xc) * (x - xc) + (y - yc) * (y - yc) <= radius * radius;
    return result;
}
