#ifndef ERROR_HANDLERS_H
#define ERROR_HANDLERS_H

#include <iostream>
#include <limits>
#include <string>

void getInput(std::string& input, const std::string& prompt) {
    std::cout << prompt;
    std::cin >> input;
}

void getInput(int& input, const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter an integer.\n";
        } else {
            break;
        }
    }
}

void getInput(double& input, const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter a decimal number.\n";
        } else {
            break;
        }
    }
}

#endif
