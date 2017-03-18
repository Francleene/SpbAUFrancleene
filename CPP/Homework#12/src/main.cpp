#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>

#include "../include/product.hpp"
#include "../include/my_vector.hpp"
#include "../include/test_function.hpp"

template<class T>
void test() {
    my_vector<T> v;
    v.resize(5);
    assert(v[4] == T());
}

int main() {
    int x1(1), x2(2);
	test_my_vector(x1, x2);
	
	Product p1("asdf", 4, 12.0), p2("qwe", -1, 7.5);
	test_my_vector<Product>(p1, p2);
    
    test<Product>();

    return 0;
}
