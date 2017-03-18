#include <iostream>
#include <string>

#include "matrix.h"

int main() {
    MatrixInterpreter matrixInterpreter;
    std::string command;

    while (1) {
        std::cin >> command;

        if (command == "load") {
            matrixInterpreter.load();
        } else if (command == "print") {
            matrixInterpreter.print();
        } else if (command == "add") {
            matrixInterpreter.add();
        } else if (command == "mul") {
            matrixInterpreter.mul();
        } else if (command == "elem") {
            matrixInterpreter.elem();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}