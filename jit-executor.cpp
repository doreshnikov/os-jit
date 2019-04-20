#include <iostream>

#include "templates/to_radix.hpp"

int main(int argc, char *argv[]) {

    std::cout << to_radix(std::stoi(argv[1])) << std::endl;

}