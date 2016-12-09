//
// Created by Александр on 09.12.16.
//

#include "../include/figure.h"

int Figure::get_id() const {
    return id;
}

int Figure::get_center_x() const {
    return center_x;
}

int Figure::get_center_y() const {
    return center_y;
}

void Figure::move(int new_x, int new_y) {
    center_x = new_x;
    center_y = new_y;
}

Figure::Figure(int init_id, int init_x, int init_y) {
    id = init_id;
    center_x = init_x;
    center_y = init_y;
}

Figure::~Figure() {
}
