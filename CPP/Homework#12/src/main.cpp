#include <iostream>
#include <vector>

#include "../include/my_vector.hpp"
#include "../src/my_vector.tpp"

class A {
public:
    A() { std::cout << "Hi" << std::endl; }
    A(const A &other) { std::cout << "Oh" << std::endl; }
    ~A() { std::cout << "Bye" << std::endl; }
};

int main() {
    my_vector<int> g;
    int y = 5;
    g.push_back(y);

    std::cout << g[0] << ' ' << g.size() << ' ' << g.capacity();
    g.pop_back();

    return 0;
}