#include <iostream>
#include <cstring>

#include <sys/mman.h>

#include "templates/to_radix.hpp"

int main(int argc, char *argv[]) {

    auto memory = reinterpret_cast<unsigned char *>(
        mmap(nullptr, 8192, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
    std::memcpy(memory, to_radix_code, sizeof(to_radix_code));
    if (mprotect(memory, 8192, PROT_EXEC | PROT_READ | PROT_WRITE)) {
        std::cout << "sucker" << std::endl;
    }

    unsigned int radix;
    unsigned int arg = std::stoi(argv[1]);
    while (true) {
        std::cin >> radix;
        if (radix == 0) {
            break;
        }
        to_radix_code[21] = static_cast<unsigned char>(radix);
        std::cout << static_cast<unsigned int>(to_radix_code[21]) << ": ";
        std::memcpy(memory, to_radix_code, sizeof(to_radix_code));
        auto fptr = reinterpret_cast<decltype(&to_radix)>(memory);
        std::cout << (*fptr)(arg) << std::endl;
    }

}