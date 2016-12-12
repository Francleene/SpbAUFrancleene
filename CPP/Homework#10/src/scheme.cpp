//
// Created by Александр on 09.12.16.
//

#include "../include/scheme.h"

Scheme::Scheme(int init_capacity) {
    size = 0;
    data = new Figure *[init_capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;
}

void Scheme::push_back_figure(Figure *fg) {
    data[size++] = fg;
}

void Scheme::remove_figure(int id) {
    int traveller = 0;

    for (; traveller < size; traveller++) {
        if (data[traveller]->get_id() == id) {
            delete data[traveller];
            break;
        }
    }

    for (; traveller < size - 1; traveller++) {
        data[traveller] = data[traveller + 1];
    }

    size -= 1;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size; i++) {
        data[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    for (int i = 0; i < size; i++) {
        if (data[i]->get_id() == id) {
            data[i]->zoom(factor);
            break;
        }
    }
}

Figure *Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size; i++) {
        if (data[i]->is_inside(x, y)) {
            return data[i];
        }
    }
    return NULL;
}

void Scheme::move(int id, int new_x, int new_y) {
    for (int i = 0; i < size; i++) {
        if (data[i]->get_id() == id) {
            data[i]->move(new_x, new_y);
            break;
        }
    }
}
