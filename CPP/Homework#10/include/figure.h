//
// Created by Александр on 09.12.16.
//

#ifndef SCHEME_FIGURE_H
#define SCHEME_FIGURE_H

class Figure {
public:
    Figure(int new_id = 1, int new_x = 0, int new_y = 0);
    virtual ~Figure();

    virtual void print() const = 0;
    virtual void zoom(int factor) = 0;
    virtual bool is_inside(int x, int y) const = 0;
    void move(int new_x, int new_y);

    int get_id() const;
    int get_center_x() const;
    int get_center_y() const;

private:
    int id, center_x, center_y;
};

#endif //SCHEME_FIGURE_H
