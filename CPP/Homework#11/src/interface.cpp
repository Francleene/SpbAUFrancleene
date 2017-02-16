//
// Created by Александр on 16.02.17.
//

#include <iostream>
#include <fstream>

#include "../include/interface.hpp"

char *  read_cstring_terminal(std::istream &is);

void Interface::load() {
    char * filename = read_cstring_terminal(std::cin);
    std::ifstream fin(filename);

    fin >> _data;

    fin.close();
    delete[] filename;
}

void Interface::list() {
    std::cout << _data;
}

void Interface::add() {
    std::cin >> _data;
}

void Interface::save() {
    char *filename = read_cstring_terminal(std::cin);
    std::ofstream fout(filename);

    fout << _data;

    fout.close();
    delete[] filename;
}
