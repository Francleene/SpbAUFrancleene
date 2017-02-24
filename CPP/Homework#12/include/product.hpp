#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

#include <iostream>
#include <fstream>

class Product {
public:
	Product();
    Product(const char* name, int quantity, double price);
	Product(const Product &other);
	Product &operator=(const Product &other);
	~Product();

	friend std::ostream &operator<<(std::ostream &os, const Product &obj);
	friend std::ofstream &operator<<(std::ofstream &os, const Product &obj);

private:
	void init_name_from(const char *str);

private:
    char *name_;
    int quantity_;
    double price_;
};

#include "../src/product.tpp"

#endif // _PRODUCT_HPP_
