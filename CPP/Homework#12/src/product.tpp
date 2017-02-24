#ifndef _PRODUCT_TPP_
#define _PRODUCT_TPP_

#include <iostream>
#include <fstream>
#include <cstring>

#include "../include/product.hpp"

Product::Product() {
	name_ 	  = nullptr;
	quantity_ = 0;
	price_    = 100500;
}

Product::Product(const char *name, int quantity, double price) {
	init_name_from(name);

	quantity_ = quantity;
	price_    = price;
}

Product::Product(const Product &other) {
	init_name_from(other.name_);

	this->quantity_ = other.quantity_;
	this->price_	= other.price_;
}

Product &Product::operator=(const Product &other) {
	Product tmp(other);

	std::swap(this->name_,     tmp.name_);
	std::swap(this->quantity_, tmp.quantity_);
	std::swap(this->price_,    tmp.price_);

	return *this;
}

Product::~Product() {
	if (name_) { delete[] name_; }
}

std::ostream &operator<<(std::ostream &os, const Product &obj) {
	os << obj.name_ << ' ' << obj.quantity_ << ' ' << obj.price_;
	return os;
}

std::ofstream &operator<<(std::ofstream &os, const Product &obj) {
	os << obj.name_ << ' ' << obj.quantity_ << ' ' << obj.price_;
	return os;
}

void Product::init_name_from(const char *str) {
	if (!str) { name_ = nullptr; return; }
	size_t str_len = strlen(str);

	name_ = new char[str_len + 1];
	strcpy(name_, str);
}

#endif // _PRODUCT_TPP_
