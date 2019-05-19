#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include <utility>
#include <stdio.h>
#include <sys/mman.h>

#include "templates/logarithm.hpp"

typedef unsigned char byte;

namespace console {

    std::string _ERROR = "\033[31;1m";
    std::string _HELP = "\033[32;1m";
    std::string _DEFAULT = "\033[0m";
    std::string _BOLD = "\033[1m";
    std::string _EMPHASIZE = "\033[33;1m";

    // @formatter:off
    std::string WHELP = "JIT compiler executor utility v.1.0.0\n"
                        "\t- type 'help' to show help message";
    std::string USAGE = "JIT compiler executor utility v.1.0.0\n\n"
                        "[!] Build help:\n"
                        "\t- 'make collect' or '" + _BOLD + "./collect.sh TEMPLATE[ TEMPLATE]*" + _DEFAULT + "'to parse\n"
                        "\t  templates/TEMPLATE.tmp to templates/TEMPLATE.hpp with bytecode inclusion\n"
                        "\t\t- you should manually edit ./jit-executor.cpp after using 'collect' utility\n"
                        "\t- 'make build' to build\n"
                        "\t- 'make run' to run\n\n"
                        "[!] Usage help: commands available after run:\n"
                        "\t- 'invoke ARG' invokes function with given ARG using saved " + _EMPHASIZE + "value" + _DEFAULT + "\n"
                        "\t- 'show' prints current " + _EMPHASIZE + "value" + _DEFAULT + " value\n"
                        "\t- 'change VALUE' changes current " + _EMPHASIZE + "value" + _DEFAULT + " to VALUE\n"
                        "\t- 'exit' exits program and " + _BOLD + "munmap" + _DEFAULT + "s all allocated memory\n"
                        "\t- 'help' shows this message";
    // @formatter:on

    int report(std::string const &message, int err = 0) {
        std::cerr << _ERROR << message;
        if (err != 0) {
            std::cerr << std::strerror(errno);
        }
        std::cerr << std::endl << _DEFAULT;
        return 0;
    }

}

template<typename function_t, typename argument_t>
class executor {

    static unsigned int const PAGE_SIZE = 8192;

    byte _code[PAGE_SIZE];
    unsigned int _length;
    std::vector<unsigned int> _loc;

    void *_memory;

    void check_not_null() const {
        if (_memory == nullptr) {
            console::report("[LOGIC FAIL] Expected not null memory pointer");
            exit(0);
        }
    }

    int update_memory() {
        check_not_null();
        std::memcpy(_memory, logarithm_code, _length);
    }

public:

    executor() : _code(), _length(0), _loc(), _memory(nullptr) {}

    executor(byte const *code, unsigned int length, std::vector<unsigned int> const &loc) {
        reset(code, length, loc);
    }

    void reset(byte const *code, unsigned int length, std::vector<unsigned int> const &loc) {
        _memory = nullptr;
        _length = length;
        _loc = loc;
        if (_length > PAGE_SIZE) {
            throw std::runtime_error("Too large function code");
        }
        std::memcpy(_code, code, _length);
    }

    void show() const {
        std::cout << "Current value: " << static_cast<unsigned int>(_code[_loc[0]]) << std::endl;
    }

    void compile() {
        if (_memory != nullptr) {
            free();
        }
        _memory = mmap(nullptr, PAGE_SIZE, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (_memory == MAP_FAILED) {
            _memory = nullptr;
            console::report("[LOGIC FAIL] Can not mmap/allocate memory", errno);
            exit(0);
        }
        std::memcpy(_memory, logarithm_code, _length);
    }

    int modify_value(byte value) {
        if (value <= 1 || value > 'z' - 'a' + 10) {
            console::report("Invalid value given, expected valid radix for [0-9a-z] digits only");
            return -1;
        }
        check_not_null();
        int status;
        if ((status = mprotect(_memory, PAGE_SIZE, PROT_WRITE | PROT_READ)) == -1) {
            console::report("Can not mprotect/change privileges [+write] on allocated memory", errno);
        } else {
            for (unsigned int index : _loc) {
                logarithm_code[index] = value;
            }
            update_memory();
        }
        return status;
    }

    int invoke(argument_t const &value) {
        check_not_null();
        int status;
        if ((status = mprotect(_memory, PAGE_SIZE, PROT_READ | PROT_EXEC | PROT_WRITE)) == -1) {
            console::report("Can not mprotect/change privileges [+exec] on allocated memory", errno);
        } else {
            std::cout << (*reinterpret_cast<function_t>(_memory))(value) << std::endl;
        }
        return status;
    }

    int free() {
        int status;
        if ((status = munmap(_memory, PAGE_SIZE)) == -1) {
            console::report("Can not munmap/free allocated memory", errno);
        }
        _memory = nullptr;
        return status;
    }

};

int main(int argc, char *argv[]) {

    std::cout << console::WHELP << std::endl;

    /*
     * TODO fix constant requirement 'loc' = {17}
     */
    executor<decltype(&logarithm), unsigned int> invoker(logarithm_code, sizeof(logarithm_code), {17});
    invoker.compile();

    std::cout << "[!] Test: " << console::_EMPHASIZE << "127 -> " << console::_DEFAULT << logarithm(127) << std::endl;

    std::string command;
    std::string arg;
    while (true) {
        std::cin >> command;

        if (command == "invoke") {
            std::cin >> arg;
            try {
                unsigned long long value = std::stoi(arg);
                invoker.invoke(value);
            } catch (std::logic_error const &e) {
                console::report("Invalid number '" + arg + "' received");
            }
        } else if (command == "show") {
            invoker.show();
        } else if (command == "change") {
            std::cin >> arg;
            try {
                unsigned long long value = std::stoi(arg);
                int status = invoker.modify_value(value);
                std::cout << "Status: " << status << std::endl;
            } catch (std::logic_error const &e) {
                console::report("Invalid number '" + arg + "' received");
            }
        } else if (command == "exit") {
            invoker.free();
            break;
        } else if (command == "help") {
            std::cout << console::USAGE << std::endl;
        } else {
            console::report("Invalid command '" + command + "' received, use 'help' to show help message");
        }
    }

}