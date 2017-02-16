#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "../include/interface.hpp"
#include "../include/employees.hpp"

char *  read_cstring_terminal(std::istream &is);

int main() {
    Interface interface;
    std::string command;

    while (1) {
        std::cin >> command;

        if      (!strcmp(command.c_str(), "load")) { interface.load(); }
        else if (!strcmp(command.c_str(), "list")) { interface.list(); }
        else if (!strcmp(command.c_str(), "add"))  { interface.add();  }
        else if (!strcmp(command.c_str(), "save")) { interface.save(); }
        else                               { std::cout << command; break;            }

        //delete[] command;
    }


    return 0;
}
