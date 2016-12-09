#include <iostream>

#include "../include/scheme.h"
#include "../include/circle.h"

int main() {
    Scheme scheme(20);
    Rectangle *r = new Rectangle(3, 0, 0, 4, 5);
    scheme.push_back_figure(new Circle(1, 2, 2, 5, "happly circle"));
    scheme.push_back_figure(new Circle(2, 3, 3, 4, "sad circle"));
    scheme.push_back_figure(r);
    scheme.push_back_figure(new Rectangle(4, 3, 3, 5, 6));

    scheme.print_all_figures();
    scheme.move(2, 6, 7);
    scheme.remove_figure(2);
    scheme.zoom_figure(4, 7);
    scheme.print_all_figures();

    return 0;
}
