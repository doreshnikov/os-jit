#include <iostream>
#include <string>
#include <cctype>

#include <sys/mman.h>
#include <cstring>

/*
 * Parses given string as an unsigned integer in specified radix.
 * If input string is invalid, returns -1
 */
int parse_int(std::string const &token) {
    unsigned int value = 0;
    unsigned int radix = DEFAULT_RADIX;
    for (char c : token) {
        if (std::isdigit(c) && c - '0' < radix) {
            (value *= 10) += c - '0';
        } else {
            return -1;
        }
    }
    return value;
}

// @formatter:off
unsigned char parse_int_code[] = {
    0x55,                                     	// push   %rbp
    0x48, 0x89, 0xe5,                         	// mov    %rsp,%rbp
    0x48, 0x83, 0xec, 0x40,                   	// sub    $0x40,%rsp
    0x48, 0x89, 0x7d, 0xc8,                   	// mov    %rdi,-0x38(%rbp)
    0x64, 0x48, 0x8b, 0x04, 0x25, 0x28, 0x00, 	// mov    %fs:0x28,%rax
    0x00, 0x00,
    0x48, 0x89, 0x45, 0xf8,                   	// mov    %rax,-0x8(%rbp)
    0x31, 0xc0,                               	// xor    %eax,%eax
    0xc7, 0x45, 0xd8, 0x00, 0x00, 0x00, 0x00, 	// movl   $0x0,-0x28(%rbp)
    0xc7, 0x45, 0xdc, 0x0a, 0x00, 0x00, 0x00, 	// movl   $0xa,-0x24(%rbp)
    0x48, 0x8b, 0x45, 0xc8,                   	// mov    -0x38(%rbp),%rax
    0x48, 0x89, 0x45, 0xf0,                   	// mov    %rax,-0x10(%rbp)
    0x48, 0x8b, 0x45, 0xf0,                   	// mov    -0x10(%rbp),%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  3d <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x3d>
    0x48, 0x89, 0x45, 0xe0,                   	// mov    %rax,-0x20(%rbp)
    0x48, 0x8b, 0x45, 0xf0,                   	// mov    -0x10(%rbp),%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  4d <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x4d>
    0x48, 0x89, 0x45, 0xe8,                   	// mov    %rax,-0x18(%rbp)
    0x48, 0x8d, 0x55, 0xe8,                   	// lea    -0x18(%rbp),%rdx
    0x48, 0x8d, 0x45, 0xe0,                   	// lea    -0x20(%rbp),%rax
    0x48, 0x89, 0xd6,                         	// mov    %rdx,%rsi
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  64 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x64>
    0x84, 0xc0,                               	// test   %al,%al
    0x74, 0x5f,                               	// je     c7 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xc7>
    0x48, 0x8d, 0x45, 0xe0,                   	// lea    -0x20(%rbp),%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  74 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x74>
    0x0f, 0xb6, 0x00,                         	// movzbl (%rax),%eax
    0x88, 0x45, 0xd7,                         	// mov    %al,-0x29(%rbp)
    0x0f, 0xbe, 0x45, 0xd7,                   	// movsbl -0x29(%rbp),%eax
    0x83, 0xe8, 0x30,                         	// sub    $0x30,%eax
    0x83, 0xf8, 0x09,                         	// cmp    $0x9,%eax
    0x77, 0x3a,                               	// ja     c0 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xc0>
    0x0f, 0xbe, 0x45, 0xd7,                   	// movsbl -0x29(%rbp),%eax
    0x83, 0xe8, 0x30,                         	// sub    $0x30,%eax
    0x39, 0x45, 0xdc,                         	// cmp    %eax,-0x24(%rbp)
    0x76, 0x2e,                               	// jbe    c0 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xc0>
    0x8b, 0x55, 0xd8,                         	// mov    -0x28(%rbp),%edx
    0x89, 0xd0,                               	// mov    %edx,%eax
    0xc1, 0xe0, 0x02,                         	// shl    $0x2,%eax
    0x01, 0xd0,                               	// add    %edx,%eax
    0x01, 0xc0,                               	// add    %eax,%eax
    0x89, 0x45, 0xd8,                         	// mov    %eax,-0x28(%rbp)
    0x48, 0x8d, 0x45, 0xd8,                   	// lea    -0x28(%rbp),%rax
    0x8b, 0x08,                               	// mov    (%rax),%ecx
    0x0f, 0xbe, 0x55, 0xd7,                   	// movsbl -0x29(%rbp),%edx
    0x01, 0xca,                               	// add    %ecx,%edx
    0x83, 0xea, 0x30,                         	// sub    $0x30,%edx
    0x89, 0x10,                               	// mov    %edx,(%rax)
    0x48, 0x8d, 0x45, 0xe0,                   	// lea    -0x20(%rbp),%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  be <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xbe>
    0xeb, 0x91,                               	// jmp    51 <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0x51>
    0xb8, 0xff, 0xff, 0xff, 0xff,             	// mov    $0xffffffff,%eax
    0xeb, 0x03,                               	// jmp    ca <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xca>
    0x8b, 0x45, 0xd8,                         	// mov    -0x28(%rbp),%eax
    0x48, 0x8b, 0x75, 0xf8,                   	// mov    -0x8(%rbp),%rsi
    0x64, 0x48, 0x33, 0x34, 0x25, 0x28, 0x00, 	// xor    %fs:0x28,%rsi
    0x00, 0x00,
    0x74, 0x05,                               	// je     de <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xde>
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  de <_Z9parse_intRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE+0xde>
    0xc9,                                     	// leaveq
    0xc3,                                     	// retq
};
// @formatter:on

/*
 * Converts given unsigned integer value to a string in specified radix.
 */
std::string to_string(unsigned int value) {
    std::string res;
    res.push_back('0' + value);
    return res;
}

// @formatter:off
unsigned char to_string_code[] = {
    0x55,                                     	// push   %rbp
    0x48, 0x89, 0xe5,                         	// mov    %rsp,%rbp
    0x53,                                     	// push   %rbx
    0x48, 0x83, 0xec, 0x28,                   	// sub    $0x28,%rsp
    0x48, 0x89, 0x7d, 0xd8,                   	// mov    %rdi,-0x28(%rbp)
    0x89, 0x75, 0xd4,                         	// mov    %esi,-0x2c(%rbp)
    0x64, 0x48, 0x8b, 0x04, 0x25, 0x28, 0x00, 	// mov    %fs:0x28,%rax
    0x00, 0x00,
    0x48, 0x89, 0x45, 0xe8,                   	// mov    %rax,-0x18(%rbp)
    0x31, 0xc0,                               	// xor    %eax,%eax
    0x48, 0x8b, 0x45, 0xd8,                   	// mov    -0x28(%rbp),%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  10b <_Z9to_stringB5cxx11j+0x2b>
    0x8b, 0x45, 0xd4,                         	// mov    -0x2c(%rbp),%eax
    0x83, 0xc0, 0x30,                         	// add    $0x30,%eax
    0x0f, 0xbe, 0xd0,                         	// movsbl %al,%edx
    0x48, 0x8b, 0x45, 0xd8,                   	// mov    -0x28(%rbp),%rax
    0x89, 0xd6,                               	// mov    %edx,%esi
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  122 <_Z9to_stringB5cxx11j+0x42>
    0xeb, 0x1a,                               	// jmp    13e <_Z9to_stringB5cxx11j+0x5e>
    0x48, 0x89, 0xc3,                         	// mov    %rax,%rbx
    0x48, 0x8b, 0x45, 0xd8,                   	// mov    -0x28(%rbp),%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  133 <_Z9to_stringB5cxx11j+0x53>
    0x48, 0x89, 0xd8,                         	// mov    %rbx,%rax
    0x48, 0x89, 0xc7,                         	// mov    %rax,%rdi
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  13e <_Z9to_stringB5cxx11j+0x5e>
    0x48, 0x8b, 0x45, 0xd8,                   	// mov    -0x28(%rbp),%rax
    0x48, 0x8b, 0x4d, 0xe8,                   	// mov    -0x18(%rbp),%rcx
    0x64, 0x48, 0x33, 0x0c, 0x25, 0x28, 0x00, 	// xor    %fs:0x28,%rcx
    0x00, 0x00,
    0x74, 0x05,                               	// je     156 <_Z9to_stringB5cxx11j+0x76>
    0xe8, 0x00, 0x00, 0x00, 0x00,             	// callq  156 <_Z9to_stringB5cxx11j+0x76>
    0x48, 0x83, 0xc4, 0x28,                   	// add    $0x28,%rsp
    0x5b,                                     	// pop    %rbx
    0x5d,                                     	// pop    %rbp
    0xc3,                                     	// retq
};
// @formatter:on

int main(int argc, char *argv[]) {

    auto memory = mmap(nullptr, 8192, PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    std::memcpy(memory, parse_int_code, sizeof(parse_int_code));
    mprotect(memory, 8192, PROT_EXEC);

    auto func = reinterpret_cast<int (*)(std::string const &)>(memory);
    std::cout << "Radix: " << DEFAULT_RADIX << "\n" << argv[1] << " to " << (*func)(argv[1]) << std::endl;

}
